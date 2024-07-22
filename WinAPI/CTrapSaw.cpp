#include "pch.h"
#include "CTrapSaw.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnim.h"
#include "CTaskMgr.h"
#include "CEngine.h"
#include "CPathMgr.h"

#include "CAssetMgr.h"
#include "CGameManager.h"
#include "CTexture.h"

CTrapSaw::CTrapSaw(TrapCondition* condition)
	: CTrap(condition), animator(nullptr)
{
	collider = AddComponent(new CCollider);
	collider->SetName(L"Collider");
	collider->SetOffset(Vec2(0.f, -38.f));
	collider->SetScale(Vec2(76.f, 76.f));

	// Player 에 Animator 컴포넌트 추가
	animator = AddComponent(new CAnimator);

	animator->LoadAnimation(L"animation\\Trap\\Trap_Saw.anim");

	animator->Play(L"Trap_Saw", true);
}

CTrapSaw::~CTrapSaw()
{
}

void CTrapSaw::Render()
{
	if (!isTrapActive) return;

	animator->Render();
}

void CTrapSaw::BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider)
{
	if (otherObj->GetLayerType() == (int)LAYER_TYPE::PLAYER)
		ActiveTrap();
}

void CTrapSaw::IsTrapActive(bool isActive)
{
	CTrap::IsTrapActive(isActive);

	if (!isActive) {
		collider->Deactivate();
	}
	else {
		collider->Activate();
	}
}
