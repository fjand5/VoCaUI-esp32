#pragma once
#include <Arduino.h>
#define FLAG_CONNECTED_STA (1 << 0)
#define FLAG_INITIALIZED_STORE (2 << 0)
#define FLAG_WEBSERVER_READY (3 << 0)
#define FLAG_WEBSOCKET_READY (4 << 0)

#define WAIT_FLAG_SET(flag) xEventGroupWaitBits( system_status, flag, pdFALSE, pdFALSE, portMAX_DELAY)
#define SET_FLAG(flag) xEventGroupSetBits(system_status, flag)

EventGroupHandle_t system_status;
void settupStatus()
{
    /* Attempt to create the event group. */
    system_status = xEventGroupCreate();
    /* Was the event group created successfully? */
    if (system_status == NULL)
    {
        /* The event group was not created because there was insufficient
        FreeRTOS heap available. */
        log_e("can't create system_status");
    }
    else
    {
        /* The event group was created. */
        log_d("created system_status");
    }
}