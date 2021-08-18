
#ifndef LV_TEXT_TABLE_H
#define LV_TEXT_TABLE_H

#ifdef __cplusplus
extern "C" {
#endif
	/*********************
	*      INCLUDES
	*********************/
#include "dataStorage.h"
	/*********************
	*      DEFINES
	*********************/

#define LANGUAGE_COUNT  5		// number of languages

#define DEFAULT_LANG	0		// default language if not initialized

	/**********************
	*      TYPEDEFS
	**********************/


	typedef enum {
		T_NONE
		, T_LANG
		, T_MIN
        , T_MAX
        , T_COUNTER
        , T_RESET
        , T_CLICK_TO_RESET
        , T_RESET_COUNTER_X
        , T_CONFIG
        , T_PARAM
        , T_PROCESS
        , T_MENU
        , T_MAIN_MENU
        , T_DECIMAL_NUM
        , T_STRING_PARAM
        , T_INT_PARAM
        , T_SUB_MENU
        , T_NETWORK
        , T_SYSTEM
        , T_INFO


	} text_ndx_t;

	
	/**********************
	* GLOBAL PROTOTYPES
	**********************/
	
	void load_language(void);
	const  char *get_text(text_ndx_t  Ndx);
	
	


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*LV_TEXT_TABLE_H*/
