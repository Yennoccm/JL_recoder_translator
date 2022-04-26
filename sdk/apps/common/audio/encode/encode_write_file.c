#include "encode_write.h"
#include "file_operate/file_bs_deal.h"
#include "audio_enc.h"
#include "media/audio_base.h"
#include "dev_manager.h"
#include "app_config.h"
#include "spi/nor_fs.h"
#include "rec_nor/nor_interface.h"

#if TCFG_ENC_WRITE_FILE_ENABLE

extern FILE *file_api_auto_create_file(const char *path, const char *folder, const char *filename, u32 *file_index);

 // *INDENT-OFF*
struct enc_write_file{
	volatile u32 init_ok : 1;
	volatile u32 wait_idle : 1;
	volatile u32 start : 1;
	volatile u32 wait_stop : 1;
	u32 write_err : 1;
	OS_SEM sem_task_run;

	struct __dev *dev;
	const char *folder;
	const char *filename;
	void *fmnt;
	FILE *file;
	u32 cut_size;
	u32 limit_size;
	int file_size;
	u32 input_frame_len;
	void *input_hdl;
	struct audio_enc_write_input *input;
	u32 write_err_no_check;

	void *evt_hdl;
	void (*evt_cb)(void *, int, int);

	void *set_head_hdl;
	int (*set_head)(void *, char **head);
};

static volatile u32 enc_file_index = (u32) - 1;
static volatile u32 enc_file_coding_type = 0;
extern u8 record_part;
void last_enc_file_codeing_type_save(u32 type)
{
	enc_file_coding_type = type;
}


static void enc_write_file_task(void *p)
{
    int ret, len;
    int pend_dly = -1;
    struct enc_write_file *wfil = p;
    s16 *frame;

    while (1) {
        if (pend_dly) {
            os_sem_pend(&wfil->sem_task_run, pend_dly);
        }
		
		printf("wfil->init_ok %d\n", wfil->init_ok);
        if (!wfil->init_ok) {
            wfil->wait_idle = 0;
            wfil->start = 0;
            wfil->wait_stop = 0;
            break;
        }
        pend_dly++;
		
		printf("wfil->start %d\n", wfil->start);
        if (!wfil->start) {
            continue;
        }
        len = wfil->input->get(wfil->input_hdl, &frame, wfil->input_frame_len);
        if (len) {
			printf("w----- len %d\n", len);
            if (wfil->write_err == 0) {
                //ret = fwrite(wfil->file, frame, len);
                // TODO: send a notify to app
                printf("notify to app \n");

				extern int app_send_user_data_do(void *priv, u8 *data, u16 len);
                //app_send_user_data_do(NULL, (u8 *)frame, len);

            } else {
                ret = 0;
            }
            if (ret != len) {
                if (wfil->write_err == 0) {
                    log_e("write file err ");
                    if (wfil->evt_cb) {
                        wfil->evt_cb(wfil->evt_hdl, ENC_WRITE_FILE_EVT_WRITE_ERR, 0);
                    }
                }
                wfil->write_err = 1;
            } else {
                pend_dly = 0;
            }
            if (wfil->input->put) {
                wfil->input->put(wfil->input_hdl, frame);
            }
        } else {
            wfil->wait_stop = 0;
        }
    }
    while (1) {
        os_time_dly(100);
    }
}

int enc_write_file_resume(void *hdl)
{
    struct enc_write_file *wfil = hdl;
    if (wfil->start && (wfil->write_err == 0)) {
		printf("fresu\n");
		os_sem_set(&wfil->sem_task_run, 0);
        os_sem_post(&wfil->sem_task_run);
        return 0;
    }
	printf("fresu err\n");
    return -1;
}

void enc_write_file_close(void *hdl)
{
    struct enc_write_file *wfil = hdl;

    if (wfil->init_ok) {
        wfil->wait_idle = 1;
        wfil->init_ok = 0;
        os_sem_set(&wfil->sem_task_run, 0);
        os_sem_post(&wfil->sem_task_run);
        while (wfil->wait_idle) {
            os_time_dly(1);
        }
        task_kill("enc_write");
    }

#if 0
    if (wfil->file) {
        int f_len = fpos(wfil->file);
        struct vfs_attr attr = {0};
        do {
            if (f_len <= wfil->cut_size) {
                enc_file_index = (u32) - 1;
                fdelete(wfil->file);
                break;
            }
            f_len -= wfil->cut_size;
            if (f_len <= wfil->limit_size) {
                enc_file_index = (u32) - 1;
                fdelete(wfil->file);
                break;
            }

            if (wfil->set_head && (wfil->write_err_no_check || wfil->write_err == 0)) {
                char *head;
                int len = wfil->set_head(wfil->set_head_hdl, &head);
                if (f_len <= len) {
                    enc_file_index = (u32) - 1;
                    fdelete(wfil->file);
                    break;
                }
                if (len) {
                    fseek(wfil->file, 0, SEEK_SET);
                    fwrite(wfil->file, head, len);
                }
            }
            fseek(wfil->file, f_len, SEEK_SET);
            fget_attrs(wfil->file, &attr);
            fclose(wfil->file);
			char *dev_logo = NULL;
#if (TCFG_RECORD_FOLDER_DEV_ENABLE)
			dev_logo = dev_manager_get_rec_logo(wfil->dev);
#else
			dev_logo = dev_manager_get_logo(wfil->dev);
#endif
			dev_manager_set_valid_by_logo(dev_logo, 1);
        } while (0);
        if (wfil->evt_cb) {
            wfil->evt_cb(wfil->evt_hdl, ENC_WRITE_FILE_EVT_FILE_CLOSE, attr.sclust);
        }
        wfil->file = NULL;
    }
#endif
    free(wfil);
}


