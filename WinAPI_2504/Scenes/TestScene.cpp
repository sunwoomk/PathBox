#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
    //TileManager::Get();
	tileMaps = new TileMaps("Resources/StageData/Test.map");
}

TestScene::~TestScene()
{
	delete tileMaps;
}

void TestScene::Update()
{
	//TileManager::Get()->Update();
	tileMaps->Update();
}

void TestScene::UpdateWorld()
{
	tileMaps->UpdateWorld();
}

void TestScene::Render()
{
	//TileManager::Get()->Render();
	tileMaps->Render();
}

