//#include "../../lv_examples.h"


#include "lvgl/lvgl.h"
#include "dataStorage.h"
#include "ui_common.h"
//#include "lvgl/examples/lv_examples.h"
//#include "lv_demos/lv_demo.h"
//#include "lv_drivers/win32drv/win32drv.h"

//static bool msgBoxOn = false;

extern void counter_conf_init(counter_id_t counterId);

static void resetMsgBox_event_cb(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_current_target(e);
    //LV_LOG_USER("Button %s clicked", lv_msgbox_get_active_btn_text(obj));
    LV_LOG_USER("Event code: %d ",e->code );

    if (e->code == LV_EVENT_DELETE) {
            
            return;
   }
   else { // reset was pressed
       
        int32_t* cVal = get_current_count((counter_id_t)(e->user_data));
        (*cVal)=0;
       lv_msgbox_close(obj);

   }

    

    /*if (e->code == LV_EVENT_DELETE) {
        msgBoxOn = false;
    }else 

    }*/
}
//------------------

static void config_init(lv_event_t* e) {
    
    lv_timer_t** tmr = get_updateTimer();
    lv_timer_set_repeat_count(*tmr , 0);
    counter_conf_init((counter_id_t)(e->user_data));
}




static void resetMsgBox(lv_event_t* e)
{
    static const char* btns[] = { "Reset", "" };
 
    lv_obj_t* mbox1 = lv_msgbox_create(NULL, "Reset Counter", "Click Reset to reset counter.", btns, true);
    //mbox1->user_data = 1;
    lv_label_set_text_fmt(lv_msgbox_get_title(mbox1), "Reset Counter: %d",1+ (int)e->user_data);
    lv_obj_add_event_cb(mbox1, resetMsgBox_event_cb, LV_EVENT_VALUE_CHANGED, e->user_data);
    lv_obj_add_event_cb(mbox1, resetMsgBox_event_cb, LV_EVENT_DELETE/*LV_EVENT_ALL*/, e->user_data);
    //lv_obj_add_event_cb(mbox1, msgBox_event_cb, LV_EVENT_CLICKED, NULL);
   // lv_obj_set_style_border_width(mbox1, LV_PART_MAIN, LV_STATE_DEFAULT, 2);
    lv_obj_set_style_border_width(mbox1, 5, LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(mbox1, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
    lv_obj_center(mbox1);
}
//
//static void cfg_btn_event_handler(lv_event_t * e)
//{
//    lv_obj_t * obj = lv_event_get_target(e);
//    LV_LOG_USER("Event code %d", e->code);
//    //resetMsgBox();
//
//}


static void drawFrmMain(lv_obj_t* win) {
    
     //win = lv_win_create(lv_scr_act(), 30);
    // window content
    //lv_obj_t* win = get_main_win();

    lv_win_add_title(win, "Process");


    // settings cfg button
    // 
    lv_obj_t* btn;
    btn = lv_win_add_btn(win, LV_SYMBOL_SETTINGS, 40);
  //  lv_obj_add_event_cb(btn, cfg_btn_event_handler, LV_EVENT_CLICKED, NULL);

    for (int i = 0; i < COUNTER_COUNT; i++) {
        // PANEL
        lv_obj_t* wcont = lv_win_get_content(win);  /*used to add content to the window*/
        lv_obj_t* panel = lv_obj_create(wcont);
        lv_obj_set_size(panel, 250, 40);
        lv_obj_align(panel, LV_ALIGN_TOP_LEFT,5, i*50 + 5);
        lv_obj_add_style(panel, get_style_panel(), 0);
        //lv_obj_add_event_cb(panel, resetMsgBox, LV_EVENT_CLICKED, i);
        lv_obj_add_event_cb(panel, config_init, LV_EVENT_CLICKED, i);

        // LABEL
        lv_obj_t* label = lv_label_create(panel);
        lv_label_set_text_fmt(label, "Counter %d ",i+1);
        
        lv_obj_align(label, LV_ALIGN_LEFT_MID, 5, 0);
        lv_obj_add_style(label, get_style_label(), 0);


        // DATA
        counter_t* cnt = get_counter(i);
        cnt->displayField = lv_label_create(panel);


        //
        //lv_label_set_text_fmt(reg->displayField, "%d",*cVal);
        lv_obj_align(cnt->displayField, LV_ALIGN_RIGHT_MID, -10, 0);
        lv_obj_add_style(cnt->displayField, get_style_data(), 0);
    }

    
}

static void     updateFrmMain(void) {

    for (int i = 0; i < COUNTER_COUNT; i++) {
        counter_t* cnt= get_counter(i);
        int32_t* cVal = get_current_count(i);
        //(*cVal)++;
        lv_label_set_text_fmt(cnt->displayField, "%d", *cVal);
    }
    
    
}

static void timer_cb(lv_timer_t* timer)
{
    
    updateFrmMain();
    LV_LOG_USER("Timer was called ");
}




void frmMain_init() {

    lv_obj_t* win = get_main_win();
    lv_obj_del(win);
    win = lv_win_create(lv_scr_act(), 30);
    drawFrmMain(win);
    lv_timer_t** tmr = get_updateTimer();
    *tmr=lv_timer_create(timer_cb, 100, NULL);
   
}
//-------------------------------------------------
