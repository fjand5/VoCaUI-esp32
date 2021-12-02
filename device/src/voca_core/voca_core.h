#include "voca_status.h"
#include "voca_wifi.h"
#include "voca_webserver.h"
#include "voca_store.h"
#include "voca_system.h"
#include "voca_websocket.h"

void setup_voca()
{
    settupStatus();
    setupStore();
    setupWifi();
    setupWebserver();
    setupWebSocket();
    setupSystem();
    
}