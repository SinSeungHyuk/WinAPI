#include "pch.h"
#include "CGameManager.h"
#include "CLogMgr.h"
#include "CAssetMgr.h"
#include "CLevelMgr.h"
#include "CTimeMgr.h"
#include "CLevel.h"
#include "CPlayer.h"

#include "CImage.h"

CGameManager::CGameManager() : coins(0), gems(0), isClear(false)
{}

CGameManager::~CGameManager()
{
}

void CGameManager::Init()
{
	
}

void CGameManager::Tick()
{
	if (isClear) {
		timer += DT;

		if (timer > 3.0f) {
			CLevelMgr::Get()->ChangeLevel(LEVEL_TYPE::EDITOR);
			return;
		}
	}
}

void CGameManager::GetCoin()
{
	coins++;

	if (coins % 3 == 0) 
		GetGem();
}

void CGameManager::GetGem()
{
	gems++;

	CImage* image = new CImage;
	image->SetPos(50.f + gems * gemOffset, 50.f);
	image->SetTexture(CAssetMgr::Get()->LoadTexture(L"gemImage", L"texture\\gemImage.png"));
	gemArray.push_back(image);
	CreateObject(image, LAYER_TYPE::UI);
}

bool CGameManager::UseGem()
{
	if (gems == 0) 
		return false;

	Destroy(gemArray[--gems]);
	gemArray.pop_back();

	return true;
}

void CGameManager::GameClear()
{
	isClear = true;
}

CPlayer* CGameManager::GetPlayer()
{
	CPlayer* player = CLevelMgr::Get()->GetCurrentLevel()->GetPlayer();

	if (player == nullptr)
		return nullptr;
	else return player;
}
