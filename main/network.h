#pragma once

#include "esp_netif.h"
#include "esp_eth.h"

void network_init(void);
void ethernet_cfg_init(void);
bool isEthernetSupported(void);
void wifi_cfg_init(void);
bool isWifisupported(void);

void wifi_AP_cfg_init(void);
void wifi_ST_cfg_init(void);
bool isSTAConnected(void);
void ip4_to_str(char *buf, tcpip_adapter_ip_info_t * ipInfo);




