#include "stdafx.h"
#include "iniTestScene.h"

HRESULT iniTestScene::init()
{
	return S_OK;
}

void iniTestScene::release()
{
}

void iniTestScene::update()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//����, Ű, ���
		//[�ù�15��]
		//����=50
		//����=100
		//...

		INIDATA->addData("�ù�15��", "����", "50.5");
		INIDATA->addData("�ù�15��", "����", "100");
		INIDATA->addData("�ù�15��", "����", "8");

		//���� �̸����� ���̺�
		INIDATA->saveINI("�ù��ù�");
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		int num = INIDATA->loadDataInteger("�ù��ù�", "�ù�15��", "����");
		cout << num << endl;
	}
}

void iniTestScene::render()
{
}
