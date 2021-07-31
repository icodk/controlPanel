#pragma once


#include "lvgl/lvgl.h"


typedef enum _REGS_ID {
    REG_0,
    REG_1,
    REG_2,
    REG_3,
    REG_4,
    REG_5,
    REG_COUNT

} counter_id_t;

#define REGULATOR_COUNT REG_COUNT

typedef struct TEMP_REGULATOR {
    uint32_t setpoint;
    uint32_t Kp;
    uint32_t Ki;
    uint32_t Kd;
    int32_t min;
    int32_t max;
    lv_obj_t* displayField;


} temp_regulator_t;


void loadSettings(void);
temp_regulator_t* get_reguator(counter_id_t regId);
int32_t* get_current_temp(counter_id_t regNdx);
