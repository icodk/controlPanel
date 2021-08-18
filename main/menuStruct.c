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

//------ MAIN MENU
static const menuItem_t mainMenu[] = {
    {MENU_ITEM_TYPE_MENU_HEADER,	T_MAIN_MENU,         NULL,   EE_NDX_NONE,ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SYS_NUM_DEC1,	T_PARAM, 	NULL,		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_PARAM,      NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SUB_MENU, T_SYSTEM,       systemMenu, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
         { MENU_ITEM_TYPE_INFO_VERSION, T_INFO,       NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        /*
        {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_STRING_PARAM, NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL,		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_INT_PARAM, NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_SUB_MENU, NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_PARAM, NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SYS_NUM_DEC1,   T_PARAM, NULL,		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_PARAM, NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_PARAM, NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_PARAM, NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_PARAM, NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_PARAM, NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_PARAM, NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        //{MENU_ITEM_TYPE_SET_CONTROL_MODE,	T_A_ONOFF, 				menuOnOff,			BOARD_MODE_ON_OFF,	ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        //{MENU_ITEM_TYPE_SET_CONTROL_MODE,	T_B_TEMPERATURE, 		menuTempSettings,	BOARD_MODE_TEMP,	ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        //{MENU_ITEM_TYPE_SET_CONTROL_MODE,	T_C_HUMIDITY, 			menuHumidSettings,	BOARD_MODE_HUMIDITY,ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        //{MENU_ITEM_TYPE_SUB_MENU, 			T_D_TIMER, 				setTimersMenu,		EE_NDX_NONE,			ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        //{MENU_ITEM_TYPE_SUB_MENU, 			T_X_SERVICE, 			menuService,		EE_NDX_NONE,			ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        //	{MENU_ITEM_TYPE_SUB_MENU, 			T_Y_CONTROLLER_TIMERS, 	menuInstallation,	EE_NDX_NONE,			ACCESS_LEVEL_2,NO_MIN,NO_MAX},
        //	{MENU_ITEM_TYPE_SUB_MENU, 			T_Z_INSTALLATION, 	menuInstallation,		EE_NDX_NONE,			ACCESS_LEVEL_2,NO_MIN,NO_MAX},
*/
    {MENU_ITEM_TYPE_END_OF_MENU, T_NONE		, NULL,EE_NDX_NONE,ACCESS_LEVEL_0,NO_MIN,NO_MAX} };


static const menuItem_t systemMenu[] = {
{MENU_ITEM_TYPE_MENU_HEADER, T_SYSTEM, mainMenu, EE_NDX_NONE, ACCESS_LEVEL_0, NO_MIN, NO_MAX},
    {MENU_ITEM_TYPE_SUB_MENU, T_NETWORK,       networkMenu, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX},
    { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_STRING_PARAM, NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX },
    { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL,		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX },
    { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_INT_PARAM, NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX },
    { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL,		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX },
    { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL,		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX },
    { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL,		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX },
    { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL,		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX },
{ MENU_ITEM_TYPE_END_OF_MENU, T_NONE		, NULL,EE_NDX_NONE,ACCESS_LEVEL_0,NO_MIN,NO_MAX } };




static const menuItem_t networkMenu[] = {

{MENU_ITEM_TYPE_MENU_HEADER, T_NETWORK, systemMenu, EE_NDX_NONE, ACCESS_LEVEL_0, NO_MIN, NO_MAX},
        { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_STRING_PARAM, NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX },
        { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL,		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX },
        { MENU_ITEM_TYPE_SYS_NUM_DEC1, T_INT_PARAM, NULL, EE_NDX_NONE, ACCESS_LEVEL_0,NO_MIN,NO_MAX },
         {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL,		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX},
          {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL,		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX},
           {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL,		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX},
            {MENU_ITEM_TYPE_SYS_NUM_DEC1, T_DECIMAL_NUM, 				    NULL,		EE_NDX_NONE,ACCESS_LEVEL_0,	NO_MIN,NO_MAX},
{ MENU_ITEM_TYPE_END_OF_MENU, T_NONE		, NULL,EE_NDX_NONE,ACCESS_LEVEL_0,NO_MIN,NO_MAX } };








/* PUBLIC FUNCTIONS --------------------------------------------------------------*/
const menuItem_t* get_main_menu(void) {

    return mainMenu;
}
