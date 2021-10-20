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
extern void wifi_scan_init(lv_obj_t* list);
extern void wifi_network_selected(void);
static bool toSave;
static lv_obj_t* kb;
//----------------------------------------------
static void home_btn_event_handler(lv_event_t* e) {
    (void)e; //ignore
    if(toSave){
       	printf("Saving network settings...\n");
       	toSave=false;
       	//saveNetworkSetting();

    }
   // frmProcess_init();
    (*get_main_frm_init())();
}

//----------------------------------------------
static void ta_event_cb(lv_event_t* e)
{
    //char buf[TEXT_BUF_SIZE_LOCAL + 1];
    LV_LOG_USER("Event code: %d ", e->code);
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* ta = lv_event_get_target(e);
    char* pass = lv_event_get_user_data(e);
    lv_obj_t* win = get_main_win();
    //buf[0] = 0;
    if (code == LV_EVENT_FOCUSED) {
        if (lv_indev_get_type(lv_indev_get_act()) != LV_INDEV_TYPE_KEYPAD) {
            kb = lv_keyboard_create(lv_scr_act());
            lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_TEXT_LOWER);
            lv_keyboard_set_textarea(kb, ta);


            //lv_obj_add_flag(counterPanel, LV_OBJ_FLAG_HIDDEN); // hide the counter for the duration of the edit
  //          lv_obj_set_style_max_height(kb, LV_HOR_RES * 2 / 3, 0);
            //lv_obj_t* wcont = lv_win_get_content(win);  /*used to add content to the window*/
            lv_obj_set_height(win, LV_VER_RES / 2);// -lv_obj_get_height(kb));
           // lv_obj_clear_flag(kb, LV_OBJ_FLAG_HIDDEN);
            lv_obj_scroll_to_view_recursive(ta, LV_ANIM_OFF);
            lv_obj_update_layout(win);   /*Be sure the sizes are recalculated*/
        }
    } else if ((code == LV_EVENT_DEFOCUSED) || code == LV_EVENT_READY) {
        //kb = lv_keyboard_create(lv_scr_act());
        //lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_TEXT_LOWER);
        //lv_keyboard_set_textarea(kb, NULL);
        lv_obj_set_height(win, LV_VER_RES);
        //lv_obj_clear_flag(counterPanel, LV_OBJ_FLAG_HIDDEN); // show the counter after editing was finished
       // lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        if (kb != NULL) {
            lv_obj_del(kb);
            kb = NULL;
        }
        lv_obj_clear_state(ta, LV_STATE_FOCUSED);
        lv_indev_reset(NULL, ta);
        //---- save the values to the fields
        //const char* txt = lv_textarea_get_text(ta);

        lv_memcpy(pass, lv_textarea_get_text(ta),1+ strlen(lv_textarea_get_text(ta)));
        wifi_network_selected(); // reconnect



    } else if (code == LV_EVENT_CANCEL) {
        lv_obj_set_height(win, LV_VER_RES);
        //lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);
        if (kb != NULL) {
            lv_obj_del(kb);
            kb = NULL;
        }
        lv_obj_clear_state(ta, LV_STATE_FOCUSED);
       // lv_obj_clear_flag(counterPanel, LV_OBJ_FLAG_HIDDEN); // hide the counter for the duration of the edit
        lv_indev_reset(NULL, ta);   /*To forget the last clicked object to make it focusable again*/
        // cancel- use the old value
       // lv_snprintf(buf, TEXT_BUF_SIZE_LOCAL, "%d", *field);
        lv_textarea_set_text(ta, pass);

    }
}

//--------------------------------------------------

static void ap_list_event_handler(lv_event_t* e) {
    //lv_event_code_t code = lv_event_get_code(e);
	static lv_obj_t * spinner=NULL;
    LV_LOG_USER("DD event %d ", e->code);
    //printf("DD event %d\n", e->code);
    lv_obj_t* list = lv_event_get_target(e);
    char buf[32];
    if (e->code == LV_EVENT_PRESSED) {

    		spinner = lv_spinner_create(lv_scr_act(), 1000, 60);
    	    lv_obj_set_size(spinner, 50, 50);
    	    lv_obj_center(spinner);
    	    wifi_scan_init(list);
    	    lv_dropdown_close(list);
    	    //lv_obj_del(spinner);
    }
    if (e->code == LV_EVENT_REFRESH) {
    	lv_obj_del(spinner);
    	spinner=NULL;
    	lv_dropdown_close(list);
    	lv_dropdown_open(list);
    }
    if (e->code == LV_EVENT_VALUE_CHANGED) { // user selected a network
    	network_settings_t *netSet = get_network_settings();
    	printf("---------net ssid: %s\n",(char *)netSet->remote_ssid_name);
    	lv_dropdown_get_selected_str(list,buf,32);
    	printf("---------buf: %s\n",buf);
    	if(strcmp(buf,(char *)netSet->remote_ssid_name)!=0){
    		lv_dropdown_get_selected_str(list,(char *)netSet->remote_ssid_name,32);
    		toSave=true;
    		printf("Saving network settings \n");
    	}

    	wifi_network_selected();
    }

}

