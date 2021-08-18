#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lvgl/lvgl.h"
#include "dataStorage.h"
#include "ui_common.h"
#include "text_table.h"

extern const char*  NUMERIC_RANGE;
extern void  frmProcess_init(void);


static counter_id_t counterId;
static lv_obj_t* kb;
static lv_obj_t* counterPanel;
static const char* int_fmt = "%d";
static bool toSave;
//----------------------------------------------
//static void saveValue(lv_obj_t* ta) {
//
//    
//}
//

//----------------------------------------------
// 
//
//static void kb_event_cb( lv_event_t *e)
//{
//    LV_LOG_USER("KeyBoard event %d",e->code);
//
//    
//    
//}

//----------------------------------------------
static void ta_event_cb(lv_event_t * e)
{
    char buf[TEXT_BUF_SIZE_LOCAL + 1];
    LV_LOG_USER("Event code: %d ", e->code);
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* ta = lv_event_get_target(e);
    int32_t * field = lv_event_get_user_data(e);
    lv_obj_t* win = get_main_win();
    if (code == LV_EVENT_FOCUSED) {
        if (lv_indev_get_type(lv_indev_get_act()) != LV_INDEV_TYPE_KEYPAD) {
            lv_keyboard_set_textarea(kb, ta);
            lv_obj_add_flag(counterPanel, LV_OBJ_FLAG_HIDDEN); // hide the counter for the duration of the edit
            lv_obj_set_style_max_height(kb, LV_HOR_RES * 2 / 3, 0);
            //lv_obj_t* wcont = lv_win_get_content(win);  /*used to add content to the window*/
            lv_obj_set_height(win, LV_VER_RES - lv_obj_get_height(kb));
            lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
            lv_obj_scroll_to_view_recursive(ta, LV_ANIM_OFF);
            lv_obj_update_layout(win);   /*Be sure the sizes are recalculated*/
        }
    }
    else if ((code == LV_EVENT_DEFOCUSED)|| code == LV_EVENT_READY ) {
        lv_keyboard_set_textarea(kb, NULL);
        lv_obj_set_height(win, LV_VER_RES);
        lv_obj_clear_flag(counterPanel, LV_OBJ_FLAG_HIDDEN); // show the counter after editing was finished
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(ta, LV_STATE_FOCUSED);
        //---- save the values to the fields
        const char* txt = lv_textarea_get_text(ta);

        
        //*field = (int32_t)atoi(txt);

        if (*field != (int32_t)atoi(txt)) {
            *field = (int32_t)atoi(txt);
            toSave = true;
        }


    }
    else if (code ==  LV_EVENT_CANCEL  ) {
        lv_obj_set_height(win, LV_VER_RES);
        lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_state(ta, LV_STATE_FOCUSED);
        lv_obj_clear_flag(counterPanel, LV_OBJ_FLAG_HIDDEN); // hide the counter for the duration of the edit
        lv_indev_reset(NULL, ta);   /*To forget the last clicked object to make it focusable again*/
        // cancel- use the old value
        lv_snprintf(buf, TEXT_BUF_SIZE_LOCAL, int_fmt, *field);
        lv_textarea_set_text(ta, buf);

    }
}

//--------------------------------------------

//-------------------------------------






static void home_btn_event_handler(lv_event_t* e) {

    if (toSave) {
        saveSettings();
    }
    toSave = false;
    lv_timer_t** tmr = get_updateTimer();
    lv_timer_set_repeat_count(*tmr, 0);
    frmProcess_init();
}

//-------------------------------------------------------
static void resetMsgBox_event_cb(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_current_target(e);
    //LV_LOG_USER("Button %s clicked", lv_msgbox_get_active_btn_text(obj));
    LV_LOG_USER("Event code: %d ", e->code);

    if (e->code == LV_EVENT_DELETE) {

        return;
    }
    else { // reset was pressed

        int32_t* cVal = get_current_count(counterId);
        (*cVal) = 0;
        lv_msgbox_close(obj);

    }



}
//------------------

