
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <list>
#include "webserver.h"


WiFiClient espClient;
PubSubClient client(espClient);

void setMqtt();
void getMqtt();

typedef void (*OnMqttIncome)(String, String);
std::list < OnMqttIncome > OnMqttIncomes;

void setOnMqttIncome(OnMqttIncome cb){
  OnMqttIncomes.push_front(cb);
}
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  String msg;
  for (int i = 0; i < length; i++) {
    msg+=(char)payload[i];
  }
  for (auto const& item : OnMqttIncomes){
      if(item != NULL)
          item(topic, msg);
  }

}
void reconnect() {
    if(!checkKey("_mqttAddr") 
    || !checkKey("_mqttPort") 
    || !checkKey("_mqttUser") 
    || !checkKey("_mqttPwd") 
    )
      return;
    Serial.print("Attempting MQTT connection...");
    String clientId = "ESP8266Client-";
    clientId += String(random(0xffff), HEX);
    client.setServer(getValueByCStr("_mqttAddr"), getValue("_mqttPort").toInt()) ;
    if (client.connect(clientId.c_str(), getValue("_mqttUser").c_str(), getValue("_mqttPwd").c_str(),
    (getValue("_mqttUser") + "/tudien/isOnline").c_str(), 1, true, "offline"
    )) {
      Serial.println("connected");
      client.publish((getValue("_mqttUser") + "/tudien/isOnline").c_str(), (const uint8_t*)"true", 4, true);
      client.subscribe("#");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
    }
}
void setupMqtt() {
  client.setCallback(mqttCallback);
  reconnect();
  addHttpApi("setMqtt",setMqtt);
  addHttpApi("getMqtt",getMqtt);

}

void loopMqtt() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
void setMqtt(){
  DynamicJsonDocument doc(256);
  auto err = deserializeJson(doc, server.arg(0));
  if(!err){
    setValue("_mqttAddr", doc["addr"], true);
    setValue("_mqttPort", doc["port"], true);
    setValue("_mqttUser", doc["user"], true);
    setValue("_mqttPwd", doc["pwd"], true);

  }
  server.send(200, "application/json", server.arg(0));

}
void getMqtt(){
  DynamicJsonDocument doc(256);
  JsonObject mqtt = doc.to<JsonObject>();
  mqtt["addr"] = getValue("_mqttAddr");
  mqtt["port"] = getValue("_mqttPort");
  mqtt["user"] = getValue("_mqttUser");
  mqtt["pwd"] = getValue("_mqttPwd");

  String ret;
  serializeJson(mqtt,ret);
  server.send(200, "application/json", ret);

}