#pragma once
#if defined(ESP8266)
#include <ESP8266WiFi.h>
#elif defined(ESP32)
#include <WiFi.h>
#endif
#include <ArduinoJson.h>
#include "store.h"
#include "webserver.h"
#define APID "vocaui"
#define APPW "12345678"
void scanWifi();
void setWifi();
void getWifi();
void WiFiStationDisconnected(WiFiEvent_t event, WiFiEventInfo_t info){
  if (checkKey("_ssid") && checkKey("_sspw"))
  {
    WiFi.begin(getValueByCStr("_ssid"), getValueByCStr("_sspw"));
  // WiFi.begin("Vong Cat-Hide", "78787878");

    while (WiFi.status() != WL_CONNECTED && millis() < 30000)
    {
      delay(500);
      Serial.print(".");
    }
  }

}
void setupWifi(void)
{
  WiFi.mode(WIFI_AP_STA);
  if (checkKey("_apid") && checkKey("_appw"))
  {
    WiFi.softAP(getValueByCStr("_apid"), getValueByCStr("_appw"));
  }
  else
  {
    WiFi.softAP(APID, APPW);
  }
  if (checkKey("_ssid") && checkKey("_sspw"))
  {
    WiFi.begin(getValueByCStr("_ssid"), getValueByCStr("_sspw"));
  // WiFi.begin("Vong Cat-Hide", "78787878");

    while (WiFi.status() != WL_CONNECTED && millis() < 30000)
    {
      delay(500);
      Serial.print(".");
    }
  }
  // WiFi.begin("Vong Cat-Hide", "78787878");

  Serial.println("");

  // Wait for connection
  if (WiFi.status() != WL_CONNECTED)
  {
    WiFi.mode(WIFI_AP);
    Serial.println("Only AP mode");
  }
  else
  {
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(getValue("_ssid"));
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  
  WiFi.onEvent(WiFiStationDisconnected, SYSTEM_EVENT_STA_DISCONNECTED);
  addHttpApi("scanWifi", scanWifi);
  addHttpApi("setWifi", setWifi);
  addHttpApi("getWifi", getWifi);
}

void loopWifi(void)
{
}

void scanWifi()
{
  DynamicJsonDocument doc(2048);
  JsonArray array = doc.to<JsonArray>();
  String ssid;
  int32_t rssi;
  uint8_t encryptionType;
  uint8_t *bssid;
  int32_t channel;
  bool hidden;
  int scanResult;

  Serial.println(F("Starting WiFi scan..."));

  scanResult = WiFi.scanNetworks(/*async=*/false, /*hidden=*/true);

  if (scanResult == 0)
  {
    Serial.println(F("No networks found"));
  }
  else if (scanResult > 0)
  {
    Serial.printf(PSTR("%d networks found:\n"), scanResult);

    // Print unsorted scan results
    for (int8_t i = 0; i < scanResult; i++)
    {
      JsonObject nestedObj = array.createNestedObject();
      WiFi.getNetworkInfo(i, ssid, encryptionType, rssi, bssid, channel);
      nestedObj["ssid"] = WiFi.SSID(i);
      nestedObj["rssi"] = WiFi.RSSI(i);

      Serial.printf(PSTR("  %02d: [CH %02d] [%02X:%02X:%02X:%02X:%02X:%02X] %ddBm %c %c %s\n"),
                    i,
                    channel,
                    bssid[0], bssid[1], bssid[2],
                    bssid[3], bssid[4], bssid[5],
                    rssi,
                    WiFi.encryptionType(i) ? ' ' : '*',
                    hidden ? 'H' : 'V',
                    ssid.c_str());
      delay(0);
    }
  }
  else
  {
    Serial.printf(PSTR("WiFi scan error %d"), scanResult);
  }
  String ret;
  serializeJson(array, ret);
  server.send(200, "application/json", ret.c_str());
}

void setWifi()
{
  DynamicJsonDocument doc(256);
  auto err = deserializeJson(doc, server.arg(0));

  if (!err)
  {
    setValue("_ssid", doc["ssid"], true);
    setValue("_sspw", doc["sspw"], true);
  }
  server.send(200, "application/json", server.arg(0));
}
void getWifi()
{
  DynamicJsonDocument doc(256);
  JsonObject obj = doc.to<JsonObject>();
  obj["wifi"] = getValue("_ssid");
  obj["ip"] = WiFi.localIP().toString();
  String ret;
  serializeJson(obj, ret);
  server.send(200, "application/json", ret);
}