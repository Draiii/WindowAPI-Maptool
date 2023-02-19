#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"

HRESULT player::init()
{
	//�÷��̾� �̹��� �ʱ�ȭ
	_rocket = IMAGEMANAGER->addImage("rocket", "rocket.bmp", WINSIZEX / 2, WINSIZEY - 100, 52, 64, true, RGB(255, 0, 255));
	//_rcPlayer = RectMakeCenter(WINSIZEX / 2, WINSIZEY - 100, 52, 64);
	
	//�̻��� Ŭ���� �ʱ�ȭ
	_missile = new missile;
	_missile->init(10, 400);

	//��ź Ŭ���� �ʱ�ȭ
	_bomb = new bomb;
	_bomb->init(5, 600);

	//ü�¹� Ŭ���� ������ �ʱ�ȭ
	_hpBar = new progressBar;
	_hpBar->init("progressBarFront", "progressBarBack", _rocket->getX(), _rocket->getY() - 20, 50, 10);
	//���� �ʱ�ȭ
	_maxHp = _currentHp = 100;
	_hpBar->setGauge(_currentHp, _maxHp);

	return S_OK;
}

void player::release()
{
	//�̻��� Ŭ���� ����
	_missile->release();
	SAFE_DELETE(_missile);

	//��ź Ŭ���� ����
	_bomb->release();
	SAFE_DELETE(_bomb);

	//ü�¹� Ŭ���� ����
	_hpBar->release();
	SAFE_DELETE(_hpBar);
}

void player::update()
{
	//�̹��� �ٿ���ڽ��� �浹ó��
	//RECT rc;
	//if(IntersectRect(&rc, &_rocket->boudingBox(), ))
	
	//�÷��̾� �����̱� & ȭ������� ����� ���ϰ�
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rocket->getX() > 0)
	{
		_rocket->setX(_rocket->getX() - 5.0f);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rocket->getX() < WINSIZEX)
	{
		_rocket->setX(_rocket->getX() + 5.0f);
	}
	//�Ѿ˹߻�
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//�Ѿ�Ŭ������ �ϲ� �߻���Ѷ�~
		_missile->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}
	//��ź�߻�
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		//��źŬ������ �ϲ� �߻���Ѷ�~
		_bomb->fire(_rocket->getX() + _rocket->getWidth() / 2, _rocket->getY() - 50);
	}

	//�̻��� Ŭ���� ������Ʈ
	_missile->update();

	//��ź Ŭ���� ������Ʈ
	_bomb->update();

	//�浹�Լ�
	this->collision();

	//ü�¹� Ŭ���� ������Ʈ
	_hpBar->update();
	//ü�¹ٰ� �÷��̾� �Ӹ����� ����ٴϰ� �����
	_hpBar->setX(_rocket->getX());
	_hpBar->setY(_rocket->getY() - 20);
	_hpBar->setGauge(_currentHp, _maxHp);

	//���̺�
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		//PLAYERDATA->setHp(_currentHp);
		//POINT pos;
		//pos.x = _rocket->getX();
		//pos.y = _rocket->getY();
		//PLAYERDATA->setPos(pos);

		//itoa =>������ ���ڷ�
		char temp[128];
		vector<string> vStr;
		vStr.push_back(itoa(_currentHp, temp, 10));
		vStr.push_back(itoa(_rocket->getX(), temp, 10));
		vStr.push_back(itoa(_rocket->getY(), temp, 10));

		TXTDATA->txtSave("save.txt", vStr);
	}
	//�ε�
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		//_currentHp = PLAYERDATA->getHp();
		//_rocket->setX(PLAYERDATA->getPos().x);
		//_rocket->setY(PLAYERDATA->getPos().y);
	
		vector<string> vStr;
		vStr = TXTDATA->txtLoad("save.txt");
		//atoi => ���ڸ� ������
		_currentHp = atoi(vStr[0].c_str());
		_rocket->setX(atoi(vStr[1].c_str()));
		_rocket->setY(atoi(vStr[2].c_str()));

	}

}

void player::render()
{
	//�÷��̾� ����
	_rocket->render(getMemDC(), _rocket->getX(), _rocket->getY());
	//_rocket->render(getMemDC(), _rcPlayer.left, _rcPlayer.top);

	//�̻��� Ŭ���� ����
	_missile->render();

	//��ź Ŭ���� ����
	_bomb->render();

	//ü�¹� Ŭ���� ����
	_hpBar->render();
}

//�浹�Լ� (�÷��̾� �Ѿ˵�� ���Ŵ����� �̴Ͼ�)
void player::collision()
{
	for (int i = 0; i < _bomb->getVBullet().size(); i++)
	{
		for (int j = 0; j < _em->getVMinion().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_bomb->getVBullet()[i].rc,
				&_em->getVMinion()[j]->getRect()))
			{
				_bomb->removeBomb(i);
				_em->removeMinion(j);
				break;
			}
		}
	}
}

void player::hitDamage(float damage)
{
	_currentHp -= damage;
}

void player::removeBomb(int index)
{
	//��źŬ������ �ϰ� �Ѿ� ������~ ���� �ε����� �Ѱ��ٲ�
	_bomb->removeBomb(index);
}
