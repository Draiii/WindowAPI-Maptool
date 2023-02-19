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
//타일
struct tagMainTile
{
	RECT rc;
	gdipImage* image;	
	float x, y, width, height;
	float leftCenter, topCenter, rightCenter, bottomCenter;
};
//타일 선택 
struct tagSelectTile
{
	RECT rc;
	gdipImage* image;
	float x, y, width, height;

};

//종류 선택 
struct tagSelectKind
{
	RECT rc;
	gdipImage* image;
	float x, y, width, height;

};

//그라운드타일
struct tagGround
{
	gdipImage* image;
	float width, height;
	int x, y;	
};

//그라운드데코타일
struct tagGroundDeco
{
	gdipImage* image;
	float width, height;
	int x, y;
};

//오브젝트
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

//캐릭터
struct tagCharacters
{
	gdipImage* image;
	float width, height;
	int x, y;
};

// 빌딩 아웃사이드
struct tagBuildingOutSide
{
	gdipImage* image;
	float width, height;
	int x, y;
};

// 빌딩 인사이드 그라운드
struct tagBuildingInSideGround
{
	gdipImage* image;
	float width, height;
	int x, y;
};

// 빌딩 인사이드 데코
struct tagBuildingInSideDeco
{
	gdipImage* image;
	float width, height;
	int x, y;
};


class mapTool1 : public gameNode
{
private:
	//타일 그릴 메인 타일
	tagMainTile mainTile[MAX];	
	//종류 선택
	tagSelectKind SelectKind[KIND_MAX];
	//타일 선택
	tagSelectTile selectTile[SELECTY][SELECTX];
	//마우스좌표에 이미지 저장할거
	gdipImage* temp;
	//그라운드 타일
	vector <tagGround> vGround;
	//그라운드 데코
	vector <tagGroundDeco> vGroundDeco;
	//오브젝트
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

	//맵이동
	void mapMove();
	mapTool1() {}
	~mapTool1() {}
};

