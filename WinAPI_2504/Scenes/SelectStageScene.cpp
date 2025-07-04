#include "Framework.h"

SelectStageScene::SelectStageScene()
{
	UIManager::Get()->SetPanels();
}

SelectStageScene::~SelectStageScene()
{
}

void SelectStageScene::Update()
{
	UIManager::Get()->Update();
}

void SelectStageScene::Render()
{
	UIManager::Get()->Render();
}
