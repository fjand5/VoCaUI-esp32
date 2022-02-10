#pragma once
#include "voca_env.h"
#ifdef AUTH_FEATURE
#include "../voca_auth/voca_auth.h"
#endif
#include "voca_store/voca_store.h"
#include "voca_status/voca_status.h"

#include <WebSocketsServer.h>
#include <ArduinoJson.h>

#include <list>
#include <functional>

typedef std::function<void(JsonObject)> WebsocketReceiveEvent;
class VocaWebsocket : public WebSocketsServer
{
private:
    SemaphoreHandle_t semWebsocket;
    std::list<WebsocketReceiveEvent> WebsocketReceiveEvents;
    void cbConnectEvent(uint8_t num, uint8_t *payload, size_t length);
    void cbWebSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length);

public:
    VocaWebsocket(int port);
    void setWebsocketReceiveEvent(WebsocketReceiveEvent cb);
    void begin();
    ~VocaWebsocket();
};

extern VocaWebsocket vocaWebsocket;