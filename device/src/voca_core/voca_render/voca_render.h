#pragma once
#include "voca_env.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <functional>
#include "../voca_websocket/voca_websocket.h"
#include "../voca_webserver/voca_webserver.h"
#include <map>
#include <list>

typedef std::function<void(String key, String value)> ComponentEvent;
class VocaRender
{
private:
  String renderData;
  SemaphoreHandle_t semVocaRender;
  std::map<String, ComponentEvent> componentEvents;
  void addComponentEvents(String key, ComponentEvent cb);

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
  void renderComponent(String compt, String tab, String espKey, String props);

public:
  VocaRender();
  void begin();
  void renderInput(String tab, String espKey, String option, ComponentEvent event);
  void renderSlider(String tab, String espKey, String option, ComponentEvent event);
  void renderSwitch(String tab, String espKey, String option, ComponentEvent event);
  void renderButton(String tab, String espKey, String option, ComponentEvent event);
  void renderColorPicker(String tab, String espKey, String option, ComponentEvent event);
  void renderSelect(String tab, String espKey, String option, ComponentEvent event);
  ~VocaRender();
};
extern VocaRender vocaRender;
