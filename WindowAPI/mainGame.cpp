#include "stdafx.h"
#include "mainGame.h"

//=============================================================
//	## �ʱ�ȭ ## init()
//=============================================================
HRESULT mainGame::init()
{
	gameNode::init();
	//�̰����� �ʱ�ȭ�� �Ѵ�

	/*������ �޿������� ������ ���鸸 ������ �Ѵ�*/
	//������ ������ ���ΰ��� ������ �ϸ� �ȴ�
	
	/*���߰�*/
	SCENEMANAGER->addScene("�׽�Ʈ��", new sceneTest);
	SCENEMANAGER->addScene("�׽�Ʈ��1", new sceneTest1);
	SCENEMANAGER->addScene("�ȼ��浹", new pixcelCollisionScene);
	SCENEMANAGER->addScene("ini������", new iniTestScene);
	SCENEMANAGER->addScene("�ε�ȭ��", new loadingScene);
	SCENEMANAGER->addScene("�����׽�Ʈ", new soundTestScene);
	SCENEMANAGER->addScene("���̼Ҹ�Ʈ��", new isometricTest);
	SCENEMANAGER->addScene("��������", new maptoolScene);
	SCENEMANAGER->addScene("GDIPLUS", new gdipTestScene);
	SCENEMANAGER->addScene("��������", new mapTool1);



	//����� ����
	SCENEMANAGER->loadScene("��������");

	return S_OK;
}

//=============================================================
//	## ���� ## release()
//=============================================================
void mainGame::release()
{
	gameNode::release();
	//�̹��� Ŭ������ ���������� ����� �� ����
	//�����Ҵ� new�� ����ߴٸ� �̰����� SAFE_DELETE() ����Ѵ�
}


//=============================================================
//	## ������Ʈ ## update()
//=============================================================
void mainGame::update()
{
	gameNode::update();
	//�̰����� ����, Ű����, ���콺��� ������Ʈ�� �Ѵ�
	//�����ϰ� �̰����� �ڵ��Ѵٰ� �����ϸ� �ȴ�
	
	//���Ŵ��� ������Ʈ
	SCENEMANAGER->update();

	//����Ŵ��� ������Ʈ(�̳�����ָ� ���尡 �����۵�����)
	SOUNDMANAGER->update();
}

//=============================================================
//	## ���� ## render(HDC hdc)
//=============================================================
void mainGame::render()
{
	//��� �� ��Ʈ�� (�̰͵� ������ �׳� �α�)
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
//=============================================================

	//���Ŵ��� ����
	SCENEMANAGER->render();

	//Ÿ�ӸŴ��� ����
	TIMEMANAGER->render(getMemDC());

//=============================================================
	//������� ������ HDC�� �׸��� (�̰͵� ������ �׳� �α�)
	this->getBackBuffer()->render(getHDC());
}
