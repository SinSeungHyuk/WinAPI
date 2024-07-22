#pragma once
#include "TrapCondition.h"
class MoveTrapCondition :
    public TrapCondition
{
private:
    const float moveDistance; // ������ �̵��� �Ÿ�
    float currentMoveDistance = 0.f; // ������ ������� �̵��� �Ÿ�
    float speed;
    bool isUp = true; // ������ ���� �ö󰡰��ִ���

public:
    MoveTrapCondition(float distance, float speed);
    virtual void ActiveTrap() override;
};

