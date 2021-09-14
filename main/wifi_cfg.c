
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
#include "esp_netif.h"
#include "esp_eth.h"

#include "nvs_flash.h"



#include "lvgl/lvgl.h"
#include "dataStorage.h"
#include "ui_common.h"
#include "text_table.h"


#define DEFAULT_SCAN_LIST_SIZE CONFIG_WIFI_PROV_SCAN_MAX_ENTRIES //CONFIG_EXAMPLE_SCAN_LIST_SIZE
#define WIFI_CONNECTED_BIT	 	BIT0
#define WIFI_FAIL_BIT      		BIT1
#define WIFI_SCAN_END_BIT      	BIT2
#define WIFI_DISCONNECTED_BIT 	BIT3
static EventGroupHandle_t event_group_bits; //FreeRTOS facilitate event bits as flags
static const char *TAG = "wifi_cfg";
typedef enum _NETWORK_STATE{
		NETWORK_INIT
		,NETWORK_WIFI_CONNECING
		,NETWORK_WIFI_CONNECTED
		,NETWORK_WIFI_SCAN_START
		,NETWORK_WIFI_SCANNING
} network_state_t;
static network_state_t net_state=NETWORK_INIT;
static lv_obj_t* dd_list;
static wifi_event_t last_event_id=WIFI_EVENT_STA_DISCONNECTED;
//------------------------------------------------------------
//static void scan_results(void){
//
//	    uint16_t number = DEFAULT_SCAN_LIST_SIZE;
//	    wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
//	    uint16_t ap_count = 0;
//	    memset(ap_info, 0, sizeof(ap_info));
//
//		ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
//	    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
//	    ESP_LOGI(TAG, "Total APs scanned = %u", ap_count);
//	    for (int i = 0; (i < DEFAULT_SCAN_LIST_SIZE) && (i < ap_count); i++) {
//	       // ESP_LOGI(TAG, "SSID %s", ap_info[i].ssid);
//	       // ESP_LOGI(TAG, "RSSI %d", ap_info[i].rssi);
//	        printf("SSID: %s RSSI: %d\n",ap_info[i].ssid,ap_info[i].rssi);
//	        //print_auth_mode(ap_info[i].authmode);
//	        //printf("\nAuth. mode: %d",ap_info[i].authmode);
//	        if (ap_info[i].authmode != WIFI_AUTH_WEP) {
//	            //print_cipher_type(ap_info[i].pairwise_cipher, ap_info[i].group_cipher);
//	           // printf("\nCipher: %d %d",ap_info[i].pairwise_cipher,ap_info[i].group_cipher);
//	        }
//	        //ESP_LOGI(TAG, "Channel \t\t%d\n", ap_info[i].primary);
//	    }
//
//
//}


