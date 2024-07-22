#include "pch.h"
#include "CStartPointItem.h"

#include "CCollider.h"
#include "CPlayer.h"
#include "CRigidBody.h"

CStartPointItem::CStartPointItem()
{
	collider = AddComponent(new CCollider);
	collider->SetName(L"Collider");
	collider->SetOffset(Vec2(0.f, 0.f));
	collider->SetScale(Vec2(32.f, 500.f));
}

CStartPointItem::~CStartPointItem()
{
}

void CStartPointItem::BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider)
{
	CPlayer* player = dynamic_cast<CPlayer*>(otherObj);

	if (player)
	{
		CRigidBody* playerRigidbody = player->GetComponent<CRigidBody>();

		player->SetCollisionType(OVERLAP_TYPE::IS_COLLISION_LEFT, true);
	}
}

void CStartPointItem::EndOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* otherCollider)
{
	CPlayer* player = dynamic_cast<CPlayer*>(otherObj);
	if (player)
	{
		CRigidBody* playerRigidbody = player->GetComponent<CRigidBody>();
		player->SetCollisionType(OVERLAP_TYPE::IS_COLLISION_LEFT, false);
	}
}
