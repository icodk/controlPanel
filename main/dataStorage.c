


#include <stdio.h>
#include <stdlib.h>
#ifdef __GNUC__                            
#include "nvs_flash.h"
#include "nvs.h"
#endif
#include "lvgl/lvgl.h"
#include "dataStorage.h"

//static const uint32_t	MAGIC_NUMBER = 0xaabbccdd;
static counter_t counterSettings[COUNTER_COUNT];
static int32_t current_count[COUNTER_COUNT];



                      

static network_settings_t network_settings={
						.sta_enable=false,			// connect to an AP
						.ap_enable=false,			// enable an  AP on this board
						.eth_enable=false,			// enable ethernet
						.remote_ssid_name="DESKTOP", 		// name of AP to connect to
						.remote_ssid_pass="1029384756", 		// pass of AP to connect to
						//.local_ssid_name=(uint8_t*)NULL,	  	//  name of local AP
						//.local_ssid_pass=(uint8_t*)NULL,	//  pass of local AP
						.sta_static_ip=false	  // sta should have static IP
											};
#ifdef __GNUC__      
static const char * STORAGE_NAMESPACE= "storage";
static const char * STORAGE_KEY_COUNTERS= "counters";
static const char * STORAGE_KEY_NETWORK= "network";
static const char * STORAGE_KEY_MAGIC_NUMBER= "magic";

#endif

static int32_t  ctl_param_table[] = {
        0	,	// 	0		CONTROL_PARMAS_START,
        0	,	// 	1		CV_CONTROL_MODE_CH1,
};


//---------------------------------

//----------------------------------                  
 void saveCounterSettings(void) {

#ifdef __GNUC__                      

		nvs_handle_t my_handle;
		 esp_err_t err;
			// Open
			err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &my_handle);
			if (err != ESP_OK) {

				printf("\nError opening storage...%d",err);
				return;
			}
			// Read params blob
			size_t required_size = sizeof(counterSettings);  //
			// obtain required memory space to store blob being read from NVS
			err = nvs_set_blob(my_handle,STORAGE_KEY_COUNTERS, counterSettings, required_size);
			if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND){
				printf("\nError reading %s (%d)",STORAGE_KEY_COUNTERS,err);
				return ;
			}
			nvs_commit(my_handle);
			printf("\nData saved...to %s",STORAGE_KEY_COUNTERS);
			nvs_close(my_handle);
#else
     printf("\nCounters Settings Saved....");

#endif      


}
 //----------------------------------
 void saveNetworkSetting(void){
#ifdef __GNUC__

		nvs_handle_t my_handle;
		 esp_err_t err;
			// Open
			err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &my_handle);
			if (err != ESP_OK) {

				printf("\nError opening storage...%d",err);
				return;
			}
			// Read params blob
			size_t required_size = sizeof(network_settings);  //
			// obtain required memory space to store blob being read from NVS
			err = nvs_set_blob(my_handle,STORAGE_KEY_NETWORK, &network_settings, required_size);
			if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND){
				printf("\nError reading %s (%d)",STORAGE_KEY_NETWORK,err);
				return ;
			}

			printf("\nData saved...to %s",STORAGE_KEY_NETWORK);
			nvs_commit(my_handle);
			nvs_close(my_handle);
#else
     printf("\nNetwork Settings Saved....");

#endif


 }


//-----------------------------------------------------
 void loadSettings(void) {
 #ifdef __GNUC__

 	//----- COUNTER settings
      nvs_handle_t my_handle;
// 	 esp_err_t err = nvs_flash_init();
// 	    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
// 	        // NVS partition was truncated and needs to be erased
// 	        // Retry nvs_flash_init
// 	    	printf("\nErasing nvs storage....");
// 	        ESP_ERROR_CHECK(nvs_flash_erase());
// 	        err = nvs_flash_init();
// 	    }
 //	    ESP_ERROR_CHECK( err );
 		// Open
      esp_err_t err = nvs_open(STORAGE_NAMESPACE, NVS_READWRITE, &my_handle);
 		if (err != ESP_OK) {

 			printf("Error (%d) opening storage: %s...\n",err,STORAGE_NAMESPACE);
 			return;
 		}
 		// Read counters params blob
 		size_t required_size = sizeof(counterSettings);  //
 		// obtain required memory space to store blob being read from NVS
 		err = nvs_get_blob(my_handle, STORAGE_KEY_COUNTERS, counterSettings, &required_size);
 		if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND){
 			printf("\nError reading Counters Settings...%d",err);

 		}

 		//-------NETWORK settings
 		//err = nvs_erase_key(my_handle, STORAGE_KEY_NETWORK); // force default
 		printf("Error erasing the %s key: %d\n",STORAGE_KEY_NETWORK,err);
 		required_size = sizeof(network_settings);  //
 			err = nvs_get_blob(my_handle, STORAGE_KEY_NETWORK, &network_settings, &required_size); // testing if settings exist
 			if (err !=  ESP_OK){ // use defaults
 				 saveNetworkSetting(); // use the default settings
 				printf("Error reading Network Settings...%d\n",err);
 				printf("Using Network Default Settings (%s,%s\n",network_settings.remote_ssid_name,network_settings.remote_ssid_pass);
 			}
 		nvs_close(my_handle);
 #else
     printf("\nSettings Loaded....");
 #endif

 }


//----------------------------------
counter_t* get_counter(counter_id_t cntId) {

    return &counterSettings[cntId];
}
//----------------------------------
int32_t* get_current_count(counter_id_t cntId) {

    return &current_count[cntId];
}
//----------------------------------
network_settings_t* get_network_settings(void){
	return &network_settings;
}
//----------------------------------
void useDefaultOnNextBoot(void ){


}
//----------------------------------
