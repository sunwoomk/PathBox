#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene(string file, wstring backgroundFile)
{
	tileMaps = new TileMaps(file);
	UIManager::Get()->SetTileMaps(tileMaps);
	UIManager::Get()->SetMenuPanel();
	background = new Quad(backgroundFile);
	background->SetLocalPosition(Vector2(CENTER));
	background->SetColor(1.0f, 1.0f, 1.0f, 0.85f);
	background->UpdateWorld();
}

TestScene::~TestScene()
{
	delete tileMaps;
	delete background;
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
	background->Render();
	tileMaps->Render();
}

void TestScene::PostRender()
{
	UIManager::Get()->Render();
}

