#include "pch.h"
#include "CEndPointItem.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnim.h"
#include "CTaskMgr.h"
#include "CEngine.h"
#include "CPathMgr.h"

#include "CAssetMgr.h"
#include "CGameManager.h"
#include "CTexture.h"
#include "CImage.h"

CEndPointItem::CEndPointItem()
	: CItem()
	, animator(nullptr)
{
	collider = AddComponent(new CCollider);
	collider->SetName(L"Collider");
	collider->SetOffset(Vec2(0.f, -16.f));
	collider->SetScale(Vec2(32.f, 32.f));

	// Player 에 Animator 컴포넌트 추가
	animator = AddComponent(new CAnimator);

	animator->LoadAnimation(L"animation\\Item\\ENDPOINT.anim");

	animator->Play(L"ENDPOINT", true);
}

CEndPointItem::~CEndPointItem()
{
}

void CEndPointItem::Tick()
{
}

void CEndPointItem::Render()
{
	animator->Render();
}

void CEndPointItem::GetItem()
{
	CGameManager::Get()->GameClear();

	CImage* image = new CImage;
	image->SetPos(645.f, 0.f);
	image->SetTexture(CAssetMgr::Get()->LoadTexture(L"clear", L"texture\\clear.png"));
	CreateObject(image, LAYER_TYPE::UI);
}

