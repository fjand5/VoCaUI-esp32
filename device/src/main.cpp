#include <Arduino.h>
#include "voca_core/voca_core.h"

void setup(void) {
  delay(555);
  setup_voca();
  Serial.print("main is running on core ");
  Serial.println(xPortGetCoreID());
  vTaskDelete(NULL);
  // Serial.begin(115200);
  // Serial.println();
  // Serial.println("1");
  // setupStore();
  // setupLedFull();
  // Serial.println("2");
  // setupWifi();
  // Serial.println("3");
  // Serial.println("4");
  // setupUpdate();
  // Serial.println("5");
  // setupWS();
  // Serial.println("6");
  // // setupMqtt();
  // Serial.println("7");
  // setupSystem();
  // Serial.println("8");
  // // setupTimer();
  // Serial.println("9");
  // // setupIO();
  // Serial.println("102");
  
  // setupWebserver();

  // Serial.println("booted");
  // setOnStoreChange([](String id, String val, bool isChange){
  //   DynamicJsonDocument doc(512);
  //   JsonObject objData = doc.to<JsonObject>();
  //   objData[id] = val;
  //   String ret;

  //   serializeJson(objData, ret);
  //   webSocket.broadcastTXT(ret);
  // });
  // setOnMqttIncome([](String topic, String msg){
  //   Serial.println(topic + ": "+ msg);
  //   DynamicJsonDocument doc(512);
  //   auto error = deserializeJson(doc, msg);
  //   if(error)
  //     return;
  //   JsonObject objData = doc.as<JsonObject>();
  //   String id = objData["id"];
  //   if(id.startsWith("schedule"))
  //     setValue(id, objData["value"], true);
  //   else
  //     setValue(id, objData["value"]);

  // });
  // setOnWSTextIncome([](String msg){
  //   DynamicJsonDocument doc(512);
  //   auto error = deserializeJson(doc, msg);
  //   if(error)
  //     return;
  //   JsonObject objData = doc.as<JsonObject>();
  //   String id = objData["id"];
  //   if(id.startsWith("schedule"))
  //     setValue(id, objData["value"], true);
  //   else
  //     setValue(id, objData["value"]);
  // });
}

void loop(void) {
  // loopWebserver();
  // loopWS();
  // loopMqtt();
  // loopTimer();
}