#include "Framework.h"

TileManager::TileManager()
{
	SetBgTileMap();
	SetObjectTileMap();
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
}

void TileManager::Update()
{
	for (auto& row : objectTiles)
		for (auto tile : row)
			if (tile) tile->Update();
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

	PlayerMove();

	for (const auto& row : objectTiles)
	{
		for (const auto& tile : row)
		{
			if (tile != nullptr)
				tile->Render();
		}
	}
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
	objectTiles[y][x] = new ObjectTile(objectType);

	SetObjectTilePos(y, x);
}

void TileManager::SetObjectTilePos(int y, int x)
{
	objectTiles[y][x]->SetTilePos(x, y);
	objectTiles[y][x]->SetLocalPosition(200 + x * TILE_SIZE_X, 185 + (MAP_ROWS - 1 - y) * TILE_SIZE_Y);
	objectTiles[y][x]->SetLocalScale(0.5f, 0.5f);
	objectTiles[y][x]->UpdateWorld();
}

void TileManager::MoveObjectTile(int fromY, int fromX, int toY, int toX)
{
	objectTiles[fromY][fromX]->SetTilePos(toY, toX);
	objectTiles[fromY][fromX]->StartMove(toX, toY);
}

void TileManager::SetObjectTileMap()
{
	objectTiles.resize(MAP_ROWS);
	for (int y = 0; y < MAP_ROWS; ++y)
	{
		objectTiles[y].resize(MAP_COLS);
		for (int x = 0; x < MAP_COLS; ++x)
		{
			if (x == 4 && y == 5)
			{
				CreateObjectTiles(ObjectType::Player, y, x);
				playerPos = { x, y };
			}
			else if (x == 5 && y == 4)
			{
				CreateObjectTiles(ObjectType::Box, y, x);
			}
			else if (x == 5 && y == 5)
			{
				CreateObjectTiles(ObjectType::Box, y, x);
			}
			else
				CreateObjectTiles(ObjectType::None, y, x);
		}
	}
}

void TileManager::PlayerMove()
{
	int dx = 0;
	int dy = 0;
	if (Input::Get()->IsKeyDown('W')) dy = -1;
	else if (Input::Get()->IsKeyDown('A')) dx = -1;
	else if (Input::Get()->IsKeyDown('S')) dy = 1;
	else if (Input::Get()->IsKeyDown('D')) dx = 1;

	int curX = playerPos.x;
	int curY = playerPos.y;
	int newX = curX + dx;
	int newY = curY + dy;

	if (newX < 0 || newX >= MAP_COLS || newY < 0 || newY >= MAP_ROWS) 
		return;

	ObjectTile* targetTile = objectTiles[newY][newX];

	if (targetTile->GetType() == ObjectType::None)
		SwapAndMove(curY, curX, newY, newX);

	else if (targetTile->GetType() == ObjectType::Box) 
	{
		int boxNewX = newX + dx;
		int boxNewY = newY + dy;

		if (boxNewX < 0 || boxNewX >= MAP_COLS || boxNewY < 0 || boxNewY >= MAP_ROWS)
			return;

		ObjectTile* beyondTile = objectTiles[boxNewY][boxNewX];

		if (beyondTile->GetType() == ObjectType::None)
		{
			SwapAndMove(newY, newX, boxNewY, boxNewX);
			SwapAndMove(curY, curX, newY, newX);
		}
	}
}

void TileManager::SwapAndMove(int fromY, int fromX, int toY, int toX)
{
	MoveObjectTile(fromY, fromX, toY, toX);
	MoveObjectTile(toY, toX, fromY, fromX);
	swap(objectTiles[fromY][fromX], objectTiles[toY][toX]);
	if (objectTiles[toY][toX]->GetType() == ObjectType::Player)
		playerPos = { toX, toY };
}

void TileManager::SetBgTileMap()
{
	bgTiles.resize(MAP_ROWS);
	for (int y = 0; y < MAP_ROWS; ++y)
	{
		bgTiles[y].resize(MAP_COLS);
		for (int x = 0; x < MAP_COLS; ++x)
		{
			if (y == 0 || y == MAP_ROWS - 1 || x == 0 || x == MAP_COLS - 1) 
				bgTiles[y][x] = new BgTile(BgType::Stone);
			else
				bgTiles[y][x] = new BgTile(BgType::Grass);
			bgTiles[y][x]->SetTilePos(x, y);
			bgTiles[y][x]->SetLocalPosition(200 + x * TILE_SIZE_X, 200 + (MAP_ROWS - 1 - y) * TILE_SIZE_Y);
			bgTiles[y][x]->SetLocalScale(0.5f, 0.5f);
			bgTiles[y][x]->UpdateWorld();
		}
	}
}
