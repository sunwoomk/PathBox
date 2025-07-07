#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene(string file)
{
	SetTileMaps(file);
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
	float blue[4] = { 0.0f, 0.5f, 1.0f, 1.0f };
	Device::Get()->Clear(blue);
	tileMaps->Render();
}

void TestScene::PostRender()
{
	UIManager::Get()->Render();
}

void TestScene::SetTileMaps(string file)
{
	tileMaps = new TileMaps(file);
	UIManager::Get()->SetTileMaps(tileMaps);
	UIManager::Get()->SetMenuPanel();
}
