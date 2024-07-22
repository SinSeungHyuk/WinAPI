#include "CLevel.h"

class CTileMap;

class CLevel_Editor
	: public CLevel
{
private:
	CTileMap* m_TileMap;

public:
	CTileMap* GetTileMap() { return m_TileMap; }
	void SaveTile();
	void LoadTile();

private:
	void TileMode();

private:
	virtual void Init() override;
	virtual void Exit() override;
	virtual void Tick() override;

public:
	CLevel_Editor();
	~CLevel_Editor();
};