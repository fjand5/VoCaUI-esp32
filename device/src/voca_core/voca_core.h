#pragma once
#include "voca_env.h"
#include "voca_auth/voca_auth.h"
#include "voca_store/voca_store.h"
#include "voca_render/voca_render.h"
#include "voca_status/voca_status.h"
#include "voca_wifi/voca_wifi.h"
#include "voca_webserver/voca_webserver.h"
#include "voca_system.h"
#include "voca_websocket/voca_websocket.h"

#include <functional>
typedef std::function<void (void)> OnVocaReady;
OnVocaReady onVocaReady;
void setOnVocaReady(OnVocaReady cbOnVocaReady){
    onVocaReady = cbOnVocaReady;
}
void setup_voca()
{
    vocaAuth.begin();
    vocaStore.begin();
    vocaRender.begin();
    vocaWifi.begin();
    vocaWebserver.begin();
    vocaWebsocket.begin();
    setupSystem();
    vocaStatus.waitAllStatus();
    if(onVocaReady != NULL)
        onVocaReady();

}