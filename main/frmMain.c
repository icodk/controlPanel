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

#include "dataStorage.h"

//#include "lvgl/examples/lv_examples.h"
//#include "lv_demos/lv_demo.h"
//#include "lv_drivers/win32drv/win32drv.h"

extern void test_function(void);
LV_FONT_DECLARE(DSEG7_classic_bold_25)
static lv_style_t style_panel = { 0 };
static lv_style_t style_data;
static lv_style_t style_label;

static const lv_font_t* font_large;
static const lv_font_t* font_normal;

static lv_obj_t* win=NULL;

static void init_styles(void) {

    // panel style
    if (style_panel.prop1 != 0) {
        return;
    }
    lv_style_init(&style_panel);

   // lv_style_set_text_font(&style_panel, font_large);
    lv_style_set_border_width(&style_panel, 1);
    lv_style_set_border_color(&style_panel, lv_palette_lighten(LV_PALETTE_GREEN, 1));
    lv_style_set_border_side(&style_panel, LV_BORDER_SIDE_LEFT| LV_BORDER_SIDE_TOP|LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT);
    lv_style_set_text_color(&style_panel, lv_color_black());

   // uint32_t  pad = lv_style_get_pad_left(&style_panel);
    lv_style_set_width(&style_panel, LV_SIZE_CONTENT);
    lv_style_set_height(&style_panel, LV_SIZE_CONTENT);
    lv_style_set_pad_all(&style_panel, 0);
    //lv_style_set_pad_top(&style_panel, 0);
    //lv_style_set_pad_bottom(&style_panel, 0);
    //lv_style_set_pad_left(&style_panel, 10);
    //lv_style_set_pad_right(&style_panel, 0);
    //lv_style_set_pad_ver(&style_panel, 0);
    //lv_style_set_pad_left(&style_panel, 0);

    // LABEL STYLE
    lv_style_init(&style_label);
    lv_style_set_pad_top(&style_label, 0);
    lv_style_set_pad_bottom(&style_label, 0);
    lv_style_set_pad_left(&style_label, 0);
    lv_style_set_pad_right(&style_label, 0);




    //  DATA STYLE
    lv_style_init(&style_data);
    //lv_style_set_text_font(&style_data, &lv_font_montserrat_18);
    lv_style_set_text_font(&style_data, &DSEG7_classic_bold_25);
   // test_function();
    /*Add outline*/
    lv_style_set_outline_width(&style_data, 1);
    //lv_style_set_outline_color(&style_data, lv_palette_main(LV_PALETTE_LIGHT_GREEN));
    lv_style_set_outline_pad(&style_data, 2);
    lv_style_set_pad_all(&style_data, 2);

    // text color
    //lv_style_set_text_color(&style_data, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_text_color(&style_data, lv_palette_lighten(LV_PALETTE_YELLOW,2));
    //lv_style_set_text_color(&style_data, lv_palette_lighten(LV_PALETTE_GREEN,5));
    //lv_style_set_text_color(&style_data, lv_palette_darken(LV_PALETTE_GREEN, 3));

    //lv_style_set_text_color(&style_data, lv_color_white());

    // background color
     lv_style_set_bg_color(&style_data, lv_color_black());
    //lv_style_set_bg_color(&style_data, lv_palette_main(LV_PALETTE_BLUE));
   // lv_style_set_bg_color(&style_data, lv_color_black());

    //lv_style_set_bg_color(&style_data,  lv_palette_main(LV_PALETTE_GREY));
    lv_style_set_bg_opa(&style_data, LV_OPA_100);
    //lv_style_set_pad_top(&style_data, 0);
    //lv_style_set_pad_bottom(&style_data, 0);
    //lv_style_set_pad_left(&style_data, 0);
    //lv_style_set_pad_right(&style_data, 0);




    font_large = LV_FONT_DEFAULT;
    font_normal = LV_FONT_DEFAULT;
}
static void event_handler(lv_event_t * e)
{
    lv_obj_t * obj = lv_event_get_target(e);
    LV_LOG_USER("Button %d clicked", lv_obj_get_child_id(obj));
    printf("Button %d clicked", lv_obj_get_child_id(obj));

}

