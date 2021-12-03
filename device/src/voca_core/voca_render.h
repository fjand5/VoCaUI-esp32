#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include "voca_websocket.h"
#include <map>
#include <list>

DynamicJsonDocument docRender(20000);
JsonArray arrayRender = docRender.to<JsonArray>();
typedef void (*OnEvent)(String key, String value);
std::list<OnEvent> OnEvents;
std::map<String, OnEvent> EventWithKeys;
void setOnEvents(String key, OnEvent cb)
{
  EventWithKeys[key] = cb;
}
void setupRender()
{
  setOnWSTextIncome([](JsonObject obj)
                    {
                      for (std::pair<String, OnEvent> e : EventWithKeys)
                      {
                        String k = e.first;
                        OnEvent cb = e.second;
                        if (obj["espKey"] == k)
                        {
                          cb(k, obj["value"]);
                        }
                      }
                    });
}
void renderComponent(String compt, String tab, String espKey, String props)
{
  JsonObject comptObj = arrayRender.createNestedObject();
  comptObj["type"] = compt;
  comptObj["tab"] = tab;
  comptObj["espKey"] = espKey;

  DynamicJsonDocument _docProps(2048);
  deserializeJson(_docProps, props);
  comptObj["props"] = _docProps.as<JsonObject>();
}
// void renderSlider(String tab, String key, String name, String option, EventFunc event = NULL){
//   addEvent(key, event);
//   renderComponent("input-slider", tab, key, name, option);
// }
// void renderToggle(String tab, String key, String name, String option, EventFunc event = NULL){
//   addEvent(key, event);
//   renderComponent("toggle", tab, key, name, option);
// }
void renderButton(String tab, String espKey, String option, OnEvent event)
{
  setOnEvents(espKey, event);
  renderComponent("EspButton", tab, espKey, option);
}
// void renderInputText(String tab, String key, String name, String option, EventFunc event = NULL){
//   addEvent(key,event);
//   renderComponent("input-text", tab, key, name, option);
// }
// void renderPassword(String tab, String key, String name, String option, EventFunc event = NULL){
//   addEvent(key,event);
//   renderComponent("password", tab, key, name, option);

// }

String getRender()
{
  String ret;
  serializeJson(docRender, ret);
  return ret;
}
