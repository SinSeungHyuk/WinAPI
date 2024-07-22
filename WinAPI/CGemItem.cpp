#include "pch.h"
#include "CGemItem.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnim.h"
#include "CTaskMgr.h"
#include "CEngine.h"
#include "CPathMgr.h"

#include "CAssetMgr.h"
#include "CGameManager.h"
#include "CTexture.h"

CGemItem::CGemItem()
	: CItem()
	, animator(nullptr)
{
	collider = AddComponent(new CCollider);
	collider->SetName(L"Collider");
	collider->SetOffset(Vec2(0.f, -16.f));
	collider->SetScale(Vec2(32.f, 32.f));

	// Player 에 Animator 컴포넌트 추가
	animator = AddComponent(new CAnimator);

	animator->LoadAnimation(L"animation\\Item\\GEM.anim");

	animator->Play(L"GEM", true);
}

CGemItem::~CGemItem()
{
}


void CGemItem::Tick()
{
}

void CGemItem::Render()
{
	animator->Render();
}

void CGemItem::GetItem()
{
	CGameManager::Get()->GetGem();
}

