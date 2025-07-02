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
		isMenuPanelActive = menuPanel->IsActive();
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

	menuPanel = new MenuPanel();
	menuPanel->UpdateWorld();
	panels.push_back(menuPanel);
}
