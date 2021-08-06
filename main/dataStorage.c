

#include "nvs_flash.h"
#include "nvs.h"

#include "lvgl/lvgl.h"
#include "dataStorage.h"

static const char * STORAGE_NAMESPACE= "storage";
static const char * STORAGE_KEAY= "settings";
counter_t counterSettings[COUNTER_COUNT];
int32_t current_count[COUNTER_COUNT];


//---------------------------------
void loadSettings(void) {
	 nvs_handle_t my_handle;
	 esp_err_t err = nvs_flash_init();
	    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
	        // NVS partition was truncated and needs to be erased
	        // Retry nvs_flash_init
	    	printf("\nErasing nvs storage....");
	        ESP_ERROR_CHECK(nvs_flash_erase());
	        err = nvs_flash_init();
	    }
	    ESP_ERROR_CHECK( err );
		// Open
		err = nvs_open(STORAGE_NAMESPACE, NVS_READONLY, &my_handle);
		if (err != ESP_OK) {

			printf("\nError opening storage...%d",err);
			return;
		}
		// Read params blob
		size_t required_size = sizeof(counterSettings);  //
		// obtain required memory space to store blob being read from NVS
		err = nvs_get_blob(my_handle, STORAGE_KEAY, counterSettings, &required_size);
		if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND){
			printf("\nError reading Settings...%d",err);
			return ;
		}
		nvs_close(my_handle);
}
//----------------------------------
void saveSettings(void) {


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
			err = nvs_set_blob(my_handle,STORAGE_KEAY, counterSettings, required_size);
			if (err != ESP_OK && err != ESP_ERR_NVS_NOT_FOUND){
				printf("\nError reading %s (%d)",STORAGE_KEAY,err);
				return ;
			}

			printf("\nData saved...to %s",STORAGE_KEAY);
			nvs_close(my_handle);




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
//----------------------------------
//----------------------------------
