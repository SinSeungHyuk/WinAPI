#include "pch.h"
#include "CLevel.h"

#include "CObj.h"
#include "CLogMgr.h"
#include "CPathMgr.h"

#include "CKeyMgr.h"

CLevel::CLevel()
	: m_CurPlayer(nullptr) , levelType()
{
}

CLevel::~CLevel()
{
	for (int i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		Release_Vector(m_arrLayer[i]);
	}	
}

void CLevel::Tick()
{
	for (int i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		for (int j = 0; j < m_arrLayer[i].size(); ++j)
		{
			m_arrLayer[i][j]->Tick();
		}
	}

	//Vec2 vMousePos = CKeyMgr::Get()->GetMousePos();
	//vMousePos = CCamera::Get()->GetRealPos(vMousePos);

	//if (KEY_TAP(KEY::LBTN))
	//{
	//	wchar_t szMousePos[255] = {};
	//	swprintf_s(szMousePos, 255, L"MouseX : %d, MousY : %d", (int)vMousePos.x, (int)vMousePos.y);
	//	LOG(LOG_LEVEL::WARNING, szMousePos);
	//}
}


void CLevel::FinalTick()
{
	for (int i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		for (int j = 0; j < m_arrLayer[i].size(); ++j)
		{
			m_arrLayer[i][j]->FinalTick();
		}
	}
}

void CLevel::Render()
{
	for (int i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		vector<CObj*>& vecObj = m_arrLayer[i];

		vector<CObj*>::iterator iter = vecObj.begin();
		for (; iter != vecObj.end(); )
		{
			if ((*iter)->IsDead())
			{
				iter = vecObj.erase(iter);
			}
			else
			{
				(*iter)->Render();
				++iter;
			}		
		}
	}
}

void CLevel::AddObject(CObj* _Obj, LAYER_TYPE _Type)
{
	m_arrLayer[(int)_Type].push_back(_Obj);
	_Obj->m_LayerType = (int)_Type;
}

void CLevel::DeleteObjects(LAYER_TYPE _Type)
{
	vector<CObj*>& vecObj = m_arrLayer[(int)_Type];
	Release_Vector(vecObj);
}

void CLevel::DeleteAllObjects()
{
	for (int i = 0; i < (int)LAYER_TYPE::END; ++i)
	{
		DeleteObjects((LAYER_TYPE)i);
	}
}

