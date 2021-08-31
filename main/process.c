/*
 * process.c
 *
 *  Created on: 31. jul. 2021
 *      Author: ico
 */


#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_freertos_hooks.h"
#include "freertos/semphr.h"
#include "esp_system.h"
#include "driver/gpio.h"


/* Littlevgl specific */
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif


#include "lvgl_helpers.h"
#include "ui_common.h"
#include "dataStorage.h"



void processMain(void){ // called by guiTask() repeatedly
//	time_t now;
//	char strftime_buf[64];
//	struct tm timeinfo;
//
//	time(&now);
//	// Set timezone to China Standard Time
//	setenv("TZ", "UTC+2", 1);
//	tzset();
//
//	localtime_r(&now, &timeinfo);
//	strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
//	//printf("\n%s", strftime_buf);
//

	for (int i = 0; i < COUNTER_COUNT; i++) {
	        //counter_t* cnt= get_counter(i);
	        int32_t* cVal = get_current_count(i);
	        (*cVal)++;
	}


}