//--------------------------------------
static void network_conn_event_handler(void* arg, esp_event_base_t event_base,
                                int32_t event_id, void* event_data)
{
	ip_event_got_ip_t* ip_event;
	printf("New Network Event Base: %s. Event Id:%d\n",event_base,event_id );
	//ESP_LOGI(TAG, "New Network Event Base: %s. Event Id:%d",event_base,event_id );


	if(event_base==WIFI_EVENT){
				switch(event_id ){
				case WIFI_EVENT_STA_START:
					printf("Event: WIFI_EVENT_STA_START\n" );
					esp_wifi_connect();
					net_state=NETWORK_WIFI_CONNECING;
					break;
				case	WIFI_EVENT_STA_CONNECTED:
						net_state=NETWORK_WIFI_CONNECTED;
						last_event_id=WIFI_EVENT_STA_CONNECTED;
						break;
				case	WIFI_EVENT_STA_DISCONNECTED:
					printf("Event: WIFI_EVENT_STA_DISCONNECTED\n" );
					 	 //esp_wifi_scan_start(NULL, false); //none blocking scan
						xEventGroupSetBits(event_group_bits, WIFI_DISCONNECTED_BIT);
						last_event_id=WIFI_EVENT_STA_DISCONNECTED;
					break;
				case	WIFI_EVENT_SCAN_DONE:
					printf("Event: WIFI_EVENT_SCAN_DONE\n" );
					xEventGroupSetBits(event_group_bits, WIFI_SCAN_END_BIT);

					//scan_results();

					break;
				default:
					printf("Unknown WIFI Based event:  Event Id:%d\n",event_id );
						break;
				}

	} else if(event_base==IP_EVENT){
			switch(event_id){
			case IP_EVENT_STA_GOT_IP:
				printf("Event: IP_EVENT_STA_GOT_IP\n" );
				 ip_event = (ip_event_got_ip_t*) event_data;
				 ESP_LOGW(TAG, "got ip:" IPSTR, IP2STR(&ip_event->ip_info.ip));

				break;
			default:
				printf("Unknown IP Based event:  Event Id:%d\n",event_id );
				break;
			}


		}


/*
	if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
//        if (s_retry_num < EXAMPLE_ESP_MAXIMUM_RETRY) {
            esp_wifi_connect();

            ESP_LOGI(TAG, "retry  to connect to the AP");
//        } else {
//            xEventGroupSetBits(s_wifi_event_group, WIFI_FAIL_BIT);
        //}
        //ESP_LOGI(TAG,"connect to the AP fail");
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ip_event_got_ip_t* event = (ip_event_got_ip_t*) event_data;
        ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));

        xEventGroupSetBits(event_group_bits, WIFI_CONNECTED_BIT);
    }
*/
}
//--------------------------------------
static void fill_network_list(void){

		uint16_t number = DEFAULT_SCAN_LIST_SIZE;
		 wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
		 uint16_t ap_count = 0;
		 memset(ap_info, 0, sizeof(ap_info));

		ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
		ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
		ESP_LOGI(TAG, "Total APs scanned = %u", ap_count);
		lv_dropdown_clear_options(dd_list);
		for (int i = 0; (i < DEFAULT_SCAN_LIST_SIZE) && (i < ap_count); i++) {
			lv_dropdown_add_option(dd_list,(char *)ap_info[i].ssid , i);
			printf("SSID: %s RSSI: %d\n",ap_info[i].ssid,ap_info[i].rssi);
		}
		lv_event_send(dd_list, LV_EVENT_REFRESH ,0 );
		lv_event_send(dd_list, LV_EVENT_READY ,0 );

}
//------------------------------------------------------------

//------------------------------------------------------------
void wifi_scan_init(lv_obj_t* list )
{


 //   uint16_t number = DEFAULT_SCAN_LIST_SIZE;
//    wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
//    uint16_t ap_count = 0;
//    memset(ap_info, 0, sizeof(ap_info));

   // ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
   // ESP_ERROR_CHECK(esp_wifi_start());

	dd_list=list; // signal to start scanning
	return;

	///////////////////////////////
//	esp_wifi_disconnect();
//	printf("--Wait for disconnect\n" );
//	EventBits_t bits = xEventGroupWaitBits(event_group_bits,
//					WIFI_DISCONNECTED_BIT | WIFI_FAIL_BIT,
//					pdTRUE,	// clear bits on exit
//					pdFALSE, //
//	   	   	   	   portMAX_DELAY);
//
//	if (bits & WIFI_DISCONNECTED_BIT ) {
//
//
//	}
//	printf("--Starting SCANE\n" );
//    esp_wifi_scan_start(NULL, true); //blocking scan
//     bits = xEventGroupWaitBits(event_group_bits,
//    		 WIFI_SCAN_END_BIT | WIFI_FAIL_BIT,
//				pdTRUE,	// clear bits on exit
//				pdFALSE,
//   	   	   	   portMAX_DELAY);
//     printf("--SCANE Finished with bits %d\n",bits );
//    if (bits & WIFI_SCAN_END_BIT) {
//    	 uint16_t number = DEFAULT_SCAN_LIST_SIZE;
//		 wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
//		 uint16_t ap_count = 0;
//		 memset(ap_info, 0, sizeof(ap_info));
//
//		ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
//		ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
//		ESP_LOGI(TAG, "Total APs scanned = %u", ap_count);
//		lv_dropdown_clear_options(list);
//		for (int i = 0; (i < DEFAULT_SCAN_LIST_SIZE) && (i < ap_count); i++) {
//			lv_dropdown_add_option(list,(char *)ap_info[i].ssid , i);
//			printf("SSID: %s RSSI: %d\n",ap_info[i].ssid,ap_info[i].rssi);
//		}
//
//
//    }
//    esp_wifi_connect();
//   //	        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
//   //	                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
//   //	    } else if (bits & WIFI_FAIL_BIT) {
//   //	        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
//   //	                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
//   //	    } else {
//   //	        ESP_LOGE(TAG, "UNEXPECTED EVENT");
//   //	    }


}

