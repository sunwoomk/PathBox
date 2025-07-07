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
	float ivory[4] = { 1.0f, 0.97f, 0.90f, 1.0f };
	Device::Get()->Clear(ivory);
	UIManager::Get()->Render();
}
