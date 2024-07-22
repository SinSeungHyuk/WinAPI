#include "pch.h"
#include "CTrapSpike.h"

#include "CCollider.h"
#include "CTaskMgr.h"
#include "CEngine.h"
#include "CPathMgr.h"

#include "CAssetMgr.h"
#include "CGameManager.h"
#include "CTexture.h"

CTrapSpike::CTrapSpike(TrapCondition* condition)
	: CTrap(condition)
{
	collider = AddComponent(new CCollider);
	collider->SetName(L"Collider");
	collider->SetOffset(Vec2(0.f, -16.f));
	collider->SetScale(Vec2(32.f, 32.f));

	texture = CAssetMgr::Get()->LoadTexture(L"Trap_Spike", L"texture\\Trap_Spike.png");
}

CTrapSpike::~CTrapSpike()
{
}

void CTrapSpike::Render()
{
	if (!isTrapActive) return;

	if (texture) {
		Vec2 vPos = GetRenderPos();
		UINT width = texture->GetWidth();
		UINT height = texture->GetHeight();

		TransparentBlt(BackDC, (int)vPos.x-16.f, (int)vPos.y - 32.f
			, width, height, texture->GetDC(), 0, 0, width, height, RGB(0, 0, 0));
	}
}

void CTrapSpike::BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider)
{
	if (otherObj->GetLayerType() == (int)LAYER_TYPE::PLAYER)
		ActiveTrap();
}

void CTrapSpike::IsTrapActive(bool isActive)
{
	CTrap::IsTrapActive(isActive);

	if (!isActive) {
		collider->Deactivate();
	}
	else {
		collider->Activate();
	}
}
