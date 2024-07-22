#pragma once
#include "CTrap.h"
class CTrapSpike :
    public CTrap
{
private:


public:
    CLONE(CTrapSpike);
    CTrapSpike(TrapCondition* condition);
    ~CTrapSpike();


    virtual void Render() override;
    virtual void BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider);

    virtual void IsTrapActive(bool isActive) override;
};

