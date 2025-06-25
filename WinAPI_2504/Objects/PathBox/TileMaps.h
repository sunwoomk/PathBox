#pragma once

class TileMaps : public Transform
{
private:
	static const int TILE_SIZE_X = 64;
	static const int TILE_SIZE_Y = 44;
public:
	TileMaps(string file);
	~TileMaps();

	BgTile* FindBgTile(int x, int y);
	ObjectTile* FindObjectTile(int x, int y);

	void Update();
	void Render();
	void UpdateWorld();

	void PlayerMove();
	void SwapAndMove(int fromY, int fromX, int toY, int toX);
	void Teleport(int curY, int curX, int destY, int destX);

private:
	void LoadFiles(string file);
	void CreateBgTiles();
	void CreateObjectTiles(BinaryReader* reader);

private:
	vector<BgTile*> bgTiles;
	vector<ObjectTile*> objectTiles;
	POINT playerPos;

	bool isTeleporting = false;
	int teleportDestX, teleportDestY;
	int teleportStartX, teleportStartY;
	int mapCols = 0;
	int mapRows = 0;
};