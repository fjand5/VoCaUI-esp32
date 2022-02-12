#include "voca_store.h"
VocaStore vocaStore;
bool VocaStore::mountSpiffs()
{
    log_d("==== Initializing SPIFFS ====\n");
    delay(111);
    if (!SPIFFS.begin())
    {
        log_w("Can't mount SPIFFS, Try format\n");
        SPIFFS.format();
        if (!SPIFFS.begin())
        {
            log_w("Can't mount SPIFFS\n");
            log_e("==== Initialize SPIFFS failed ====\n");
            return false;
        }
        else
        {
            log_d("SPIFFS mounted\n");
            return true;
        }
    }
    else
    {
        log_d("SPIFFS mounted\n");
        return true;
    }
}

bool VocaStore::loadFileToContent()
{
    File cfg_file = SPIFFS.open(CONFIG_FILE, "r");
    if (cfg_file)
    {
        String content = cfg_file.readString();
        // Mỗi dòng là một phần tử (một cặp key value) (key)=(value)
        log_d("\n=======\n%s=======\n", content.c_str());
        while (content.indexOf("\n") >= 0)
        {
            String curLine = content.substring(0, content.indexOf("\n"));
            String key = curLine.substring(0, content.indexOf("="));
            String value = curLine.substring(content.indexOf("=") + 1);
            storeContent[key] = value;
            content.remove(0, curLine.length() + 1);
        }
        semStoreContent = xSemaphoreCreateBinary();
        xSemaphoreGive(semStoreContent);
        return true;
    }
    else
    {
        // create file if not exist
        SPIFFS.open(CONFIG_FILE, "a");
    }
    cfg_file.close();
}
VocaStore::VocaStore()
{
}
void VocaStore::begin()
{

    if (!mountSpiffs())
    {
        return;
    }
    semSpiffs = xSemaphoreCreateBinary();
    xSemaphoreGive(semSpiffs);
    loadFileToContent();
    vocaStatus.setStatus(Status_Store_Initialized);
    ready();
}
bool VocaStore::checkValidKey(const String key)
{
    if (key.startsWith("*")       // system key
        || key.indexOf("=") >= 0  // invalid key
        || key.indexOf("\n") >= 0 // invalid key
    )
        return false;
    return true;
}
bool VocaStore::checkValidValue(const String value)
{
    if (value.indexOf("=") >= 0     // invalid value
        || value.indexOf("\n") >= 0 // invalid value
    )
        return false;
    return true;
}
void VocaStore::setValue(const String key, const String value, const bool save)
{
    log_d("Setting Value: key: %s; value: %s\n", key.c_str(), value.c_str());
    bool isNoChange = storeContent[key] == value;
    if (!isNoChange)
    {
        if (!checkValidKey(key) || !checkValidValue(value))
        {
            return;
        }

        if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
        {
            storeContent[key] = value;
            xSemaphoreGive(semStoreContent);
        }
    }
    else
    {
        log_d("Nothing change!!!\n");
    }

    EventBusData *eventBusData = new EventBusData;
    eventBusData->key = key;
    eventBusData->val = value;
    vocaEventBus.executeEventBus(VOCA_STORE_NAME, 0, (void *)eventBusData, sizeof(EventBusData));
    // nếu không yêu cầu lưu vào flash hoặc giá trị như cũ
    if (!save || isNoChange)
    {
        return;
    }
    updateStore();
};
bool VocaStore::updateStore()
{
    if (xSemaphoreTake(semSpiffs, portMAX_DELAY) == pdTRUE)
    {
    REOPEN:
        File cfg_file = SPIFFS.open(CONFIG_FILE, "w");
        if (!cfg_file)
        {
            cfg_file.close();
            delay(100);
            log_e("Can't open file, reopening...");
            SPIFFS.end();
            SPIFFS.begin();
            goto REOPEN;
        }
        if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
        {
            for (std::pair<String, String> e : storeContent)
            {
                String k = e.first;
                String v = e.second;
                cfg_file.print(k + "=" + v + "\n");
            }
            xSemaphoreGive(semStoreContent);
        }

        cfg_file.close();
        xSemaphoreGive(semSpiffs);
        return true;
    }
    return false;
}
void VocaStore::addStoreChangeEvent(EventBusFunction cb, void *prams)
{
    vocaEventBus.addEventBus(VOCA_STORE_NAME, cb,
                             prams, true);
}

bool VocaStore::checkKey(const String key)
{
    if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
    {
        bool ret = storeContent.find(key) != storeContent.end();
        xSemaphoreGive(semStoreContent);
        return ret;
    }
    return false;
}
const String VocaStore::getValue(const String key, const String def, bool createIfNotExist, bool save)
{
    if (!checkValidKey(key))
        return "";
    if (checkKey(key))
    {
        if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
        {
            String ret = storeContent[key];
            xSemaphoreGive(semStoreContent);
            return ret;
        }
    }
    else
    {
        if (createIfNotExist)
        {
            setValue(key, def, save);
        }
        return def;
    }
}
void VocaStore::readValueToObject(const String key, JsonObject objectValue, const String def, bool createIfNotExist)
{
    if (!checkValidKey(key))
        return;
    String value = getValue(key, def, createIfNotExist);
    objectValue[key] = value;
}
char *VocaStore::getValueByCStr(const String key, const String def, bool createIfNotExist)
{
    char *ret = nullptr;
    if (!checkValidKey(key))
    {
        return ret;
    }
    if (checkKey(key))
    {
        String tmp;
        if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
        {
            tmp = storeContent[key];
            xSemaphoreGive(semStoreContent);
        }
        ret = new char[tmp.length() + 1];
        strcpy(ret, tmp.c_str());
        return ret;
    }
    else
    {
        if (createIfNotExist)
        {
            setValue(key, def, true);
        }
        String tmp = def;
        ret = new char[tmp.length() + 1];
        strcpy(ret, tmp.c_str());
        return ret;
    }
}
String VocaStore::getStore()
{
    String ret = "";
    if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
    {
        for (std::pair<String, String> e : storeContent)
        {
            String k = e.first;
            if (k.startsWith("*"))
                continue;
            String v = e.second;
            ret += k + "=" + v + "\n";
        }
        xSemaphoreGive(semStoreContent);
    }
    return ret;
}
void VocaStore::readStore(JsonObject objectValues)
{
    if (xSemaphoreTake(semStoreContent, portMAX_DELAY) == pdTRUE)
    {
        for (std::pair<String, String> e : storeContent)
        {
            String k = e.first;
            if (k.startsWith("*"))
                continue;
            String v = e.second;
            objectValues[k] = v;
        }
        xSemaphoreGive(semStoreContent);
    }
}