#include "Framework.h"
#include "TestScene.h"

TestScene::TestScene()
{
    TileManager::Get();
    SetTileMaps();

	int centerX = MAP_COLS * 0.5f;
	int centerY = MAP_ROWS * 0.5f;

    player = new Player();
    //player->SetLocalPosition(centerX + 200, centerY + 200);
    player->SetLocalPosition(GetTilePos(centerX, centerY) + Vector2(0, 10));
    player->SetLocalScale(0.5f, 0.5f);
    player->UpdateWorld();
}

TestScene::~TestScene()
{
}

void TestScene::Update()
{
	//if (Input::Get()->IsKeyDown('W'))
	//{
	//	SetPlayerPos(player->GetTileY() - 1, player->GetTileX());
	//}
}

void TestScene::UpdateWorld()
{
	for (const auto& row : bgTiles)
	{
		for (const auto& tile : row)
		{
			if (tile != nullptr)
				tile->UpdateWorld();
		}
	}
}

void TestScene::Render()
{
	TileManager::Get()->Render();
	player->Render();
}

void TestScene::SetTilePos(int y, int x)
{
    bgTiles[y][x]->SetLocalPosition(200 + x * TILE_SIZE_X, 200 + (MAP_ROWS - 1 - y) * TILE_SIZE_Y);
}

void TestScene::SetPlayerPos(int y, int x)
{
	player->SetLocalPosition(GetTilePos(y, x) + Vector2(0, 10));
	player->UpdateWorld();
}

void TestScene::SetTileMaps()
{
    bgTiles.resize(MAP_ROWS);
    for (int y = 0; y < MAP_ROWS; ++y)
    {
        bgTiles[y].resize(MAP_COLS);
        for (int x = 0; x < MAP_COLS; ++x)
        {
            // 예시: 맵의 테두리는 Stone, 내부는 Grass로 구성
            if (y == 0 || y == MAP_ROWS - 1 || x == 0 || x == MAP_COLS - 1)
                bgTiles[y][x] = new BgTile(BgTile::BgTileType::Stone);
            else
                bgTiles[y][x] = new BgTile(BgTile::BgTileType::Grass);
            SetTilePos(y, x);
            bgTiles[y][x]->SetLocalScale(0.5f, 0.5f);
            bgTiles[y][x]->UpdateWorld();
        }
    }
}
