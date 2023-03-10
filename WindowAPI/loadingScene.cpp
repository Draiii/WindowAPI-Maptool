#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release()
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 화면 변경
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("픽셀충돌");
	}
}

void loadingScene::render()
{
	//로딩클래스 렌더
	_loading->render();
}

void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();
	//_loading->loadSound();
	//IMAGEMANAGER->addImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));
	_loading->loadImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_loading->loadImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));

	//로딩이 너무 빠르게 진행되서 천천히 돌아가도록 테스트용으로 만들기
	for (int i = 0; i < 500; i++)
	{
		_loading->loadImage("테스트", WINSIZEX, WINSIZEY);
	}

}

void loadingScene::loadingSound()
{
}
