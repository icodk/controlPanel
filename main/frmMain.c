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


static void resetMsgBox_event_cb(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_current_target(e);
    //LV_LOG_USER("Button %s clicked", lv_msgbox_get_active_btn_text(obj));
    LV_LOG_USER("Event code: %d ",e->code );

    if (e->code == LV_EVENT_DELETE) {

            return;
   }
   else { // reset was pressed

        int32_t* cVal = get_current_temp((reg_id_t)(e->user_data));
        (*cVal)=0;
       lv_msgbox_close(obj);

   }



    /*if (e->code == LV_EVENT_DELETE) {
        msgBoxOn = false;
    }else

    }*/
}
//------------------






void resetMsgBox(lv_event_t* e)
{
	 static const char* btns[] = { "Reset", "" };

	    lv_obj_t* mbox1 = lv_msgbox_create(NULL, "Reset Counter", "Click Reset to reset counter.", btns, true);
	    //mbox1->user_data = 1;
	    lv_label_set_text_fmt(lv_msgbox_get_title(mbox1), "Reset Counter: %d",1+ (int)e->user_data);
	    lv_obj_add_event_cb(mbox1, resetMsgBox_event_cb, LV_EVENT_VALUE_CHANGED, e->user_data);
	    lv_obj_add_event_cb(mbox1, resetMsgBox_event_cb, LV_EVENT_DELETE/*LV_EVENT_ALL*/, e->user_data);
	    //lv_obj_add_event_cb(mbox1, msgBox_event_cb, LV_EVENT_CLICKED, NULL);
	    //lv_obj_set_style_border_width(mbox1, LV_PART_MAIN, LV_STATE_DEFAULT, 2);
	    lv_obj_set_style_border_width(mbox1, 5, LV_STATE_DEFAULT);
	    lv_obj_set_style_border_color(mbox1, lv_palette_main(LV_PALETTE_RED), LV_PART_MAIN);

	    lv_obj_center(mbox1);
}

static void cfg_btn_event_handler(lv_event_t * e)
{
	lv_obj_t * obj = lv_event_get_target(e);
	    LV_LOG_USER("Event code %d", e->code);
	    //resetMsgBox();
}


static void drawFrmMain(){

	    win = lv_win_create(lv_scr_act(), 30);


	    // window content
	    lv_win_add_title(win, "Process");
	    // settings button
	    lv_obj_t* btn;
	    btn = lv_win_add_btn(win, LV_SYMBOL_SETTINGS, 40);
	    //lv_obj_add_event_cb(btn, event_handler, LV_EVENT_CLICKED, NULL);
	    lv_obj_add_event_cb(btn, cfg_btn_event_handler, LV_EVENT_CLICKED, NULL);

	    for (int i = 0; i < REGULATOR_COUNT; i++) {
	            // PANEL
	            lv_obj_t* wcont = lv_win_get_content(win);  /*used to add content to the window*/
	            lv_obj_t* panel = lv_obj_create(wcont);
	            lv_obj_set_size(panel, 250, 40);
	            lv_obj_align(panel, LV_ALIGN_TOP_LEFT,5, i*50 + 5);
	            lv_obj_add_style(panel, &style_panel, 0);
	            lv_obj_add_event_cb(panel, resetMsgBox, LV_EVENT_LONG_PRESSED, (void *)i);

	            // LABEL
	            lv_obj_t* label = lv_label_create(panel);
	            lv_label_set_text_fmt(label, "Counter %d ",i+1);

	            lv_obj_align(label, LV_ALIGN_LEFT_MID, 5, 0);
	            lv_obj_add_style(label, &style_label, 0);


	            // DATA
	            temp_regulator_t* reg = get_reguator(i);
	            reg->displayField = lv_label_create(panel);


	            //
	            //lv_label_set_text_fmt(reg->displayField, "%d",*cVal);
	            lv_obj_align(reg->displayField, LV_ALIGN_RIGHT_MID, -10, 0);
	            lv_obj_add_style(reg->displayField, &style_data, 0);
	        }



}


static void     updateFrmMain(void) {

	 for (int i = 0; i < REGULATOR_COUNT; i++) {
		temp_regulator_t* reg = get_reguator(i);
		int32_t* cVal = get_current_temp(i);
		(*cVal)++;
		lv_label_set_text_fmt(reg->displayField, "%d", *cVal);
	}


}

static void timer_cb(lv_timer_t* timer)
{
    //reg_id_t regId;
    updateFrmMain();
    //LV_LOG_USER("Timer was called ");
}


void frmMain_init(void)
{


    init_styles();
    drawFrmMain();
    lv_timer_create(timer_cb, 100, NULL);


}










