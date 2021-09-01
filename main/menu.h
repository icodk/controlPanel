#pragma once

#include "text_table.h"


typedef enum {
    //MENU_ITEM_TYPE_MAIN_MENU_HEADER
     MENU_ITEM_TYPE_MENU_HEADER
    , MENU_ITEM_TYPE_END_OF_MENU
    , MENU_ITEM_TYPE_SUB_MENU
    , MENU_ITEM_TYPE_NETWORK_FORM
    , MENU_ITEM_TYPE_EXIT
    , MENU_ITEM_TYPE_COMMAND
    , MENU_ITEM_TYPE_FUNCTION
    , MENU_ITEM_TYPE_YES_NO_DLG				// YES_NO_DLG
    , MENU_ITEM_TYPE_SYS_YES_NO_DLG

    , MENU_ITEM_TYPE_ON_OFF_DLG
    , MENU_ITEM_TYPE_SYS_ON_OFF_DLG

    , MENU_ITEM_TYPE_SYS_NUM_INT

    , MENU_ITEM_TYPE_TIME_DLG
    , MENU_ITEM_TYPE_SYS_TIME_DLG
    , MENU_ITEM_TYPE_DATE_TIME_DLG

    //,MENU_ITEM_TYPE_DLG
    , MENU_ITEM_TYPE_TEMP_DLG
    , MENU_ITEM_TYPE_HUM_DLG
    , MENU_ITEM_TYPE_NUM_DLG
    , MENU_ITEM_TYPE_MULTI_DLG
    , MENU_ITEM_TYPE_ACCESS_LEVEL
    , MENU_ITEM_TYPE_INFO_VERSION


    , MENU_ITEM_TYPE_SYS_NUM_DEC1
    , MENU_ITEM_TYPE_SYS_NUM_DEC2

    , MENU_ITEM_TYPE_INT32
    , MENU_ITEM_TYPE_SET_CONTROL_MODE
    , MENU_ITEM_TYPE_SET_TIMER

} menuItemType_t;

typedef enum {
    ACCESS_LEVEL_0
    , ACCESS_LEVEL_1
    , ACCESS_LEVEL_2
    //,ACCESS_LEVEL_3
}access_level_t;


typedef  struct _MENU_ITEM
{
    const menuItemType_t menuItemType;
    const text_ndx_t menuItemText;
    const void* menuItemPntr;
    const void* visableFncPtr;           // pointer to a function that returns bool true if item should be shown
    const uint16_t eeNdx;				//EE location
    const access_level_t accesslevel;
    const int32_t minVal;
    const int32_t maxVal;

} menuItem_t;


// menu item configuration
#define  MIN_VAL_ZERO	(uint8_t)0
#define  MAX_VAL_255	(uint8_t)255
#define  MAX_SKRAP_FILTER_3	(uint8_t)3
#define  HEADER_NO_TXT	1000
#define	EE_NDX_NONE	(uint8_t)0
#define	NO_MIN		INT_MIN
#define	NO_MAX		INT_MAX

#define	SHOW_ITEM   NULL




void frmMenu_init(void);
const menuItem_t* get_main_menu(void);
