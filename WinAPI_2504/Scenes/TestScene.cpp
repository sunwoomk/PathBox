#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
    //TileManager::Get();
	//tileMaps = new TileMaps("Resources/StageData/TestMap.map");
	//tileMaps = new TileMaps("Resources/StageData/Test.map");
	//tileMaps = new TileMaps("Resources/StageData/Stage1.map");
	//tileMaps = new TileMaps("Resources/StageData/Stage2.map");
	//tileMaps = new TileMaps("Resources/StageData/Stage3.map");
	//tileMaps = new TileMaps("Resources/StageData/Stage4.map");
	//tileMaps = new TileMaps("Resources/StageData/Stage5.map");
	tileMaps = new TileMaps("Resources/StageData/Stage6.map");
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

