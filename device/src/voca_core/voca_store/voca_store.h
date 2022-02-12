#ifndef VOCA_STORE
#define VOCA_STORE
#define VOCA_STORE_NAME "voca_store"

#include "../voca_env.h"
#include "../voca_status/voca_status.h"
#include "../voca_eventbus/voca_eventbus.h"
#include "../voca_base/voca_base.h"
#include "FS.h"
#include "SPIFFS.h"
#include <map>
#include <list>
#include <ArduinoJson.h>
extern VocaEventBus vocaEventBus;
class VocaStore: public VocaBase
{
private:
  std::map<String, String> storeContent;
  std::map<int32_t, String> keyIndex;
  SemaphoreHandle_t semSpiffs;
  SemaphoreHandle_t semStoreContent;
  bool mountSpiffs();
  bool loadFileToContent();
  bool checkValidKey(const String key);
  bool checkValidValue(const String value);

public:
  VocaStore();
  void begin();
  void setValue(const String key, const String value, bool save = false);
  bool updateStore();
  void addStoreChangeEvent(EventBusFunction cb, void *prams);
  bool checkKey(const String key);
  const String getValue(const String key, const String def = "", bool createValueByDefault = true, bool save = true);
  void readValueToObject(const String key, JsonObject objectValue, const String def = "", bool createIfNotExist = true);
  char *getValueByCStr(const String key, const String def = "", bool createIfNotExist = true);

  String getStore();
  void readStore(JsonObject objectValues);
};
extern VocaStore vocaStore;


#if 0
String getUsername()
{
  String username;
  if (!checkKey("*username"))
    return DEFAULT_USERNAME;
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    username = ConfigContent["*username"];
    xSemaphoreGive(configContent_sem);
  }
  return username;
}
void setUsername(String username)
{
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    ConfigContent["*username"] = username;
    xSemaphoreGive(configContent_sem);
  }
  saveConfigFile();
}
void setPassword(String password)
{
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    ConfigContent["*password"] = password;
    xSemaphoreGive(configContent_sem);
  }
  saveConfigFile();
}
String getPassword()
{
  String password;
  if (!checkKey("*password"))
    return DEFAULT_PASSWORD;
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    password = ConfigContent["*password"];
    xSemaphoreGive(configContent_sem);
  }
  return password;
}
bool Authentication(String username, String password)
{
  if (getUsername() == username && getPassword() == password)
    return true;
  return false;
}
#endif
#endif

// Lấy giá trị của Key
// Lấy toàn bộ file content