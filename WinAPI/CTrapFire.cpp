#include "pch.h"
#include "CTrapFire.h"

#include "CCollider.h"
#include "CTaskMgr.h"
#include "CEngine.h"
#include "CPathMgr.h"
#include "CTimeMgr.h"
#include "CPlayer.h"

#include "CAssetMgr.h"
#include "CGameManager.h"
#include "CTexture.h"

CTrapFire::CTrapFire(TrapCondition* condition)
	: CTrap(condition), fireOnTexture(nullptr), fireCollider(nullptr)
{
	collider = AddComponent(new CCollider);
	collider->SetName(L"Collider");
	collider->SetOffset(Vec2(0.f, -16.f));
	collider->SetScale(Vec2(32.f, 32.f));

	fireCollider = AddComponent(new CCollider);
	fireCollider->SetName(L"fireCollider");
	fireCollider->SetOffset(Vec2(0.f, -48.f));
	fireCollider->SetScale(Vec2(30.f, 32.f));
	fireCollider->Deactivate();

	texture = CAssetMgr::Get()->LoadTexture(L"Trap_Fire_Off", L"texture\\Trap_Fire_Off.png");
	fireOnTexture = CAssetMgr::Get()->LoadTexture(L"Trap_Fire_On", L"texture\\Trap_Fire_On.png");
}

CTrapFire::~CTrapFire()
{
}

void CTrapFire::Tick()
{
	CTrap::Tick();

	timer += DT;

	if (timer > 2.f) {
		timer = 0.f;

		if (fireCollider->IsActive())
			fireCollider->Deactivate();
		else fireCollider->Activate();

		isFireOn = !isFireOn;
	}
}

void CTrapFire::Render()
{
	if (!isTrapActive) return;

	if (isFireOn)
	{
		Vec2 vPos = GetRenderPos();
		UINT width = fireOnTexture->GetWidth();
		UINT height = fireOnTexture->GetHeight();

		TransparentBlt(BackDC, (int)vPos.x - 16.f, (int)vPos.y - 64.f
			, width, height, fireOnTexture->GetDC(), 0, 0, width, height, RGB(0, 0, 0));
	}

	else {
		Vec2 vPos = GetRenderPos();
		UINT width = texture->GetWidth();
		UINT height = texture->GetHeight();

		TransparentBlt(BackDC, (int)vPos.x - 16.f, (int)vPos.y - 64.f
			, width, height, texture->GetDC(), 0, 0, width, height, RGB(0, 0, 0));
	}
}

void CTrapFire::BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider)
{
	if (ownCollider == fireCollider && otherObj->GetLayerType() == (int)LAYER_TYPE::PLAYER)
		ActiveTrap();
}

void CTrapFire::IsTrapActive(bool isActive)
{
	CTrap::IsTrapActive(isActive);

	if (!isActive) {
		timer = 0.f;
		collider->Deactivate();
	}
	else {
		collider->Activate();
	}
}
