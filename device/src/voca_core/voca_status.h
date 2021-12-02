#pragma once
#include <Arduino.h>
#define FLAG_CONNECTED_STA (1<<0)
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