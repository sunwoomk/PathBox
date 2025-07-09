#pragma once

class SceneManager : public Singleton<SceneManager>
{
public:
	SceneManager();
	~SceneManager();

	void Update();
	void PreRender();
	void Render();
	void PostRender();
	void GUIRender();

	void AddScene(string key, Scene* scene);
	void ChangeScene(string key);

	void AddStageScene(StageScene* scene) { stageScenes.push_back(scene); }
	void ChangeNextStageScene();

	int GetCurrentStageIndex();
	bool IsCurrentStageScene();

private:
	Scene* currentScene;
	
	unordered_map<string, Scene*> scenes;
	vector<StageScene*> stageScenes;
};