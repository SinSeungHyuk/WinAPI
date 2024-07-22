#pragma once
#include "CTrap.h"

class CCollider;
class CTexture;

class CTrapFire :
    public CTrap
{
private:
    CCollider* fireCollider;
    CTexture* fireOnTexture;

    float timer = 0.f;
    bool isFireOn = false;

public:
    CLONE(CTrapFire);
    CTrapFire(TrapCondition* condition);
    ~CTrapFire();

    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider);

    virtual void IsTrapActive(bool isActive) override;
};

