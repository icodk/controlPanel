
/**
* @file lv_text_table.c
* Created: 2020-09-12
* by  ico
* text definitions
*/

/*********************
*      INCLUDES
*********************/
#include <stdint.h>
#include "text_table.h"




/*********************
*      DEFINES
*********************/

/**********************
*      TYPEDEFS
**********************/

/**********************
*  STATIC PROTOTYPES
**********************/



/**********************
*  STATIC VARIABLES
**********************/

//========== ENGLISH============
static const  char *  danish[] = {
	""
	,"Dansk"
    ,"Min"
    ,"Max"
    ,"Counter"
    ,"Reset"
    ,"Click Reset to reset counter."
    ,"Reset Counter: %d"
    ,"Config."
    ,"Param"
    ,"Process"
    ,"Menu"
    ,"Main Menu"

    ,"Decimal no."
    ,"String Param"
    ,"int param"
    ,"A sub menu"
    ,"Network"
    ,"System"
    ,"Info"
    ,"Wifi"
    ,"Ethernet"
    

};
//========== ENGLISH============
static const  char *  english[] = {
	""			//	0
	,"English"		//	1
    ,"Min"
    ,"Max"
    ,"Counter"
    ,"Reset Counter: %d"
    ,"Config."
    ,"Param"
    ,"Process"
    ,"Menu"
    ,"Main Menu"
    ,"Decimal no."
    ,"String Param"
    ,"int param"
    ,"A sub menu"
    ,"Network"
    ,"System"
    ,"Info"
    ,"Wifi"
    ,"Ethernet"

};


//-----------------------------------------------------
static const char *lang_symb[] = { "DK","EN" };
static const char **  lang_avail[] = {	(const   char **)danish,			// don't change the order here
										(const   char **)english,
									};

const  char *  * lang_table;
//----------------------------------------------------
//static const  text_ndx_t board_mode_text[] = { };
//----------------------------------------------------
//static const char *tempUnits[] = { "\337C","\337F" }; //
													  //----------------------------------------------------
//const char * getTempUnitText(temp_unitId_t tunits) {
//
//	//temp_units_t tunits=getCtlParam(BOARD_1,SYS_TEMP_UNIT);
//	return tempUnits[tunits];
//
//}
/**********************
*   STATIC FUNCTIONS
**********************/
static uint8_t  get_lang(void)
{
	return 0;
}

/**********************
*   GLOBAL FUNCTIONS
**********************/
void load_language(void)
{
	uint8_t  cLang = get_lang();
	//	BYTE buf[512];
	if (cLang >LANGUAGE_COUNT)
	{
		cLang = DEFAULT_LANG;

	}
	//NewLang=1;
	lang_table = (const char * *)lang_avail[cLang];
}
//------------------------------------
const  char *getLangName(text_ndx_t Ndx)
{
	const  char *  * tbl;
	tbl = (const char * *)lang_avail[Ndx];
	return (char  *)tbl[0];
}

//----------------------------------
//
// Return the two char current language symbol
//
const char *get_lang_symb(uint8_t id)
{
	return lang_symb[id];
}

//------------------------------------
const  char *get_text(text_ndx_t   Ndx)
{

	return (char *)lang_table[Ndx & 0x01FF]; // 9 bit text index the rest of the bits (7) are for numbers from 1 to 127

}

//-------------------------------------------------- EOF text_table.c

