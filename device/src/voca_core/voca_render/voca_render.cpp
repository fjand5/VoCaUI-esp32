#include "voca_render.h"
VocaRender vocaRender;
VocaRender::VocaRender(/* args */)
{
}

void VocaRender::addComponentEvents(String key, ComponentEvent cb)
{
  componentEvents[key] = cb;
}

void VocaRender::renderComponent(String compt, String tab, String espKey, String props)
{
  if (xSemaphoreTake(semVocaRender, portMAX_DELAY) == pdTRUE)
  {
    DynamicJsonDocument docRender(20000);
    DeserializationError err = deserializeJson(docRender, renderData);

    renderData = "";
    JsonArray arrayRender;
    if (err)
    {
      arrayRender = docRender.to<JsonArray>();
    }
    else
    {
      arrayRender = docRender.as<JsonArray>();
    }

    JsonObject comptObj = arrayRender.createNestedObject();
    comptObj["type"] = compt;
    comptObj["tab"] = tab;
    comptObj["espKey"] = espKey;
    comptObj["props"] = serialized(props);

    serializeJson(docRender, renderData);
    xSemaphoreGive(semVocaRender);
  }
}
void VocaRender::begin()
{
  semVocaRender = xSemaphoreCreateBinary();
  xSemaphoreGive(semVocaRender);
  vocaWebserver.addHttpApi(
      "/render",
      [this]()
      {
        vocaWebserver.send_P(200, "application/json", renderData.c_str());
      });
  vocaWebsocket.setWebsocketReceiveEvent(
      [this](JsonObject obj)
      {
        for (std::pair<String, ComponentEvent> e : componentEvents)
        {
          String k = e.first;
          ComponentEvent cb = e.second;
          if (obj["espKey"] == k)
          {
            cb(k, obj["espValue"]);
          }
        }
      });
}

void VocaRender::renderInput(String tab, String espKey, String option, ComponentEvent event)
{
  addComponentEvents(espKey, event);
  renderComponent("EspInput", tab, espKey, option);
}
void VocaRender::renderSlider(String tab, String espKey, String option, ComponentEvent event)
{
  addComponentEvents(espKey, event);
  renderComponent("EspSlider", tab, espKey, option);
}
void VocaRender::renderSwitch(String tab, String espKey, String option, ComponentEvent event)
{
  addComponentEvents(espKey, event);
  renderComponent("EspSwitch", tab, espKey, option);
}
void VocaRender::renderButton(String tab, String espKey, String option, ComponentEvent event)
{
  addComponentEvents(espKey, event);
  renderComponent("EspButton", tab, espKey, option);
}
void VocaRender::renderColorPicker(String tab, String espKey, String option, ComponentEvent event)
{
  addComponentEvents(espKey, event);
  renderComponent("EspColorPicker", tab, espKey, option);
}
void VocaRender::renderSelect(String tab, String espKey, String option, ComponentEvent event)
{
  addComponentEvents(espKey, event);
  renderComponent("EspSelect", tab, espKey, option);
}
VocaRender::~VocaRender()
{
}