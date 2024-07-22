#pragma once
#include "CObj.h"

class TrapCondition;
class CTexture;
class CCollider;

class CTrap :
    public CObj
{
private:
    TrapCondition* trapCondition;

protected:
    CTexture* texture;
    CCollider* collider;
    bool isTrapActive = true;

public:
    void SetTexture(CTexture* texture) { this->texture = texture; }

    virtual void Tick() override;
    virtual void Render() override;
    virtual void BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider);

    virtual void ActiveTrap() final;
    virtual void IsTrapActive(bool isActive) {
        isTrapActive = isActive;
    }

    virtual CTrap* Clone() = 0;
    CTrap(TrapCondition* condition);
    ~CTrap();
};


