
#include "lvgl/lvgl.h"
#include "dataStorage.h"
#include "ui_common.h"

extern void  frmMain_init(void);

static counter_id_t counterId;
static void home_btn_event_handler(lv_event_t* e) {

    frmMain_init();
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
    static const char* btns[] = { "Reset", "" };

    lv_obj_t* mbox1 = lv_msgbox_create(NULL, "Reset Counter", "Click Reset to reset counter.", btns, true);
    //mbox1->user_data = 1;
    lv_label_set_text_fmt(lv_msgbox_get_title(mbox1), "Reset Counter: %d", 1 + counterId);
    lv_obj_add_event_cb(mbox1, resetMsgBox_event_cb, LV_EVENT_VALUE_CHANGED, e->user_data);
    lv_obj_add_event_cb(mbox1, resetMsgBox_event_cb, LV_EVENT_DELETE/*LV_EVENT_ALL*/, e->user_data);
    //lv_obj_add_event_cb(mbox1, msgBox_event_cb, LV_EVENT_CLICKED, NULL);
   // lv_obj_set_style_border_width(mbox1, LV_PART_MAIN, LV_STATE_DEFAULT, 2);
    lv_obj_set_style_border_width(mbox1, 5, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(mbox1, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
    lv_obj_center(mbox1);
}


static void     updateFrmConfig(void) {
    counter_t* reg = get_counter(counterId);
    int32_t* cVal = get_current_count(counterId);
    (*cVal)++;
    lv_label_set_text_fmt(reg->displayField, "%d", *cVal);

}


static void timer_cb(lv_timer_t* timer)
{

    updateFrmConfig();
    LV_LOG_USER("Timer was called ");
}





void counter_conf_init(counter_id_t cId) {
//void init_counter_conf(void) {
    counterId = cId;
    lv_obj_t*  win =get_main_win();
    lv_obj_del(win);
    win=lv_win_create(lv_scr_act(), 30);
    lv_obj_t*  title=lv_win_add_title(win, "Counter Config.");
    lv_label_set_text_fmt(title, "Counter %d Config.", 1 + counterId);
    lv_obj_t* btn;
    btn = lv_win_add_btn(win, LV_SYMBOL_HOME, 40);
    lv_obj_add_event_cb(btn, home_btn_event_handler, LV_EVENT_CLICKED, NULL);

    // Counter state:
    // PANEL
    lv_obj_t* wcont = lv_win_get_content(win);  /*used to add content to the window*/
    lv_obj_t* panel = lv_obj_create(wcont);
    lv_obj_set_size(panel, 250, 40);
    lv_obj_align(panel, LV_ALIGN_TOP_LEFT, 5,  5);
    lv_obj_add_style(panel, get_style_panel(), 0);
    lv_obj_add_event_cb(panel, resetMsgBox, LV_EVENT_CLICKED, NULL);
    //lv_obj_add_event_cb(panel, config_init, LV_EVENT_CLICKED, i);

    // LABEL
    lv_obj_t* label = lv_label_create(panel);
    lv_label_set_text_fmt(label, "Counter %d ", counterId + 1);

    lv_obj_align(label, LV_ALIGN_LEFT_MID, 5, 0);
    lv_obj_add_style(label, get_style_label(), 0);


    // DATA
    counter_t* cnt= get_counter(counterId);
    cnt->displayField = lv_label_create(panel);


    //
    //lv_label_set_text_fmt(reg->displayField, "%d",*cVal);
    lv_obj_align(cnt->displayField, LV_ALIGN_RIGHT_MID, -10, 0);
    lv_obj_add_style(cnt->displayField, get_style_data(), 0);

    lv_timer_t** tmr = get_updateTimer();
    *tmr = lv_timer_create(timer_cb, 100, NULL);


}

//-----------------------------------------------------
