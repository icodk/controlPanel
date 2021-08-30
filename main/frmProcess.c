//#include "../../lv_examples.h"


#ifdef __GNUC__
#include <time.h>

#else
#include <windows.h>



#endif

#include <stdio.h>
#include <stdlib.h>
#include "lvgl/lvgl.h"
#include "dataStorage.h"
#include "ui_common.h"
#include "text_table.h"

//#include "lvgl/examples/lv_examples.h"
//#include "lv_demos/lv_demo.h"
//#include "lv_drivers/win32drv/win32drv.h"

//static bool msgBoxOn = false;

extern void counter_conf_init(counter_id_t counterId);
extern void frmMenu_init(void);

static int8_t showDate= 0;
//--------------------------------------------------
//static void resetMsgBox_event_cb(lv_event_t* e)
//{
//    lv_obj_t* obj = lv_event_get_current_target(e);
//    //LV_LOG_USER("Button %s clicked", lv_msgbox_get_active_btn_text(obj));
//    LV_LOG_USER("Event code: %d ",e->code );
//
//    if (e->code == LV_EVENT_DELETE) {
//
//            return;
//   }
//   else { // reset was pressed
//
//        int32_t* cVal = get_current_count((counter_id_t)(e->user_data));
//        (*cVal)=0;
//       lv_msgbox_close(obj);
//
//   }
//
//
//
//    /*if (e->code == LV_EVENT_DELETE) {
//        msgBoxOn = false;
//    }else
//
//    }*/
//}
//------------------
static void  title_click_event_handler(lv_event_t * e) {

    if (e->code == LV_EVENT_CLICKED) {
        LV_LOG_USER("title event %d ", e->code);
        if(showDate >0){
        	showDate =0;
        }else{
        	showDate = 5;
        }
    }

}
//------------------
// counter configuration init when clicking on a counter
static void config_init(lv_event_t* e) {
    showDate = 0;
    lv_timer_t** tmr = get_updateTimer();
    lv_timer_set_repeat_count(*tmr , 0); // delete the timer, not needed when in conf. mode
    counter_conf_init((counter_id_t)(e->user_data));
}


//------------------

//static void resetMsgBox(lv_event_t* e)
//{
//    static const char* btns[] = { "Reset", "" };
// 
//    lv_obj_t* mbox1 = lv_msgbox_create(NULL, "Reset Counter", "Click Reset to reset counter.", btns, true);
//    //mbox1->user_data = 1;
//    lv_label_set_text_fmt(lv_msgbox_get_title(mbox1), "Reset Counter: %d",1+ (int)e->user_data);
//    lv_obj_add_event_cb(mbox1, resetMsgBox_event_cb, LV_EVENT_VALUE_CHANGED, e->user_data);
//    lv_obj_add_event_cb(mbox1, resetMsgBox_event_cb, LV_EVENT_DELETE/*LV_EVENT_ALL*/, e->user_data);
//    //lv_obj_add_event_cb(mbox1, msgBox_event_cb, LV_EVENT_CLICKED, NULL);
//   // lv_obj_set_style_border_width(mbox1, LV_PART_MAIN, LV_STATE_DEFAULT, 2);
//    lv_obj_set_style_border_width(mbox1, 5, LV_STATE_DEFAULT);
//    lv_obj_set_style_border_color(mbox1, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);
//    lv_obj_center(mbox1);
//}
//------------------
static void menu_btn_event_handler(lv_event_t * e)
{
   // lv_obj_t * obj = lv_event_get_target(e);
    LV_LOG_USER("Event code %d", e->code);
    showDate = 0;
    lv_timer_t** tmr = get_updateTimer();
    lv_timer_set_repeat_count(*tmr, 0);
    frmMenu_init();
    //resetMsgBox();

}