void *enc_write_file_open(char *logo, const char *folder, const char *filename)
{
#if 0
    if (!logo || !folder || !filename) {
        return NULL;
    }
#endif
    int err;
    struct enc_write_file *wfil = zalloc(sizeof(struct enc_write_file));
    if (!wfil) {
        return NULL;
	}
#if 0 //removed by sc
	struct __dev *dev = dev_manager_find_spec(logo, 0);
	if(!dev){
		free(wfil);
		return NULL;
	}

	char *root_path = dev_manager_get_root_path(dev);
    wfil->dev = dev;
    wfil->folder = folder;
    wfil->filename = filename;
    char *path = NULL;
	u32 path_len = get_creat_path_len(root_path, folder, filename);
	printf("path_len %d\n", path_len);
    path = zalloc(path_len);
	if(path == NULL){
        goto _exit;
	}
    create_path(path, root_path, folder, filename);
    wfil->file = fopen(path, "w+");
    free(path);
    path = NULL;
    if (!wfil->file) {
        log_e("file create err ");
        goto _exit;
    }
    enc_file_index = get_last_num(); //获取最后的数字
#endif
    /* r_printf(">>>[test]:enc_file_index = %d\n", enc_file_index); */
    os_sem_create(&wfil->sem_task_run, 0);
#if 0
    err = task_create(enc_write_file_task, wfil, "enc_write");
    if (err != OS_NO_ERR) {
        log_e("task create err ");
        goto _exit;
    }
#endif
    wfil->init_ok = 1;

    return wfil;

_exit:
	printf("\n--func=%s, line=%d\n", __FUNCTION__, __LINE__);
    enc_write_file_close(wfil);
	printf("\n--func=%s, line=%d\n", __FUNCTION__, __LINE__);
    return NULL;
}

int enc_write_file_start(void *hdl)
{
    struct enc_write_file *wfil = hdl;

    if (wfil->init_ok) {
        wfil->start = 1;
        return 0;
    }
    return -1;
}

void enc_write_file_stop(void *hdl, u32 delay_ms)
{
    struct enc_write_file *wfil = hdl;

    if (wfil->start) {
        wfil->wait_stop = 1;
        u32 dly = 0;
        do {
            if (!wfil->wait_stop) {
                break;
            }
            if (wfil->write_err) {
                break;
            }
            os_time_dly(1);
            dly += 10;
        } while (dly < delay_ms);
        wfil->start = 0;
    }
}

void enc_write_file_set_head_handler(void *hdl, int (*set_head)(void *, char **head), void *set_head_hdl)
{
    struct enc_write_file *wfil = hdl;
    wfil->set_head = set_head;
    wfil->set_head_hdl = set_head_hdl;
}

void enc_write_file_set_evt_handler(void *hdl, void (*evt_cb)(void *, int, int), void *evt_hdl)
{
    struct enc_write_file *wfil = hdl;
    wfil->evt_cb = evt_cb;
    wfil->evt_hdl = evt_hdl;
}

void enc_write_file_set_input(void *hdl, struct audio_enc_write_input *input, void *input_hdl, u32 input_frame_len)
{
    struct enc_write_file *wfil = hdl;
    wfil->input = input;
    wfil->input_hdl = input_hdl;
    wfil->input_frame_len = input_frame_len;
}


int get_enc_file_len(void *hdl)
{
    struct enc_write_file *wfil = hdl;
    int filelen = 0;
    if (!wfil) {
        return -1;
    }
    if (wfil->file) {
        filelen = wfil->file_size;
        /* filelen = fpos(wfil->file);		 */
        /* filelen = flen(wfil->file);		 */
    }
    return filelen;
}


void *get_wfil_head_hdl(void *enc_whdl)
{
    struct enc_write_file *wfil = (struct enc_write_file *)enc_whdl;
    return wfil->set_head_hdl;
}

