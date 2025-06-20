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
	if (isTeleporting && !objectTiles[teleportStartY][teleportStartX]->IsMoving())
	{
		Teleport(teleportStartY, teleportStartX, teleportDestY, teleportDestX);
		isTeleporting = false;
	}
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

void TileManager::CreateBgTiles(BgType bgType, int y, int x)
{
	bgTiles[y][x] = new BgTile(bgType);

	SetBgTilePos(y, x);
}

void TileManager::CreateObjectTiles(ObjectType objectType, int y, int x)
{
	objectTiles[y][x] = new ObjectTile(objectType);

	SetObjectTilePos(y, x);
}

void TileManager::SetBgTilePos(int y, int x)
{
	bgTiles[y][x]->SetTilePos(x, y);
	bgTiles[y][x]->SetLocalPosition(200 + x * TILE_SIZE_X, 200 + (MAP_ROWS - 1 - y) * TILE_SIZE_Y);
	bgTiles[y][x]->SetLocalScale(0.5f, 0.5f);
	bgTiles[y][x]->UpdateWorld();
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

void TileManager::PlayerMove()
{
	if (objectTiles[playerPos.y][playerPos.x]->IsMoving())
		return;

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

	else if (targetTile->GetType() == ObjectType::IcyRoad) 
	{
		int slideX = newX;
		int slideY = newY;
		while (true)
		{
			int nextX = slideX + dx;
			int nextY = slideY + dy;

			if (nextX < 0 || nextX >= MAP_COLS || nextY < 0 || nextY >= MAP_ROWS)
				break;

			ObjectTile* nextTile = objectTiles[nextY][nextX];

			if (nextTile->GetType() == ObjectType::IcyRoad)
			{
				slideX = nextX;
				slideY = nextY;
				continue;
			}
			else if (nextTile->GetType() == ObjectType::None)
			{
				slideX = nextX;
				slideY = nextY;
			}
			break;
		}

		if (slideX != curX || slideY != curY)
			SwapAndMove(curY, curX, slideY, slideX);
	}

	else if (targetTile->GetType() == ObjectType::Portal) 
	{
		isTeleporting = true;
		teleportStartX = curX;
		teleportStartY = curY;
		teleportDestX = 7;
		teleportDestY = 1;
		objectTiles[curY][curX]->StartMove(newX, newY);
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

void TileManager::Teleport(int curY, int curX, int destY, int destX)
{
	objectTiles[curY][curX]->SetTilePos(destX, destY);
	objectTiles[curY][curX]->SetLocalPosition(200 + destX * TILE_SIZE_X, 185 + (MAP_ROWS - 1 - destY) * TILE_SIZE_Y);
	objectTiles[curY][curX]->UpdateWorld();
	swap(objectTiles[curY][curX], objectTiles[destY][destX]);
	playerPos = { destX, destY };
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
				CreateBgTiles(BgType::Stone, y, x);
			else if ((x == 3 || x == 4 || x == 5) && (y == 4 || y == 5))
			{
				CreateBgTiles(BgType::IcyRoad, y, x);
			}
			else
				CreateBgTiles(BgType::Grass, y, x);
		}
	}
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
			else if (x == 7 && y == 5)
			{
				CreateObjectTiles(ObjectType::Box, y, x);
			}
			else if (x == 7 && y == 6)
			{
				CreateObjectTiles(ObjectType::Box, y, x);
			}
			else if ((x == 3 || x == 4 || x == 5) && (y == 3 || y == 4))
			{
				CreateObjectTiles(ObjectType::IcyRoad, y, x);
			}
			else if (x == 2 && y == 7)
			{
				CreateObjectTiles(ObjectType::Portal, y, x);
			}
			else
				CreateObjectTiles(ObjectType::None, y, x);
		}
	}
}
