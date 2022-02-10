#pragma once
#include "voca_env.h"
#include "voca_dist.h"
#include <WebServer.h>
#include <ArduinoJson.h>
#include <HTTPUpdateServer.h>
#ifdef AUTH_FEATURE
#include "../voca_auth/voca_auth.h"
#endif
#include "../voca_status/voca_status.h"
class VocaWebserver : public WebServer
{
private:
  SemaphoreHandle_t semHttpRequest;
  HTTPUpdateServer httpUpdater;

  typedef std::function<void()> Response;

public:
  void sendComHeader();
  VocaWebserver(int port);
  void begin();
  void addHttpApi(const String url, Response response);
  ~VocaWebserver();
};
extern VocaWebserver vocaWebserver;
