#pragma once
#ifdef _MCS_VER
#include <Windows.h>
#include "resource.h"
#endif

#include "lvgl/lvgl.h"


typedef enum _REGS_ID {
    CNT_0,
    CNT_1,
    CNT_2,
    CNT_3,
    CNT_4,
    CNT_5,
    CNT_COUNT

} counter_id_t;

#define COUNTER_COUNT CNT_COUNT

typedef struct _COUNTER{
    uint32_t setpoint;
    uint32_t Kp;
    uint32_t Ki;
    uint32_t Kd;
    int32_t min;
    int32_t max;
    int32_t param;
    lv_obj_t* displayField;


} counter_t;

typedef struct _NETWORK_SETTINGS{
	bool sta_enable;	// connect to an AP
	bool ap_enable;	// enable an  AP on this board
    bool eth_enable;	// enable ethernet
	char remote_ap_name[32]; 		// name of AP to connect to
	char local_ap_name[32];	  	//  name of local AP
	bool sta_static_ip;	  // sta should have static IP

}network_settings_t;



typedef enum {



    CONTROL_PARMAS_START,	//  	0
    CV_CONTROL_MODE_CH1,	//  	1
    CV_CONTROL_MODE_CH2,	//  	2
    CV_A01_ON_TIME_CH1,	//  	3
    CV_A01_ON_TIME_CH2,	//  	4
    CV_A02_OFF_TIME_CH1,	//  	5
    CV_A02_OFF_TIME_CH2,	//  	6
    CV_A03_WETTING_CH1,	//  	7
    CV_A03_WETTING_CH2,	//  	8
    CV_A11_DUST_MANUAL_
} ctl_param_t;


void loadSettings(void);
void saveCounterSettings(void);
counter_t* get_counter(counter_id_t regId);
int32_t* get_current_count(counter_id_t regNdx);

network_settings_t * get_network_settings(void);
