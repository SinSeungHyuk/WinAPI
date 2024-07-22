#pragma once
#include "CTrap.h"

class CAnimator;

class CTrapSaw :
    public CTrap
{
private:
    CAnimator* animator;

public:
    CLONE(CTrapSaw);
    CTrapSaw(TrapCondition* condition);
    ~CTrapSaw();

    virtual void Render() override;
    virtual void BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider);

    virtual void IsTrapActive(bool isActive) override;
};

