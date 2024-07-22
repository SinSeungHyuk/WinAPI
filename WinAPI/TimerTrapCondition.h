#pragma once
#include "TrapCondition.h"
class TimerTrapCondition :
    public TrapCondition
{
private:
    float timer = 0.f;
    bool isActive = false;

public:
    virtual void ActiveTrap() override;
};

