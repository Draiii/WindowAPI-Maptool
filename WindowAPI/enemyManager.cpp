#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	//�̴Ͼ� ���� ex) ����, �Ϲ� ���� ����
	//���� �Լ��� ���� ó���ϸ� ���⿡ ���ϴ�
	
	//�̴Ͼ� ����
	this->setMinion();
	//���� ����
	//this->setBoss();

	_count = 0;

	//�Ѿ� Ŭ���� �ʱ�ȭ
	_bullet = new bullet;
	_bullet->init("bullet", 15, 600);

	return S_OK;
}

void enemyManager::release()
{
	//�Ѿ� Ŭ���� ����
	_bullet->release();
	SAFE_DELETE(_bullet);
}

void enemyManager::update()
{
	//�Ѿ� Ŭ���� ������Ʈ
	_bullet->update();

	//���Ϳ� ��� �̴Ͼ�� ������Ʈ
	for (int i = 0; i < _vMinion.size(); i++)
	{
		_vMinion[i]->update();
	}

	//�̴Ͼ� �Ѿ˹߻�
	this->minionBulletFire();

	//�浹�Լ�
	this->collision();

}

void enemyManager::render()
{
	//�Ѿ� Ŭ���� ����
	_bullet->render();

	//���Ϳ� ��� �̴Ͼ�� ����
	for (int i = 0; i < _vMinion.size(); i++)
	{
		_vMinion[i]->render();
	}
}

//�浹ó�� (�����Ѿ˵�, �÷��̾�)
void enemyManager::collision()
{
	for (int i = 0; i < _bullet->getVBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_bullet->getVBullet()[i].rc,
			&_player->getPlayerImg()->boudingBox()))
		{
			//�����Ѿ� ����
			_bullet->removeBullet(i);
			//�÷��̾� ������
			_player->hitDamage(10);
			break;
		}
	}
}

void enemyManager::setMinion()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			enemy* ufo = new minion;
			ufo->init("ufo", PointMake(50 + j * 100, 100 + i * 100));

			_vMinion.push_back(ufo);
		}
	}

}

void enemyManager::minionBulletFire()
{
	_viMinion = _vMinion.begin();
	for (_viMinion; _viMinion != _vMinion.end(); ++_viMinion)
	{
		if ((*_viMinion)->bulletCountFire())
		{
			RECT rc = (*_viMinion)->getRect();
			_bullet->fire(rc.left + (rc.right - rc.left) / 2, rc.bottom + 30, -(PI / 2), 3.0f);
		}
	}
}

void enemyManager::removeMinion(int index)
{
	_vMinion.erase(_vMinion.begin() + index);
}
