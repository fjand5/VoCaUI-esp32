#pragma once
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
WebSocketsServer webSocket = WebSocketsServer(81);

#include <list>

typedef void (*OnWSTextIncome)(JsonObject);
std::list<OnWSTextIncome> OnWSTextIncomes;

void setOnWSTextIncome(OnWSTextIncome cb)
{
    OnWSTextIncomes.push_front(cb);
}
void onConnect(uint8_t num)
{
    String ret= "";
    DynamicJsonDocument doc = getValuesByJson();
    serializeJson(doc, ret);
    webSocket.sendTXT(num, ret);

}
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
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
        if (obj["cmd"] == "exe")
        {
            for (auto const &item : OnWSTextIncomes)
            {
                if (item != NULL)
                    item(obj);
            }
        }
        String ret;
        serializeJson(_doc, ret);
        webSocket.sendTXT(num, ret.c_str());
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
}

void setupWebSocket()
{
    xTaskCreatePinnedToCore(
        [](void *param)
        {
            webSocket.begin();
            webSocket.onEvent(webSocketEvent);
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