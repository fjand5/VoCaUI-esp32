#pragma once
#include "../voca_env.h"
#include <WiFi.h>
#include <ArduinoJson.h>
#include "../voca_store/voca_store.h"
#include "../voca_webserver/voca_webserver.h"
#include "../voca_status/voca_status.h"
class VocaWifi
{
private:

public:
  VocaWifi();
  void begin();
};
extern VocaWifi vocaWifi;
