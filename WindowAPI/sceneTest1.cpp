#include "stdafx.h"
#include "sceneTest1.h"


HRESULT sceneTest1::init()
{
	return S_OK;
}

void sceneTest1::release()
{
}

void sceneTest1::update()
{
	//������
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		//���������� �ݵ�� �����ʹ� �����صα�

		//�����Ŀ� �������ϱ�
		SCENEMANAGER->loadScene("�׽�Ʈ��");
	}
}

void sceneTest1::render()
{
	TextOut(getMemDC(), 100, 100, "�׽�Ʈ1����", strlen("�׽�Ʈ1����"));
}
