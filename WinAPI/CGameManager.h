#pragma once

class CImage;
class CPlayer;

class CGameManager
{
	SINGLE(CGameManager);

private:
	int coins;		 // ���� ����
	int gems;		 // �� ����
	const int gemOffset = 100.f; // ȭ�� ��ܿ� ���� ���� ����
	const int coinsPerGem = 5;  // ������ ��ȯ�ϱ� ���� ���ΰ���

	vector<CImage*> gemArray; // ��UI�� �����ϱ� ���� ����

	bool isClear;
	float timer = 0.f;

public:
	void Init();
	void Tick();

	void GetCoin(); // ���� ȹ��
	void GetGem(); // ���� ȹ��
	bool UseGem();	// �� ���

	void GameClear();

	CPlayer* GetPlayer(); // �÷��̾� ��ȯ
};
