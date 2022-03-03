#ifndef __MIC_EFFECT_H__
#define __MIC_EFFECT_H__



#include "system/includes.h"
#include "audio_mic/effect_reg.h"
#include "audio_mic/effect_cfg.h"
#include "app_config.h"
#include "application/audio_pemafrow.h"
enum {
    MIC_EQ_MODE_SHOUT_WHEAT = 0x0,
    MIC_EQ_MODE_LOW_SOUND,
    MIC_EQ_MODE_HIGH_SOUND,
};


/*----------------------------------------------------------------------------*/
/**@brief    (mic数据流)混响打开接口
   @param
   @return   true - 成功, false - 失败.
   @note
*/
/*----------------------------------------------------------------------------*/
bool mic_effect_start(void);

/*----------------------------------------------------------------------------*/
/**@brief    (mic数据流)混响关闭接口
   @param
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_effect_stop(void);


/*----------------------------------------------------------------------------*/
/**@brief    (mic数据流)混响暂停接口(数据置0)
   @param     mark :1 暂停 0：恢复
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_effect_pause(u8 mark);


/*----------------------------------------------------------------------------*/
/**@brief    (mic数据流)混响暂停输出到DAC(数据流后级不写入DAC)
   @param    mark :1 暂停 0：恢复
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_effect_dac_pause(u8 mark);

/*----------------------------------------------------------------------------*/
/**@brief    (mic数据流)混响状态获取接口
   @param
   @return true - 运行, false - 未启动
   @note
*/
/*----------------------------------------------------------------------------*/
u8 mic_effect_get_status(void);

/*----------------------------------------------------------------------------*/
/**@brief    数字音量调节接口
   @param   vol 待设置的音量值[0,31]
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_effect_set_dvol(u8 vol);

/*----------------------------------------------------------------------------*/
/**@brief    获取数字音量接口
   @param
   @return   当前数字数字音量等级
   @note
*/
/*----------------------------------------------------------------------------*/
u8 mic_effect_get_dvol(void);


/*----------------------------------------------------------------------------*/
/**@brief    获取默认mic增益
   @param
   @return  默认mic增益值
   @note
*/
/*----------------------------------------------------------------------------*/
u8 mic_effect_get_micgain(void);


/*----------------------------------------------------------------------------*/
/**@brief   设置reverb 湿声增益
   @param   待设增益值[0,300]
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_effect_set_reverb_wet(int wet);

/*----------------------------------------------------------------------------*/
/**@brief   获取当前reverb混响湿声增益值
   @param
   @return   当前增益值[0,300]
   @note
*/
/*----------------------------------------------------------------------------*/
int mic_effect_get_reverb_wet(void);


/*----------------------------------------------------------------------------*/
/**@brief    设置echo 回声延时
   @param    delay 回声延时[0,max_ms]
   @return
   @note   默认max_ms = 200
*/
/*----------------------------------------------------------------------------*/
void mic_effect_set_echo_delay(u32 delay);

/*----------------------------------------------------------------------------*/
/**@brief    获取当前 echo 回声延时值
   @param
   @return    当前回声延时delay值
   @note
*/
/*----------------------------------------------------------------------------*/
u32 mic_effect_get_echo_delay(void);


/*----------------------------------------------------------------------------*/
/**@brief    设置echo 回声衰减系数
   @param    decay 衰减系数值[0,70]
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_effect_set_echo_decay(u32 decay);


/*----------------------------------------------------------------------------*/
/**@brief    获取echo 回声衰减系数
   @param
   @return   当前衰减系数值
   @note
*/
/*----------------------------------------------------------------------------*/
u32 mic_effect_get_echo_decay(void);


/*----------------------------------------------------------------------------*/
/**@brief    mic_effect_cal_coef 混响喊麦、高低音 调节接口
   @param    type :MIC_EQ_MODE_SHOUT_WHEAT 喊麦模式，gainN：喊麦开关，0:关喊麦， 1：开喊麦
   @param    type:MIC_EQ_MODE_LOW_SOUND   低音调节   gainN：调节的增益，范围0~10
   @param    type:MIC_EQ_MODE_HIGH_SOUND  高音调节   gainN：调节的增益，范围0~10
   @return
   @note     混响喊麦、高低音调节
*/
/*----------------------------------------------------------------------------*/
void mic_effect_cal_coef(u8 type, u32 gainN);


/*----------------------------------------------------------------------------*/
/**@brief    获取EQ段数
   @param
   @return   当前EQ使用的段数
   @note
*/
/*----------------------------------------------------------------------------*/
u8 mic_effect_eq_section_num(void);


