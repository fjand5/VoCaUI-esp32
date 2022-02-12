#ifndef VOCA_BASE
#define VOCA_BASE

#include <functional>

class VocaBase
{
private:
    typedef std::function<void(void)> OnReady;
    OnReady onReady;

protected:
    void ready();

public:
    VocaBase(/* args */);
    void setOnReady(OnReady cbOnReady);
};
#endif