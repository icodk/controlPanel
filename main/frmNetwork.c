/*
* frmWif.c
*
* Created on : 01. Sep. 2021
* Author : ico
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lvgl/lvgl.h"
#include "dataStorage.h"
#include "ui_common.h"
#include "text_table.h"
/*-------------------------------------------------*/
extern void  frmProcess_init(void);
extern bool isEthernetSupported(void);

 typedef enum {
    WIFI_STA,
    WIFI_AP,
    ETHERNET

}network_mode_t;


static void home_btn_event_handler(lv_event_t* e) {
    frmProcess_init();
}

static void enable_event_handler(lv_event_t* e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED) {
        network_mode_t nm = (network_mode_t)lv_event_get_user_data(e);
        switch (nm) {
            case    WIFI_STA:
                break;
            case    WIFI_AP:
                break;
            case    ETHERNET:
                break;
            default:
                break;
        }

        const char* txt = lv_checkbox_get_text(obj);
        const char* state = lv_obj_get_state(obj) & LV_STATE_CHECKED ? "Checked" : "Unchecked";
        LV_LOG_USER("%s: %s", txt, state);
    }
}




void frmNetwork_init(void) {

    char buf[TEXT_BUF_SIZE_LOCAL];
    lv_obj_t* win = get_main_win();
    lv_obj_del(win);
    win = lv_win_create(lv_scr_act(), 30);
    lv_win_add_title(win, get_text(T_NETWORK));
    lv_obj_t* btn = lv_win_add_btn(win, LV_SYMBOL_HOME, 30);
    lv_obj_add_event_cb(btn, home_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t* wcont = lv_win_get_content(win);  /*used to add content to the window*/
    lv_obj_t* tabview;
    tabview = lv_tabview_create(wcont, LV_DIR_TOP, 20);

    /*STA TAB*/
    lv_obj_t* tabWifiSTA = lv_tabview_add_tab(tabview, "Wifi STA");

    lv_obj_t* cb = lv_checkbox_create(tabWifiSTA);
    lv_checkbox_set_text(cb, "Enable STA");
    lv_obj_add_state(cb, LV_STATE_CHECKED);
    lv_obj_add_event_cb(cb, enable_event_handler, LV_EVENT_VALUE_CHANGED, (void *)WIFI_STA);


    /*AP TAB*/
    lv_obj_t* tabWifiAP = lv_tabview_add_tab(tabview, "Wifi AP");

    cb = lv_checkbox_create(tabWifiAP);
    lv_checkbox_set_text(cb, "Enable AP");
    lv_obj_add_state(cb, LV_STATE_CHECKED);
    lv_obj_add_event_cb(cb, enable_event_handler, LV_EVENT_VALUE_CHANGED, (void*)WIFI_AP);



    /*Etheret TAB*/
    if (isEthernetSupported()) {
        lv_obj_t* tabEthernet = lv_tabview_add_tab(tabview, "Ethernet");
        cb = lv_checkbox_create(tabEthernet);
        lv_checkbox_set_text(cb, "Enable Ethernet");
        lv_obj_add_state(cb, LV_STATE_CHECKED);
        lv_obj_add_event_cb(cb, enable_event_handler, LV_EVENT_VALUE_CHANGED, (void*)WIFI_AP);
    }


    //lv_obj_t* info_label = lv_label_create(wcont);
    //lv_obj_align(info_label, LV_ALIGN_TOP_LEFT, 0, 0);
#ifdef __GNUC__ 
    //lv_label_set_text_fmt(info_label, "App: %s\nIDF: %s\nlvgl: %d.%d.%d", STR_GIT_VERSION, IDF_VER, lv_version_major(), lv_version_minor(), lv_version_patch());
    //lv_label_set_text_fmt(info_label, "Version: %s\nIDF: %s",STR_GIT_VERSION,IDF_VER);
#else
   // lv_label_set_text_fmt(info_label, "Version information");
#endif



}
