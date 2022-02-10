#include "esp_event.h"
#include "../voca_env.h"
#define VOCA_EVENTBUS_NAME "eventBusArgs"
#include <functional>

typedef std::function<void(String, String, void *)> EventBusFunction;

typedef struct
{
    String key;
    String val;
} EventBusData;
class VocaEventBus
{
private:
    int32_t idAutoIncrease = 1;
    esp_event_loop_args_t eventBusArgs = {
        .queue_size = 32,
        .task_name = VOCA_EVENTBUS_NAME,
        .task_priority = 0,
        .task_stack_size = 2048,
        .task_core_id = VOCA_CORE_CPU};
    esp_event_loop_handle_t eventBusHandle;

public:
    VocaEventBus(/* args */);
    int32_t addEventBus(
        const char* name,
        EventBusFunction cbEventBus, void *prams, bool anyId = false);
    void executeEventBus(
        const char* name,
        int32_t id,
        void *data,
        size_t data_size);
    ~VocaEventBus();
};
extern VocaEventBus vocaEventBus;