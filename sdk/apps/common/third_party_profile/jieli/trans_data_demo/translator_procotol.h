// binary representation
// attribute size in bytes (16), flags(16), handle (16), uuid (16/128), value(...)

#ifndef _TRANSLATOR_PROCOTOL_H
#define _TRANSLATOR_PROCOTOL_H

#include <stdint.h>

#define		HEARD_H		0x05
#define		HEARD_L		0x12

#define		TAIL		0x21

enum{
	DEVICE_SEND_HAND_SHAKE = 0x01,
	DEVICE_RECEIVE_HAND_SHAKE,

	DEVICE_SEND_GET_DEV_INFO,
	DEVICE_RECEIVE_GET_DEV_INFO,

	DEVICE_RECEIVE_GET_MAC_INFO,
	DEVICE_SEND_GET_MAC_INFO,

	DEVICE_RECEIVE_SET_BLE_NAME,
	DEVICE_SEND_SET_BLE_NAME,

	DEVICE_RECEIVE_GET_BAT_LEVEL,
	DEVICE_SEND_GET_BAT_LEVEL,

	DEVICE_RECEIVE_SET_COUNTRY_INFO,
	DEVICE_SEND_SET_COUNTRY_INFO,

	DEVICE_RECEIVE_GET_COUNTRY_INFO,
	DEVICE_SEND_GET_COUNTRY_INFO,

	DEVICE_RECEIVE_SET_QUDAO_INFO,
	DEVICE_SEND_SET_QUDAO_INFO,

	DEVICE_RECEIVE_GET_QUDAO_INFO,
	DEVICE_SEND_GET_QUADO_INFO,

	DEVICE_SEND_KEY_LEFT_LONG_DOWN = 0x13,
	DEVICE_RECEIVE_KEY_LEFT_LONG_DOWN = 0x14,

	DEVICE_SEND_KEY_LEFT_LONG_UP = 0x15,
	DEVICE_RECEIVE_KEY_LEFT_LONG_UP = 0x16,


	DEVICE_SEND_KEY_RIGHT_LONG_DOWN = 0x17,
	DEVICE_RECEIVE_KEY_RIGHT_LONG_DOWN = 0x18,

	DEVICE_SEND_KEY_RIGHT_LONG_UP = 0x19,
	DEVICE_RECEIVE_KEY_RIGHT_LONG_UP = 0x1a,

	DEVICE_SEND_REQUEST_SEND_VOICE_DATA = 0x33,
	DEVICE_RECEIVE_REQUEST_SEND_VOICE_DATA = 0x34,

	DEVICE_RECEIVE_STOP_RECODER = 0x35,
	DEVICE_SEND_STOP_RECODER = 0x36,

	DEVICE_SEND_PLAY_PREVIOUS = 0x1c,
	DEVICE_RECEIVE_PLAY_PREVIOUS = 0x1d,

	DEVICE_SEND_PLAY_NEXT = 0x1e,
	DEVICE_RECEIVE_PLAY_NEXT = 0x1f
};
	
extern void receive_data_form_app(u8 *data, u8 len);
extern void send_hand_shake_to_app(void);

#endif
