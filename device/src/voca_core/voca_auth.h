#pragma once
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ArduinoJWT.h>
#include "voca_store.h"

#define EXPIRE_TIME 48 * 24 * 60 * 1000 // miliseconds (2 ngày)
ArduinoJWT auth_jwt(__TIME__);
uint32_t simpleHash(String str)
{
    uint32_t ret = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        ret += int8_t(str[i]);
    }
    return ret;
}
String create_auth_jwt()
{
    DynamicJsonDocument _doc(128);
    JsonObject obj = _doc.to<JsonObject>();
    obj["exp"] = String(millis() + EXPIRE_TIME);
    obj["hpw"] = simpleHash(getPassword());
    String tmp;
    serializeJson(_doc, tmp);
    return auth_jwt.encodeJWT(tmp);
}
bool check_auth_jwt(String token)
{
    DynamicJsonDocument _doc(128);
    String payload;
    if (auth_jwt.decodeJWT(token, payload))
    {
        DeserializationError err = deserializeJson(_doc, payload);
        if (err) // sai cấu trúc json
            return false;
        JsonObject obj = _doc.as<JsonObject>();
        int exp = obj["exp"];

        if (exp < millis() || exp >= (millis() + EXPIRE_TIME)) 
        // hết hạn hoặc  không hợp lệ
        {
            return false;
        }
        if (obj["hpw"] != simpleHash(getPassword())) // mật khẩu đã thay đổi
        {
            return false;
        }
        return true;
    }
    else
    {
        return false;
    }
}