#include "Framework.h"
#include "StageScene.h"

StageScene::StageScene(string file)
{
	SetTileMaps(file);
}

StageScene::~StageScene()
{
	delete tileMaps;
}

void StageScene::Update()
{
	tileMaps->Update();
	UIManager::Get()->Update();
}

void StageScene::UpdateWorld()
{
	tileMaps->UpdateWorld();
}

void StageScene::Render()
{
	float blue[4] = { 0.0f, 0.5f, 1.0f, 1.0f };
	Device::Get()->Clear(blue);
	tileMaps->Render();
}

void StageScene::PostRender()
{
	UIManager::Get()->Render();
}

void StageScene::SetTileMaps(string file)
{
	tileMaps = new TileMaps(file);
	UIManager::Get()->SetTileMaps(tileMaps);
	UIManager::Get()->SetMenuPanel();
}
