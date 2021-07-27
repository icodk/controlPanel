/*
 * dataStorage.c
 *
 *  Created on: 27. jul. 2021
 *      Author: ico
 */





#include "lvgl.h"
#include "dataStorage.h"


temp_regulator_t temp_reg[REGULATOR_COUNT];
int32_t current_temp[REGULATOR_COUNT];


//---------------------------------


void loadSettings(void) {



}
//----------------------------------
temp_regulator_t* get_reguator(reg_id_t regNdx) {

    return &temp_reg[regNdx];
}
//----------------------------------
int32_t* get_current_temp(reg_id_t regNdx) {

    return &current_temp[regNdx];
}
//----------------------------------
//----------------------------------
//----------------------------------
