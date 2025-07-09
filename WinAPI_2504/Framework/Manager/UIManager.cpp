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
		if (SCENE->IsCurrentStageScene()) 
		{
			menuPanel->SetActive(!menuPanel->IsActive());
		}
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

bool UIManager::GetPanelActive(string panel)
{
	if (panel == "StageClearPanel")
	{
		return stageClearPanel->IsActive();
	}
	else if (panel == "SelectStagePanel")
	{
		return selectStagePanel->IsActive();
	}
	else if (panel == "StartScenePanel")
	{
		return startScenePanel->IsActive();
	}
	else if (panel == "MenuPanel")
	{
		return menuPanel->IsActive();
	}
	return false;
}

void UIManager::SetPanelActive(string panel, bool active)
{
	if (panel == "StageClearPanel")
	{
		stageClearPanel->SetActive(active);
	}
	else if (panel == "SelectStagePanel")
	{
		selectStagePanel->SetActive(active);
	}
	else if (panel == "StartScenePanel")
	{
		startScenePanel->SetActive(active);
	}
	else if (panel == "MenuPanel")
	{
		menuPanel->SetActive(active);
	}
}

void UIManager::SetPanels()
{
	panels.clear();

	stageClearPanel = new StageClearPanel();
	panels.push_back(stageClearPanel);

	selectStagePanel = new SelectStagePanel();
	panels.push_back(selectStagePanel);

	startScenePanel = new StartScenePanel();
	panels.push_back(startScenePanel);
}

void UIManager::SetMenuPanel()
{
	if (menuPanel == nullptr) 
	{
		menuPanel = new MenuPanel(tileMaps);
		panels.push_back(menuPanel);
	}
	else 
	{
		menuPanel->SetTileMaps(tileMaps);
	}
}
