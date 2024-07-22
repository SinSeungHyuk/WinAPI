#pragma once
#include "CItem.h"
class CStartPointItem :
    public CItem
{
public:
    CLONE(CStartPointItem);
    CStartPointItem();
    ~CStartPointItem();

    virtual void GetItem() override {}

    virtual void BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider);
    virtual void EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider);

};
