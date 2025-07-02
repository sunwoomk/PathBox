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
	bool GetIsMenuPanelActive() const { return isMenuPanelActive; }

	void SetTileMaps(TileMaps* tileMaps) { this->tileMaps = tileMaps; }
	void SetPanels();

private:
	bool isMenuPanelActive = false;

	vector<Panel*> panels;
	StageClearPanel* stageClearPanel;
	MenuPanel* menuPanel;
	TileMaps* tileMaps = nullptr;
};