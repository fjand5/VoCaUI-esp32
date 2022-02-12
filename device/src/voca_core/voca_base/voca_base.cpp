#include "voca_base.h"
VocaBase::VocaBase()
{
}
void VocaBase::setOnReady(OnReady cbOnReady)
{
    onReady = cbOnReady;
}
void VocaBase::ready()
{
    if (onReady != NULL)
        onReady();
}