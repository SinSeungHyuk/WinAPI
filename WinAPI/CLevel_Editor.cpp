#include "pch.h"
#include "CLevel_Editor.h"

#include "CLogMgr.h"
#include "CPathMgr.h"

#include "CKeyMgr.h"
#include "CTile.h"
#include "resource.h"

#include "CLevelMgr.h"
#include "CLevel.h"

#include "CAssetMgr.h"

#include "CEngine.h"
#include "CTileMap.h"
#include "CGemItem.h"

#include "CBtnUI.h"
#include "CPanel.h"
#include "CImage.h"
#include "CUIMgr.h"

#include "CSound.h"

#include "resource.h"


LRESULT CALLBACK TileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
void BtnPlay()
{
	CCamera::Get()->SetFilterEffect(FADE_OUT, 1.f);
	ChangeLevel(LEVEL_TYPE::START);

	CCamera::Get()->SetFilterEffect(FADE_IN, 1.f);
}


CLevel_Editor::CLevel_Editor()
	: m_TileMap(nullptr)
{
}

CLevel_Editor::~CLevel_Editor()
{
}


void CLevel_Editor::Init()
{
	// BGM 지정
	CSound* pBGM = CAssetMgr::Get()->LoadSound(L"DM_BGM", L"sound\\bgm.wav");
	pBGM->Play();

	// 메뉴가 붙었으니까, 다시 윈도우 크기 재계산
	UINT width = CEngine::Get()->GetResolution().x;
	UINT height = CEngine::Get()->GetResolution().y;

	CCamera::Get()->SetLookAt(Vec2(width * 0.5f, height * 0.5f));

	SetLevelType(LEVEL_TYPE::EDITOR);

	// 오브젝트 생성
	CObj* pObj = nullptr;

	// Tile

	pObj = new CTile;
	pObj->SetName(L"TILE_Atlas");
	pObj->SetPos(0.f, 0.f);

	m_TileMap = pObj->GetComponent<CTileMap>();

	m_TileMap->SetAtlas(CAssetMgr::Get()->LoadTexture(L"TILE_Atlas", L"texture\\TILE_Atlas.png"));
	m_TileMap->SetAtlasTileSize(Vec2(50.f, 50.f));

	m_TileMap->SetTileSize(Vec2(50.f, 50.f));
	m_TileMap->SetRowCol(55, 100);
	AddObject(pObj, LAYER_TYPE::TILE);

	// UI 추가하기
	CBtnUI* pUI = new CBtnUI;
	Vec2 vResol = CEngine::Get()->GetResolution();
	pUI->SetTexture(CAssetMgr::Get()->LoadTexture(L"BtnPlay", L"texture\\BtnPlay.png"));
	pUI->SetScale(Vec2(224.f, 64.f));
	pUI->SetPos(Vec2(width * 0.5f - 112.f, height * 0.4f));
	pUI->SetCallBack(&BtnPlay);
	AddObject(pUI, LAYER_TYPE::UI);

	CImage* image = new CImage;
	image->SetPos(Vec2(width * 0.5f - 250.f, 0));
	image->SetTexture(CAssetMgr::Get()->LoadTexture(L"Logo", L"texture\\Logo.png"));
	AddObject(image, LAYER_TYPE::UI);

	// 오브젝트 추가
	CItem* gem1 = new CGemItem;
	gem1->SetPos(375.f, 475.f);
	gem1->SetScale(32.f, 32.f);
	AddObject(gem1, LAYER_TYPE::ITEM);

	CItem* gem2 = new CGemItem;
	gem2->SetPos(575.f, 625.f);
	gem2->SetScale(32.f, 32.f);
	AddObject(gem2, LAYER_TYPE::ITEM);

	CItem* gem3 = new CGemItem;
	gem3->SetPos(625, 625);
	gem3->SetScale(32.f, 32.f);
	AddObject(gem3, LAYER_TYPE::ITEM);

	CItem* gem4 = new CGemItem;
	gem4->SetPos(975, 825);
	gem4->SetScale(32.f, 32.f);
	AddObject(gem4, LAYER_TYPE::ITEM);

	CItem* gem5 = new CGemItem;
	gem5->SetPos(1225, 775);
	gem5->SetScale(32.f, 32.f);
	AddObject(gem5, LAYER_TYPE::ITEM);

	CItem* gem6 = new CGemItem;
	gem6->SetPos(1625, 825);
	gem6->SetScale(32.f, 32.f);
	AddObject(gem6, LAYER_TYPE::ITEM);

	CItem* gem7 = new CGemItem;
	gem7->SetPos(1400, 725);
	gem7->SetScale(32.f, 32.f);
	AddObject(gem7, LAYER_TYPE::ITEM);


	wstring strContentPath = CPathMgr::Get()->GetContentPath() + L"tile\\MainMenu.Tile";
	m_TileMap->Load(strContentPath.c_str());
}

