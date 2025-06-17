#include "Framework.h"

TileManager::TileManager()
{
	SetBgTileMap();
	SetObjectTileMap();
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

	for (auto& row : objectTiles)
	{
		for (auto tile : row)
		{
			if (tile != nullptr)
				delete tile;
		}
	}
	objectTiles.clear();

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

	if (Input::Get()->IsKeyDown(VK_F1))
	{
		swap(objectTiles[4][4], objectTiles[4][5]);
		objectTiles[4][4]->SetTile(ObjectTile::ObjectTileType::None);
		objectTiles[4][5]->SetTile(ObjectTile::ObjectTileType::Box);
		SetObjectTiles(4, 4);
		SetObjectTiles(4, 5);
	}

	for (const auto& row : objectTiles)
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

void TileManager::CreateBgTiles()
{
}

void TileManager::CreateObjectTiles(ObjectType objectType, int y, int x)
{
	switch (objectType)
	{
	case ObjectType::None:
		objectTiles[y][x] = new ObjectTile(ObjectTile::ObjectTileType::None);
		break;
	case ObjectType::Box:
		objectTiles[y][x] = new ObjectTile(ObjectTile::ObjectTileType::Box);
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

	SetObjectTiles(y, x);
}

void TileManager::SetObjectTiles(int y, int x)
{
	objectTiles[y][x]->SetTilePos(x, y);
	objectTiles[y][x]->SetLocalPosition(200 + x * TILE_SIZE_X, 185 + (MAP_ROWS - 1 - y) * TILE_SIZE_Y);
	objectTiles[y][x]->SetLocalScale(0.5f, 0.5f);
	objectTiles[y][x]->UpdateWorld();
}

void TileManager::SetObjectTileMap()
{
	objectTiles.resize(MAP_ROWS);
	for (int y = 0; y < MAP_ROWS; ++y)
	{
		objectTiles[y].resize(MAP_COLS);
		for (int x = 0; x < MAP_COLS; ++x)
		{
			if (x == 4 && y == 4)
			{
				CreateObjectTiles(ObjectType::Box, y, x);
			}
			else
				CreateObjectTiles(ObjectType::None, y, x);
		}
	}
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
