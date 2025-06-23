#include "Framework.h"
#include "SampleTileGameScene.h"

SampleTileGameScene::SampleTileGameScene()
{
	tileMap = new TileMap("Resources/TextData/Stage1.map");
	tileMap->SetLocalPosition(0, SCREEN_HEIGHT);	
	tileMap->SetTag("TileMap");
	tileMap->Load();
	tileMap->UpdateWorld();

	tank = new Tank();
	tank->SetTileMap(tileMap);

	aStar = new AStar(tileMap);
}

SampleTileGameScene::~SampleTileGameScene()
{
	delete tileMap;
	delete tank;
	delete aStar;
}

void SampleTileGameScene::Update()
{
	//tileMap->UpdateWorld();
	if (Input::Get()->IsKeyDown(VK_LBUTTON))
	{
		int start = aStar->FindCloseNode(tank->GetLocalPosition());
		int end = aStar->FindCloseNode(mousePos);

		tank->SetPath(aStar->GetPath(start, end));
	}

	tank->Update();
}

void SampleTileGameScene::Render()
{
	tileMap->Render();
	tank->Render();
	aStar->Render();
}

void SampleTileGameScene::GUIRender()
{
	tileMap->Edit();
}
