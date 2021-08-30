

#include "lvgl/lvgl.h"
#include "dataStorage.h"
#include "ui_common.h"

const char* NUMERIC_RANGE = "0123456789";

LV_FONT_DECLARE(DSEG7_classic_bold_25);
static lv_style_t style_panel = { 0 };
static lv_style_t style_data;
static lv_style_t style_label;

static const lv_font_t* font_large;
static const lv_font_t* font_normal;
static lv_obj_t* win = NULL;
static lv_obj_t* win_title = NULL;
static lv_timer_t* updateTimer = NULL;


static void init_common_styles(void) {

    // panel style
    if (style_panel.prop1 != 0) {
        return;
    }
    lv_style_init(&style_panel);

    // lv_style_set_text_font(&style_panel, font_large);
    lv_style_set_border_width(&style_panel, 1);
    lv_style_set_border_color(&style_panel, lv_palette_lighten(LV_PALETTE_GREEN, 1));
    lv_style_set_border_side(&style_panel, LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_TOP | LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_RIGHT);
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
    /*Add outline*/
    lv_style_set_outline_width(&style_data, 1);
    lv_style_set_outline_color(&style_data, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_outline_pad(&style_data, 2);
    lv_style_set_pad_all(&style_data, 2);

    //lv_style_set_text_color(&style_data, lv_palette_main(LV_PALETTE_GREEN));
    //lv_style_set_text_color(&style_data, lv_palette_lighten(LV_PALETTE_GREEN, 2));
    lv_style_set_text_color(&style_data, lv_palette_lighten(LV_PALETTE_YELLOW, 2));
    // lv_style_set_bg_color(&style_data, lv_color_black());
     //lv_style_set_bg_color(&style_data, lv_palette_main(LV_PALETTE_RED));
    lv_style_set_bg_color(&style_data, lv_color_black());
    lv_style_set_bg_opa(&style_data, LV_OPA_100);
    //lv_style_set_pad_top(&style_data, 0);
    //lv_style_set_pad_bottom(&style_data, 0);
    //lv_style_set_pad_left(&style_data, 0);
    //lv_style_set_pad_right(&style_data, 0);




    font_large = LV_FONT_DEFAULT;
    font_normal = LV_FONT_DEFAULT;
}
//----------------------------------------------
lv_obj_t** get_main_win_title(void) {

    return &win_title;
}

//----------------------------------------------
lv_obj_t* get_main_win(void) {

    return win;
}

//----------------------------------------------
void ui_common_init(void) {
    win= lv_win_create(lv_scr_act(), 30);
    
    init_common_styles();
}
//----------------------------------------------
lv_style_t* get_style_panel(void) {
    return &style_panel;
}
//----------------------------------------------
lv_style_t* get_style_label(void) {
return &style_label;
}
//----------------------------------------------
lv_style_t* get_style_data(void) {
    return &style_data;
}
//----------------------------------------------
lv_timer_t** get_updateTimer(void) {
    return &updateTimer;
}
//----------------------------------------------
