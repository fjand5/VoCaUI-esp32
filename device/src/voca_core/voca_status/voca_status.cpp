#include "voca_status.h"

VocaStatus::VocaStatus(/* args */)
{
    systemStatus = xEventGroupCreate();
}

VocaStatus::~VocaStatus()
{
}
void VocaStatus::waitStatus(ModuleFlagReady_e status)
{
    xEventGroupWaitBits(systemStatus, 1<<status, pdFALSE, pdFALSE, portMAX_DELAY);

};
void VocaStatus::waitAllStatus()
{
#define MODULE_FLAG_STATUS(name) \
    waitStatus(name);
    LIST_MODULE_FLAG_STATUS
#undef MODULE_FLAG_STATUS
};
void VocaStatus::setStatus(ModuleFlagReady_e status)
{
    xEventGroupSetBits(systemStatus, 1<<status);
};
void VocaStatus::clearStatus(ModuleFlagReady_e status)
{
    xEventGroupClearBits(systemStatus, 1<<status);
};

VocaStatus vocaStatus;