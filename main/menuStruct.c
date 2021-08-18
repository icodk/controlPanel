/*
 * menuStruct.c
 *
 *  Created on: 11. aug. 2021
 *      Author: ico
 */

 /* INCLUDES  -------------------------------------------------------------------*/

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
//static const menuItem_t menuOnOff[];
//static const menuItem_t	menuTempSettings[];
//static const menuItem_t menuHumidSettings[];
//static const menuItem_t setTimersMenu[];
//static const menuItem_t menuService[];
//static const menuItem_t menuInstallation[];
//static const menuItem_t menuDustAuto[];
//static const menuItem_t menuDrainAuto[];

//------ MAIN MENU
static const menuItem_t menuMain[] = {
    {MENU_ITEM_TYPE_MAIN_MENU_HEADER,	T_NONE,	menuMain,						EE_NDX_NONE,ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        //{MENU_ITEM_TYPE_COMMAND,			T_EXIT, 				application_init,		EE_NDX_NONE,ACCESS_LEVEL_0,	NULL,NULL},
        //{MENU_ITEM_TYPE_SET_CONTROL_MODE,	T_A_ONOFF, 				menuOnOff,			BOARD_MODE_ON_OFF,	ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        //{MENU_ITEM_TYPE_SET_CONTROL_MODE,	T_B_TEMPERATURE, 		menuTempSettings,	BOARD_MODE_TEMP,	ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        //{MENU_ITEM_TYPE_SET_CONTROL_MODE,	T_C_HUMIDITY, 			menuHumidSettings,	BOARD_MODE_HUMIDITY,ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        //{MENU_ITEM_TYPE_SUB_MENU, 			T_D_TIMER, 				setTimersMenu,		EE_NDX_NONE,			ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        //{MENU_ITEM_TYPE_SUB_MENU, 			T_X_SERVICE, 			menuService,		EE_NDX_NONE,			ACCESS_LEVEL_0,NO_MIN,NO_MAX},
        //	{MENU_ITEM_TYPE_SUB_MENU, 			T_Y_CONTROLLER_TIMERS, 	menuInstallation,	EE_NDX_NONE,			ACCESS_LEVEL_2,NO_MIN,NO_MAX},
        //	{MENU_ITEM_TYPE_SUB_MENU, 			T_Z_INSTALLATION, 	menuInstallation,		EE_NDX_NONE,			ACCESS_LEVEL_2,NO_MIN,NO_MAX},
    {MENU_ITEM_TYPE_END_OF_MENU, T_NONE		, NULL,EE_NDX_NONE,ACCESS_LEVEL_0,NO_MIN,NO_MAX} };


