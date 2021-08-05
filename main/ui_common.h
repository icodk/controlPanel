#pragma once
#include "dataStorage.h"
#define TEXT_BUF_SIZE_LOCAL 50

typedef struct _PARAM_EDIT {
    counter_id_t counterId;
    lv_obj_t* label;
}param_edit_t;

    void ui_common_init(void);

    lv_obj_t* get_main_win(void);
    lv_style_t* get_style_panel(void);
    lv_style_t* get_style_label(void);
    lv_style_t* get_style_data(void);
    lv_timer_t** get_updateTimer(void);




