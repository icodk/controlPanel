#pragma once
/*
 * data_struct.h
 *
 *  Created on: 26. jul. 2021
 *      Author: ico
 */

#ifndef MAIN_DATASTORAGE_H_
#define MAIN_DATASTORAGE_H_


#include "lvgl/lvgl.h"

#define REGULATOR_COUNT 10
typedef enum _REGS_ID {
    REG_0,
    REG_1,
    REG_2

} reg_id_t;

typedef struct TEMP_REGULATOR {
    uint32_t setpoint;
    uint32_t Kp;
    uint32_t Ki;
    uint32_t Kd;

} temp_regulator_t;


void loadSettings(void);
temp_regulator_t* get_reguator(reg_id_t regId);
int32_t* get_current_temp(reg_id_t regNdx);




#endif /* MAIN_DATASTORAGE_H_ */
