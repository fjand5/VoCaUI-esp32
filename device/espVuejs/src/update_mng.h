/*
  To upload through terminal you can use: curl -F "image=@firmware.bin" esp8266-webupdate.local/update
*/
#pragma once
#include "webserver.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <HTTPUpdateServer.h>
extern WebServer server;
HTTPUpdateServer httpUpdater;

void setupUpdate(void) {
  httpUpdater.setup(&server);
}
