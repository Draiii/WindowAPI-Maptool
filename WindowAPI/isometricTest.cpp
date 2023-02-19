#include "stdafx.h"
#include "isometricTest.h"

HRESULT isometricTest::init()
{
	//Ÿ�� ����ü �ʱ�ȭ
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			_tile[i][j].x = STARTX + (j * (TILESIZEX_HALF)) - (i * (TILESIZEX_HALF));
			_tile[i][j].y = STARTY + (j * (TILESIZEY_HALF)) + (i * (TILESIZEY_HALF));
			_tile[i][j].rc = RectMakeCenter(_tile[i][j].x, _tile[i][j].y, TILESIZEX, TILESIZEY);
		}
	}

	//�ε��� �ʱ�ȭ
	_index = { 0, 0 };

	return S_OK;
}

void isometricTest::release()
{
}

void isometricTest::update()
{
	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//��Ʈ��� ���콺��ǥ�� �浹�ߴ���?
			if (PtInRect(&_tile[i][j].rc, _ptMouse))
			{

				if (_ptMouse.y > _tile[i][j].y) //3, 4�и�
				{
					if (_ptMouse.x > _tile[i][j].x) //4�и�
					{
						if ((_ptMouse.x) <= _tile[i][j].x + TILESIZEX_HALF + _tile[i][j].y - (_ptMouse.y - _tile[i][j].y))
						{
							_index.x = j;
							_index.y = i;
						}
					}
					else//3�и�
					{
						if (_ptMouse.x >= (_tile[i][j].x - TILESIZEX_HALF) + ((_ptMouse.y - _tile[i][j].y) * 2))
						{
							_index.x = j;
							_index.y = i;
						}
					}
				}
				else//1, 2�и�
				{
					if (_ptMouse.x > _tile[i][j].x) //1�и�
					{

					}
					else //2�и�
					{

					}

				}


			}
		}
	}

}

void isometricTest::render()
{
	char str[128];

	for (int i = 0; i < TILEY; i++)
	{
		for (int j = 0; j < TILEX; j++)
		{
			//������ ��Ʈ �����ֱ�
			if (KEYMANAGER->isToggleKey(VK_F1))
			{
				Rectangle(getMemDC(), _tile[i][j].rc);
				//FrameRect(getMemDC(), _tile[i][j].rc, RGB(255, 0, 0));
			}

			//������ �� �׸���
			MoveToEx(getMemDC(), _tile[i][j].x - (TILESIZEX / 2), _tile[i][j].y, NULL);
			LineTo(getMemDC(), _tile[i][j].x, _tile[i][j].y - (TILESIZEY / 2));
			LineTo(getMemDC(), _tile[i][j].x + (TILESIZEX / 2), _tile[i][j].y);
			LineTo(getMemDC(), _tile[i][j].x , _tile[i][j].y + (TILESIZEY / 2));
			LineTo(getMemDC(), _tile[i][j].x - (TILESIZEX / 2), _tile[i][j].y);

			//Ÿ�Ͼȿ� �ε��� ǥ��
			sprintf(str, "[%d, %d]", j, i);
			TextOut(getMemDC(), _tile[i][j].x, _tile[i][j].y - 15, str, strlen(str));

		}
	}

	sprintf(str, "�����ε��� : [%d, %d]", _index.x, _index.y);
	TextOut(getMemDC(), STARTX + 200, STARTY - 50, str, strlen(str));

}
