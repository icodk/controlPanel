/*
 * frmInfo.c
 *
 *  Created on: 19. aug. 2021
 *      Author: ico
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


static void home_btn_event_handler(lv_event_t* e) {
    frmProcess_init();
}








/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
void frmInfo_init(void) {

    char buf[TEXT_BUF_SIZE_LOCAL];
    lv_obj_t* win = get_main_win();
    lv_obj_del(win);
    win = lv_win_create(lv_scr_act(), 30);
    lv_win_add_title(win, get_text(T_INFO));
    lv_obj_t* btn = lv_win_add_btn(win, LV_SYMBOL_HOME, 40);
    lv_obj_add_event_cb(btn, home_btn_event_handler, LV_EVENT_CLICKED, NULL);
    lv_obj_t* wcont = lv_win_get_content(win);  /*used to add content to the window*/
    lv_obj_t* info_label = lv_label_create(wcont);
    lv_obj_align(info_label, LV_ALIGN_TOP_LEFT, 0, 0);

    lv_label_set_text_fmt(info_label, "Version: %s\nIDF: %s\nlvgl:%d.%d.%d",STR_GIT_VERSION,IDF_VER,lv_version_major(),lv_version_minor(),lv_version_patch());
    //lv_label_set_text_fmt(info_label, "Version: %s\nIDF: %s",STR_GIT_VERSION,IDF_VER);



}

