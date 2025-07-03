#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene(string file)
{
	tileMaps = new TileMaps(file);
	UIManager::Get()->SetTileMaps(tileMaps);
	UIManager::Get()->SetMenuPanel();
}

TestScene::~TestScene()
{
	delete tileMaps;
}

void TestScene::Update()
{
	tileMaps->Update();
	UIManager::Get()->Update();
}

void TestScene::UpdateWorld()
{
	tileMaps->UpdateWorld();
}

void TestScene::Render()
{
	tileMaps->Render();
}

void TestScene::PostRender()
{
	UIManager::Get()->Render();
}

