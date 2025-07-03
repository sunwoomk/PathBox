#include "Framework.h"

SelectStageScene::SelectStageScene()
{
	selectStagePanel = new SelectStagePanel();
	selectStagePanel->SetLocalPosition(Vector2(CENTER));
	selectStagePanel->UpdateWorld();
}

SelectStageScene::~SelectStageScene()
{
	delete selectStagePanel;
}

void SelectStageScene::Update()
{
	selectStagePanel->Update();
}

void SelectStageScene::Render()
{
	selectStagePanel->Render();
}
