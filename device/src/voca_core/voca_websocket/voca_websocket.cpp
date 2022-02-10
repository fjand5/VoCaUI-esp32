#include "voca_websocket.h"
VocaWebsocket vocaWebsocket(81);

VocaWebsocket::VocaWebsocket(int port) : WebSocketsServer(port)
{
}

void VocaWebsocket::setWebsocketReceiveEvent(WebsocketReceiveEvent cb)
{
    WebsocketReceiveEvents.push_front(cb);
}

void VocaWebsocket::cbConnectEvent(uint8_t num, uint8_t *payload, size_t length)
{
    String token = "";
    for (int i = 0; i < length; i++)
    {
        token += (char)payload[i];
    }
    token.replace("/", "");
#ifdef AUTH_FEATURE
    if (!vocaAuth.checkAuthJwt(token))
    {
        log_d("Token: %s num: %d", token.c_str(), num);
        xSemaphoreGive(semWebsocket);
        disconnect(num);
    }
    else
    {
        log_d("Token: %s num: %d", token.c_str(), num);
    }
#endif
}
void VocaWebsocket::cbWebSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
    if (xSemaphoreTake(semWebsocket, portMAX_DELAY) == pdTRUE)
    {
        switch (type)
        {
        case WStype_DISCONNECTED:
        {
            break;
        }
        case WStype_CONNECTED:
        {
            cbConnectEvent(num, payload, length);
            break;
        }
        case WStype_TEXT:
        {

            DynamicJsonDocument _doc(10000);
            deserializeJson(_doc, payload, length);
            JsonObject obj = _doc.as<JsonObject>();
            String ret;
            if (obj["cmd"] == "exe")
            {
                for (auto const &item : WebsocketReceiveEvents)
                {
                    if (item != NULL)
                        item(obj);
                }
                String _key = obj["espKey"];
                obj = _doc.to<JsonObject>();
                vocaStore.readValueToObject(_key, obj);
            }
            else if (obj["cmd"] == "gal")
            {
                obj = _doc.to<JsonObject>();
                vocaStore.readStore(obj);
            }
            else if (obj["cmd"] == "ping")
            {
                obj = _doc.to<JsonObject>();
                obj["cmd"] = "pong";
                obj["stamp"] = millis();
            }
            // dùng luôn _doc để lấy giá trị
            serializeJson(_doc, ret);
            broadcastTXT(ret);
            break;
        }
        case WStype_BIN:
            break;
        case WStype_ERROR:
        case WStype_FRAGMENT_TEXT_START:
        case WStype_FRAGMENT_BIN_START:
        case WStype_FRAGMENT:
        case WStype_FRAGMENT_FIN:
            break;
        }
        xSemaphoreGive(semWebsocket);
    }
}
void VocaWebsocket::begin()
{
    vocaStatus.setStatus(Status_SetupWifi_Done);
    WebSocketsServer::begin();
    onEvent([this](uint8_t num, WStype_t type, uint8_t *payload, size_t length)
            { cbWebSocketEvent(num, type, payload, length); });
    semWebsocket = xSemaphoreCreateBinary();
    xSemaphoreGive(semWebsocket);
    xTaskCreatePinnedToCore(
        [](void *param)
        {
            VocaWebsocket *vocaWebsocket = (VocaWebsocket *)param;
            log_w("loopSocket is running on core: %d", xPortGetCoreID());

            vocaStatus.setStatus(Status_WebSocket_Ready);
            vocaStatus.waitStatus(Status_WebServer_Ready);
            vocaStatus.waitStatus(Status_Store_Initialized);

            vocaStore.addStoreChangeEvent(
                [](String key, String value, void *p)
                {
                    VocaWebsocket *_ws = (VocaWebsocket *)p;
                    DynamicJsonDocument _doc(2048);
                    JsonObject obj = _doc.to<JsonObject>();
                    vocaStore.readValueToObject(key, obj);
                    String ret;
                    serializeJson(_doc, ret);
                    _ws->broadcastTXT(ret);
                },
                (void *)vocaWebsocket);
            log_w("loopSocket is running on core: %d", xPortGetCoreID());

            while (1)
            {
                vocaWebsocket->loop();
                delay(10);
            }
        },
        "loopSocket",
        5000,
        (void *)this,
        2,
        NULL,
        VOCA_CORE_CPU);
}
VocaWebsocket::~VocaWebsocket()
{
}
