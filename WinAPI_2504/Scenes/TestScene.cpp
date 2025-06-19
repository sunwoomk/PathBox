#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
    TileManager::Get();
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	TileManager::Get()->Update();
}

void TestScene::UpdateWorld()
{
}

void TestScene::Render()
{
	TileManager::Get()->Render();
}

