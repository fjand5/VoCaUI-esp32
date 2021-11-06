#pragma once
#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <list>


typedef void (*OnMinute)(int h, int m);
std::list < OnMinute > OnMinutes;
void setOnMinute(OnMinute cb){
  OnMinutes.push_front(cb);
}

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, 3600*7);
int lastMinute = -1;
bool gotTime = false;
void setupTimer(){
  timeClient.begin();
  gotTime = timeClient.update();
   
  Serial.println(timeClient.getFormattedTime());
}

void loopTimer() {
  if(!gotTime)
    gotTime = timeClient.update();

  if(timeClient.getMinutes() != lastMinute){
    lastMinute = timeClient.getMinutes();
    for (auto const& item : OnMinutes){
        if(item != NULL)
            item(timeClient.getHours(),timeClient.getMinutes());
    }
  }
}