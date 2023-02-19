#pragma once
#include "gameNode.h"
/*������ ���ΰ����� ������ ���鸸 ������ �Ѵ�*/
/*������ϸ� ���ΰ��ӿ� �߰��ϱ�*/
#include "sceneTest.h"
#include "sceneTest1.h"
#include "pixcelCollisionScene.h"
#include "iniTestScene.h"
#include "loadingScene.h"
#include "soundTestScene.h"
#include "isometricTest.h"
#include "maptoolScene.h"
#include "gdipTestScene.h"
#include "mapTool1.h"

class mainGame : public gameNode
{
public:
	HRESULT init();
	void release();
	void update();
	void render();

	mainGame() {}
	~mainGame() {}
};

