#include "Framework.h"

TileManager::TileManager()
{
	SetBgTileMap();
	SetObjectTileMap();
	//player = new Player();
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

	//delete player;
}

void TileManager::Update()
{
	//player->Update();
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
	//player->Render();
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

	SetObjectTiles(y, x);
}

void TileManager::SetObjectTiles(int y, int x)
{
	objectTiles[y][x]->SetTilePos(x, y);
	objectTiles[y][x]->SetLocalPosition(200 + x * TILE_SIZE_X, 185 + (MAP_ROWS - 1 - y) * TILE_SIZE_Y);
	//objectTiles[y][x]->SetLocalPosition(200 + x * TILE_SIZE_X, 185 + y * TILE_SIZE_Y);
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
			beyondTile->SetTile(ObjectType::Box);
			targetTile->SetTile(ObjectType::None);
			SetObjectTiles(boxNewY, boxNewX);
			SetObjectTiles(newY, newX);

			SwapAndMove(curY, curX, newY, newX);
		}
	}
	//int x = playerPos.x;
	//int y = playerPos.y;
	//swap(objectTiles[y][x], objectTiles[y + dy][x + dx]);
	//objectTiles[y][x]->SetTile(ObjectType::None);
	//objectTiles[y + dy][x + dx]->SetTile(ObjectType::Player);
	//SetObjectTiles(y, x);
	//SetObjectTiles(y + dy, x + dx);
	//playerPos.x = x + dx;
	//playerPos.y = y + dy;
}

void TileManager::SwapAndMove(int fromY, int fromX, int toY, int toX)
{
	swap(objectTiles[fromY][fromX], objectTiles[toY][toX]);
	objectTiles[fromY][fromX]->SetTile(ObjectType::None);
	objectTiles[toY][toX]->SetTile(ObjectType::Player);
	SetObjectTiles(fromY, fromX);
	SetObjectTiles(toY, toX);
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
			// 예시: 맵의 테두리는 Stone, 내부는 Grass로 구성
			if (y == 0 || y == MAP_ROWS - 1 || x == 0 || x == MAP_COLS - 1) 
				bgTiles[y][x] = new BgTile(BgType::Stone);
			else
				bgTiles[y][x] = new BgTile(BgType::Grass);
			bgTiles[y][x]->SetTilePos(x, y);
			bgTiles[y][x]->SetLocalPosition(200 + x * TILE_SIZE_X, 200 + (MAP_ROWS - 1 - y) * TILE_SIZE_Y);
			//bgTiles[y][x]->SetLocalPosition(200 + x * TILE_SIZE_X, 185 + y * TILE_SIZE_Y);
			bgTiles[y][x]->SetLocalScale(0.5f, 0.5f);
			bgTiles[y][x]->UpdateWorld();
		}
	}
}
