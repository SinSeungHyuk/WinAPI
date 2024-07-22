#include "pch.h"
#include "CTrap.h"
#include "TrapCondition.h"
#include "CTexture.h"
#include "CPlayer.h"
#include "CEngine.h"
#include "CGameManager.h"
#include "CLogMgr.h"
#include "CTimeMgr.h"


CTrap::CTrap(TrapCondition* condition)
	: trapCondition(condition), texture(nullptr), collider(nullptr)
{
	trapCondition->owner = this;
}

CTrap::~CTrap()
{
}

void CTrap::Tick()
{
	trapCondition->ActiveTrap();
}

void CTrap::Render()
{
}

void CTrap::BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider)
{
}

void CTrap::ActiveTrap()
{
	CPlayer* player = CGameManager::Get()->GetPlayer();

	if (player != nullptr)
		//LOG(LOG_LEVEL::LOG, L"Æ®·¦¿¡ ´ê¾ÒÀ½");
		player->Dead();
}


