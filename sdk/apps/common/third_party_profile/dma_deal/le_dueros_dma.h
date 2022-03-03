
#ifndef _LE_DUEROS_DMA_H
#define _LE_DUEROS_DMA_H

#include <stdint.h>
#include "bt_common.h"

#if (TCFG_BLE_DEMO_SELECT == DEF_BLE_DEMO_DUEROS_DMA)
// #include <le_user.h>
//
// gatt profile include file, generated by jieli gatt_inc_generator.exe
//

static const uint8_t profile_data[] = {
    //////////////////////////////////////////////////////
    //
    // 0x0001 PRIMARY_SERVICE  1801
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x28, 0x01, 0x18,

    /* CHARACTERISTIC,  2a05,INDICATE */
    // 0x0002 CHARACTERISTIC 2a05 INDICATE
    0x0d, 0x00, 0x02, 0x00, 0x02, 0x00, 0x03, 0x28, 0x20, 0x03, 0x00, 0x05, 0x2a,
    // 0x0003 VALUE 2a05 INDICATE
    0x08, 0x00, 0x20, 0x00, 0x03, 0x00, 0x05, 0x2a,
    // 0x0004 CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x04, 0x00, 0x02, 0x29, 0x00, 0x00,

    //////////////////////////////////////////////////////
    //
    // 0x0005 PRIMARY_SERVICE  1800
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x05, 0x00, 0x00, 0x28, 0x00, 0x18,

    /* CHARACTERISTIC,  2a00,READ */
    // 0x0006 CHARACTERISTIC 2a00 READ
    0x0d, 0x00, 0x02, 0x00, 0x06, 0x00, 0x03, 0x28, 0x02, 0x07, 0x00, 0x00, 0x2a,
    // 0x0007 VALUE 2a00 READ
    0x08, 0x00, 0x02, 0x00, 0x07, 0x00, 0x00, 0x2a,

    /* CHARACTERISTIC,  2a01,READ */
    // 0x0008 CHARACTERISTIC 2a01 READ
    0x0d, 0x00, 0x02, 0x00, 0x08, 0x00, 0x03, 0x28, 0x02, 0x09, 0x00, 0x01, 0x2a,
    // 0x0009 VALUE 2a01 READ
    0x08, 0x00, 0x02, 0x00, 0x09, 0x00, 0x01, 0x2a,

    /* CHARACTERISTIC,  2aa6,READ */
    // 0x000a CHARACTERISTIC 2aa6 READ
    0x0d, 0x00, 0x02, 0x00, 0x0a, 0x00, 0x03, 0x28, 0x02, 0x0b, 0x00, 0xa6, 0x2a,
    // 0x000b VALUE 2aa6 READ
    0x08, 0x00, 0x02, 0x00, 0x0b, 0x00, 0xa6, 0x2a,

    //////////////////////////////////////////////////////
    //
    // 0x000c PRIMARY_SERVICE  fe35
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x0c, 0x00, 0x00, 0x28, 0x35, 0xfe,

    /* CHARACTERISTIC,  2a00,READ|WRITE|DYNAMIC */
    // 0x000d CHARACTERISTIC 2a00 READ|WRITE|DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x0d, 0x00, 0x03, 0x28, 0x0a, 0x0e, 0x00, 0x00, 0x2a,
    // 0x000e VALUE 2a00 READ|WRITE|DYNAMIC
    0x08, 0x00, 0x0a, 0x01, 0x0e, 0x00, 0x00, 0x2a,

    /* CHARACTERISTIC,  2a01,INDICATE|NOTIFY */
    // 0x000f CHARACTERISTIC 2a01 INDICATE|NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x0f, 0x00, 0x03, 0x28, 0x30, 0x10, 0x00, 0x01, 0x2a,
    // 0x0010 VALUE 2a01 INDICATE|NOTIFY
    0x08, 0x00, 0x30, 0x00, 0x10, 0x00, 0x01, 0x2a,
    // 0x0011 CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x11, 0x00, 0x02, 0x29, 0x00, 0x00,

    /* CHARACTERISTIC,  2a02,WRITE|DYNAMIC */
    // 0x0012 CHARACTERISTIC 2a02 WRITE|DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x12, 0x00, 0x03, 0x28, 0x08, 0x13, 0x00, 0x02, 0x2a,
    // 0x0013 VALUE 2a02 WRITE|DYNAMIC
    0x08, 0x00, 0x08, 0x01, 0x13, 0x00, 0x02, 0x2a,

    /* CHARACTERISTIC,  2a03,INDICATE|NOTIFY */
    // 0x0014 CHARACTERISTIC 2a03 INDICATE|NOTIFY
    0x0d, 0x00, 0x02, 0x00, 0x14, 0x00, 0x03, 0x28, 0x30, 0x15, 0x00, 0x03, 0x2a,
    // 0x0015 VALUE 2a03 INDICATE|NOTIFY
    0x08, 0x00, 0x30, 0x00, 0x15, 0x00, 0x03, 0x2a,
    // 0x0016 CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x16, 0x00, 0x02, 0x29, 0x00, 0x00,

    //////////////////////////////////////////////////////
    //
    // 0x0017 PRIMARY_SERVICE  046a
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x17, 0x00, 0x00, 0x28, 0x6a, 0x04,

    /* CHARACTERISTIC,  046c,READ|WRITE|DYNAMIC */
    // 0x0018 CHARACTERISTIC 046c READ|WRITE|DYNAMIC
    0x0d, 0x00, 0x02, 0x00, 0x18, 0x00, 0x03, 0x28, 0x0a, 0x19, 0x00, 0x6c, 0x04,
    // 0x0019 VALUE 046c READ|WRITE|DYNAMIC
    0x08, 0x00, 0x0a, 0x01, 0x19, 0x00, 0x6c, 0x04,

    //////////////////////////////////////////////////////
    //
    // 0x001a PRIMARY_SERVICE  fe04
    //
    //////////////////////////////////////////////////////
    0x0a, 0x00, 0x02, 0x00, 0x1a, 0x00, 0x00, 0x28, 0x04, 0xfe,

    /* CHARACTERISTIC,  b84ac9c6-29c5-46d4-bba1-9d534784330f,READ|WRITE|NOTIFY|DYNAMIC */
    // 0x001b CHARACTERISTIC b84ac9c6-29c5-46d4-bba1-9d534784330f READ|WRITE|NOTIFY|DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x1b, 0x00, 0x03, 0x28, 0x10, 0x1c, 0x00, 0x0f, 0x33, 0x84, 0x47, 0x53, 0x9d, 0xa1, 0xbb, 0xd4, 0x46, 0xc5, 0x29, 0xc6, 0xc9, 0x4a, 0xb8,
    // 0x001c VALUE b84ac9c6-29c5-46d4-bba1-9d534784330f READ|WRITE|NOTIFY|DYNAMIC
    0x16, 0x00, 0x10, 0x03, 0x1c, 0x00, 0x0f, 0x33, 0x84, 0x47, 0x53, 0x9d, 0xa1, 0xbb, 0xd4, 0x46, 0xc5, 0x29, 0xc6, 0xc9, 0x4a, 0xb8,
    // 0x001d CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x1d, 0x00, 0x02, 0x29, 0x00, 0x00,

    /* CHARACTERISTIC,  c2e758b9-0e78-41e0-b0cb-98a593193fc5,READ|WRITE_WITHOUT_RESPONSE|NOTIFY|DYNAMIC */
    // 0x001e CHARACTERISTIC c2e758b9-0e78-41e0-b0cb-98a593193fc5 READ|WRITE_WITHOUT_RESPONSE|NOTIFY|DYNAMIC
    0x1b, 0x00, 0x02, 0x00, 0x1e, 0x00, 0x03, 0x28, 0x0c, 0x1f, 0x00, 0xc5, 0x3f, 0x19, 0x93, 0xa5, 0x98, 0xcb, 0xb0, 0xe0, 0x41, 0x78, 0x0e, 0xb9, 0x58, 0xe7, 0xc2,
    // 0x001f VALUE c2e758b9-0e78-41e0-b0cb-98a593193fc5 READ|WRITE_WITHOUT_RESPONSE|NOTIFY|DYNAMIC
    0x16, 0x00, 0x0c, 0x03, 0x1f, 0x00, 0xc5, 0x3f, 0x19, 0x93, 0xa5, 0x98, 0xcb, 0xb0, 0xe0, 0x41, 0x78, 0x0e, 0xb9, 0x58, 0xe7, 0xc2,
    // 0x0020 CLIENT_CHARACTERISTIC_CONFIGURATION
    0x0a, 0x00, 0x0a, 0x01, 0x20, 0x00, 0x02, 0x29, 0x00, 0x00,

    // END
    0x00, 0x00,
};
//
// characteristics <--> handles
//
#define ATT_CHARACTERISTIC_2a05_01_VALUE_HANDLE 0x0003
#define ATT_CHARACTERISTIC_2a05_01_CLIENT_CONFIGURATION_HANDLE 0x0004
#define ATT_CHARACTERISTIC_2a00_01_VALUE_HANDLE 0x0007
#define ATT_CHARACTERISTIC_2a01_01_VALUE_HANDLE 0x0009
#define ATT_CHARACTERISTIC_2aa6_01_VALUE_HANDLE 0x000b
#define ATT_CHARACTERISTIC_2a00_02_VALUE_HANDLE 0x000e
#define ATT_CHARACTERISTIC_2a01_02_VALUE_HANDLE 0x0010
#define ATT_CHARACTERISTIC_2a01_02_CLIENT_CONFIGURATION_HANDLE 0x0011
#define ATT_CHARACTERISTIC_2a02_01_VALUE_HANDLE 0x0013
#define ATT_CHARACTERISTIC_2a03_01_VALUE_HANDLE 0x0015
#define ATT_CHARACTERISTIC_2a03_01_CLIENT_CONFIGURATION_HANDLE 0x0016
#define ATT_CHARACTERISTIC_046c_01_VALUE_HANDLE 0x0019
#define ATT_CHARACTERISTIC_b84ac9c6_29c5_46d4_bba1_9d534784330f_01_VALUE_HANDLE 0x001c
#define ATT_CHARACTERISTIC_b84ac9c6_29c5_46d4_bba1_9d534784330f_01_CLIENT_CONFIGURATION_HANDLE 0x001d
#define ATT_CHARACTERISTIC_c2e758b9_0e78_41e0_b0cb_98a593193fc5_01_VALUE_HANDLE 0x001f
#define ATT_CHARACTERISTIC_c2e758b9_0e78_41e0_b0cb_98a593193fc5_01_CLIENT_CONFIGURATION_HANDLE 0x0020

#endif
#endif
