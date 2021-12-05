#pragma once
#define CONFIG_FILE "/config.txt"
#include "FS.h"
#include <LITTLEFS.h>
#include <map>
#include <list>
#include <WS2812FX.h>

void saveConfigFile();
void setValue(String key, String value, bool save = true);
std::map<String, String> ConfigContent;
typedef void (*configChangeCallback)(String, String);
std::list<configChangeCallback> onStoreChanges;
SemaphoreHandle_t spiffs_sem;
SemaphoreHandle_t configContent_sem;
void setOnStoreChange(void (*func)(String key, String value))
{
  onStoreChanges.push_front(func);
}
// Mỗi dòng là một phần tử (một cặp key value) (key):(value)\n
void loadFileIntoConfig(String content)
{
  log_d("%s", content.c_str());
  configContent_sem = xSemaphoreCreateBinary();
  while (content.indexOf("\n") >= 0)
  {
    String curLine = content.substring(0, content.indexOf("\n"));
    String key = curLine.substring(0, content.indexOf("="));
    String value = curLine.substring(content.indexOf("=") + 1);
    ConfigContent[key] = value;
    content.remove(0, curLine.length() + 1);
  }
  xSemaphoreGive(configContent_sem);
  xEventGroupSetBits(system_status, FLAG_INITIALIZED_STORE);
}
// Kiểm tra key có tồn tại không
bool checkKey(String key)
{
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    bool ret = ConfigContent.find(key) != ConfigContent.end();
    xSemaphoreGive(configContent_sem);
    return ret;
  }
  return false;
}

// Lấy giá trị của Key
String getValue(String key, String def = "", bool setDefaultTokey = true)
{
  if (checkKey(key))
  {
    if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
    {
      String ret = ConfigContent[key];
      xSemaphoreGive(configContent_sem);
      return ret;
    }
  }
  else
  {
    if (setDefaultTokey)
    {
      setValue(key, def, true);
    }
    return def;
  }
}
void getValueByObject(String key, JsonObject objectValue, String def = "", bool setDefaultTokey = true)
{
  String value = getValue(key, def, setDefaultTokey);
  objectValue[key] = value;

}
char *getValueByCStr(String key, String def = "", bool setDefaultTokey = true)
{
  char *ret;

  if (checkKey(key))
  {
    String tmp;
    if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
    {
      tmp = ConfigContent[key];
      xSemaphoreGive(configContent_sem);
    }
    ret = new char[tmp.length() + 1];
    strcpy(ret, tmp.c_str());
    return ret;
  }
  else
  {
    if (setDefaultTokey)
    {
      setValue(key, def, true);
    }
    String tmp = def;
    ret = new char[tmp.length() + 1];
    strcpy(ret, tmp.c_str());
    return ret;
  }
}
// Lấy toàn bộ file content
String getValuesByString()
{
  String ret = "";
  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    for (std::pair<String, String> e : ConfigContent)
    {
      String k = e.first;
      String v = e.second;
      ret += k + "=" + v + "\n";
    }
    xSemaphoreGive(configContent_sem);
  }
  return ret;
}
DynamicJsonDocument getValuesByJson()
{
  DynamicJsonDocument doc(8192);
  JsonObject obj = doc.to<JsonObject>();

  if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
  {
    for (std::pair<String, String> e : ConfigContent)
    {
      String k = e.first;
      String v = e.second;
      obj[k] = v;
    }
    xSemaphoreGive(configContent_sem);
  }
  return doc;
}
// Gán giá trị cho key
void setValue(String key, String value, bool save)
{

  bool noChange = ConfigContent[key] == value;
  if (!noChange)
  {
    if (key.indexOf("=") >= 0 || key.indexOf("\n") >= 0 || value.indexOf("\n") >= 0)
      return;
    if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
    {
      ConfigContent[key] = value;
      xSemaphoreGive(configContent_sem);
    }
  }

  for (auto onStoreChange = onStoreChanges.begin();
       onStoreChange != onStoreChanges.end();
       ++onStoreChange)
  {
    if ((*onStoreChange) != NULL)
    {
      (*onStoreChange)(key, value);
    }
  }

  log_d("key: %s; value: %s; save: %d; noChange: %d", key.c_str(), value.c_str(), save, noChange);
  // nếu không yêu cầu lưu vào flash hoặc giá trị như cũ
  if (!save || noChange)
  {
    return;
  }
  saveConfigFile();
}

void saveConfigFile()
{
  if (xSemaphoreTake(spiffs_sem, portMAX_DELAY) == pdTRUE)
  {
  REOPEN:
    File cfg_file = LITTLEFS.open(CONFIG_FILE, "w");
    if (!cfg_file)
    {
      cfg_file.close();
      delay(100);
      log_e("can't open file, reopening...");
      LITTLEFS.end();
      LITTLEFS.begin();
      goto REOPEN;
    }
    if (xSemaphoreTake(configContent_sem, portMAX_DELAY) == pdTRUE)
    {
      for (std::pair<String, String> e : ConfigContent)
      {
        String k = e.first;
        String v = e.second;
        cfg_file.print(k + "=" + v + "\n");
      }
      xSemaphoreGive(configContent_sem);
    }

    cfg_file.close();
    xSemaphoreGive(spiffs_sem);
  }
}
// Khởi tạo
void setupStore()
{
  spiffs_sem = xSemaphoreCreateBinary();
  if (!LITTLEFS.begin())
  {
    log_d("Can't mount LITTLEFS, Try format");
    LITTLEFS.format();
    if (!LITTLEFS.begin())
    {
      log_d("Can't mount SPIFFS");
      return;
    }
    else
    {
      log_d("SPIFFS mounted");
      xSemaphoreGive(spiffs_sem);
    }
  }
  else
  {
    log_d("SPIFFS mounted ");
    xSemaphoreGive(spiffs_sem);
  }
  if (xSemaphoreTake(spiffs_sem, portMAX_DELAY) == pdTRUE)
  {
    File cfg_file = LITTLEFS.open(CONFIG_FILE, "r");
    if (cfg_file)
    {
      String tmp = cfg_file.readString();
      loadFileIntoConfig(tmp);
    }
    else
    {
      LITTLEFS.open(CONFIG_FILE, "a");
    }
    cfg_file.close();
    xSemaphoreGive(spiffs_sem);
  }
}

void loopConfig()
{
}