void CLevel_Editor::Exit()
{
	// 오브젝트 삭제
	DeleteAllObjects();
}

void CLevel_Editor::Tick()
{
	CLevel::Tick();

	// 타일 관련 마우스 체크
	//TileMode();
}

void CLevel_Editor::TileMode()
{
	Vec2 vMousePos = CKeyMgr::Get()->GetMousePos();
	vMousePos = CCamera::Get()->GetRealPos(vMousePos);

	if (KEY_TAP(KEY::RBTN))
	{
		Vec2 TileSize = m_TileMap->GetTileSize();

		UINT Col = vMousePos.x / TileSize.x;
		UINT Row = vMousePos.y / TileSize.y;

		tTileInfo* pTileInfo = m_TileMap->GetTileInfo(Col, Row);

		if (nullptr != pTileInfo)
		{
			if (pTileInfo->ImgIdx == 2) pTileInfo->ImgIdx = 0;
			else ++pTileInfo->ImgIdx;
		}
	}

	if (KEY_TAP(KEY::ENTER))
	{
		SaveTile();
	}
}

void CLevel_Editor::SaveTile()
{
	wstring strContentPath = CPathMgr::Get()->GetContentPath();

	// 파일 경로 문자열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetSaveFileName(&Desc))
	{
		if (wcslen(szFilePath) != 0)
		{
			m_TileMap->Save(szFilePath);
		}
	}

	CUIMgr::Get()->SetPreventFrame(1);
}

void CLevel_Editor::LoadTile()
{
	wstring strContentPath = CPathMgr::Get()->GetContentPath();

	// 파일 경로 문자열
	wchar_t szFilePath[255] = {};

	OPENFILENAME Desc = {};

	Desc.lStructSize = sizeof(OPENFILENAME);
	Desc.hwndOwner = nullptr;
	Desc.lpstrFile = szFilePath;
	Desc.nMaxFile = 255;
	Desc.lpstrFilter = L"Tile\0*.tile\0ALL\0*.*";
	Desc.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	Desc.lpstrInitialDir = strContentPath.c_str();

	if (GetOpenFileName(&Desc))
	{
		if (wcslen(szFilePath) != 0)
		{
			m_TileMap->Load(szFilePath);
		}
	}

	CUIMgr::Get()->SetPreventFrame(1);
}






// ===============================
// 타일관련 다이얼로그 프로시저 함수
// ===============================
LRESULT CALLBACK TileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			int Col = GetDlgItemInt(hWnd, IDC_COL, nullptr, true);
			int Row = GetDlgItemInt(hWnd, IDC_ROW, nullptr, true);

			if (Col == 0 || Row == 0)
			{
				MessageBox(nullptr, L"타일의 행 or 열은 0 이 될 수 없습니다.", L"타일 행, 렬 설정 오류", MB_OK);
				return (INT_PTR)TRUE;
			}

			// 1. 현재 레벨에 접근
			CLevel* pCurLevel = CLevelMgr::Get()->GetCurrentLevel();
			CLevel_Editor* pEditorLevel = dynamic_cast<CLevel_Editor*>(pCurLevel);

			// 에디터 레벨에서만 사용해야하는 다이얼로그 윈도우가 다른레벨에서 띄워진 경우
			assert(pEditorLevel);

			CTileMap* pTileMap = pEditorLevel->GetTileMap();
			pTileMap->SetRowCol(Col, Row);


			EndDialog(hWnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hWnd, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}

		break;
	}
	return (INT_PTR)FALSE;
}