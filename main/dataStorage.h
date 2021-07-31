#pragma once


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
    lv_obj_t* displayField;


} counter_t;


void loadSettings(void);
counter_t* get_counter(counter_id_t regId);
int32_t* get_current_count(counter_id_t regNdx);
