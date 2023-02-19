#pragma once
#include "gameNode.h"
#include "minion.h"		//�̴Ͼ� Ŭ������ ����ϱ� ����
#include "bullet.h"		//�����Ѿ� Ŭ������ ����ϱ� ����

//�÷��̾�� ��ȣ�����ϱ� ���� Ŭ���� ���漱��
class player;

class enemyManager : public gameNode
{
private:
	vector<enemy*> _vMinion;
	vector<enemy*>::iterator _viMinion;
	
	bullet* _bullet;	//�����Ѿ� Ŭ����
	int _count;

	player* _player;	//�����Ҵ� �ϸ� �ȵȴ�!!
	//���ΰ��ӿ��� ������ �÷��̾�� ���⼭ ������ �÷��̾��
	//���� �ٸ� �޸𸮿� �����Ǿ ���� ������ �Ұ���

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//�浹�Լ�
	void collision();

	//�̴Ͼ� ���� => �ʱ�ȭ �ֱ�
	void setMinion();
	//�̴Ͼ� �Ѿ˹߻�
	void minionBulletFire();
	//�̴Ͼ� ����
	void removeMinion(int index);
	//�̴Ͼ� ���� ��������
	vector<enemy*> getVMinion() { return _vMinion; }

	//��ȣ������ �÷��̾� �����͸� �ѱ� �����Լ�
	void setPlayerLink(player* player) { _player = player; }

	enemyManager() {}
	~enemyManager() {}
};

