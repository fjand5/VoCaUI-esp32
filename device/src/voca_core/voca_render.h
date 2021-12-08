#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include "voca_websocket.h"
#include "voca_webserver.h"
#include <map>
#include <list>

String getRender();
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
  addHttpApi("/render", []()
             {
               server.send_P(200, "application/json", getRender().c_str());
             });
  setOnWSTextIncome([](JsonObject obj)
                    {
                      for (std::pair<String, OnEvent> e : EventWithKeys)
                      {
                        String k = e.first;
                        OnEvent cb = e.second;
                        if (obj["espKey"] == k)
                        {
                          cb(k, obj["espValue"]);
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

/*
option.span : số cột component chiếm
  option.span.xs (<768px)
  option.span.sm (>=768px)
  option.span.md (>=992px)
  option.span.lg (>=1200)
  option.span.xl (>=1920px)
option.offset : số cột component dịch sang phải (những components phía sau cũng bị dịch theo)
option.pull : di chuyển component sang phải (những components khác KHÔNG bị dịch theo)
option.push : di chuyển component sang trái
*/
void renderInput(String tab, String espKey, String option, OnEvent event){
  setOnEvents(espKey, event);
  renderComponent("EspInput", tab, espKey, option);

}
void renderSlider(String tab, String espKey, String option, OnEvent event){
  setOnEvents(espKey, event);
  renderComponent("EspSlider", tab, espKey, option);

}
void renderSwitch(String tab, String espKey, String option, OnEvent event)
{
  setOnEvents(espKey, event);
  renderComponent("EspSwitch", tab, espKey, option);
}
void renderButton(String tab, String espKey, String option, OnEvent event)
{
  setOnEvents(espKey, event);
  renderComponent("EspButton", tab, espKey, option);
}
void renderColorPicker(String tab, String espKey, String option, OnEvent event)
{
  setOnEvents(espKey, event);
  renderComponent("EspColorPicker", tab, espKey, option);
}
void renderSelect(String tab, String espKey, String option, OnEvent event)
{
  setOnEvents(espKey, event);
  renderComponent("EspSelect", tab, espKey, option);
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
