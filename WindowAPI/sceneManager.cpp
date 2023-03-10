#include "stdafx.h"
#include "sceneManager.h"
#include "gameNode.h" //이놈 추가해줘야 함

HRESULT sceneManager::init()
{
	return S_OK;
}

void sceneManager::release()
{
	//정석적인 방법
	miSceneList iter = _mSceneList.begin();
	for (;iter != _mSceneList.end();)
	{
		if (iter->second != NULL)
		{
			if (iter->second == _currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = _mSceneList.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	_mSceneList.clear();

	//C++ 고급문법
	//for(auto scene in _mSceneList) 지금은 사용불가
	//for (auto scene : _mSceneList)
	//{
	//	scene.second->release();
	//	SAFE_DELETE(scene.second);
	//}

}

void sceneManager::update()
{
	//현재씬이 존재하면 해당하는 현재씬을 업데이트해라
	if (_currentScene) _currentScene->update();
}

void sceneManager::render()
{
	//현재씬이 존재하면 해당하는 현재씬을 렌더해라
	if (_currentScene) _currentScene->render();
}

gameNode * sceneManager::addScene(string sceneName, gameNode * scene)
{
	//씬이 없으면 그냥 널 리턴
	if (!scene) return NULL;

	//씬이 있으면 맵에 담기
	_mSceneList.insert(make_pair(sceneName, scene));
	//_mSceneList.insert(pair<string, gameNode*>(sceneName, scene));
	return scene;
}

HRESULT sceneManager::loadScene(string sceneName)
{
	miSceneList find = _mSceneList.find(sceneName);

	//못찾았다면 E_FAIL
	if (find == _mSceneList.end()) return E_FAIL;

	//바꾸려는 씬과 현재씬이 같다면 E_FAIL
	if (find->second == _currentScene) return E_FAIL;

	//여기까지 왔으면 문제가 없으니 씬을 변경처리하자
	if (SUCCEEDED(find->second->init()))
	{
		_currentScene = find->second;
		return S_OK;
	}

	return E_FAIL;
}
