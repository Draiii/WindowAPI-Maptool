#pragma once
#include "gameNode.h"

#define X_EA 16
#define Y_EA 16
#define MAX (X_EA * Y_EA)

#define WIDTH 82
#define HEIGHT (WIDTH / 2)

#define SELECTX 3
#define SELECTY 9
//타일
struct tagMainTile
{
	RECT rc;
	image* image;
	int x, y;
	float width, height;
	float leftCenter, topCenter, rightCenter, bottomCenter;
};
//선택 타일
struct tagSelectTile
{
	RECT rc;
	image* image;
	float width, height;
	int  x, y;

};

class mapTool :	public gameNode
{
private:
	tagMainTile mainTile[MAX];
	tagSelectTile selectTile[SELECTX][SELECTY];
	image* temp;

	RECT screen;
	RECT secondScreen;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	mapTool() {}
	~mapTool() {}
};