FILE *get_wfil_file(void *enc_whdl)
{
    struct enc_write_file *wfil = (struct enc_write_file *)enc_whdl;
    return wfil->file;
}

//////////////////////////////////////////////////////////////////////////////
#if 0

#define W_OUTBUF_LEN				(1 * 1024)
struct enc_write_test {
    volatile u32 start : 1;
        volatile u32 err : 1;
        void *hdl;
        OS_SEM sem_in;
        OS_SEM sem_out;
        u8 output_buf[W_OUTBUF_LEN];
        cbuffer_t output_cbuf;
        s16 output_frame[512 / 2];             //align 4Bytes
    };

    static void enc_w_evt(void *hdl, int err)
{
    struct enc_write_test *tst = hdl;
    printf("err: %d ", err);
    if (err) {
        tst->err = 1;
        os_sem_set(&tst->sem_in, 0);
        os_sem_post(&tst->sem_in);
        os_sem_set(&tst->sem_out, 0);
        os_sem_post(&tst->sem_out);
    }
}
static int enc_w_set_head(void *hdl, char **head)
{
    struct enc_write_test *tst = hdl;
    u8 hdtab[] = "i'm head!!! ";
    memcpy(tst->output_frame, hdtab, sizeof(hdtab));
    *head = tst->output_frame;
    return sizeof(hdtab);
}

static int enc_w_get(void *hdl, s16 **frame, u16 frame_len)
{
    int rlen;
    struct enc_write_test *tst = hdl;
    do {
        rlen = cbuf_read(&tst->output_cbuf, tst->output_frame, frame_len);
        if (rlen == frame_len) {
            break;
        }
        if (rlen == -EINVAL) {
            return 0;
        }
        if (!tst->start) {
            return 0;
        }
        if (tst->err) {
            return 0;
        }
        os_sem_set(&tst->sem_in, 0);
        os_sem_post(&tst->sem_in);

        os_sem_pend(&tst->sem_out, 2);
    } while (1);

    *frame = tst->output_frame;
    return rlen;
}
static void enc_w_put(void *hdl, s16 *frame)
{
}

const struct audio_enc_write_input enc_w_input = {
    .get = enc_w_get,
    .put = enc_w_put,
};

void enc_w_test(void)
{
    struct enc_write_test *tst = zalloc(sizeof(struct enc_write_test));
    printf("%s,%d ", __func__, __LINE__);
    if (!tst) {
        return ;
    }
    printf("%s,%d ", __func__, __LINE__);
    os_sem_create(&tst->sem_in, 0);
    os_sem_create(&tst->sem_out, 0);
    cbuf_init(&tst->output_cbuf, tst->output_buf, W_OUTBUF_LEN);

    printf("%s,%d ", __func__, __LINE__);
    tst->hdl = enc_write_file_open("sd0", "/"REC_FOLDER_NAME, "AC690000.MP3");
    printf("%s,%d ", __func__, __LINE__);
    if (!tst->hdl) {
        goto __exit;
    }

    printf("%s,%d ", __func__, __LINE__);
    enc_write_file_set_evt_handler(tst->hdl, enc_w_evt, tst);
    enc_write_file_set_input(tst->hdl, &enc_w_input, tst, sizeof(tst->output_frame));
    enc_write_file_set_head_handler(tst->hdl, enc_w_set_head, tst);
    enc_write_file_set_limit(tst->hdl, 123, 5000);
    printf("%s,%d ", __func__, __LINE__);

    tst->start = 1;

    enc_write_file_start(tst->hdl);

    int cnt = 0;
    u8 str[] = "This is a test string.";
    while (cnt < 1000) {
        /* printf("%s,%d ", __func__, __LINE__); */
        int len = cbuf_write(&tst->output_cbuf, str, sizeof(str));
        os_sem_set(&tst->sem_out, 0);
        os_sem_post(&tst->sem_out);
        enc_write_file_resume(tst->hdl);
        /* printf("%s,%d ", __func__, __LINE__); */
        if (len != sizeof(str)) {
            putchar('N');
            os_sem_pend(&tst->sem_in, 2);
        } else {
            putchar('Y');
            cnt++;
        }
        if (tst->err) {
            os_sem_set(&tst->sem_out, 0);
            os_sem_post(&tst->sem_out);
            break;
        }
    }

__exit:
    printf("%s,%d ", __func__, __LINE__);
    tst->start = 0;
    if (tst->hdl) {
        enc_write_file_stop(tst->hdl, 1000);
        enc_write_file_close(tst->hdl);
        tst->hdl = 0;
    }
    printf("%s,%d ", __func__, __LINE__);
    free(tst);
}
#endif

#endif

