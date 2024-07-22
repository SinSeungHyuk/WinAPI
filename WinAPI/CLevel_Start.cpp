#include "pch.h"
#include "CLevel_Start.h"

#include "CEngine.h"
#include "CPlayer.h"
#include "CCollider.h"
#include "CPatrolMonster.h"
#include "CTraceMonster.h"
#include "CProjectileMonster.h"
#include "ItemDropEvent.h"
#include "CPlatform.h"
#include "CTile.h"
#include "CTileMap.h"
#include "CImage.h"
#include "CCoinItem.h"
#include "CGemItem.h"
#include "CEndPointItem.h"
#include "CTrapSpike.h"
#include "CTrapSaw.h"
#include "CTrapFire.h"
#include "TimerTrapCondition.h"
#include "MoveTrapCondition.h"
#include "CStartPointItem.h"
#include "NormalTrapCondition.h"
#include "CEndPointItem.h"

#include "CAssetMgr.h"
#include "CPathMgr.h"
#include "CSound.h"


#include "CCollisionMgr.h"
#include "CKeyMgr.h"

CLevel_Start::CLevel_Start()
{
}

CLevel_Start::~CLevel_Start()
{
}

void CLevel_Start::Init()
{
	// BGM 지정
	CSound* pBGM = CAssetMgr::Get()->LoadSound(L"DM_BGM", L"sound\\bgm.wav");
	pBGM->Play();

	SetLevelType(LEVEL_TYPE::START);

	// 오브젝트 위치 설정
	CPlayer* pPlayer = new CPlayer;
	pPlayer->SetName(L"Player");
	Vec2 vResol = CEngine::Get()->GetResolution();
	pPlayer->SetPos(vResol.x * 0.6f, 900.f );
	pPlayer->SetScale(64.f, 64.f);
	// 플레이어를 현재 레벨에 등록
	RegisterPlayer(pPlayer);
	// 플레이어를 레벨에 추가
	AddObject(pPlayer, LAYER_TYPE::PLAYER);

	CItem* start = new CStartPointItem;
	start->SetName(L"start");
	start->SetPos(vResol.x * 0.5f, 872.f);
	start->SetScale(128.f, 128.f);
	start->SetTexture(CAssetMgr::Get()->LoadTexture(L"StartPoint", L"texture\\StartPoint.png"));
	AddObject(start, LAYER_TYPE::ITEM);

	// Monster
	DeathEventStrategy* deathEvent1 = new ItemDropEvent(new CCoinItem);
	DeathEventStrategy* deathEvent2 = new ItemDropEvent(new CCoinItem);
	DeathEventStrategy* deathEvent3 = new ItemDropEvent(new CCoinItem);
	CMonster* monster1 = new CTraceMonster(3,100.0f,300.0f,deathEvent1);
	monster1->SetScale(64.f, 64.f);
	monster1->SetName(L"Monster");
	monster1->SetPos(2025.f,675.f);
	AddObject(monster1, LAYER_TYPE::MONSTER);

	CMonster* monster3= new CPatrolMonster(3, 150.0f, 300.0f, deathEvent2);
	monster3->SetScale(64.f, 64.f);
	monster3->SetName(L"Monster2");
	monster3->SetPos(1400.f, 800.f);
	AddObject(monster3, LAYER_TYPE::MONSTER);

	CMonster* monster2 = new CProjectileMonster(3, 150.0f, 300.0f, deathEvent3);
	monster2->SetScale(64.f, 64.f);
	monster2->SetName(L"Monster2");
	monster2->SetPos(2875.0f, 700.f);
	AddObject(monster2, LAYER_TYPE::MONSTER);

		//	// Item
	CItem* gem = new CGemItem;
	gem->SetName(L"coin");
	gem->SetPos(2425.f, 825.f);
	gem->SetScale(32.f, 32.f);
	AddObject(gem, LAYER_TYPE::ITEM);

	CItem* goal = new CEndPointItem;
	goal->SetName(L"coin");
	goal->SetPos(3500.f, 1000.f);
	goal->SetScale(32.f, 32.f);
	AddObject(goal, LAYER_TYPE::ITEM);

	// trap
	TimerTrapCondition* timerTrapCondition = new TimerTrapCondition();
	TimerTrapCondition* timerTrapCondition2 = new TimerTrapCondition();
	TrapCondition* NormalTrapCondition3 = new NormalTrapCondition();
	TrapCondition* NormalTrapCondition4 = new NormalTrapCondition();
	TrapCondition* NormalTrapCondition5 = new NormalTrapCondition();
	TrapCondition* NormalTrapCondition6 = new NormalTrapCondition();
	TrapCondition* NormalTrapCondition7 = new NormalTrapCondition();
	TrapCondition* NormalTrapCondition8 = new NormalTrapCondition();
	TrapCondition* moveTrapCondition1 = new MoveTrapCondition(300.f,150.f);
	TrapCondition* moveTrapCondition2 = new MoveTrapCondition(250.f,200.f);
	TrapCondition* moveTrapCondition3 = new MoveTrapCondition(200.f,250.f);
	TrapCondition* moveTrapCondition4 = new MoveTrapCondition(200.f,250.f);

	CTrap* spike = new CTrapSpike(timerTrapCondition);
	spike->SetName(L"spike");
	spike->SetPos(1675.f, 1000.f);
	spike->SetScale(32.f, 32.f);
	AddObject(spike, LAYER_TYPE::TRAP);

	CTrap* spike2 = new CTrapSpike(moveTrapCondition4);
	spike2->SetName(L"spike");
	spike2->SetPos(1725.f, 1000.f);
	spike2->SetScale(32.f, 32.f);
	AddObject(spike2, LAYER_TYPE::TRAP);

	CTrapFire* fire1 = new CTrapFire(NormalTrapCondition3);
	fire1->SetName(L"fire1");
	fire1->SetPos(2325.f, 1000.f);
	fire1->SetScale(32.f, 32.f);
	AddObject(fire1, LAYER_TYPE::TRAP);
	CTrapFire* fire2 = new CTrapFire(NormalTrapCondition4);
	fire2->SetName(L"fire1");
	fire2->SetPos(2375.f, 1000.f);
	fire2->SetScale(32.f, 32.f);
	AddObject(fire2, LAYER_TYPE::TRAP);
	CTrapFire* fire3 = new CTrapFire(NormalTrapCondition5);
	fire3->SetName(L"fire1");
	fire3->SetPos(2425.f, 1000.f);
	fire3->SetScale(32.f, 32.f);
	AddObject(fire3, LAYER_TYPE::TRAP);
	CTrapFire* fire4 = new CTrapFire(NormalTrapCondition6);
	fire4->SetName(L"fire1");
	fire4->SetPos(2475.f, 1000.f);
	fire4->SetScale(32.f, 32.f);
	AddObject(fire4, LAYER_TYPE::TRAP);
	CTrapFire* fire5 = new CTrapFire(NormalTrapCondition7);
	fire5->SetName(L"fire1");
	fire5->SetPos(2525.f, 1000.f);
	fire5->SetScale(32.f, 32.f);
	AddObject(fire5, LAYER_TYPE::TRAP);
	CTrapFire* fire6 = new CTrapFire(NormalTrapCondition8);
	fire6->SetName(L"fire1");
	fire6->SetPos(2575.f, 1000.f);
	fire6->SetScale(32.f, 32.f);
	AddObject(fire6, LAYER_TYPE::TRAP);

	CTrap* saw1 = new CTrapSaw(moveTrapCondition1);
	saw1->SetName(L"fire1");
	saw1->SetPos(3075.f, 1000.f);
	saw1->SetScale(32.f, 32.f);
	AddObject(saw1, LAYER_TYPE::TRAP);
	CTrap* saw2 = new CTrapSaw(moveTrapCondition2);
	saw2->SetName(L"fire1");
	saw2->SetPos(3175.f, 1000.f);
	saw2->SetScale(32.f, 32.f);
	AddObject(saw2, LAYER_TYPE::TRAP);
	CTrap* saw3 = new CTrapSaw(moveTrapCondition3);
	saw3->SetName(L"fire1");
	saw3->SetPos(3275.f, 1000.f);
	saw3->SetScale(32.f, 32.f);
	AddObject(saw3, LAYER_TYPE::TRAP);



	// Platform
	CPlatform* pPlatform = new CPlatform;
	pPlatform->SetName(L"Platform");
	pPlatform->SetPos(2500.f, 1050.f);
	pPlatform->SetScale(5000.f, 100.f);
	AddObject(pPlatform, LAYER_TYPE::PLATFORM);

	CPlatform* pPlatform2 = new CPlatform;
	pPlatform2->SetName(L"Platform");
	pPlatform2->SetPos(1425.f, 875.f);
	pPlatform2->SetScale(450.f, 50.f);
	AddObject(pPlatform2, LAYER_TYPE::PLATFORM);

	CPlatform* pPlatform3 = new CPlatform;
	pPlatform3->SetName(L"Platform");
	pPlatform3->SetPos(2025.f, 775.f);
	pPlatform3->SetScale(550.f, 50.f);
	AddObject(pPlatform3, LAYER_TYPE::PLATFORM);

	CPlatform* pPlatform4 = new CPlatform;
	pPlatform4->SetName(L"Platform");
	pPlatform4->SetPos(2725.f, 775.f);
	pPlatform4->SetScale(350.f, 50.f);
	AddObject(pPlatform4, LAYER_TYPE::PLATFORM);

	CPlatform* pPlatform5 = new CPlatform;
	pPlatform5->SetName(L"Platform");
	pPlatform5->SetPos(2425.f, 875.f);
	pPlatform5->SetScale(50.f, 50.f);
	AddObject(pPlatform5, LAYER_TYPE::PLATFORM);



	CPlatform* pPlatform6 = new CPlatform;
	pPlatform6->SetPos(1200.f, 825.f);
	pPlatform6->SetScale(10.f, 10.f);
	pPlatform6->GetComponent<CCollider>()->SetTrigger(true);
	AddObject(pPlatform6, LAYER_TYPE::PLATFORM);

	CPlatform* pPlatform7 = new CPlatform;
	pPlatform7->SetPos(1650.f, 825.f);
	pPlatform7->SetScale(10.f, 10.f);
	pPlatform7->GetComponent<CCollider>()->SetTrigger(true);
	AddObject(pPlatform7, LAYER_TYPE::PLATFORM);

	CPlatform* pPlatform8 = new CPlatform;
	pPlatform8->SetPos(1750.f, 725.f);
	pPlatform8->SetScale(10.f, 10.f);
	pPlatform8->GetComponent<CCollider>()->SetTrigger(true);
	AddObject(pPlatform8, LAYER_TYPE::PLATFORM);

	CPlatform* pPlatform9 = new CPlatform;
	pPlatform9->SetPos(2300.f, 725.f);
	pPlatform9->SetScale(10.f, 10.f);
	pPlatform9->GetComponent<CCollider>()->SetTrigger(true);
	AddObject(pPlatform9, LAYER_TYPE::PLATFORM);

	CPlatform* pPlatform10 = new CPlatform;
	pPlatform10->SetPos(2550.f, 700.f);
	pPlatform10->SetScale(10.f, 10.f);
	pPlatform10->GetComponent<CCollider>()->SetTrigger(true);
	AddObject(pPlatform10, LAYER_TYPE::PLATFORM);

	CPlatform* pPlatform11 = new CPlatform;
	pPlatform11->SetPos(2900.f, 700.f);
	pPlatform11->SetScale(10.f, 10.f);
	pPlatform11->GetComponent<CCollider>()->SetTrigger(true);
	AddObject(pPlatform11, LAYER_TYPE::PLATFORM);
	

	CTile* pObj = new CTile;
	pObj->SetName(L"TILE_Atlas");
	CTileMap* m_TileMap = pObj->GetComponent<CTileMap>();
	AddObject(pObj, LAYER_TYPE::TILE);


	// 충돌 지정
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER, (UINT)LAYER_TYPE::MONSTER, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER, (UINT)LAYER_TYPE::MONSTER_PROJECTILE, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER, (UINT)LAYER_TYPE::ITEM, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER, (UINT)LAYER_TYPE::TRAP, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLATFORM, (UINT)LAYER_TYPE::MONSTER, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER, (UINT)LAYER_TYPE::PLATFORM, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER_PROJECTILE, (UINT)LAYER_TYPE::MONSTER, true);
	CCollisionMgr::Get()->CollisionCheck((UINT)LAYER_TYPE::PLAYER_PROJECTILE, (UINT)LAYER_TYPE::PLATFORM, true);

	wstring strContentPath = CPathMgr::Get()->GetContentPath() + L"tile\\Stage1.Tile";
	m_TileMap->Load(strContentPath.c_str());
}

void CLevel_Start::Exit()
{
	// 모든 오브젝트를 삭제해둔다.
	DeleteAllObjects();
}

void CLevel_Start::Tick()
{
	CLevel::Tick();
}