static void resetMsgBox(lv_event_t* e)
{
    //static const char* btns[] = { "Reset", "" };
    static const char* btns[2]; 
    btns[0] = get_text(T_RESET);
    btns[1] = NULL;
    lv_obj_t* mbox1 = lv_msgbox_create(NULL, "", get_text(T_CLICK_TO_RESET), btns, true);
    lv_label_set_text_fmt(lv_msgbox_get_title(mbox1), get_text(T_RESET_COUNTER_X), 1 + counterId);
    lv_obj_add_event_cb(mbox1, resetMsgBox_event_cb, LV_EVENT_VALUE_CHANGED, e->user_data);
    lv_obj_add_event_cb(mbox1, resetMsgBox_event_cb, LV_EVENT_DELETE/*LV_EVENT_ALL*/, e->user_data);
    lv_obj_set_style_border_width(mbox1, 5, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(mbox1, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
    lv_obj_center(mbox1);
}


static void     updateFrmConfig(void) {
    counter_t* cnt = get_counter(counterId);
    int32_t* cVal = get_current_count(counterId);
    #ifdef  _MSC_VER
    (*cVal)++;
    #endif
    lv_label_set_text_fmt(cnt->displayField, "%d", *cVal);

}


static void timer_cb(lv_timer_t* timer)
{

    updateFrmConfig();
    LV_LOG_USER("Timer was called ");
}





void counter_conf_init(counter_id_t cId) {
//void init_counter_conf(void) {
    counterId = cId;
    char buf[TEXT_BUF_SIZE_LOCAL+1];
    lv_obj_t*  win =get_main_win();
    lv_obj_del(win);
    win=lv_win_create(lv_scr_act(), 30);
    lv_obj_t*  title=lv_win_add_title(win, NULL);
    lv_label_set_text_fmt(title, "%s: ' %d'  %s", get_text(T_COUNTER), 1 + counterId, get_text(T_CONFIG));

    lv_obj_t* btn;
    btn = lv_win_add_btn(win, LV_SYMBOL_HOME, 40);
    lv_obj_add_event_cb(btn, home_btn_event_handler, LV_EVENT_CLICKED, NULL);
    counter_t* counter = get_counter(counterId);


    /*Create a keyboard*/
    kb = lv_keyboard_create(lv_scr_act());
    lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_NUMBER);
    lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);

    


    // Counter state:
    // PANEL
    lv_obj_t* wcont = lv_win_get_content(win);  /*used to add content to the window*/
    counterPanel = lv_obj_create(wcont);
    lv_obj_set_size(counterPanel, 250, 40);
    lv_obj_align(counterPanel, LV_ALIGN_TOP_LEFT, 5,  5);
    lv_obj_add_style(counterPanel, get_style_panel(), 0);
    lv_obj_add_event_cb(counterPanel, resetMsgBox, LV_EVENT_CLICKED, NULL);
    //lv_obj_add_event_cb(panel, config_init, LV_EVENT_CLICKED, i);

    // LABEL
    lv_obj_t* label = lv_label_create(counterPanel);
    lv_label_set_text_fmt(label, "%s:  %d", get_text(T_COUNTER), 1 + counterId);


    //lv_label_set_text_fmt(label, "Counter %d ", counterId + 1);
    //lv_label_set_text_fmt(title, "Counter %d Config.", 1 + counterId);
   
    lv_obj_align(label, LV_ALIGN_LEFT_MID, 5, 0);
    lv_obj_add_style(label, get_style_label(), 0);


    // DATA
    //counter_t* cnt= get_counter(counterId);
    counter->displayField = lv_label_create(counterPanel);


    //
    //lv_label_set_text_fmt(reg->displayField, "%d",*cVal);
    lv_obj_align(counter->displayField, LV_ALIGN_RIGHT_MID, -10, 0);
    lv_obj_add_style(counter->displayField, get_style_data(), 0);

    lv_timer_t** tmr = get_updateTimer();
    *tmr = lv_timer_create(timer_cb, 100, NULL);



    // --- Fields
    /*  min. value field*/
    lv_obj_t* minVal= lv_textarea_create(wcont);
    lv_textarea_set_one_line(minVal, true);
    lv_obj_set_size(minVal, 60, 40);
    lv_obj_align(minVal, LV_ALIGN_CENTER, 0, 0);
    lv_textarea_set_max_length(minVal, 4);

    lv_snprintf(buf, TEXT_BUF_SIZE_LOCAL, int_fmt, counter->min);
    lv_textarea_set_text(minVal, buf);

    
    // label the field
    lv_obj_t* min_label = lv_label_create(wcont);
    lv_label_set_text(min_label, get_text(T_MIN));
    lv_obj_align(min_label, LV_ALIGN_LEFT_MID, 20, 0);
    lv_obj_add_event_cb(minVal, ta_event_cb, LV_EVENT_ALL, &counter->min);

    /*  max. value field*/
    lv_obj_t* maxVal = lv_textarea_create(wcont);
    lv_textarea_set_one_line(maxVal, true);
    lv_obj_set_size(maxVal, 60, 40);
    lv_obj_align(maxVal, LV_ALIGN_CENTER, 0, 50);
    lv_textarea_set_max_length(maxVal, 4);
    // label the field
    lv_obj_t* max_label = lv_label_create(wcont);
    lv_label_set_text(max_label,get_text(T_MAX));
    lv_obj_align(max_label, LV_ALIGN_LEFT_MID, 20, 50);
    lv_obj_add_event_cb(maxVal, ta_event_cb, LV_EVENT_ALL, &counter->max);

    lv_snprintf(buf, TEXT_BUF_SIZE_LOCAL, int_fmt, counter->max);
    lv_textarea_set_text(maxVal, buf);




    /*  Param. value field*/
    lv_obj_t* paramVal = lv_textarea_create(wcont);
    lv_textarea_set_one_line(paramVal, true);
    lv_obj_set_size(paramVal, 60, 40);
    lv_obj_align(paramVal, LV_ALIGN_CENTER, 0, 100);
    lv_textarea_set_max_length(paramVal, 4);
    // label the field
    lv_obj_t* param_label = lv_label_create(wcont);
    lv_label_set_text(param_label,get_text(T_PARAM));
    lv_obj_align(param_label, LV_ALIGN_LEFT_MID, 20, 100);
    lv_obj_add_event_cb(paramVal, ta_event_cb, LV_EVENT_ALL, &counter->param);

    lv_snprintf(buf, TEXT_BUF_SIZE_LOCAL, int_fmt, counter->param);
    lv_textarea_set_text(paramVal, buf);




   
   // /* max*/

   //lastObj = create_numeric_field(win, get_text(T_MAX), &cnt->max, 5, 100);
   //lv_obj_add_event_cb(lastObj, ta_event_cb, LV_EVENT_ALL, kb);



}

//-----------------------------------------------------
