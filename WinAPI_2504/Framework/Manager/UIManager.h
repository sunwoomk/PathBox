#pragma once

class UIManager : public Singleton<UIManager> 
{
public:
	UIManager();
	~UIManager();

	void Update();
	void Render();

	//void SetActiveStageClearPanel() { stageClearPanel->SetActive(true); }
	//bool GetIsMenuPanelActive() { return menuPanel->IsActive(); }

	bool GetPanelActive(string panel);
	void SetPanelActive(string panel, bool active);

	void SetTileMaps(TileMaps* tileMaps) { this->tileMaps = tileMaps; }
	void SetPanels();
	void SetMenuPanel();

	SelectStagePanel* GetSelectStagePanel() { return selectStagePanel; }

private:
	vector<Panel*> panels;
	SelectStagePanel* selectStagePanel;
	StageClearPanel* stageClearPanel;
	StartScenePanel* startScenePanel;
	MenuPanel* menuPanel;
	TileMaps* tileMaps = nullptr;
};