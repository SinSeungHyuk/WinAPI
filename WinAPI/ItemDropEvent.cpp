#include "pch.h"
#include "ItemDropEvent.h"
#include "CLogMgr.h"
#include "CMonster.h"
#include "CAnimator.h"
#include "CTimeMgr.h"

#include "CCoinItem.h"

ItemDropEvent::ItemDropEvent(CItem* item)
	: item(item)
{
}

void ItemDropEvent::OnDeath(CMonster& monster)
{
	//LOG(LOG_LEVEL::LOG, L"OnDeath Log Test");

	monster.PlayAnimation(ANIMATION_TYPE::DEAD);

	monster.IsDead(true);

	item->SetPos(monster.GetPos().x, monster.GetPos().y);
	CreateObject(item, LAYER_TYPE::ITEM);
}


