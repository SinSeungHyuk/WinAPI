#pragma once
#include "TrapCondition.h"
class MoveTrapCondition :
    public TrapCondition
{
private:
    const float moveDistance; // 함정이 이동할 거리
    float currentMoveDistance = 0.f; // 함정이 현재까지 이동한 거리
    float speed;
    bool isUp = true; // 함정이 위로 올라가고있는지

public:
    MoveTrapCondition(float distance, float speed);
    virtual void ActiveTrap() override;
};

