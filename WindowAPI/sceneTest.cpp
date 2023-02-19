#include "stdafx.h"
#include "sceneTest.h"

HRESULT sceneTest::init()
{
	//��׶��� �̹����ʱ�ȭ
	IMAGEMANAGER->addImage("��׶���", "background.bmp", WINSIZEX, WINSIZEY);
	//UFO ������ �̹����ʱ�ȭ
	IMAGEMANAGER->addFrameImage("ufo", "ufo.bmp", 530, 32, 10, 1);
	//�Ѿ� �̹���
	IMAGEMANAGER->addImage("bullet", "bullet.bmp", 21, 21, true, RGB(255, 0, 255));


	//�÷��̾� Ŭ���� �ʱ�ȭ
	_player = new player;
	_player->init();

	//���Ŵ��� Ŭ���� �ʱ�ȭ
	_enemyManager = new enemyManager;
	_enemyManager->init();

	//��ȣ���� �����ϱ�
	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	return S_OK;
}

void sceneTest::release()
{
	//�÷��̾� Ŭ���� ����
	//_player->release();
	SAFE_DELETE(_player);

	//���Ŵ��� Ŭ���� ����
	_enemyManager->release();
	SAFE_DELETE(_enemyManager);
}

void sceneTest::update()
{
	//�÷��̾� Ŭ���� ������Ʈ
	_player->update();

	//���Ŵ��� Ŭ���� ������Ʈ
	_enemyManager->update();

	//������
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SCENEMANAGER->loadScene("�׽�Ʈ��1");
	}
}

void sceneTest::render()
{
	//��׶��� ����
	IMAGEMANAGER->render("��׶���", getMemDC());

	//�÷��̾� Ŭ���� ����
	_player->render();

	//���Ŵ��� Ŭ���� ����
	_enemyManager->render();
}
