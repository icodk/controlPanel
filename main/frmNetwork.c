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

static void home_btn_event_handler(lv_event_t* e) {
    (void)e; //ignore
    
    frmProcess_init();
}
//--------------------------------------------------

static void ap_list_event_handler(lv_event_t* e) {
    //lv_event_code_t code = lv_event_get_code(e);
    LV_LOG_USER("DD event %d ", e->code);
    lv_obj_t * list= lv_event_get_target(e);
    lv_dropdown_set_options(list, "kuku\n");

}

//--------------------------------------------------
static void enable_event_handler(lv_event_t* e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED) {
        bool * enable_mode= (bool *)lv_event_get_user_data(e);
        

        const char* txt = lv_checkbox_get_text(obj);
        const char* state = lv_obj_get_state(obj) & LV_STATE_CHECKED ? "Checked" : "Unchecked";
        *enable_mode = lv_obj_get_state(obj) & LV_STATE_CHECKED ? true : false;
        LV_LOG_USER("%s: %s", txt, state);
    }
}
//--------------------------------------------------
static void fillSTATab(lv_obj_t* tab, network_settings_t* netSet) {
    lv_obj_t* dd;
    dd = lv_dropdown_create(tab);
    lv_dropdown_set_options(dd, netSet->remote_ap_name);
    lv_dropdown_set_dir(dd, LV_DIR_RIGHT);
   // lv_dropdown_set_symbol(dd, LV_SYMBOL_DOWN);
    lv_obj_align(dd, LV_ALIGN_TOP_LEFT, 0, 25);
    lv_obj_add_event_cb(dd, ap_list_event_handler, LV_EVENT_PRESSED, NULL);


}

//--------------------------------------------------
void frmNetwork_init(void) {

    //char buf[TEXT_BUF_SIZE_LOCAL];
    lv_obj_t* win = get_main_win();
    lv_obj_del(win);
    win = lv_win_create(lv_scr_act(), 30);
    lv_win_add_title(win, get_text(T_NETWORK));
    lv_obj_t* btn = lv_win_add_btn(win, LV_SYMBOL_HOME, 30);
    lv_obj_add_event_cb(btn, home_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t* wcont = lv_win_get_content(win);  /*used to add content to the window*/
    lv_obj_t* tabview;
    tabview = lv_tabview_create(wcont, LV_DIR_TOP, 20);
    network_settings_t *netSet = get_network_settings();

    /*-------------------STA TAB*/
    lv_obj_t* tabWifiSTA = lv_tabview_add_tab(tabview, get_text(T_WIFI_STA));// "Wifi STA");

    lv_obj_t* cb = lv_checkbox_create(tabWifiSTA);
    lv_checkbox_set_text(cb, get_text(T_ENABLE_STA));
    if (netSet->sta_enable) {
        lv_obj_add_state(cb, LV_STATE_CHECKED);
        fillSTATab(tabWifiSTA,netSet);
    }
    lv_obj_add_event_cb(cb, enable_event_handler, LV_EVENT_VALUE_CHANGED, (void *)&netSet->sta_enable);
    //------

    //lv_obj_t* label = lv_label_create(tabWifiSTA);
    //lv_label_set_text(label, "kuku");// netSet->remote_ap_name);
    ////lv_obj_align(label, LV_ALIGN_LEFT_MID, 5, 0);
    //lv_obj_align_to(label, cb, LV_ALIGN_OUT_BOTTOM_MID, 0, 10);
    //lv_obj_add_style(label, get_style_label(), 0);






    /*------------------AP TAB*/
    lv_obj_t* tabWifiAP = lv_tabview_add_tab(tabview, get_text(T_WIFI_AP));// "Wifi AP");

    cb = lv_checkbox_create(tabWifiAP);
    lv_checkbox_set_text(cb, get_text(T_ENABLE_AP));
    if (netSet->ap_enable) {
        lv_obj_add_state(cb, LV_STATE_CHECKED);
    }
    
    lv_obj_add_event_cb(cb, enable_event_handler, LV_EVENT_VALUE_CHANGED, (void *)&netSet->ap_enable);



    /*-------------------------Etheret TAB*/
    if (isEthernetSupported()) {
        lv_obj_t* tabEthernet = lv_tabview_add_tab(tabview, get_text(T_ETHERNET));
        cb = lv_checkbox_create(tabEthernet);
        lv_checkbox_set_text(cb, get_text(T_ENABLE_ETH));
        if (netSet->eth_enable) {
            lv_obj_add_state(cb, LV_STATE_CHECKED);
        }
        lv_obj_add_event_cb(cb, enable_event_handler, LV_EVENT_VALUE_CHANGED, (void *)&netSet->eth_enable);
    }




}
