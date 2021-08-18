/*
 * menu.c
 *
 *  Created on: 11. aug. 2021
 *      Author: ico
 */


/*
File: menu.c
Date: 2021-08-08


*/



#include "lvgl/lvgl.h"
#include "dataStorage.h"
#include "ui_common.h"
#include "text_table.h"
#include "menu.h"
//----------------------------------------
//----------------------------------------
 extern void  frmProcess_init(void);

static lv_obj_t* menuList;
static int event_count[45];


//----------------------------------------
//
static void back_btn_event_handler(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    LV_LOG_USER("Event code %d", e->code);
    //resetMsgBox();

}
//----------------------------------------

static void home_btn_event_handler(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    LV_LOG_USER("Event code %d", e->code);
    frmProcess_init();
    //resetMsgBox();

}
//----------------------------------------
static void scroll_up_btn_event_handler(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    LV_LOG_USER("Event code %d", e->code);
    //resetMsgBox();
     lv_obj_t* win = get_main_win();
     lv_obj_t* wcont = lv_win_get_content(win);
    //lv_list_up(menuList);
    lv_obj_scroll_by(menuList,0, 200, LV_ANIM_ON);
    //lv_obj_scroll_to_view(wcont, LV_ANIM_ON);
}
//----------------------------------------
static void scroll_down_btn_event_handler(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    LV_LOG_USER("Event code %d", e->code);
    lv_obj_t* win = get_main_win();
    lv_obj_t* wcont = lv_win_get_content(win);
    lv_obj_scroll_by(menuList, 0,  -200, LV_ANIM_ON);
    //lv_obj_scroll_to_view(wcont, LV_ANIM_ON);
    //lv_list_down(menuList);
    //resetMsgBox();

}
//----------------------------------------

//
//static void menuList_scroll_event_cb(lv_event_t* e) {
//
//    lv_obj_t* obj = lv_event_get_target(e);
//    event_count[e->code]++;
//    //if ((e->code == 9) || (e->code == 10) || (e->code == 11)) {
//
//        LV_LOG_USER("Event code %d", e->code);
//    //}
//   /* lv_event_t e_data;
//    e_data.code = LV_EVENT_SCROLL;
//    lv_event_send(&menuList, LV_EVENT_SCROLL, &e_data);*/
//
//}
//


#define ITEM_CNT 20

static void draw_event_cb(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    lv_obj_draw_part_dsc_t* dsc = lv_event_get_draw_part_dsc(e);
    //if (e->code != 27) {
        LV_LOG_USER("Event code %d", e->code);
    //}

    /*If the cells are drawn...*/
    if (dsc->part == LV_PART_ITEMS) {
        bool chk = lv_table_has_cell_ctrl(obj, dsc->id, 0, LV_TABLE_CELL_CTRL_CUSTOM_1);

        lv_draw_rect_dsc_t rect_dsc;
        lv_draw_rect_dsc_init(&rect_dsc);
        rect_dsc.bg_color = chk ? lv_theme_get_color_primary(obj) : lv_palette_lighten(LV_PALETTE_GREY, 2);
        rect_dsc.radius = LV_RADIUS_CIRCLE;

        lv_area_t sw_area;
        sw_area.x1 = dsc->draw_area->x2 - 50;
        sw_area.x2 = sw_area.x1 + 40;
        sw_area.y1 = dsc->draw_area->y1 + lv_area_get_height(dsc->draw_area) / 2 - 10;
        sw_area.y2 = sw_area.y1 + 20;
        lv_draw_rect(&sw_area, dsc->clip_area, &rect_dsc);

        rect_dsc.bg_color = lv_color_white();
        if (chk) {
            sw_area.x2 -= 2;
            sw_area.x1 = sw_area.x2 - 16;
        }
        else {
            sw_area.x1 += 2;
            sw_area.x2 = sw_area.x1 + 16;
        }
        sw_area.y1 += 2;
        sw_area.y2 -= 2;
        lv_draw_rect(&sw_area, dsc->clip_area, &rect_dsc);
    }
}

static void change_event_cb(lv_event_t* e)
{
    lv_obj_t* obj = lv_event_get_target(e);
    uint16_t col;
    uint16_t row;
    lv_table_get_selected_cell(obj, &row, &col);
    bool chk = lv_table_has_cell_ctrl(obj, row, 0, LV_TABLE_CELL_CTRL_CUSTOM_1);
    if (chk) lv_table_clear_cell_ctrl(obj, row, 0, LV_TABLE_CELL_CTRL_CUSTOM_1);
    else lv_table_add_cell_ctrl(obj, row, 0, LV_TABLE_CELL_CTRL_CUSTOM_1);
}


