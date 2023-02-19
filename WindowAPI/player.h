#pragma once
#include "gameNode.h"
#include "bullet.h"
#include "progressBar.h"	//ü�¹� Ŭ������ ����ϱ� ����

//���Ŵ����� ��ȣ �����ϱ� ���� Ŭ���� ���漱��
class enemyManager;

class player : public gameNode
{
private:
	image* _rocket;		//����(�÷��̾�) �̹���
	//RECT _rcPlayer;
	missile* _missile;	//�̻��� Ŭ����
	bomb* _bomb;		//��ź Ŭ����

	enemyManager* _em;	//�����Ҵ� ���� �ȵȴ�!!!
	//���ΰ��ӿ��� ������ em�� ���⼭ �����Ҵ��ع��� em��
	//���� �ٸ� �޸� �ּҶ�� ���� ������ �� ������

	progressBar* _hpBar;		//ü�¹�
	float _maxHp, _currentHp;	//�ִ�ü��, ����ü��

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//�浹�Լ�
	void collision();

	//ü�¹� ������
	void hitDamage(float damage);

	//�̻��� ũ���� ��������
	missile* getMissile() { return _missile; }

	//��ź Ŭ���� ��������
	bomb* getBomb() { return _bomb; }

	//��ź ����
	void removeBomb(int index);

	//�÷��̾� �̹��� ��������
	image* getPlayerImg() { return _rocket; }

	//��ȣ������ ���Ŵ��� �����͸� �ѱ� �����Լ�
	void setEMLink(enemyManager* em) { _em = em; }

	player() {}
	~player() {}
};

