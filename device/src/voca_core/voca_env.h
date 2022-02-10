#pragma once
#include <Preferences.h>

#define VOCA_CORE_CPU 1

// Bật/Tắt tính năng kiểm tra quá hạn token
// #define AUTH_FEATURE
#define CHECK_EXPIRE
#define EXPIRE_TIME 48 * 24 * 60 * 1000 // miliseconds (2 ngày)
#define DEFAULT_USERNAME "admin"
#define DEFAULT_PASSWORD "12345678"


// #define USE_DATA_FROM_FILE
#define APID "vocaui"
#define APPW "12345678"

#define CONFIG_FILE "/config.txt"

