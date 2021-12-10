#pragma once

#include "voca_dist.h"
#include <WebServer.h>
#include <ArduinoJWT.h>
#include <ArduinoJson.h>
#include "voca_store.h"

WebServer server(80);
SemaphoreHandle_t http_api_sem;
ArduinoJWT jwt(__TIME__);
typedef void (*Response)(void);
void comHeader()
{
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.sendHeader("Access-Control-Allow-Methods", "PUT,POST,GET,OPTIONS");
  server.sendHeader("Access-Control-Allow-Headers", "*");
  server.sendHeader("Access-Control-Expose-Headers", "*");
}
void addHttpApi(String url, Response response)
{
  if (url.startsWith("/"))
    url = url.substring(1);
  server.on(String("/api/") + url, [response]()
            {
              String token = server.header("Authorization");
              token.replace("Bearer ", "");
              String payload;
              // log_d("111111");
              if (jwt.decodeJWT(token, payload) && getJwtPayload() == payload)
              {
              // log_d("222222");
                if (xSemaphoreTake(http_api_sem, portMAX_DELAY) == pdTRUE)
                {
              // log_d("333333");
                  comHeader();
                  String tmp = String(millis());
                  setJwtPayload(tmp);
                  String bearerHeader;
                  bearerHeader = String("Bearer ") + jwt.encodeJWT(tmp);
                  server.sendHeader("Authorization", bearerHeader);
                  response();
                  xSemaphoreGive(http_api_sem);
              // log_d("444444");
                }

              }
              else
              {
              // log_d("55555");
                server.send(401);
              }
            });
}

void handleIndex()
{
  comHeader();
  server.sendHeader("Content-Encoding", "gzip");
  server.send_P(200, "text/html", index_html, index_html_length);
}
void setupWebserver()
{

  xTaskCreatePinnedToCore(
      [](void *param)
      {
        server.on("/", handleIndex);
        server.on("/login",
                  []()
                  {
                    comHeader();
                    if (server.authenticate(getUsername().c_str(), getPassword().c_str()))
                    {
                      String tmp = String(millis());
                      setJwtPayload(tmp);
                      server.send_P(200, "application/json", jwt.encodeJWT(tmp).c_str());
                    }
                    else
                    {
                      server.send(401);
                    }
                  });
        server.on("/js/app.js",
                  []()
                  {
                    comHeader();
                    server.sendHeader("Content-Encoding", "gzip");
                    server.send_P(200, "application/javascript", app_js, app_js_length);
                  });
        server.on("/fonts/element-icons.woff",
                  []()
                  {
                    comHeader();
                    server.sendHeader("Content-Encoding", "gzip");
                    server.send_P(200, "application/javascript", font_woff, font_woff_length);
                  });
        server.on("/static/favicon.ico",
                  []()
                  {
                    comHeader();
                    server.sendHeader("Content-Encoding", "gzip");
                    server.send_P(200, "application/javascript", favicon_ico, favicon_ico_length);
                  });
        server.begin();
        Serial.print("loopWebserver is running on core ");
        Serial.println(xPortGetCoreID());
        http_api_sem = xSemaphoreCreateBinary();
        xSemaphoreGive(http_api_sem);
        SET_FLAG(FLAG_WEBSERVER_READY);
        WAIT_FLAG_SET(FLAG_WEBSERVER_READY | FLAG_WEBSOCKET_READY);

        while (1)
        {
          server.handleClient();
          delay(20);
        }
      },
      "loopWebserver",
      100000,
      NULL,
      1,
      NULL,
      0);
}