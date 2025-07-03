#include "Framework.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	for (pair<string, Scene*> scene : scenes)
	{
		delete scene.second;
	}
}

void SceneManager::Update()
{
	currentScene->Update();
}

void SceneManager::PreRender()
{
	currentScene->PreRender();
}

void SceneManager::Render()
{
	currentScene->Render();	
}

void SceneManager::PostRender()
{
	currentScene->PostRender();
}

void SceneManager::GUIRender()
{
	currentScene->GUIRender();
}

void SceneManager::AddScene(string key, Scene* scene)
{
	if (scenes.count(key) > 0)
		return;

	scenes[key] = scene;
}

void SceneManager::ChangeScene(string key)
{
	if (scenes.count(key) == 0)
		return;

	//if (currentScene != nullptr)
	if(currentScene)
	{
		currentScene->End();
	}

	currentScene = scenes[key];

	TestScene* testScene = dynamic_cast<TestScene*>(currentScene);
	if (testScene) 
	{
		TileMaps* tileMaps = testScene->GetTileMaps();
		UIManager::Get()->SetTileMaps(tileMaps);
		tileMaps->Restart();
		UIManager::Get()->SetMenuPanel();
	}
	currentScene->Start();
}

void SceneManager::ChangeNextStageScene()
{
	for (size_t i = 0; i < stageScenes.size(); ++i)
	{
		if (stageScenes[i] == currentScene)
		{
			if (i + 1 < stageScenes.size())
			{
				for (const auto& pair : scenes)
				{
					if (pair.second == stageScenes[i + 1])
					{
						ChangeScene(pair.first);
						return;
					}
				}
			}
			else
				return;
		}
	}
}

int SceneManager::GetCurrentStageIndex()
{
	for (int i = 0; i < stageScenes.size(); i++)
	{
		if (stageScenes[i] == currentScene)
			return static_cast<int>(i);
	}
	return -1;
}
