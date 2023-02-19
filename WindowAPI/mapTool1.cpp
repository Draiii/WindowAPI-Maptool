#include "stdafx.h"
#include "mapTool1.h"



HRESULT mapTool1::init()
{
	screen = RectMake(40, 40, 1000, 820);
	kindScreen = RectMake(1080, 40, 280, 160);
	secondScreen = RectMake(1080, 220, 280, 820 - 180);
	tileType = GROUND;

	moveX = moveY = 0;

	//페이지 넘기기 화살표
	leftArrow = RectMake(1040, 525, 40, 40);
	rightArrow = RectMake(1040 + 280 + 40, 525, 40, 40);

	//화살표 이미지
	GDIPLUS->addImage("right", "img/right1.png");
	GDIPLUS->addImage("left", "img/left1.png");
	//페이지 넘기기
	page = 0;
	pageCount = 0;
	//타일
	for (int i = 0; i < Y_EA; i++)
	{
		for (int j = 0; j < X_EA; j++)
		{
			INT total = i * X_EA + j;

			mainTile[total].width = WIDTH;
			mainTile[total].height = HEIGHT;
			mainTile[total].x = (screen.left + screen.right / 2) + (j * (mainTile->width / 2)) - (i * mainTile->width / 2);
			mainTile[total].y = 100 + (j * (mainTile->height / 2)) + (i * (mainTile->height / 2));
			mainTile[total].rc = RectMakeCenter(mainTile[total].x, mainTile[total].y, mainTile->width, mainTile->height);
			mainTile[total].leftCenter = mainTile[total].rightCenter = (mainTile[total].rc.top + mainTile[total].rc.bottom) / 2;
			mainTile[total].topCenter = mainTile[total].bottomCenter = (mainTile[total].rc.right + mainTile[total].rc.left) / 2;
			mainTile[total].image = NULL;
		}
	}

	//종류 선택	
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			SelectKind[i * 2 + j].width = 130;
			SelectKind[i * 2 + j].height = 30;
			SelectKind[i * 2 + j].x = kindScreen.left + 5 + (j * 135);
			SelectKind[i * 2 + j].y = 20 + (i * 40);
			SelectKind[i * 2 + j].rc = RectMake(SelectKind[i * 2 + j].x, SelectKind[i * 2 + j].y, SelectKind->width, SelectKind->height);
		}
	}
	

	IMAGEMANAGER->addImage("ground", "img/frame_ground.bmp", 130, 30, true, RGB(255,0,255));
	IMAGEMANAGER->addImage("ground_deco", "img/frame_ground_deco.bmp", 130, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("objects", "img/frame_objects.bmp", 130, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("npc", "img/frame_npc.bmp", 130, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("characters", "img/frame_characters.bmp", 130, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("building_inside", "img/frame_building_in.bmp", 130, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("building_outside", "img/frame_building_out.bmp", 130, 30, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("building_deco", "img/frame_building_deco.bmp", 130, 30, true, RGB(255, 0, 255));
	
	//셀렉트타일
	for (int i = 0; i < SELECTY; i++)
	{
		for (int j = 0; j < SELECTX; j++)
		{
			selectTile[i][j].width = WIDTH;
			selectTile[i][j].height = HEIGHT;
			selectTile[i][j].x = secondScreen.left + 50 + (j * WIDTH) + (j * 5);
			selectTile[i][j].y = secondScreen.top + 51  + (i * HEIGHT * 2) + (i * 5);
			selectTile[i][j].rc = RectMakeCenter(selectTile[i][j].x, selectTile[i][j].y, WIDTH, HEIGHT * 2);
			selectTile[i][j].image = NULL;
		}
	}
	
	//그라운드 타일
	for (int i = 0;i < GROUND_MAX; i++)
	{		
		tagGround ground;
		ground.height = IMAGE_WIDTH;
		ground.width = IMAGE_HEIGHT;
		ground.x = NULL;
		ground.y = NULL;
		char num[128];
		char file[128];
		sprintf(num, "ground%04d", i);
		sprintf(file, "img/ground/%04d.gif", i);
		/*if (i >= 0 && i < 10)
		{
			sprintf(num, "ground000%d", i);
			sprintf(file, "img/ground/000%d.gif", i);
		}
		else if (i >= 10 && i < 100)
		{
			sprintf(num, "ground00%d", i);
			sprintf(file, "img/ground/00%d.gif", i);
		}	
		else if (i >= 100 && i < 1000)
		{
			sprintf(num, "ground0%d", i);
			sprintf(file, "img/ground/0%d.gif", i);
		}		*/
		ground.image = GDIPLUS->addImage(num, file, IMAGE_WIDTH, IMAGE_HEIGHT);

		////빠져나오기
		//if (ground.groundImage == NULL)	break;
		vGround.push_back(ground);	
	}	

	//그라운드 데코 타일
	for (int i = 0; i < 353; i++)
	{
		tagGroundDeco groundDeco;
		groundDeco.height = IMAGE_WIDTH;
		groundDeco.width = IMAGE_HEIGHT;
		groundDeco.x = NULL;
		groundDeco.y = NULL;
		char num[128];
		char file[128];
		sprintf(num, "ground_decor%04d", i);
		sprintf(file, "img/ground_decor/%04d.gif", i);

		groundDeco.image = GDIPLUS->addImage(num, file, IMAGE_WIDTH, IMAGE_HEIGHT);

		////빠져나오기
		//if (ground.groundImage == NULL)	break;
		vGroundDeco.push_back(groundDeco);
	}

	//오브젝트
	for (int i = 0; i < 17; i++)
	{
		tagObject objects;
		objects.height = IMAGE_WIDTH;
		objects.width = IMAGE_HEIGHT;
		objects.x = NULL;
		objects.y = NULL;
		char num[128];
		char file[128];
		sprintf(num, "object%04d", i);
		sprintf(file, "img/objects/%04d.gif", i);

		objects.image = GDIPLUS->addImage(num, file, IMAGE_WIDTH, IMAGE_HEIGHT);

		////빠져나오기
		//if (ground.groundImage == NULL)	break;
		vObjects.push_back(objects);
	}

	//NPC
	for (int i = 0; i < NPC_MAX; i++)
	{
		tagNpc npc;
		npc.height = IMAGE_WIDTH;
		npc.width = IMAGE_HEIGHT;
		npc.x = NULL;
		npc.y = NULL;
		char num[128];
		char file[128];
		sprintf(num, "npc%04d", i);
		sprintf(file, "img/npc/%04d.gif", i);

		npc.image = GDIPLUS->addImage(num, file, IMAGE_WIDTH, IMAGE_HEIGHT);

		////빠져나오기
		//if (ground.groundImage == NULL)	break;
		vNpc.push_back(npc);
	}

	//charactors
	for (int i = 0; i < CHARACTORS_MAX; i++)
	{
		tagCharacters characters;
		characters.height = IMAGE_WIDTH;
		characters.width = IMAGE_HEIGHT;
		characters.x = NULL;
		characters.y = NULL;
		char num[128];
		char file[128];
		sprintf(num, "characters%04d", i);
		sprintf(file, "img/characters/%04d.gif", i);

		characters.image = GDIPLUS->addImage(num, file, IMAGE_WIDTH, IMAGE_HEIGHT);

		////빠져나오기
		//if (ground.groundImage == NULL)	break;
		vCharacters.push_back(characters);
	}



	//buildngOutSide
	for (int i = 0; i < BUILDING_OUTSIDE_MAX; i++)
	{
		tagBuildingOutSide buildngOutSide;
		buildngOutSide.height = IMAGE_WIDTH;
		buildngOutSide.width = IMAGE_HEIGHT;
		buildngOutSide.x = NULL;
		buildngOutSide.y = NULL;
		char num[128];
		char file[128];
		sprintf(num, "buildngOutSide%04d", i);
		sprintf(file, "img/building_outside/%04d.gif", i);

		buildngOutSide.image = GDIPLUS->addImage(num, file, IMAGE_WIDTH, IMAGE_HEIGHT);

		////빠져나오기
		//if (ground.groundImage == NULL)	break;
		vBuildingOutSide.push_back(buildngOutSide);
	}

	//buildnginSideground
	for (int i = 0; i < BUILDING_INSIDE_GROUND_MAX; i++)
	{
		tagBuildingInSideGround buildngInSideGround;
		buildngInSideGround.height = IMAGE_WIDTH;
		buildngInSideGround.width = IMAGE_HEIGHT;
		buildngInSideGround.x = NULL;
		buildngInSideGround.y = NULL;
		char num[128];
		char file[128];
		sprintf(num, "buildngInSideGround%04d", i);
		sprintf(file, "img/building_inside_ground/%04d.gif", i);

		buildngInSideGround.image = GDIPLUS->addImage(num, file, IMAGE_WIDTH, IMAGE_HEIGHT);

		////빠져나오기
		//if (ground.groundImage == NULL)	break;
		vBuildingInSideGround.push_back(buildngInSideGround);
	}

	//buildnginSideground
	for (int i = 0; i < BUILDING_INSIDE_DECO_MAX; i++)
	{
		tagBuildingInSideDeco buildngInSideDeco;
		buildngInSideDeco.height = IMAGE_WIDTH;
		buildngInSideDeco.width = IMAGE_HEIGHT;
		buildngInSideDeco.x = NULL;
		buildngInSideDeco.y = NULL;
		char num[128];
		char file[128];
		sprintf(num, "buildngInSideDeco%04d", i);
		sprintf(file, "img/building_inside_deco/%04d.gif", i);

		buildngInSideDeco.image = GDIPLUS->addImage(num, file, IMAGE_WIDTH, IMAGE_HEIGHT);

		////빠져나오기
		//if (ground.groundImage == NULL)	break;
		vBuildingInSideDeco.push_back(buildngInSideDeco);
	}

	//툴바
	GDIPLUS->addImage("back1", "img/back1.png");
	


	temp = NULL;

	return S_OK;
}

void mapTool1::release()
{
}

void mapTool1::update()
{
	//타일타입에 따라 상자갯수 만들기
	if (tileType == GROUND)	tileTypeNum = 48;	
	if (tileType == GROUND_DECO) tileTypeNum = 118;
	if (tileType == OBJECTS) tileTypeNum = 6;
	if (tileType == NPC) tileTypeNum = 12;
	if (tileType == CHARACTERS) tileTypeNum = 9;
	if (tileType == BUILDING_OUTSIDE) tileTypeNum = 26;
	if (tileType == BUILDING_INSIDE_GORUND) tileTypeNum = 8;
	if (tileType == BUILDING_INSIDE_DECO) tileTypeNum = 29;


	//메인타일업데이트
	for (int i = 0; i < MAX; i++)
	{
		mainTile[i].rc = RectMakeCenter(mainTile[i].x + moveX, mainTile[i].y + moveY, mainTile->width, mainTile->height);
	}



	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		//타일 위에 그리기
		for (int i = 0; i < MAX; i++)
		{
			if (PtInRect(&mainTile[i].rc, _ptMouse))
			{
				if (_ptMouse.y > mainTile[i].y)//3 4분면 체크
				{
					if (_ptMouse.x > mainTile[i].x) //4분면
					{
						if ((_ptMouse.x) <= mainTile[i].x + (WIDTH / 2) + (_ptMouse.y + mainTile[i].y) * 2)
						{
							mainTile[i].image = temp;


							for (int i = 0; i < MAX; i++)
							{
								if (mainTile[i].rc.left > screen.right) continue;
								if (mainTile[i].rc.top > screen.bottom) continue;
								if (mainTile[i].rc.right < screen.left) continue;
								if (mainTile[i].rc.bottom < screen.top) continue;


								GDIPLUS->findImage("ground0001")->gdiRender(tempDC->getMemDC(), mainTile[i].rc.left, mainTile[i].rc.top - HEIGHT);
								//타일 그리기
								if (mainTile[i].image != NULL)
									mainTile[i].image->gdiRender(tempDC->getMemDC(), mainTile[i].rc.left, mainTile[i].rc.top - HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT);

								//타일위에 오브젝트 보여주기
								if (PtInRect(&mainTile[i].rc, _ptMouse))
								{
									if (temp == NULL) continue;
									temp->gdiRender(tempDC->getMemDC(), mainTile[i].rc.left, mainTile[i].rc.top - HEIGHT);
								}
							}

							break;
						}
					}

					else	//3분면
					{
						if ((_ptMouse.x) <= mainTile[i].x + (WIDTH / 2) - (_ptMouse.y + mainTile[i].y) * 2)
						{
							mainTile[i].image = temp;

							GDIPLUS->findImage("ground0001")->gdiRender(tempDC->getMemDC(), mainTile[i].rc.left, mainTile[i].rc.top - HEIGHT);
							//타일 그리기
							if (mainTile[i].image != NULL)
								mainTile[i].image->gdiRender(tempDC->getMemDC(), mainTile[i].rc.left, mainTile[i].rc.top - HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT);

							//타일위에 오브젝트 보여주기
							if (PtInRect(&mainTile[i].rc, _ptMouse))
							{
								if (temp == NULL) continue;
								temp->gdiRender(tempDC->getMemDC(), mainTile[i].rc.left, mainTile[i].rc.top - HEIGHT);
							}
							break;
						}
					}
				}

				else //1 2 분면
				{
					if (_ptMouse.x > mainTile[i].x) //1 분면
					{
						if ((_ptMouse.x) <= mainTile[i].x + (WIDTH / 2) + (_ptMouse.y + mainTile[i].y) * 2)
						{
							mainTile[i].image = temp;

							GDIPLUS->findImage("ground0001")->gdiRender(tempDC->getMemDC(), mainTile[i].rc.left, mainTile[i].rc.top - HEIGHT);
							//타일 그리기
							if (mainTile[i].image != NULL)
								mainTile[i].image->gdiRender(tempDC->getMemDC(), mainTile[i].rc.left, mainTile[i].rc.top - HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT);

							//타일위에 오브젝트 보여주기
							if (PtInRect(&mainTile[i].rc, _ptMouse))
							{
								if (temp == NULL) continue;
								temp->gdiRender(tempDC->getMemDC(), mainTile[i].rc.left, mainTile[i].rc.top - HEIGHT);
							}
							break;
						}
					}
					else	//2분면
					{
						if ((_ptMouse.x) <= mainTile[i].x + (WIDTH / 2) - (_ptMouse.y + mainTile[i].y) * 2)
						{
							mainTile[i].image = temp;

							GDIPLUS->findImage("ground0001")->gdiRender(tempDC->getMemDC(), mainTile[i].rc.left, mainTile[i].rc.top - HEIGHT);
							//타일 그리기
							if (mainTile[i].image != NULL)
								mainTile[i].image->gdiRender(tempDC->getMemDC(), mainTile[i].rc.left, mainTile[i].rc.top - HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT);

							//타일위에 오브젝트 보여주기
							if (PtInRect(&mainTile[i].rc, _ptMouse))
							{
								if (temp == NULL) continue;
								temp->gdiRender(tempDC->getMemDC(), mainTile[i].rc.left, mainTile[i].rc.top - HEIGHT);
							}
							break;
						}
					}
				}
			}
		}


		//병준쓰 
		for (int i = 0; i < X_EA; i++)
		{
			for (int j = 0; j < Y_EA; j++)
			{
				if (i == j)
					continue;
				if (PtInRect(&mainTile[i].rc, _ptMouse) && PtInRect(&mainTile[j].rc, _ptMouse))
				{
					int x1 = (mainTile[i].rc.left + mainTile[i].rc.right) / 2;
					int y1 = (mainTile[i].rc.top + mainTile[i].rc.bottom) / 2;
					int x2 = (mainTile[j].rc.left + mainTile[j].rc.right) / 2;
					int y2 = (mainTile[j].rc.top + mainTile[j].rc.bottom) / 2;

					x1 = abs(x1 - _ptMouse.x);
					y1 = abs((y1 - _ptMouse.y) * 2);
					x2 = abs(x2 - _ptMouse.x);
					y2 = abs((y2 - _ptMouse.y) * 2);


					int one = abs(x1 + y1);
					int two = abs(x2 + y2);

					if (one < two)
					{
						mainTile[i].image = temp;		
						break;
					}

					else 
					{
						mainTile[j].image = temp;		
						break;
					}
				}
			}
		}

	}


	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{		

		//페이지 넘기기
		if (PtInRect(&leftArrow, _ptMouse))	pageCount--;		
		if (PtInRect(&rightArrow, _ptMouse))  pageCount++;

		//종류 선택
		for (int i = 0; i < KIND_MAX; i++)
		{
			if (PtInRect(&SelectKind[i].rc, _ptMouse))
			{
				pageCount = 0;
				if (i == 0) tileType = GROUND;
				else if (i == 1) tileType = GROUND_DECO;
				else if (i == 2) tileType = OBJECTS;
				else if (i == 3) tileType = NPC;
				else if (i == 4) tileType = CHARACTERS;
				else if (i == 5) tileType = BUILDING_OUTSIDE;
				else if (i == 6) tileType = BUILDING_INSIDE_GORUND;
				else if (i == 7) tileType = BUILDING_INSIDE_DECO;
			}
		}
			   

		//타일 선택
		for (int i = 0; i < SELECTY; i++)
		{
			for (int j = 0; j < SELECTX; j++)
			{
				if (PtInRect(&selectTile[i][j].rc, _ptMouse))
				{
					if (tileType == GROUND)
					{
						temp = vGround[(i * 3 + j) + page].image;
					}

					if (tileType == GROUND_DECO)
					{
						temp = vGroundDeco[(i * 3 + j) + page].image;
					}

					if (tileType == OBJECTS)
					{
						temp = vObjects[(i * 3 + j) + page].image;
					}

					if (tileType == NPC)
					{
						temp = vNpc[(i * 3 + j) + page].image;
					}

					if (tileType == CHARACTERS)
					{
						temp = vCharacters[(i * 3 + j) + page].image;
					}

					if (tileType == BUILDING_OUTSIDE)
					{
						temp = vBuildingOutSide[(i * 3 + j) + page].image;
					}

					if (tileType == BUILDING_INSIDE_GORUND)
					{
						temp = vBuildingInSideGround[(i * 3 + j) + page].image;
					}

					if (tileType == BUILDING_INSIDE_DECO)
					{
						temp = vBuildingInSideDeco[(i * 3 + j) + page].image;
					}
				}
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RBUTTON))
	{
		//오브젝트 지우기
		for (int i = 0; i < MAX; i++)
		{
			
		}
	}

	this->mapMove();

	if (pageCount < 0) pageCount = 0;
	page = (SELECTY * SELECTX) * pageCount;
}

void mapTool1::render()
{
	//메인 스크린
	Rectangle(getMemDC(), screen);	
	gdipImage* ground0001 = GDIPLUS->findImage("ground0001");
	tempDC->render(getMemDC());
	//메인 타일
	//for (int i = 0; i < MAX; i++)
	//{
	//	if (mainTile[i].rc.left > screen.right) continue;
	//	if (mainTile[i].rc.top > screen.bottom) continue;
	//	if (mainTile[i].rc.right < screen.left) continue;
	//	if (mainTile[i].rc.bottom < screen.top) continue;
	//	//Rectangle(getMemDC(),mainTile[i].rc);

	//	//if (PtInRect(&mainTile[i].rc, _ptMouse))
	//	//{
	//	//	//탑>레프트
	//	//	LineMake(getMemDC(), mainTile[i].topCenter, mainTile[i].rc.top, mainTile[i].rc.left, mainTile[i].leftCenter);
	//	//	//레프트>바텀
	//	//	LineMake(getMemDC(), mainTile[i].rc.left, mainTile[i].leftCenter, mainTile[i].bottomCenter, mainTile[i].rc.bottom);
	//	//	//바텀>라이트
	//	//	LineMake(getMemDC(), mainTile[i].bottomCenter, mainTile[i].rc.bottom, mainTile[i].rc.right, mainTile[i].rightCenter);
	//	//	//라이트>탑
	//	//	LineMake(getMemDC(), mainTile[i].rc.right, mainTile[i].rightCenter, mainTile[i].topCenter, mainTile[i].rc.top);
	//	//}
	//	
	//	ground0001->gdiRender(getMemDC(), mainTile[i].rc.left, mainTile[i].rc.top - HEIGHT);
	//	//타일 그리기
	//	if (mainTile[i].image != NULL)
	//		mainTile[i].image->gdiRender(getMemDC(), mainTile[i].rc.left, mainTile[i].rc.top - HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT);

	//	//타일위에 오브젝트 보여주기
	//	if (PtInRect(&mainTile[i].rc, _ptMouse))
	//	{
	//		if (temp == NULL) continue;
	//		temp->gdiRender(getMemDC(), mainTile[i].rc.left, mainTile[i].rc.top - HEIGHT);
	//	}
	//}




	//셀렉트 툴 스크린
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH oBrush = (HBRUSH)SelectObject(getMemDC(), brush);	
	Rectangle(getMemDC(), secondScreen);
	SelectObject(getMemDC(), oBrush);
	DeleteObject(brush);
	

	//셀렉트 타일
	for (int i = 0; i < SELECTY; i++)
	{
		for (int j = 0; j < SELECTX; j++)
		{		
			Rectangle(getMemDC(), selectTile[i][j].rc);
		}
	}

	

	//타일 선택하는거 그리는거임
	for (int i = 0; i < SELECTY; i++)
	{
		for (int j = 0; j < SELECTX; j++)
		{
			//프레임 렉트 녹색선
			if (PtInRect(&selectTile[i][j].rc, _ptMouse))
			{
				FrameRect(getMemDC(), selectTile[i][j].rc, RGB(50, 255, 0));
			}

			//그라운드 그리기
			if (tileType == GROUND)
			{				
				if ((i * 3 + j) + page >= GROUND_MAX) break;
				
				vGround[(i * 3 + j) + page].image->gdiRender(getMemDC(), selectTile[i][j].rc.left, selectTile[i][j].rc.top);
			
			}		

			//그라운드 데코 그리기
			if (tileType == GROUND_DECO)
			{
				if ((i * 3 + j) + page >= GROUND_DECO_MAX) break;
				if ((i * 3 + j) + page < 0) break;
				vGroundDeco[(i * 3 + j) + page].image->gdiRender(getMemDC(), selectTile[i][j].rc.left, selectTile[i][j].rc.top);
			}

			//오브젝트 그리기
			if (tileType == OBJECTS)
			{
				if ((i * 3 + j) + page >= OBJECTS_MAX) break;
				if ((i * 3 + j) + page < 0) break;
				vObjects[(i * 3 + j) + page].image->gdiRender(getMemDC(), selectTile[i][j].rc.left, selectTile[i][j].rc.top);
			}

			//NPC 그리기
			if (tileType == NPC)
			{
				if ((i * 3 + j) + page >= NPC_MAX) break;
				if ((i * 3 + j) + page < 0) break;
				vNpc[(i * 3 + j) + page].image->gdiRender(getMemDC(), selectTile[i][j].rc.left, selectTile[i][j].rc.top);
			}

			//charactors 그리기
			if (tileType == CHARACTERS)
			{
				if ((i * 3 + j) + page >= CHARACTORS_MAX) break;
				if ((i * 3 + j) + page < 0) break;
				vCharacters[(i * 3 + j) + page].image->gdiRender(getMemDC(), selectTile[i][j].rc.left, selectTile[i][j].rc.top);
			}

			//building_outside 그리기
			if (tileType == BUILDING_OUTSIDE)
			{
				if ((i * 3 + j) + page >= BUILDING_OUTSIDE_MAX) break;
				if ((i * 3 + j) + page < 0) break;
				vBuildingOutSide[(i * 3 + j) + page].image->gdiRender(getMemDC(), selectTile[i][j].rc.left, selectTile[i][j].rc.top);
				
			}

			//building_outside 그리기
			if (tileType == BUILDING_INSIDE_GORUND)
			{
				if ((i * 3 + j) + page >= BUILDING_INSIDE_GROUND_MAX) break;
				if ((i * 3 + j) + page < 0) break;
				vBuildingInSideGround[(i * 3 + j) + page].image->gdiRender(getMemDC(), selectTile[i][j].rc.left, selectTile[i][j].rc.top);
			}

			//building_inside_deco 그리기
			if (tileType == BUILDING_INSIDE_DECO)
			{
				if ((i * 3 + j) + page >= BUILDING_INSIDE_DECO_MAX) break;
				if ((i * 3 + j) + page < 0) break;
				vBuildingInSideDeco[(i * 3 + j) + page].image->gdiRender(getMemDC(), selectTile[i][j].rc.left, selectTile[i][j].rc.top);
			}
		}
	}
	
	
	//백그라운드 (메인타일이 가려지게 밑에 렌더)
	GDIPLUS->gdiRender("back1", getMemDC());


	//왼쪽 오른쪽 넘기기
	//Rectangle(getMemDC(), leftArrow);
	//Rectangle(getMemDC(), rightArrow);
	GDIPLUS->gdiRender("right", getMemDC(), rightArrow.left, rightArrow.top);
	GDIPLUS->gdiRender("left", getMemDC(), leftArrow.left, leftArrow.top);

	// 오브젝트 / 종류 선택
	Rectangle(getMemDC(), kindScreen);
	for (int i = 0; i < KIND_MAX; i++)
	{
		//Rectangle(getMemDC(), SelectKind[i].rc);		
	}
	IMAGEMANAGER->render("ground", getMemDC(), SelectKind[0].rc.left, SelectKind[0].rc.top, 0, 0, 130, 30);
	IMAGEMANAGER->render("ground_deco", getMemDC(), SelectKind[1].rc.left, SelectKind[1].rc.top, 0, 0, 130, 30);
	IMAGEMANAGER->render("objects", getMemDC(), SelectKind[2].rc.left, SelectKind[2].rc.top, 0, 0, 130, 30);
	IMAGEMANAGER->render("npc", getMemDC(), SelectKind[3].rc.left, SelectKind[3].rc.top, 0, 0, 130, 30);
	IMAGEMANAGER->render("characters", getMemDC(), SelectKind[4].rc.left, SelectKind[4].rc.top, 0, 0, 130, 30);
	IMAGEMANAGER->render("building_inside", getMemDC(), SelectKind[5].rc.left, SelectKind[5].rc.top, 0, 0, 130, 30);
	IMAGEMANAGER->render("building_outside", getMemDC(), SelectKind[6].rc.left, SelectKind[6].rc.top, 0, 0, 130, 30);
	IMAGEMANAGER->render("building_deco", getMemDC(), SelectKind[7].rc.left, SelectKind[7].rc.top, 0, 0, 130, 30);


	/*GROUND, GROUND_DECO,
		OBJECTS, NPC, CHARACTERS, CHANGE_ZONE,
		BUILDING_OUTSIDE, BUILDING_INSIDE_GORUND, BUILDING_INSIDE_DECO
*/

	//테스트
	//GDIPLUS->gdiRender("ground0011", getMemDC(), selectTile[0]->rc.left, selectTile[0]->rc.top);
	//GDIPLUS->gdiRender("ground0000", getMemDC(), _ptMouse.x-41, _ptMouse.y-62);

	//그라운드 렌더


	////마우스에 이미지 띄우기
	//if (temp != NULL)
	//	temp->gdiRender(getMemDC(), _ptMouse.x - WIDTH / 2, _ptMouse.y - HEIGHT);
	//그냥 마우스 따라다니는 라인...
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		if (PtInRect(&screen, _ptMouse))
		{
			LineMake(getMemDC(), _ptMouse.x, screen.top, _ptMouse.x, screen.bottom);		
			LineMake(getMemDC(), screen.left, _ptMouse.y, screen.right,_ptMouse.y);
		}
	}

}
//맵이동
void mapTool1::mapMove()
{

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		moveX += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		moveY += 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		moveX -= 5;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		moveY -= 5;
	}





}
