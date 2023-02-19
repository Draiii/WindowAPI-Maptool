#pragma once
#include "gameNode.h"

#define X_EA 16
#define Y_EA 16
#define MAX (X_EA * Y_EA)
#define KIND_MAX 10
#define WIDTH 84
#define HEIGHT (WIDTH / 2)
#define IMAGE_WIDTH 80
#define IMAGE_HEIGHT 80
#define SELECTX 3
#define SELECTY 7

#define GROUND_MAX 142
#define GROUND_DECO_MAX 353
#define OBJECTS_MAX 17
#define NPC_MAX 35
#define CHARACTORS_MAX 27
#define CHANGE_ZONE_MAX 12
#define BUILDING_OUTSIDE_MAX 78
#define BUILDING_INSIDE_GROUND_MAX 23
#define BUILDING_INSIDE_DECO_MAX 87
enum TYPE
{
	GROUND, GROUND_DECO,
	OBJECTS, NPC, CHARACTERS, BUILDING_OUTSIDE, BUILDING_INSIDE_GORUND, BUILDING_INSIDE_DECO
};
//Ÿ��
struct tagMainTile
{
	RECT rc;
	gdipImage* image;	
	float x, y, width, height;
	float leftCenter, topCenter, rightCenter, bottomCenter;
};
//Ÿ�� ���� 
struct tagSelectTile
{
	RECT rc;
	gdipImage* image;
	float x, y, width, height;

};

//���� ���� 
struct tagSelectKind
{
	RECT rc;
	gdipImage* image;
	float x, y, width, height;

};

//�׶���Ÿ��
struct tagGround
{
	gdipImage* image;
	float width, height;
	int x, y;	
};

//�׶��嵥��Ÿ��
struct tagGroundDeco
{
	gdipImage* image;
	float width, height;
	int x, y;
};

//������Ʈ
struct tagObject
{
	gdipImage* image;
	float width, height;
	int x, y;
};

//NPC
struct tagNpc
{
	gdipImage* image;
	float width, height;
	int x, y;
};

//ĳ����
struct tagCharacters
{
	gdipImage* image;
	float width, height;
	int x, y;
};

// ���� �ƿ����̵�
struct tagBuildingOutSide
{
	gdipImage* image;
	float width, height;
	int x, y;
};

// ���� �λ��̵� �׶���
struct tagBuildingInSideGround
{
	gdipImage* image;
	float width, height;
	int x, y;
};

// ���� �λ��̵� ����
struct tagBuildingInSideDeco
{
	gdipImage* image;
	float width, height;
	int x, y;
};


class mapTool1 : public gameNode
{
private:
	//Ÿ�� �׸� ���� Ÿ��
	tagMainTile mainTile[MAX];	
	//���� ����
	tagSelectKind SelectKind[KIND_MAX];
	//Ÿ�� ����
	tagSelectTile selectTile[SELECTY][SELECTX];
	//���콺��ǥ�� �̹��� �����Ұ�
	gdipImage* temp;
	//�׶��� Ÿ��
	vector <tagGround> vGround;
	//�׶��� ����
	vector <tagGroundDeco> vGroundDeco;
	//������Ʈ
	vector <tagObject> vObjects;
	//NPC
	vector <tagNpc> vNpc;
	//Charactors
	vector <tagCharacters> vCharacters;
	//tagBuildingOutSide
	vector <tagBuildingOutSide> vBuildingOutSide;
	//tagBuildingInSideGround
	vector <tagBuildingInSideGround> vBuildingInSideGround;
	//tagBuildingInSideGround
	vector <tagBuildingInSideDeco> vBuildingInSideDeco;


	RECT screen;
	RECT kindScreen;
	RECT secondScreen;
	TYPE tileType;
	int tileTypeNum;

	RECT leftArrow;
	RECT rightArrow;
	int page;
	int pageCount;
	int moveX;
	int moveY;

	image* tempDC = IMAGEMANAGER->addImage("tempDC", WINSIZEX, WINSIZEY);

public:
	HRESULT init();
	void release();
	void update();
	void render();

	//���̵�
	void mapMove();
	mapTool1() {}
	~mapTool1() {}
};

