#include "pch.h"
#include "CPlayer.h"

#include "CDebugMgr.h"

#include "CTimeMgr.h"
#include "CLevelMgr.h"
#include "CLevel.h"
#include "CMissile.h"

#include "CKeyMgr.h"
#include "CTaskMgr.h"
#include "CEngine.h"
#include "CPathMgr.h"
#include "CGameManager.h"
#include "CAssetMgr.h"
#include "CTexture.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CAnim.h"
#include "CRigidBody.h"
#include "CPlayerStateMachine.h"
#include "CCamera.h"

#include "CLogMgr.h"

CPlayer::CPlayer()
	: speed(300.f)
	, collider(nullptr)
	, animator(nullptr)
	, rigidbody(nullptr)
	, isPlayerLeft(false)
	, isCollisionUp(false)
	, isCollisionDown(false)
	, isCollisionLeft(false)
	, isCollisionRight(false)
{
	// 컴포넌트 설정
	collider = AddComponent(new CCollider);
	collider->SetName(L"Body Collider");
	collider->SetOffset(Vec2(0.f, -32.f));
	collider->SetScale(Vec2(60.f, 64.f));

	// RigidBody
	rigidbody = AddComponent(new CRigidBody);
	rigidbody->SetMass(1.f);
	rigidbody->SetMaxSpeed(300.f);
	rigidbody->SetFriction(1000.f);
	rigidbody->SetMaxGravitySpeed(1500.f);
	rigidbody->SetJumpSpeed(700.f);


	// Player 에 Animator 컴포넌트 추가
	animator = AddComponent(new CAnimator);

	animator->LoadAnimation(L"animation\\Player\\HIT.anim");
	animator->LoadAnimation(L"animation\\Player\\HIT_LEFT.anim");
	animator->LoadAnimation(L"animation\\Player\\IDLE_RIGHT.anim");
	animator->LoadAnimation(L"animation\\Player\\IDLE_LEFT.anim");
	animator->LoadAnimation(L"animation\\Player\\RUN_LEFT.anim");
	animator->LoadAnimation(L"animation\\Player\\RUN_RIGHT.anim");

	// Animation 플레이
	animator->Play(L"IDLE_RIGHT", true);

	// 스테이트머신
	stateMachine = AddComponent(new CPlayerStateMachine);
	stateMachine->SetLayer();

	// 카메라
	mainCam = CCamera::Get();
}

CPlayer::CPlayer(const CPlayer& _Other)
	: CObj(_Other)
	, collider(nullptr)
	, animator(nullptr)
	, rigidbody(nullptr)
{
	collider = (CCollider*)GetComponentByName(L"Body Collider");
	animator = GetComponent<CAnimator>();
	rigidbody = GetComponent<CRigidBody>();
}

CPlayer::~CPlayer()
{
	
}

void CPlayer::Tick()
{
	Vec2 pos = GetPos();
	prevPos = pos;

	if (pos.y >= 1000.f) rigidbody->SetGround(true);

	if (KEY_RELEASED(KEY::A) || KEY_RELEASED(KEY::D))
		stateMachine->ChangeState(L"IdleState", 0);
	if (KEY_TAP(KEY::A)) {
		isPlayerLeft = true;		
		stateMachine->ChangeState(L"MoveState", 0);
	}
	else if (KEY_TAP(KEY::D)) {
		isPlayerLeft = false;
		stateMachine->ChangeState(L"MoveState", 0);
	}

	if (KEY_PRESSED(KEY::A) && !isCollisionLeft)
		pos.x -= speed * DT;
	else if (KEY_PRESSED(KEY::D) && !isCollisionRight)
		pos.x += speed * DT;


	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 mousePos = CKeyMgr::Get()->GetMousePos();
		// 방향벡터 (마우스 포지션이 스크린좌표이므로 플레이어도 RenderPos)
		Vec2 dirVec = mousePos - GetRenderPos(); 

		CMissile* pMissile = new CMissile;
		pMissile->SetName(L"Missile");
		pMissile->SetTexture(CAssetMgr::Get()->LoadTexture(L"circle", L"texture\\Missile.png"));
		pMissile->SetPos(GetPos().x, GetPos().y - GetScale().y / 2.f);
		pMissile->SetVelocity(dirVec, 500.f);

		CreateObject(pMissile, LAYER_TYPE::PLAYER_PROJECTILE);

		CGameManager::Get()->UseGem();
	}


	if (KEY_TAP(KEY::SPACE) && rigidbody->GetGround())
	{
		rigidbody->Jump();
	}

	SetPos(pos);

	mainCam->SetLookAt(pos);

	if (playerDead) {
		CLevel* level = CLevelMgr::Get()->GetCurrentLevel();
		CLevelMgr::Get()->ChangeLevel(level->GetLevelType());
		return;
	}
}

void CPlayer::Render()
{
	animator->Render();
}

void CPlayer::SetCollisionType(OVERLAP_TYPE type, bool isCollision) {
	switch (type)
	{
	case OVERLAP_TYPE::IS_COLLISION_UP:
		isCollisionUp = isCollision;
		break;
	case OVERLAP_TYPE::IS_COLLISION_DOWN:
		isCollisionDown = isCollision;
		break;
	case OVERLAP_TYPE::IS_COLLISION_LEFT:
		isCollisionLeft = isCollision;
		break;
	case OVERLAP_TYPE::IS_COLLISION_RIGHT:
		isCollisionRight = isCollision;
		break;
	default:
		break;
	}
}


void CPlayer::BeginOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{
	if (_OtherObj->GetLayerType() == (int)LAYER_TYPE::MONSTER_PROJECTILE)
	{
		Dead();
	}	
}

void CPlayer::Overlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

}

void CPlayer::EndOverlap(CCollider* _OwnCollider, CObj* _OtherObj, CCollider* _OtherCollider)
{

}

void CPlayer::Dead()
{
	if (CGameManager::Get()->UseGem()) {
		return;
	}

	playerDead = true;
}
