#pragma once

class UIManager : public Singleton<UIManager> 
{
public:
	UIManager();
	~UIManager();

	void Update();
	void Render();

	void SwitchMenuPanel() { menuPanel->SetActive(!menuPanel->IsActive()); }
	void SetActiveStageClearPanel() { stageClearPanel->SetActive(true); }
	bool GetIsMenuPanelActive() const { return menuPanel->IsActive(); }

	void SetTileMaps(TileMaps* tileMaps) { this->tileMaps = tileMaps; }
	void SetPanels();

private:
	vector<Panel*> panels;
	StageClearPanel* stageClearPanel;
	MenuPanel* menuPanel;
	TileMaps* tileMaps = nullptr;
};