static void drawFrmMain(){


	if (win != NULL) {
	        lv_obj_del(win);
	    }
	    win = lv_win_create(lv_scr_act(), 30);


	    // window content
	    lv_win_add_title(win, "Process");
	    // settings button
	    lv_obj_t* btn;
	    btn = lv_win_add_btn(win, LV_SYMBOL_SETTINGS, 40);
	    lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);


	    // PANEL
	    lv_obj_t* wcont = lv_win_get_content(win);  /*used to add content to the window*/
	    lv_obj_t* panel=lv_obj_create(wcont);
	    lv_obj_set_size(panel, 150, 40);
	    lv_obj_align(panel, LV_ALIGN_TOP_LEFT, 5, 5);
	    lv_obj_add_style(panel, &style_panel, 0);

	    // LABEL
	    lv_obj_t* label = lv_label_create(panel);
	    lv_label_set_text(label, "Temp 1:");
	    lv_obj_align(label, LV_ALIGN_LEFT_MID, 5, 0);
	    lv_obj_add_style(label, &style_label, 0);


	    // DATA
	    lv_obj_t* data= lv_label_create(panel);
	    int32_t *cVal= get_current_temp(REG_0);
	        (*cVal)++;


	        lv_label_set_text_fmt(data, "%d",*cVal);
	    //lv_label_set_text(data, "12.34:56");
	    lv_obj_align(data, LV_ALIGN_RIGHT_MID,-10, 0);
	    lv_obj_add_style(data, &style_data, 0);


}


static void timer_cb(lv_timer_t* timer)
{
    reg_id_t regId;
    drawFrmMain();
    //LV_LOG_USER("Timer was called ");
}


void frmMain_init(void)
{


    init_styles();
    drawFrmMain();
    lv_timer_create(timer_cb, 100, NULL);
//    //--prepare the main window
//    lv_obj_t * win = lv_win_create(lv_scr_act(), 30);
//    // window content
//    lv_win_add_title(win, "Process");
//    // settings button
//    lv_obj_t* btn;
//    btn = lv_win_add_btn(win, LV_SYMBOL_SETTINGS, 40);
//    lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
//
//
//    // PANEL
//    lv_obj_t* wcont = lv_win_get_content(win);  /*used to add content to the window*/
//    lv_obj_t* panel=lv_obj_create(wcont);
//    lv_obj_set_size(panel, 150, 40);
//    lv_obj_align(panel, LV_ALIGN_TOP_LEFT, 5, 5);
//    lv_obj_add_style(panel, &style_panel, 0);
//
//    // LABEL
//    lv_obj_t* label = lv_label_create(panel);
//    lv_label_set_text(label, "Temp 1:");
//    lv_obj_align(label, LV_ALIGN_LEFT_MID, 5, 0);
//    lv_obj_add_style(label, &style_label, 0);
//
//
//    // DATA
//    lv_obj_t* data= lv_label_create(panel);
//    lv_label_set_text(data, "12.3456");
//    lv_obj_align(data, LV_ALIGN_RIGHT_MID,-10, 0);
//    lv_obj_add_style(data, &style_data, 0);
//
//

}










void frmMain_1(void)
{


	printf("\n============================= 1");
	fflush(stdout);

	/*Create a window*/
	  lv_obj_t * win = lv_win_create(lv_scr_act(), 30);

	        lv_obj_t * btn;
//	        btn = lv_win_add_btn(win, LV_SYMBOL_LIST, 30);
//	        lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

	        lv_win_add_title(win, "Process");

//	        btn = lv_win_add_btn(win, LV_SYMBOL_BARS, 30);
//	        lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);

	        btn = lv_win_add_btn(win, LV_SYMBOL_SETTINGS, 40);
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
