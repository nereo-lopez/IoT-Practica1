#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_event_loop.h"
#include "esp_wifi.h"
#include "nvs_flash.h"
#include "esp_check.h"


#define STA_SSID "Tec 911"
#define STA_PASSWORD "0123456789"

#define RED GPIO_NUM_5
#define YELLOW GPIO_NUM_17
#define GREEN GPIO_NUM_16

uint8_t isScanned = 0;

void networkScan()
{
    wifi_scan_config_t scan_config = {
    .ssid = 0,
    .bssid = 0,
    .channel = 0,
        .show_hidden = true
    };
    printf("Comienza scanner...\n");
    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));
    printf("Scanner completado!\n");
 
    uint8_t ap_num;
    esp_wifi_scan_get_ap_num(&ap_num);
    wifi_ap_record_t ap_records[20];
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&ap_num, ap_records));
  
    printf("Se encontraron %d puntos de acceso:\n", ap_num);

    printf("               SSID              | Canal   | RSSI |   MAC \n\n");
    for(int i = 0; i < ap_num; i++)
        printf("%32s | %7d | %4d | %2x:%2x:%2x:%2x:%2x:%2x   \n", ap_records[i].ssid, ap_records[i].primary, ap_records[i].rssi , *ap_records[i].bssid, *ap_records[i].bssid+1, *(ap_records[i].bssid)+2, *(ap_records[i].bssid)+3, *(ap_records[i].bssid)+4, *(ap_records[i].bssid)+5);

    isScanned = 1;
}

void delayMs(uint16_t ms)
{
    vTaskDelay(ms / portTICK_PERIOD_MS);
}

void app_main()
{
    ESP_ERROR_CHECK(nvs_flash_init());
    esp_netif_init();
    esp_event_loop_create_default();
    esp_netif_t *sta_netif = esp_netif_create_default_wifi_sta();
    assert(sta_netif);

    wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&wifi_config));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_APSTA));

    wifi_config_t sta_config = 
    {
        .sta = 
        {
        .ssid= STA_SSID,
        .password = STA_PASSWORD
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA,&sta_config));

    ESP_ERROR_CHECK(esp_wifi_start());
    ESP_ERROR_CHECK(esp_wifi_connect());

    while(1)
    {  
        delayMs(1000);
        if(isScanned == 0)
            networkScan();
    }
  }