//--------------------------------------------------
static void enable_event_handler(lv_event_t* e) {
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t* obj = lv_event_get_target(e);
    if (code == LV_EVENT_VALUE_CHANGED) {
        bool * enable_mode= (bool *)lv_event_get_user_data(e);
        

        //const char* txt = lv_checkbox_get_text(obj);
        //const char* state = lv_obj_get_state(obj) & LV_STATE_CHECKED ? "Checked" : "Unchecked";
        *enable_mode = lv_obj_get_state(obj) & LV_STATE_CHECKED ? true : false;
        LV_LOG_USER("%s: %s", txt, state);
    }
}
//--------------------------------------------------
static void fill_STA_tab(lv_obj_t* tab, network_settings_t* netSet) {
    lv_obj_t* dd;
    //------ ssid list (drop down list)
    dd = lv_dropdown_create(tab);
    lv_obj_set_width(dd, tab->coords.x2/ 2);
    lv_dropdown_set_options(dd,(char *)netSet->remote_ssid_name);
    lv_dropdown_set_dir(dd, LV_DIR_RIGHT);
   // lv_dropdown_set_symbol(dd, LV_SYMBOL_DOWN);
    lv_obj_align(dd, LV_ALIGN_TOP_LEFT, 0, 25);
    lv_obj_add_event_cb(dd, ap_list_event_handler, LV_EVENT_ALL, NULL);

    //---- password field
    // label the field
    lv_obj_t* pass_label = lv_label_create(tab);
    lv_label_set_text(pass_label, get_text(T_PASSWORD));
    lv_obj_align(pass_label, LV_ALIGN_TOP_LEFT,  0,80);

    lv_obj_t* passField = lv_textarea_create(tab);
    lv_textarea_set_one_line(passField, true);
    lv_obj_set_width(passField, tab->coords.x2 / 2);
    lv_obj_align(passField, LV_ALIGN_TOP_LEFT, 0, 100);
    lv_textarea_set_max_length(passField, 62);
    //lv_snprintf(buf, TEXT_BUF_SIZE_LOCAL, int_fmt, counter->min);
    lv_textarea_set_text(passField, (char*)netSet->remote_ssid_pass);

    lv_obj_add_event_cb(passField, ta_event_cb, LV_EVENT_ALL, netSet->remote_ssid_pass);

    


}
//--------------------------------------------------
//static void tab_event_handler(lv_event_t* e) {
//
//    if (e->code == LV_EVENT_VALUE_CHANGED) {
//        LV_LOG_USER("Tab event %d ", e->code);
//    }
//    
//
//}

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
    //-------  keybaord for entering password
    
    //lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_TEXT_LOWER);
    //lv_keyboard_set_mode(kb, LV_KEYBOARD_MODE_SPECIAL);

   // lv_obj_add_flag(kb, LV_OBJ_FLAG_HIDDEN);



    /*-------------------STA TAB*/
    lv_obj_t* tab_wifi_STA= lv_tabview_add_tab(tabview, get_text(T_WIFI_STA));// "Wifi STA");
    //lv_obj_add_event_cb(tab_wifi_STA, tab_event_handler, LV_EVENT_ALL, NULL);
    //-- Enable sta checkbox
    lv_obj_t* cb = lv_checkbox_create(tab_wifi_STA);
    lv_checkbox_set_text(cb, get_text(T_ENABLE_STA));
    if (netSet->sta_enable) {
        lv_obj_add_state(cb, LV_STATE_CHECKED);
        fill_STA_tab(tab_wifi_STA,netSet);
    }
   // lv_obj_add_event_cb(cb, enable_event_handler, LV_EVENT_VALUE_CHANGED, (void *)&netSet->sta_enable);
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
