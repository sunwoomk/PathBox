#include "Framework.h"

TileManager::TileManager()
{
	SetBgTileMap();
	player = new Player();
}

TileManager::~TileManager()
{
	for (auto& row : bgTiles)
	{
		for (auto tile : row)
		{
			if (tile != nullptr)
				delete tile;
		}
	}
	bgTiles.clear();

	delete player;
}

void TileManager::Update()
{
	player->Update();
}

void TileManager::Render()
{
	for (const auto& row : bgTiles)
	{
		for (const auto& tile : row)
		{
			if (tile != nullptr)
				tile->Render();
		}
	}
	player->Render();
}

void TileManager::SetBgTiles(BgType bgType)
{
	switch (bgType)
	{
	case BgType::None:
		// No image for None type
		break;
	case BgType::Grass:
		image = new Quad(L"Resources/Textures/Tiles/tileGrass.png");
		break;
	case BgType::Water:
		image = new Quad(L"Resources/Textures/Tiles/tileWater_1.png");
		break;
	case BgType::Sand:
		image = new Quad(L"Resources/Textures/Tiles/tileSand.png");
		break;
	case BgType::Stone:
		image = new Quad(L"Resources/Textures/Tiles/tileStone.png");
		break;
	case BgType::Wood:
		image = new Quad(L"Resources/Textures/Tiles/tileWood.png");
		break;
	case BgType::IcyRoad:
		image = new Quad(L"Resources/Textures/Tiles/tileSnow.png");
		break;
	}
}

void TileManager::SetObjectTiles(ObjectType objectType)
{
	switch (objectType)
	{
	case ObjectType::None:
		// No image for None type
		break;
	case ObjectType::Box:
		//image = new Quad(L"Resources/Textures/Tiles/tileBuilding_sand.png");
		//새로 박스 객체 생성
		break;
	case ObjectType::Wall:
		image = new Quad(L"Resources/Textures/Tiles/tileCastle.png");
		break;
	case ObjectType::Portal:
		// Set tile to Portal
		break;
	case ObjectType::Water:
		// Set tile to Water
		break;
	case ObjectType::IcyRoad:
		// Set tile to IcyRoad
		break;
	}
}

void TileManager::SetObjectTileMap()
{
}

void TileManager::SetBgTileMap()
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
			bgTiles[y][x]->SetTilePos(x, y);
			bgTiles[y][x]->SetLocalPosition(200 + x * TILE_SIZE_X, 200 + (MAP_ROWS - 1 - y) * TILE_SIZE_Y);
			bgTiles[y][x]->SetLocalScale(0.5f, 0.5f);
			bgTiles[y][x]->UpdateWorld();
		}
	}
}
