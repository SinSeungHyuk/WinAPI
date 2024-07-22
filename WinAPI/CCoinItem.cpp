#include "pch.h"
#include "CCoinItem.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnim.h"
#include "CTaskMgr.h"
#include "CEngine.h"
#include "CPathMgr.h"

#include "CAssetMgr.h"
#include "CGameManager.h"
#include "CTexture.h"

CCoinItem::CCoinItem()
	: CItem()
	, animator(nullptr)
{
	collider = AddComponent(new CCollider);
	collider->SetName(L"Collider");
	collider->SetOffset(Vec2(0.f, -16.f));
	collider->SetScale(Vec2(32.f, 32.f));

	// Player 에 Animator 컴포넌트 추가
	animator = AddComponent(new CAnimator);

	animator->LoadAnimation(L"animation\\Item\\COIN.anim");

	animator->Play(L"COIN", true);
}

CCoinItem::~CCoinItem()
{
}


void CCoinItem::Tick()
{
}

void CCoinItem::Render()
{
	animator->Render();
}

void CCoinItem::GetItem()
{
	CGameManager::Get()->GetCoin();
}

