#pragma once
#include "voca_dist.h"
#include <WebServer.h>

#include <ArduinoJson.h>
#include "voca_store.h"
WebServer server(80);
SemaphoreHandle_t http_api_sem;

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
              if (xSemaphoreTake(http_api_sem, portMAX_DELAY) == pdTRUE)
              {
                comHeader();
                response();
                xSemaphoreGive(http_api_sem);
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