#pragma once

class TileManager : public Singleton<TileManager>
{
private:
	static const int TILE_SIZE_X = 64;
	static const int TILE_SIZE_Y = 44;
	static const int MAP_COLS = 10;
	static const int MAP_ROWS = 10;
public:
	TileManager();
	~TileManager();
	void Update();
	void Render();

	void SetBgTilePos(int y, int x);
	void SetObjectTilePos(int y, int x);
	void MoveObjectTile(int fromY, int fromX, int toY, int toX);

	void CreateBgTiles(BgType bgType, int y, int x);
	void CreateObjectTiles(ObjectType objectType, int y, int x);

	void SetBgTileMap();
	void SetObjectTileMap();

	void PlayerMove();
	void SwapAndMove(int fromY, int fromX, int toY, int toX);
	void Teleport(int curY, int curX, int destY, int destX);

private:
	vector<vector<BgTile*>> bgTiles;
	vector<vector<ObjectTile*>> objectTiles;
	Quad* image;
	POINT playerPos;
	bool isTeleporting = false;
	int teleportDestX, teleportDestY;
	int teleportStartX, teleportStartY;
};
