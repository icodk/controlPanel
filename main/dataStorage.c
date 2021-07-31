

#include "lvgl/lvgl.h"
#include "dataStorage.h"


counter_t counter[COUNTER_COUNT];
int32_t current_count[COUNTER_COUNT];


//---------------------------------


void loadSettings(void) {



}
//----------------------------------
counter_t* get_counter(counter_id_t cntId) {

    return &counter[cntId];
}
//----------------------------------
int32_t* get_current_count(counter_id_t cntId) {

    return &current_count[cntId];
}
//----------------------------------
//----------------------------------
//----------------------------------
