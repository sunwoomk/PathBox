#include "Framework.h"

UIManager::UIManager()
{
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
	stageClearPanel = new StageClearPanel();
	stageClearPanel->UpdateWorld();
	panels.push_back(stageClearPanel);

	menuPanel = new MenuPanel(tileMaps);
	menuPanel->UpdateWorld();
	panels.push_back(menuPanel);
}
