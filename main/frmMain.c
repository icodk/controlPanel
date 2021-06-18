/*
 * frmMain.c
 *
 *  Created on: 12. jun. 2021
 *      Author: ico
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"
#include "lvgl.h"
//#include "lvgl/examples/lv_examples.h"
//#include "lv_demos/lv_demo.h"
//#include "lv_drivers/win32drv/win32drv.h"


static void event_handler(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    LV_LOG_USER("Button %d clicked", lv_obj_get_child_id(obj));
}


void frmMain(void)
{


	printf("\n============================= 1");
	fflush(stdout);

	/*Create a window*/
	  lv_obj_t * win = lv_win_create(lv_scr_act(), 30);

	        lv_obj_t * btn;
	        btn = lv_win_add_btn(win, LV_SYMBOL_LIST, 30);
	        lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

	        lv_win_add_title(win, "A title");

	        btn = lv_win_add_btn(win, LV_SYMBOL_BARS, 30);
	        lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

	        btn = lv_win_add_btn(win, LV_SYMBOL_CLOSE, 40);
	        lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

	        lv_obj_t * cont = lv_win_get_content(win);  /*Content can be aded here*/
	        lv_obj_t * label =  lv_label_create(cont);
	        lv_label_set_text(label, "This is\n"
	                                 "a pretty\n"
	                                 "long text\n"
	                                 "to see how\n"
	                                 "the window\n"
	                                 "becomes\n"
	                                 "scrollable.\n"
	                                 "\n"
	                                 "\n"
	                                 "Some more\n"
	                                 "text to be\n"
	                                 "sure it\n"
	                                 "overflows. :)");


	        printf("\n============================= 2");
	        	fflush(stdout);

}