//------------------
static void drawFrmProcess(lv_obj_t* win) {
    
     //win = lv_win_create(lv_scr_act(), 30);
    // window content
    //lv_obj_t* win = get_main_win();
   

    for (int i = 0; i < COUNTER_COUNT; i++) {
        // PANEL
        lv_obj_t* wcont = lv_win_get_content(win);  /*used to add content to the window*/
        lv_obj_t* panel = lv_obj_create(wcont);
        lv_obj_set_size(panel, 250, 40);
        lv_obj_align(panel, LV_ALIGN_TOP_LEFT,5, i*50 + 5);
        lv_obj_add_style(panel, get_style_panel(), 0);
        //lv_obj_add_event_cb(panel, resetMsgBox, LV_EVENT_CLICKED, i);
        lv_obj_add_event_cb(panel, config_init, LV_EVENT_CLICKED,(void *) i);

        // LABEL
        lv_obj_t* label = lv_label_create(panel);
        lv_label_set_text_fmt(label, "%s  %d ",get_text(T_COUNTER),i+1);
        
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
//------------------
static void     updateFrmProcess(void) {
    static int16_t lastSecond;
    for (int i = 0; i < COUNTER_COUNT; i++) {
        counter_t* cnt= get_counter(i);
        int32_t* cVal = get_current_count(i);
        (*cVal)++;
        lv_label_set_text_fmt(cnt->displayField, "%d", *cVal);
    }

#ifdef __GNUC__
    time_t now;
    struct tm timeinfo;

       time(&now);
       // Set timezone to China Standard Time
       setenv("TZ", "UTC+2", 1);
       tzset();

       //localtime_r(&now, &timeinfo);
       //localtime(&now);
       localtime_r(&now, &timeinfo);
       if (lastSecond!=timeinfo.tm_sec ) {
               lastSecond = timeinfo.tm_sec;
               lv_obj_t** title = get_main_win_title();
               if (showDate > 0) {
                   showDate--;
                   lv_label_set_text_fmt(*title, "%s     %02d-%02d-%02d", get_text(T_PROCESS), timeinfo.tm_year, timeinfo.tm_mon, timeinfo.tm_mday);
               } else {
                   lv_label_set_text_fmt(*title, "%s     %02d:%02d:%02d", get_text(T_PROCESS), timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec);
               }
           }



#else
    SYSTEMTIME lt;// , st;

    //GetSystemTime(&st);
    GetLocalTime(&lt);
    if (lastSecond!=lt.wSecond ) {
        lastSecond = lt.wSecond;
        lv_obj_t** title = get_main_win_title();
        if (showDate > 0) {
            showDate--;
            lv_label_set_text_fmt(*title, "%s     %02d-%02d-%02d", get_text(T_PROCESS), lt.wYear, lt.wMonth, lt.wDay);
        } else {
            lv_label_set_text_fmt(*title, "%s     %02d:%02d:%02d", get_text(T_PROCESS), lt.wHour, lt.wMinute, lt.wSecond);
        }
    }

#endif

    
    
    
}
//---------------------------------------
static void timer_cb(lv_timer_t* timer)
{
    
    updateFrmProcess();
//    LV_LOG_USER("Timer was called ");
}


//---------------------------------------

void frmProcess_init() {

    lv_obj_t* win = get_main_win();
    lv_obj_del(win);
    win = lv_win_create(lv_scr_act(), 30);
    lv_obj_t** title = get_main_win_title();
    *title = lv_win_add_title(win, get_text(T_PROCESS));
    lv_obj_t* header = lv_win_get_header(win);
    lv_obj_add_event_cb(header, title_click_event_handler, LV_EVENT_ALL, NULL);

    // settings cfg button
    // 
    lv_obj_t* btn;
    btn = lv_win_add_btn(win, LV_SYMBOL_LIST, 40);
    lv_obj_add_event_cb(btn, menu_btn_event_handler, LV_EVENT_CLICKED, NULL);



    drawFrmProcess(win);
    lv_timer_t** tmr = get_updateTimer();
    *tmr=lv_timer_create(timer_cb, 100, NULL);

#ifdef __GNUC__

//    time_t now;
//    char strftime_buf[64];
//    struct tm timeinfo;
//
//    time(&now);
//    // Set timezone to China Standard Time
//    setenv("TZ", "UTC+2", 1);
//    tzset();
//
//    //localtime_r(&now, &timeinfo);
//    localtime(&now);
//    //strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
//    printf("\n%s", strftime_buf);

#else
    SYSTEMTIME st, lt;

    GetSystemTime(&st);
    GetLocalTime(&lt);

    printf("\nThe system time is: %02d:%02d\n", st.wHour, st.wMinute);
    printf("\nThe local time is: %02d:%02d\n", lt.wHour, lt.wMinute);

#endif



   
}
//-------------------------------------------------
