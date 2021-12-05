#pragma once
#include <WebSocketsServer.h>
#include <ArduinoJson.h>

#include <list>

WebSocketsServer webSocket = WebSocketsServer(81);
SemaphoreHandle_t websocket_sem;
typedef void (*OnWSTextIncome)(JsonObject);
std::list<OnWSTextIncome> OnWSTextIncomes;

void setOnWSTextIncome(OnWSTextIncome cb)
{
    OnWSTextIncomes.push_front(cb);
}
void onConnect(uint8_t num)
{
    // String ret = "";
    // DynamicJsonDocument doc = getValuesByJson();
    // serializeJson(doc, ret);
    // webSocket.sendTXT(num, ret);
}
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
    if (xSemaphoreTake(websocket_sem, portMAX_DELAY) == pdTRUE)
    {
        String data;
        switch (type)
        {
        case WStype_DISCONNECTED:
            break;
        case WStype_CONNECTED:
        {

            onConnect(num);
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
                for (auto const &item : OnWSTextIncomes)
                {
                    if (item != NULL)
                        item(obj);
                }
                String _key = obj["espKey"];
                obj = _doc.to<JsonObject>();
                getValueByObject(_key, obj);
            }
            else if (obj["cmd"] == "gal")
            {
                obj = _doc.to<JsonObject>();
                getValuesByObject(obj);
                log_w("get all data =================================");
            }
            // dùng luôn _doc để lấy giá trị
            serializeJson(_doc, ret);
            webSocket.broadcastTXT(ret.c_str());
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
        xSemaphoreGive(websocket_sem);
    }
}

void setupWebSocket()
{
    xTaskCreatePinnedToCore(
        [](void *param)
        {
            webSocket.begin();
            webSocket.onEvent(webSocketEvent);
            websocket_sem = xSemaphoreCreateBinary();
            xSemaphoreGive(websocket_sem);
            SET_FLAG(FLAG_WEBSOCKET_READY);
            WAIT_FLAG_SET(FLAG_WEBSERVER_READY | FLAG_WEBSOCKET_READY);
            while (1)
            {
                webSocket.loop();
                delay(10);
            }
        },
        "loopSocket",
        10000,
        NULL,
        2,
        NULL,
        0);
}

void loopWebSocket()
{
}