//--------------------------------------
//--------------------------------------


//
//void wifi_AP_cfg_init(void) {
//
//	printf("Wifi_AP_cfg_init()\n");
//}

//--------------------------------------
static void wifi_STA_cfg_init(void) {

		printf("Wifi_STA_cfg_init()\n");


		network_settings_t * netSet=get_network_settings();
		if(netSet->sta_enable==false){
			return;
		}
		 ESP_ERROR_CHECK(esp_wifi_stop());

	    esp_event_handler_instance_t instance_any_id;
	    esp_event_handler_instance_t instance_got_ip;
	    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT,
	                                                        ESP_EVENT_ANY_ID,
	                                                        &network_conn_event_handler,
	                                                        NULL,
	                                                        &instance_any_id));
	    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT,
	                                                        IP_EVENT_STA_GOT_IP,
	                                                        &network_conn_event_handler,
	                                                        NULL,
	                                                        &instance_got_ip));

	    printf("#001\n");
	    wifi_config_t wifi_config = {
	        .sta = {

	            //.ssid = (char *)netSet->remote_ssid_name,
	            //.password = netSet->remote_ssid_pass,
	            /* Setting a password implies station will connect to all security modes including WEP/WPA.
	             * However these modes are deprecated and not advisable to be used. Incase your Access point
	             * doesn't support WPA2, these mode can be enabled by commenting below line */
		     .threshold.authmode = WIFI_AUTH_WPA2_PSK,

	            .pmf_cfg = {
	                .capable = true,
	                .required = false
	            },
	        },
	    };

	    memcpy(wifi_config.sta.ssid,netSet->remote_ssid_name,32);
	    memcpy(wifi_config.sta.password,netSet->remote_ssid_pass,64);
	    printf("#010\n");
	    printf("ssid: %s,pass: %s\n",wifi_config.sta.ssid,wifi_config.sta.password);

	    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
	    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config) );


	    ESP_ERROR_CHECK(esp_wifi_start() ); // this will trigger WIFI_EVENT_STA_START and a call to esp_wifi_connect();

	    ESP_LOGI(TAG, "wifi_init_sta finished.");


	    /* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or connection failed for the maximum
	     * number of re-tries (WIFI_FAIL_BIT). The bits are set by event_handler() (see above) */
//	    EventBits_t bits = xEventGroupWaitBits(event_group_bits,
//	            WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
//	            pdFALSE,
//	            pdFALSE,
//	            portMAX_DELAY);

	    /* xEventGroupWaitBits() returns the bits before the call returned, hence we can test which event actually
	     * happened. */

//	    if (bits & WIFI_CONNECTED_BIT) {
//	        ESP_LOGI(TAG, "connected to ap SSID:%s password:%s",
//	                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
//	    } else if (bits & WIFI_FAIL_BIT) {
//	        ESP_LOGI(TAG, "Failed to connect to SSID:%s, password:%s",
//	                 EXAMPLE_ESP_WIFI_SSID, EXAMPLE_ESP_WIFI_PASS);
//	    } else {
//	        ESP_LOGE(TAG, "UNEXPECTED EVENT");
//	    }

	    /* The event will not be processed after unregister */
	//    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip));
	//    ESP_ERROR_CHECK(esp_event_handler_instance_unregister(WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id));
	//    vEventGroupDelete(s_wifi_event_group);


	//wifi_scan();

}
//--------------------------------------
bool isSTAConnected(void){

	 tcpip_adapter_ip_info_t ipInfo;
	 tcpip_adapter_get_ip_info(TCPIP_ADAPTER_IF_STA, &ipInfo);
	return (last_event_id==WIFI_EVENT_STA_CONNECTED)&&(ipInfo.ip.addr!=0);
}
void wifi_network_selected(void){ // user has selected a network from the list

	wifi_STA_cfg_init();
}

