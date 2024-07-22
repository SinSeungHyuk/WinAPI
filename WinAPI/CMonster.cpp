#include "pch.h"
#include "CMonster.h"
#include "CPlayer.h"
#include "CPlatform.h"
#include "MonsterData.h"
#include "CLogMgr.h"


#include "CTimeMgr.h"
#include "CCollider.h"


#include "CEngine.h"
#include "CAnimator.h"
#include "CRigidBody.h"

#include "DeathEventStrategy.h"



CMonster::CMonster(int hp, float speed, float range,DeathEventStrategy* deathEvent)
	: collider(nullptr), rigidbody(nullptr), animator(nullptr), deathEvent(deathEvent), isMonsterLeft(false), isDead(false)
{
	monsterData = new MonsterData( hp,speed,range);

	// RigidBody
	rigidbody = AddComponent(new CRigidBody);
	rigidbody->SetMass(1.f);
	rigidbody->SetMaxSpeed(300.f);
	rigidbody->SetFriction(1000.f);
	rigidbody->SetMaxGravitySpeed(1500.f);
}

CMonster::CMonster(const CMonster& _Other)
	: CObj(_Other)
	, monsterData(_Other.monsterData)
	, collider(nullptr)
	, rigidbody(nullptr)
	, animator(nullptr)
	, deathEvent(_Other.deathEvent)
	, isMonsterLeft(_Other.isMonsterLeft)
{

}

CMonster::~CMonster()
{
}

void CMonster::Tick()
{
	if (isDead) {
		Destroy(this);
		return;
	}
}

void CMonster::Render()
{
	animator->Render();
}

void CMonster::BeginOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* _OtherCollider)
{
	CPlayer* player = dynamic_cast<CPlayer*>(otherObj);
	if (player) {
		//int playerPos = player->GetPrevPos().y;
		//int monsterPos = GetPos().y - GetScale().y + 1.0f;

		//if (playerPos <= monsterPos) 
		//	deathEvent->OnDeath(*this);
		//else {
			player->Dead(); // 몬스터를 위에서 밟지 않으면 플레이어 사망
		//}
	}

	// 여기서는 기본적으로 모든 몬스터들이 땅 위에 올라서거나 위에 부딪힘
	CPlatform* platform = dynamic_cast<CPlatform*>(otherObj);
	if (platform)
	{
		float platformPosUp = platform->GetPos().y - platform->GetScale().y * 0.45;
		float platformPosDown = platform->GetPos().y + platform->GetScale().y * 0.45;
		float posUp = GetPos().y - GetScale().y;
		float posDown = GetPos().y;

		// 아래에서 위로 올라왔을때 부딪힘
		if (posUp - platformPosDown > 0.f)
			rigidbody->SetGravityVelocity(Vec2(0.f, 0.f));
		// 위에서 아래로 내려왔을때 부딪힘
		else if (posDown - platformPosUp <= 0.f)
			rigidbody->SetGround(true); // 바닥 윗면에 있을 경우 SetGround(true)
	}

	if (otherObj->GetLayerType() == (int)LAYER_TYPE::PLAYER_PROJECTILE) 
		deathEvent->OnDeath(*this);
}

void CMonster::Overlap(CCollider* ownCollider, CObj* otherObj, CCollider* _OtherCollider)
{
	if (otherObj->GetLayerType() == (int)LAYER_TYPE::PLATFORM)
	{
		rigidbody->SetGround(true);
	}
}

void CMonster::EndOverlap(CCollider* ownCollider, CObj* otherObj, CCollider* _OtherCollider)
{
	CPlatform* platform = dynamic_cast<CPlatform*>(otherObj);
	if (platform)
	{
		rigidbody->SetGround(false); // 바닥 윗면에 있다가 떨어질 경우 SetGround(false)
	}
}