/*----------------------------------------------------------------------------*/
/**@brief    reverb 混响参数更新
   @param    parm 新混响参数，为NULL时模块会变直通
  			 fade ：参数更新是否淡入更新 只对部分参数有效
			 online:是否是在线调试 true 在线 false 非在线
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_effect_reverb_parm_fill(REVERBN_PARM_SET *parm, u8 fade, u8 online);

/*----------------------------------------------------------------------------*/
/**@brief    echo 混响参数更新
   @param    parm 新混响参数，为NULL时模块会变直通
  			 fade ：参数更新是否淡入更新 只对部分参数有效
			 online:是否是在线调试 true 在线 false 非在线
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_effect_echo_parm_fill(ECHO_PARM_SET *parm, u8 fade, u8 online);


/*----------------------------------------------------------------------------*/
/**@brief    变声参数更新
   @param    parm 新混响参数，为NULL时模块会变直通
  			 fade ：参数更新是否淡入更新 无效
			 online:是否是在线调试 true 在线 false 非在线
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_effect_pitch_parm_fill(PITCH_PARM_SET2 *parm, u8 fade, u8 online);

/*----------------------------------------------------------------------------*/
/**@brief    噪声抑制参数更新
   @param    parm 新混响参数，为NULL时模块会变直通
  			 fade ：参数更新是否淡入更新 无效
			 online:是否是在线调试   无区别
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_effect_noisegate_parm_fill(NOISE_PARM_SET *parm, u8 fade, u8 online);


/*----------------------------------------------------------------------------*/
/**@brief    喊mic参数更新
   @param    parm 新混响参数，为NULL时无效
  			 fade ：参数更新是否淡入更新 无效
			 online:是否是在线调试   无区别
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_effect_shout_wheat_parm_fill(SHOUT_WHEAT_PARM_SET *parm, u8 fade, u8 online);


/*----------------------------------------------------------------------------*/
/**@brief    低音参数更新
   @param    parm 新混响参数，为NULL时无效
  			 fade ：参数更新是否淡入更新 无效
			 online:是否是在线调试   无区别
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_effect_low_sound_parm_fill(LOW_SOUND_PARM_SET *parm, u8 fade, u8 online);


/*----------------------------------------------------------------------------*/
/**@brief    高音参数更新
   @param    parm 新混响参数，为NULL时无效
  			 fade ：参数更新是否淡入更新 无效
			 online:是否是在线调试   无区别
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_effect_high_sound_parm_fill(HIGH_SOUND_PARM_SET *parm, u8 fade, u8 online);


/*----------------------------------------------------------------------------*/
/**@brief    mic增益更新
   @param    parm 新混响参数，为NULL时无效
  			 fade ：参数更新是否淡入更新 无效
			 online:是否是在线调试   无区别
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_effect_mic_gain_parm_fill(EFFECTS_MIC_GAIN_PARM *parm, u8 fade, u8 online);

/*----------------------------------------------------------------------------*/
/**@brief    mic数据流参数更新
   @param    parm 新参数，
   @return
   @note       暂未使用
*/
/*----------------------------------------------------------------------------*/
void mic_effect_set_mic_parm(struct __mic_stream_parm *parm);



/*----------------------------------------------------------------------------*/
/**@brief    设置变声模式
   @param    shiftv: 变声模式
  			 sr ：数据采样率
			 effect:变调比例[40,230]
			 formant_shift:共振峰偏移比例 [40,230]
   @return
   @note
   模式配置说明：
   1.EFFECT_PITCH_SHIFT  移频，变调不变速，shiftv调节有效，formant_shift调节无效
   2.EFFECT_VOICECHANGE_KIN0  变声，可以调节不同的 shiftv  跟 formant_shift ，调出更多的声音效果
   3.EFFECT_VOICECHANGE_KIN1  变声，同EFFECT_VOICECHANGE_KIN0类似的，但是2者由于运算的不同，会有区别。
   4.EFFECT_ROBORT 机器音效果，类似 喜马拉雅那样的
   5.EFFECT_AUTOTUNE  电音效果
*/
/*----------------------------------------------------------------------------*/
void set_pitch_para(u32 shiftv, u32 sr, u8 effect, u32 formant_shift);


/*----------------------------------------------------------------------------*/
/**@brief   设置音效模式
   @param    mode 模式索引
   @return
   @note    模式与工具调试出的效果文件对应
   			模式在effect_reg_echo.c和effect_reg_reverb.c中定义
*/
/*----------------------------------------------------------------------------*/
void mic_effect_change_mode(u16 mode);

/*----------------------------------------------------------------------------*/
/**@brief   获取音效模式
   @param
   @return   模式索引
   @note    未使用效果文件时无效
*/
/*----------------------------------------------------------------------------*/
u16 mic_effect_get_cur_mode(void);



/*----------------------------------------------------------------------------*/
/**@brief    能量检测运行过程，是否触发闪避
   @param
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_dodge_ctr(void);


/*----------------------------------------------------------------------------*/
/**@brief    能量检测运行过程，是否触发闪避
   @param
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
u8 mic_dodge_get_status(void);

/*----------------------------------------------------------------------------*/
/**@brief    mic eq信息获取接口
   @param   index:获取第几段eq
   @return  返回struct eq_seg_info结构体
   @note
*/
/*----------------------------------------------------------------------------*/
struct eq_seg_info *mic_eq_get_info(u16 index);

/*----------------------------------------------------------------------------*/
/**@brief    mic eq设置接口
   @param   详见struct eq_seg_info结构体
   @return
   @note
*/
/*----------------------------------------------------------------------------*/

int mic_eq_set_info(struct eq_seg_info *info);

/*----------------------------------------------------------------------------*/
/**@brief    K歌模式音效切换例程
   @param    eff_mode 模式索引
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_mode_switch(u8 eff_mode);


/*----------------------------------------------------------------------------*/
/**@brief    混响mic数据到USB mic 开关
   @param    mark : true 开 false 关
   @return
   @note
*/
/*----------------------------------------------------------------------------*/
void mic_effect_to_usbmic_onoff(u8 mark);

#endif// __MIC_EFFECT_H__
