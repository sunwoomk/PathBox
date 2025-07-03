#include "Framework.h"

SelectStageScene::SelectStageScene()
{
	//selectStagePanel = new SelectStagePanel();
	//selectStagePanel->SetLocalPosition(Vector2(CENTER));
	//selectStagePanel->UpdateWorld();
	UIManager::Get()->SetPanels();
	//selectStagePanel = UIManager::Get()->GetSelectStagePanel();
}

SelectStageScene::~SelectStageScene()
{
	//delete selectStagePanel;
}

void SelectStageScene::Update()
{
	//selectStagePanel->Update();
	UIManager::Get()->Update();
}

void SelectStageScene::Render()
{
	//selectStagePanel->Render();
	UIManager::Get()->Render();
}
