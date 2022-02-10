#pragma once
#include "voca_env.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ArduinoJWT.h>
#include "voca_store/voca_store.h"
class VocaAuth: public ArduinoJWT
{
private:

    Preferences authPreferences;
    uint32_t createHash(String str);
public:
    VocaAuth();
    void begin();
    String createAuthJwt();
    bool checkAuthJwt(String token);
    String getPassword();
    String getUsername();
    void setPassword(String pwd);
    void setUsername(String usr);

    ~VocaAuth();
};
extern VocaAuth vocaAuth;