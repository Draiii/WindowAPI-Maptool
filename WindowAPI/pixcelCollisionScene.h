#pragma once
#include "gameNode.h"

class pixcelCollisionScene : public gameNode
{
private:
	image* _mountain;	//��׶��� �̹���
	image* _ball;		//���̹���
	RECT _rc;			//�� ��Ʈ

	float _x, _y;		//��ġ��ǥ
	int _probeY;		//�ȼ��浹 Ž���� Y��

public:
	HRESULT init();
	void release();
	void update();
	void render();

	pixcelCollisionScene() {}
	~pixcelCollisionScene() {}
};

