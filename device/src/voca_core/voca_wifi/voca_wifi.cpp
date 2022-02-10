#include "voca_wifi.h"
VocaWifi vocaWifi;


#if 1
static void scanWifi()
{
  DynamicJsonDocument doc(2048);
  JsonArray array = doc.to<JsonArray>();
  String ssid;
  int32_t rssi;
  uint8_t encryptionType;
  uint8_t *bssid;
  int32_t channel;
  int scanResult;

  log_d("Starting WiFi scan...");

  scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);

  if (scanResult == 0)
  {
    log_d("No networks found");
  }
  else if (scanResult > 0)
  {
    for (int8_t i = 0; i < scanResult; i++)
    {
      JsonObject nestedObj = array.createNestedObject();
      WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel);
      nestedObj["ssid"] = WiFi.SSID(i);
      nestedObj["rssi"] = WiFi.RSSI(i);
      delay(0);
    }
  }
  else
  {
  }
  String ret;
  serializeJson(array, ret);
  vocaWebserver.send(200, "application/json", ret.c_str());
}
static void setWifi()
{
  DynamicJsonDocument doc(256);
  auto err = deserializeJson(doc, vocaWebserver.arg(0));

  if (!err)
  {
    vocaStore.setValue("_ssid", doc["ssid"], true);
    vocaStore.setValue("_sspw", doc["sspw"], true);
  }
  vocaWebserver.send(200, "application/json", vocaWebserver.arg(0));
}
static void getWifi()
{
  DynamicJsonDocument doc(256);
  JsonObject obj = doc.to<JsonObject>();
  obj["wifi"] = vocaStore.getValue("_ssid");
  obj["ip"] = WiFi.localIP().toString();
  String ret;
  serializeJson(obj, ret);
  vocaWebserver.send(200, "application/json", ret);
}

#endif
static void cbWiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info)
{
  if (vocaStore.checkKey("_ssid") && vocaStore.checkKey("_sspw"))
  {
    WiFi.begin(vocaStore.getValueByCStr("_ssid"), vocaStore.getValueByCStr("_sspw"));
    // WiFi.begin("Vong Cat 3", "78787878");

    while (WiFi.status() != WL_CONNECTED && millis() < 30000)
    {
      delay(500);
      log_d(".");
    }
    if (WiFi.status() == WL_CONNECTED)
    {
      vocaStatus.setStatus(Status_WifiStation_Connected);
    }
  }
}
// static void scanWifi(){};

VocaWifi::VocaWifi(/* args */)
{
}
void VocaWifi::begin()
{
    vocaStatus.waitStatus(Status_Store_Initialized);
    WiFi.mode(WIFI_AP_STA);
    if (vocaStore.checkKey("_apid") && vocaStore.checkKey("_appw"))
    {
        WiFi.softAP(vocaStore.getValueByCStr("_apid"), vocaStore.getValueByCStr("_appw"));
    }
    else
    {
        String mac = WiFi.macAddress();
        mac.replace(":", "");
        String apid = String(APID) + "-" + mac;
        WiFi.softAP(apid.c_str(), APPW);
    }
    
    char *ssid = vocaStore.getValueByCStr("_ssid", "Vong Cat-Hide");
    char *sspw = vocaStore.getValueByCStr("_sspw", "78787878");
    WiFi.begin(ssid, sspw);
    

    while (WiFi.status() != WL_CONNECTED && millis() < 30000)
    {
        delay(500);
        log_d(".");
    }

    if (WiFi.status() != WL_CONNECTED)
    {
        WiFi.mode(WIFI_AP);
        log_w("Only AP mode");
    }
    else
    {
        log_d("\nConnected to: %s", vocaStore.getValueByCStr("_ssid"));
        WiFi.onEvent(cbWiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);
        vocaStatus.setStatus(Status_WifiStation_Connected);
    }

    vocaWebserver.addHttpApi("scanWifi", scanWifi);
    vocaWebserver.addHttpApi("setWifi", setWifi);
    vocaWebserver.addHttpApi("getWifi", getWifi);
    vocaStatus.setStatus(Status_SetupWifi_Done);
}
