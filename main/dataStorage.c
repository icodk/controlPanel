

#include "lvgl/lvgl.h"
#include "dataStorage.h"


temp_regulator_t temp_reg[REGULATOR_COUNT];
int32_t current_temp[REGULATOR_COUNT];


//---------------------------------


void loadSettings(void) {



}
//----------------------------------
temp_regulator_t* get_reguator(counter_id_t regNdx) {

    return &temp_reg[regNdx];
}
//----------------------------------
int32_t* get_current_temp(counter_id_t regNdx) {

    return &current_temp[regNdx];
}
//----------------------------------
//----------------------------------
//----------------------------------
