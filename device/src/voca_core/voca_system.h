#pragma once

#include "voca_env.h"
#include "voca_webserver/voca_webserver.h"

void renderUI()
{
  vocaRender.renderInput(F("System"), F("_apid"), F(R"({
    "name":"Tên wifi",
    "description":"",
    "newLine":true,
    "span":{
      
    }
  })"),
                         [](String key, String value)
                         {
                           vocaStore.setValue(key, value, true);
                         });
  vocaRender.renderInput(F("System"), F("_appw"), F(R"({
    "name":"Mật khẩu wifi",
    "description":"",
    "newLine":true,
    "password":true
  })"),
                         [](String key, String value)
                         {
                           vocaStore.setValue(key, value, true);
                         });
  vocaRender.renderButton(F("System"), F("_reset"), F(R"({
    "name":"Khởi động lại",
    "description":"",
    "confirm":"Bạn có chắc muốn khởi động lại hệ thống không?",
    "span":{}
  })"),
                          [](String key, String value)
                          {
                            ESP.restart();
                          });
  vocaRender.renderButton(F("System"), F("_format"), F(R"({
    "name":"Xóa dữ liệu",
    "description":"",
    "newLine":true,
    "confirm":"Bạn có chắc muốn xóa toàn bộ dữ liệu không?",
    "span":{
    }
  })"),
                          [](String key, String value)
                          {
                            SPIFFS.format();
                          });
  vocaRender.renderInput(F("System"), F("_version"), F(R"({
    "name":"Phiên bản",
    "description":""
  })"),
                         [](String key, String value) {
                         });
}
void setupSystem()
{
  renderUI();
  vocaWebserver
      .addHttpApi("/manifest",
                  []()
                  {
                    String manifestData;
                    DynamicJsonDocument docManifest(1024);
                    JsonObject manifestObject = docManifest.to<JsonObject>();
                    #ifdef AUTH_FEATURE
                      manifestObject["auth"]=true;
                    #endif
                    manifestObject["mqtt"]=false;
                    manifestObject["wifiSta"]=true;
                    manifestObject["creator"]="thinhchodien@gmail.com";

                    serializeJson(manifestObject, manifestData);
                    vocaWebserver.send_P(200, "application/json", manifestData.c_str());
                  }, false);
  vocaWebserver
      .addHttpApi("/reset", []()
                  {
        log_w("Reset system");
        vocaWebserver.send(200);
        delay(500); // chờ send thành công.
        ESP.restart(); });
}