//----------------------------------------
static void menuDraw(lv_obj_t* win) {

    /*Measure memory usage*/
    lv_mem_monitor_t mon1;
    lv_mem_monitor(&mon1);

    uint32_t t = lv_tick_get();
    lv_obj_t* wcont = lv_win_get_content(win);  /*used to add content to the window*/
    lv_obj_set_style_pad_top(wcont, 0, LV_PART_MAIN);
    lv_obj_set_style_pad_bottom(wcont, 0, LV_PART_MAIN);
   /* lv_obj_set_height_margin(wcont, 0);
    lv_obj_set_width_margin(wcont, 0);*/


    menuList = lv_table_create(wcont);
    //lv_obj_set_style_pad_top(menuList, 0, LV_PART_MAIN);
   // lv_obj_set_style_pad_row(menuList, 0, LV_PART_MAIN);
    //lv_obj_set_style_pad_bottom(menuList, 0, LV_PART_MAIN);
    lv_obj_set_style_bg_color(menuList, lv_palette_main(LV_PALETTE_ORANGE), LV_PART_MAIN);
    //lv_obj_set_style_padding(menuList, 0, LV_PART_MAIN);
    /*Set a smaller height to the table. It'll make it scrollable*/
    //lv_obj_set_size(table, LV_SIZE_CONTENT, 300);
    //lv_obj_set_size(menuList, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    //lv_obj_set_size(menuList, LV_SIZE_CONTENT, 190);
    lv_obj_set_height(menuList, lv_pct(100));
    lv_table_set_col_width(menuList, 0, 250);
    lv_table_set_row_cnt(menuList, ITEM_CNT); /*Not required but avoids a lot of memory reallocation lv_table_set_set_value*/
    lv_table_set_col_cnt(menuList, 1);

    /*Don't make the cell pressed, we will draw something different in the event*/
   // lv_obj_remove_style(menuList, NULL, LV_PART_ITEMS | LV_STATE_PRESSED);

    uint32_t i;
    for (i = 0; i < ITEM_CNT; i++) {
        lv_table_set_cell_value_fmt(menuList, i, 0, "Item %d", i + 1);

    }

    //lv_obj_align(table, LV_ALIGN_CENTER, 0, -20);
    //lv_obj_align(menuList, LV_ALIGN_OUT_TOP_LEFT, -10, -35);
    lv_obj_center(menuList);
    /*Add an event callback to to apply some custom drawing*/
    lv_obj_add_event_cb(menuList, draw_event_cb, LV_EVENT_DRAW_PART_END, NULL);
    lv_obj_add_event_cb(menuList, change_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
    //lv_obj_add_event_cb(menuList, menuList_scroll_event_cb, LV_EVENT_ALL, NULL);

    //lv_mem_monitor_t mon2;
    //lv_mem_monitor(&mon2);

    //uint32_t mem_used = mon1.free_size - mon2.free_size;

    //uint32_t elaps = lv_tick_elaps(t);

    //lv_obj_t* label = lv_label_create(lv_scr_act());
    //lv_label_set_text_fmt(label, "%d items were created in %d ms\n"
    //    "using %d bytes of memory",
    //    ITEM_CNT, elaps, mem_used);

    //lv_obj_align(label, LV_ALIGN_BOTTOM_MID, 0, -10);


}



//----------------------------------------
void frmMenu_init(void) {

    lv_obj_t* win = get_main_win();
    lv_obj_del(win);
    win = lv_win_create(lv_scr_act(), 30);
   /*
   drawFrmProcess(win);
    lv_timer_t** tmr = get_updateTimer();
    *tmr = lv_timer_create(timer_cb, 100, NULL);
    */

    lv_win_add_title(win, get_text(T_MENU));

    lv_obj_t*  btn = lv_win_add_btn(win, LV_SYMBOL_LEFT, 40);
    lv_obj_add_event_cb(btn, back_btn_event_handler, LV_EVENT_CLICKED, NULL);

    btn = lv_win_add_btn(win, LV_SYMBOL_UP, 40);
    lv_obj_add_event_cb(btn, scroll_up_btn_event_handler, LV_EVENT_CLICKED, NULL);

    btn = lv_win_add_btn(win, LV_SYMBOL_DOWN, 40);
    lv_obj_add_event_cb(btn, scroll_down_btn_event_handler, LV_EVENT_CLICKED, NULL);

    btn = lv_win_add_btn(win, LV_SYMBOL_HOME, 40);
    lv_obj_add_event_cb(btn, home_btn_event_handler, LV_EVENT_CLICKED, NULL);

    menuDraw(win);


}
