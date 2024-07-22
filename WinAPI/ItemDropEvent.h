#pragma once
#include "DeathEventStrategy.h"

class CItem;

class ItemDropEvent :
    public DeathEventStrategy
{
private:
    CItem* item;

public:
    ItemDropEvent(CItem* item);
    void OnDeath(CMonster& monster) override;
};

