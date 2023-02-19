#pragma once
#include "gameNode.h"

//Ÿ�ϰ���
#define TILEX 5
#define TILEY 5
//Ÿ��ũ��
#define TILESIZEX 200
#define TILESIZEY (TILESIZEX / 2)
//Ÿ�Ϲ�ũ��
#define TILESIZEX_HALF (TILESIZEX / 2)
#define TILESIZEY_HALF (TILESIZEY / 2)
//���̼�Ÿ�� ������ǥ(0, 0)
#define STARTX (WINSIZEX / 2)
#define STARTY 100

//Ÿ�� ����ü
struct tagCell
{
	int x, y;
	RECT rc;
};

class isometricTest : public gameNode
{
private:
	tagCell _tile[TILEX][TILEY];  //Ÿ�ϱ���ü �� 25��
	POINT _index;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	isometricTest() {}
	~isometricTest() {}
};