//--------------------------------------
void network_init(void){

kuku
	network_settings_t * netSet=get_network_settings();
	if(!(netSet->sta_enable||netSet->ap_enable||netSet->eth_enable)){
		ESP_LOGI(TAG, "No network is configured\n");
		return;
	}
    // Initialize TCP/IP network interface (should be called only once in application)
    ESP_ERROR_CHECK(esp_netif_init());
    // Create default event loop that running in background
    ESP_ERROR_CHECK(esp_event_loop_create_default()); // for all network events used by the esp32 network by default.
    event_group_bits = xEventGroupCreate(); //FreeRTOS group of bits falgs
    if((netSet->sta_enable||netSet->ap_enable)){
    	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
        if(netSet->sta_enable){
        	esp_netif_create_default_wifi_sta();
        	wifi_STA_cfg_init();
        }


    }

  	if(netSet->ap_enable){


  	}
    if(netSet->eth_enable){

   }

}

//--------------------------------------
bool isWifisupported(void) {
    return true;
}
//--------------------------------------
void network_monitor(void){

	EventBits_t bits;
	//printf("network_monitor %d\n",net_state);
	switch(net_state){
	case	NETWORK_INIT:
		if(dd_list!=NULL){ // a request from UI for network scan
			xEventGroupSetBits(event_group_bits,WIFI_DISCONNECTED_BIT); // simulate disconnect
			net_state = NETWORK_WIFI_SCAN_START;
			break;
		}
		break;
	case 	NETWORK_WIFI_CONNECING:
		if(dd_list!=NULL){ // a request from UI for network scan
			//lv_dropdown_clear_options(dd_list);
			//xEventGroupSetBits(event_group_bits, WIFI_SCAN_REQUEST_BIT);
			//esp_wifi_disconnect();
			net_state = NETWORK_WIFI_SCAN_START;
			break;
		}


			bits=xEventGroupGetBits(event_group_bits);
			if(bits & WIFI_DISCONNECTED_BIT){
				xEventGroupClearBits(event_group_bits,WIFI_DISCONNECTED_BIT);
				printf("Re Connecting...\n");
				esp_wifi_connect();
				//wifi_STA_cfg_init();
				break;
			}
			if(bits & WIFI_CONNECTED_BIT){
				net_state=NETWORK_WIFI_CONNECTED;
				break;
			}
			break;
	case 	NETWORK_WIFI_CONNECTED:
			bits=xEventGroupGetBits(event_group_bits);
			if((bits & WIFI_DISCONNECTED_BIT)&&(dd_list==NULL)){
				xEventGroupClearBits(event_group_bits,WIFI_CONNECTED_BIT| WIFI_DISCONNECTED_BIT);
				net_state=NETWORK_WIFI_CONNECING;
				esp_wifi_connect();
				//wifi_STA_cfg_init();
				break;
			}
			if((dd_list!=NULL)){
				esp_wifi_disconnect();
				xEventGroupClearBits(event_group_bits,WIFI_CONNECTED_BIT| WIFI_DISCONNECTED_BIT);
				net_state = NETWORK_INIT;
			}


			break;
	case 	NETWORK_WIFI_SCAN_START:
			bits=xEventGroupGetBits(event_group_bits);
			if(bits & WIFI_DISCONNECTED_BIT){ // waiting for disconnect bit
				xEventGroupClearBits(event_group_bits,WIFI_DISCONNECTED_BIT | WIFI_SCAN_END_BIT);
				printf("start scanning...\n");
				esp_wifi_scan_start(NULL, false); //none blocking scan
				net_state=NETWORK_WIFI_SCANNING;
			}
		break;
	case 	NETWORK_WIFI_SCANNING:
			bits=xEventGroupGetBits(event_group_bits);
			if(bits & WIFI_SCAN_END_BIT){ // waiting for scan end bit
				fill_network_list();
				net_state=NETWORK_WIFI_CONNECING;
				dd_list=NULL;
				net_state = NETWORK_INIT; // Wait for the user to select a new ssid before reconnecting
			}

			break;
	default:
		break;

	}


//	bits=xEventGroupClearBits( event_group_bits, WIFI_SCAN_END_BIT);
//	//printf("Bits: %d\n",bits);
//	if(bits!=0){
//		printf("----Bits: %d\n",bits);
//		scan_results();
//		esp_wifi_connect();
//	}
}



