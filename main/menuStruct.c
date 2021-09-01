/*
 * menuStruct.c
 *
 *  Created on: Apr 22, 2020
 *      Author: ico
 */



 /* INCLUDES  -------------------------------------------------------------------*/
#include <limits.h>
#include "menu.h"
//#include "frmProcess.h"
#include "text_table.h"
#include "network.h"
/* MACROS    -------------------------------------------------------------------*/

/* CONSTANTS -------------------------------------------------------------------*/

/* TYPEDEFS  -------------------------------------------------------------------*/

/* GLOBAL VARIABLES ------------------------------------------------------------*/

/* EXTERNAL VARIABLES ----------------------------------------------------------*/

/* EXTERNAL FUNCTIONS -----------------------------------------------------------*/


/* LOCAL PROTOTYPES--------------------------------------------------------------*/
//static const menuItem_t menuMain[];
#ifdef _MSC_VER
extern const menuItem_t networkMenu[];
extern const menuItem_t systemMenu[];
#else
static  const menuItem_t networkMenu[];
static  const menuItem_t systemMenu[];
#endif
//static const menuItem_t	menuTempSettings[];
//static const menuItem_t menuHumidSettings[];
//static const menuItem_t setTimersMenu[];
//static const menuItem_t menuService[];
//static const menuItem_t menuInstallation[];
//static const menuItem_t menuDustAuto[];
//static const menuItem_t menuDrainAuto[];
//static bool hidenItem(void) {
//    return false;
//}
//------ MAIN MENU
static const menuItem_t mainMenu[] = {
    {MENU_ITEM_TYPE_MENU_HEADER,	T_MAIN_MENU,            NULL, SHOW_ITEM,   EE_NDX_NONE,ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SYS_NUM_DEC1,	T_PARAM, 	        NULL, SHOW_ITEM, 		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_INT32, T_PARAM,                     NULL, SHOW_ITEM,  EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SUB_MENU, T_SYSTEM,    systemMenu,  SHOW_ITEM,  EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        { MENU_ITEM_TYPE_INFO_VERSION, T_INFO,       NULL,  SHOW_ITEM, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        
    {MENU_ITEM_TYPE_END_OF_MENU, T_NONE		, NULL, SHOW_ITEM, EE_NDX_NONE,ACCESS_LEVEL_0,NO_MIN,NO_MAX} };


static const menuItem_t systemMenu[] = {
{MENU_ITEM_TYPE_MENU_HEADER, T_SYSTEM, mainMenu, SHOW_ITEM,  EE_NDX_NONE, ACCESS_LEVEL_0, NO_MIN, NO_MAX},
    {MENU_ITEM_TYPE_NETWORK_FORM, T_NETWORK,       networkMenu, SHOW_ITEM,  EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
    { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_STRING_PARAM, NULL, SHOW_ITEM,  EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX },
    { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL, SHOW_ITEM, 		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX },
    { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_INT_PARAM, NULL, SHOW_ITEM,  EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX },
    { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL, SHOW_ITEM, 		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX },
    { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL, SHOW_ITEM, 		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX },
    { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL, SHOW_ITEM, 		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX },
    { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL, SHOW_ITEM, 		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX },
{ MENU_ITEM_TYPE_END_OF_MENU, T_NONE		, NULL, SHOW_ITEM, EE_NDX_NONE,ACCESS_LEVEL_0,NO_MIN,NO_MAX } };




static const menuItem_t networkMenu[] = {

{MENU_ITEM_TYPE_MENU_HEADER, T_NETWORK,         systemMenu, SHOW_ITEM,  EE_NDX_NONE, ACCESS_LEVEL_0, NO_MIN, NO_MAX},
        {MENU_ITEM_TYPE_FUNCTION, T_WIFI,       wifi_AP_cfg_init, isWifisupported,  EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_FUNCTION, T_ETHERNET,   ethernet_cfg_init, isEthernetSupported,  EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},


{ MENU_ITEM_TYPE_END_OF_MENU, T_NONE		, NULL, SHOW_ITEM, EE_NDX_NONE,ACCESS_LEVEL_0,NO_MIN,NO_MAX } };








/* PUBLIC FUNCTIONS --------------------------------------------------------------*/
const menuItem_t* get_main_menu(void) {

    return mainMenu;
}
