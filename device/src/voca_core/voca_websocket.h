#pragma once
#include <WebSocketsServer.h>
#include <ArduinoJson.h>
WebSocketsServer webSocket = WebSocketsServer(81);

#include <list>

typedef void (*OnWSTextIncome)(String);
std::list<OnWSTextIncome> OnWSTextIncomes;

void setOnWSTextIncome(OnWSTextIncome cb)
{
    OnWSTextIncomes.push_front(cb);
}
void onConnect(uint8_t num)
{
    log_d("onConnect: %d", num);
    //   DynamicJsonDocument doc(10000);
    //   JsonObject objData = doc.to<JsonObject>();
    //   for (auto const& item : Store)
    //   {
    //     objData[item.first] = item.second;
    //   }
    //   String ret;

    //   serializeJson(doc, ret);
    //   webSocket.sendTXT(num, ret);
}
void webSocketEvent(uint8_t num, WStype_t type, uint8_t *payload, size_t length)
{
    String data;

    switch (type)
    {
    case WStype_DISCONNECTED:
        break;
    case WStype_CONNECTED:
        onConnect(num);
        break;
    case WStype_TEXT:
        for (size_t i = 0; i < length; i++)
        {
            data += (char)payload[i];
        }
        log_d("WStype_TEXT: %s", data.c_str());
        for (auto const &item : OnWSTextIncomes)
        {
            if (item != NULL)
                item(data);
        }
        break;
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
	        webSocket.setAuthorization("user", "Password");
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