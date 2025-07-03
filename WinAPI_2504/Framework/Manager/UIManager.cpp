#include "Framework.h"

UIManager::UIManager()
{
	SetPanels();
}

UIManager::~UIManager()
{
	for (Panel* panel : panels)
	{
		delete panel;
	}
	panels.clear();
}

void UIManager::Update()
{
	if (Input::Get()->IsKeyDown(VK_ESCAPE)) 
	{
		menuPanel->SetActive(!menuPanel->IsActive());
	}
	for (Panel* panel : panels)
	{
		if (panel->IsActive())
			panel->Update();
	}
}

void UIManager::Render()
{
	for (Panel* panel : panels)
	{
		if (panel->IsActive())
			panel->Render();
	}
}

void UIManager::SetPanels()
{
	panels.clear();
	stageClearPanel = new StageClearPanel();
	panels.push_back(stageClearPanel);

	selectStagePanel = new SelectStagePanel();
	selectStagePanel->UpdateWorld();
	panels.push_back(selectStagePanel);
}

void UIManager::SetMenuPanel()
{
	menuPanel = new MenuPanel(tileMaps);
	panels.push_back(menuPanel);
}
