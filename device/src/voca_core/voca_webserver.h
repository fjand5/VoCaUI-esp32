#pragma once
#include "voca_dist.h"
#include <WebServer.h>

#include <ArduinoJson.h>
#include "voca_store.h"
WebServer server(80);

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
  server.on(String("/api/") + url, response);
}

void handleIndex()
{
  comHeader();
  server.sendHeader("Content-Encoding", "gzip");
  server.send_P(200, "text/html", index_html, index_html_length);
}
void setupWebserver()
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
  // server.on("/update", HTTP_POST, []() {
  //     server.sendHeader("Connection", "close");
  //     server.send_P(200);
  //   }, []() {
  //     HTTPUpload& upload = server.upload();
  //     if (upload.status == UPLOAD_FILE_START) {
  //       Serial.setDebugOutput(true);
  //       Serial.printf("Update: %s\n", upload.filename.c_str());
  //       uint32_t maxSketchSpace = (ESP.getFreeSketchSpace() - 0x1000) & 0xFFFFF000;
  //       if (!Update.begin(maxSketchSpace)) { //start with max available size
  //         Update.printError(Serial);
  //       }
  //     } else if (upload.status == UPLOAD_FILE_WRITE) {
  //       if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
  //         Update.printError(Serial);
  //       }
  //     } else if (upload.status == UPLOAD_FILE_END) {
  //       if (Update.end(true)) { //true to set the size to the current progress
  //         Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
  //       } else {
  //         Update.printError(Serial);
  //       }
  //       Serial.setDebugOutput(false);
  //     }
  //     yield();
  //   });
  server.begin();
  xTaskCreatePinnedToCore(
      [](void* param)
      {
        Serial.print("loopWebserver is running on core ");
        Serial.println(xPortGetCoreID());
        while (1)
        {
          server.handleClient();
        }
      },
      "loopWebserver",
      100000,
      NULL,
      1,
      NULL,
      0
  );
}
void loopWebserver()
{
}