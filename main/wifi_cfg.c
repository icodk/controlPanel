
/*
 * wifi_cfg.c
 *
 *  Created on: 19. aug. 2021
 *      Author: ico
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_log.h"
#include "esp_event.h"
#include "nvs_flash.h"
#include "lvgl/lvgl.h"
#include "dataStorage.h"
#include "ui_common.h"
#include "text_table.h"


#define DEFAULT_SCAN_LIST_SIZE CONFIG_WIFI_PROV_SCAN_MAX_ENTRIES //CONFIG_EXAMPLE_SCAN_LIST_SIZE

static const char *TAG = "wifi_scan";
static void wifi_scan(void)
{
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    uint16_t number = DEFAULT_SCAN_LIST_SIZE;
    wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
    uint16_t ap_count = 0;
    memset(ap_info, 0, sizeof(ap_info));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
    esp_wifi_scan_start(NULL, true);
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
    ESP_LOGI(TAG, "Total APs scanned = %u", ap_count);
    for (int i = 0; (i < DEFAULT_SCAN_LIST_SIZE) && (i < ap_count); i++) {
        ESP_LOGI(TAG, "SSID \t\t%s", ap_info[i].ssid);
        ESP_LOGI(TAG, "RSSI \t\t%d", ap_info[i].rssi);
        printf("SSID \t\t%s RSSI \t\t%d",ap_info[i].ssid,ap_info[i].rssi);
        //print_auth_mode(ap_info[i].authmode);
        //printf("\nAuth. mode: %d",ap_info[i].authmode);
        if (ap_info[i].authmode != WIFI_AUTH_WEP) {
            //print_cipher_type(ap_info[i].pairwise_cipher, ap_info[i].group_cipher);
           // printf("\nCipher: %d %d",ap_info[i].pairwise_cipher,ap_info[i].group_cipher);
        }
        ESP_LOGI(TAG, "Channel \t\t%d\n", ap_info[i].primary);
    }

}





void wifi_AP_cfg_init(void) {

	printf("Wifi_AP_cfg_init()\n");
}

void wifi_ST_cfg_init(void) {

	printf("Wifi_ST_cfg_init()\n");
	wifi_scan();

}


bool isWifisupported(void) {
    return true;
}

