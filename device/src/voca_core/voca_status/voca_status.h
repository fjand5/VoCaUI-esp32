#pragma once
#include "../voca_env.h"
#include <Arduino.h>

#define LIST_MODULE_FLAG_STATUS                      \
    MODULE_FLAG_STATUS(Status_WifiStation_Connected) \
    MODULE_FLAG_STATUS(Status_Store_Initialized)     \
    MODULE_FLAG_STATUS(Status_WebServer_Ready)       \
    MODULE_FLAG_STATUS(Status_WebSocket_Ready)       \
    MODULE_FLAG_STATUS(Status_SetupWifi_Done)

typedef enum
{
#define MODULE_FLAG_STATUS(name) \
    name,
    LIST_MODULE_FLAG_STATUS
#undef MODULE_FLAG_STATUS
} ModuleFlagReady_e;

class VocaStatus
{
private:
    EventGroupHandle_t systemStatus;

public:
    VocaStatus();
    void waitStatus(ModuleFlagReady_e status);
    void waitAllStatus();
    void setStatus(ModuleFlagReady_e status);
    void clearStatus(ModuleFlagReady_e status);
    ~VocaStatus();
};
extern VocaStatus vocaStatus;
