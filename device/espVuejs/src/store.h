#pragma once
#define STORE_FILE_NAME "/store"
#include <ArduinoJson.h>
#include "FS.h"
#if defined(ESP8266)
#include <FILE_SYS.h>
#define FILE_SYS LittleFS
#elif defined(ESP32)
#include "SPIFFS.h"
#define FILE_SYS SPIFFS
#endif
#include <map>
#include <list>

typedef void (*OnStoreChange)(String, String, bool);
std::list < OnStoreChange > OnStoreChanges;

void setOnStoreChange(OnStoreChange cb){
  OnStoreChanges.push_front(cb);
}

std::map <String, String> Store;

bool loadConfig() {
  File configFile = FILE_SYS.open(STORE_FILE_NAME, "r");
  if (!configFile) {
    Serial.println("Failed to open config file");
    return false;
  }

  size_t size = configFile.size();

  // Allocate a buffer to store contents of the file.
  std::unique_ptr<char[]> buf(new char[size]);

  // We don't use String here because ArduinoJson library requires the input
  // buffer to be mutable. If you don't use ArduinoJson, you may as well
  // use configFile.readString instead.
  configFile.readBytes(buf.get(), size);

  DynamicJsonDocument doc(10000);
  auto error = deserializeJson(doc, buf.get());
  JsonObject objData;
  if (error) {
    objData = doc.to<JsonObject>();
    Serial.println("Failed to parse config file");
  }
  objData = doc.as<JsonObject>();
  for (JsonPair kv : objData) {
      Store[kv.key().c_str()] = kv.value().as<char*>();
  }
  Serial.println("Store content: ");
  serializeJsonPretty(doc, Serial);
  return true;
}

bool saveConfig() {
  DynamicJsonDocument doc(10000);
  JsonObject objData = doc.to<JsonObject>();

  
  for (auto const& item : Store)
  {
    objData[item.first] = item.second;
  }

  File configFile = FILE_SYS.open(STORE_FILE_NAME, "w");
  if (!configFile) {
    Serial.println("Failed to open config file for writing");
    return false;
  }

  serializeJson(doc, configFile);
  return true;
}
bool checkKey(String key){
  if (Store.find(key) != Store.end())
  {
    return true;
  }
  return false;
}
void setValue(String key, String val, bool save = false){
  bool isChange = Store[key] != val;
  Store[key] = val;
  if(save)
    saveConfig();

  
  for (auto const& item : OnStoreChanges){
      if(item != NULL)
          item(key, val, isChange);
  }
  
}

String getValue(String key, String def = ""){
  if(checkKey(key))
    return Store[key];
  return def;
}
const char * getValueByCStr(String key){
  unsigned int len = Store[key].length();
  char * ret = new char[len+1]();
  Store[key].toCharArray(ret, len+1);
  return ret;
}
void setupStore() {
  Serial.println("");
  delay(1000);
  Serial.println("Mounting FS...");

  if (!FILE_SYS.begin()) {
    Serial.println("Failed to mount file system");
    FILE_SYS.format();
    Serial.println("Try formatting...");
    if (!FILE_SYS.begin()) {
      return;
    }
  }
  Serial.println("Mounted");
  if (!loadConfig()) {
    Serial.println("Failed to load config");
  } else {
    Serial.println("Config loaded");
  }
}