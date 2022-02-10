#include "voca_auth.h"
VocaAuth vocaAuth;

VocaAuth::VocaAuth() : ArduinoJWT(__TIME__)
{
}

void VocaAuth::begin()
{
    authPreferences.begin("VocaAuth");
}

String VocaAuth::getPassword()
{
    return authPreferences.getString("pwd", DEFAULT_PASSWORD);
};

String VocaAuth::getUsername()
{
    return authPreferences.getString("usr", DEFAULT_USERNAME);
};
void VocaAuth::setPassword(String pwd){

};
void VocaAuth::setUsername(String usr){

};
uint32_t VocaAuth::createHash(String str)
{
    uint32_t ret = 0;
    for (size_t i = 0; i < str.length(); i++)
    {
        ret += int8_t(str[i]);
    }
    return ret;
}

String VocaAuth::createAuthJwt()
{
    DynamicJsonDocument _doc(128);
    JsonObject obj = _doc.to<JsonObject>();
    obj["exp"] = String(millis() + EXPIRE_TIME);
    obj["hpw"] = createHash(getPassword());
    String tmp;
    serializeJson(_doc, tmp);
    return encodeJWT(tmp);
}

bool VocaAuth::checkAuthJwt(String token)
{
    DynamicJsonDocument _doc(128);
    String payload;
    if (decodeJWT(token, payload))
    {
        DeserializationError err = deserializeJson(_doc, payload);
        if (err) // sai cấu trúc json
            return false;
        JsonObject obj = _doc.as<JsonObject>();

#ifdef CHECK_EXPIRE
        int exp = obj["exp"];
        if (exp < millis() || exp >= (millis() + EXPIRE_TIME))
        // hết hạn hoặc  không hợp lệ
        {
            return false;
        }
#endif
        if (obj["hpw"] != createHash(getPassword())) // mật khẩu đã thay đổi
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
VocaAuth::~VocaAuth()
{
}