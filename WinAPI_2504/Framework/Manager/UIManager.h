#pragma once

class UIManager : public Singleton<UIManager> 
{
public:
	UIManager();
	~UIManager();

	void Update();
	void Render();

	void SetActiveStageClearPanel() { stageClearPanel->SetActive(true); }
	bool GetIsMenuPanelActive() const { return menuPanel->IsActive(); }

	void SetTileMaps(TileMaps* tileMaps) { this->tileMaps = tileMaps; }
	void SetPanels();

	SelectStagePanel* GetSelectStagePanel() const { return selectStagePanel; }

private:
	vector<Panel*> panels;
	SelectStagePanel* selectStagePanel;
	StageClearPanel* stageClearPanel;
	MenuPanel* menuPanel;
	TileMaps* tileMaps = nullptr;
};