#include "voca_eventbus.h"
VocaEventBus vocaEventBus;
VocaEventBus::VocaEventBus(/* args */)
{

    esp_event_loop_create(&eventBusArgs, &eventBusHandle);
}

int32_t VocaEventBus::addEventBus(
    const char* name, EventBusFunction cbEventBus, void *prams, bool anyId)
{
    typedef struct
    {
        EventBusFunction func;
        void *p;
    } AddEventBusBundle;
    AddEventBusBundle *addEventBusBundle = new AddEventBusBundle;
    addEventBusBundle->func = cbEventBus;
    addEventBusBundle->p = prams;

    int32_t id;
    if (anyId)
    {
        id = ESP_EVENT_ANY_ID;
    }
    else
    {

        id = idAutoIncrease;
    }
    idAutoIncrease++;
    esp_event_handler_register_with(
        eventBusHandle,
        name,
        id,
        [](void *event_handler_arg,
           esp_event_base_t event_base,
           int32_t event_id,
           void *event_data)
        {
            AddEventBusBundle *_addEventBusBundle = (AddEventBusBundle *)event_handler_arg;
            EventBusData *eventBusData = (EventBusData *)event_data;
            _addEventBusBundle->func(eventBusData->key, eventBusData->val, _addEventBusBundle->p);
        },
        (void *)addEventBusBundle);
    return id;
};

void VocaEventBus::executeEventBus(
    const char* name, int32_t id,
    void *data,
    size_t data_size)
{
    esp_event_post_to(
        eventBusHandle,
        name,
        id,
        data,
        data_size,
        portMAX_DELAY);

};
VocaEventBus::~VocaEventBus()
{
}
