#pragma once

class TileMaps : public Transform
{
private:
	static const int TILE_SIZE_X = 64;
	static const int TILE_SIZE_Y = 44;
	static const int START_POS_X = 200;
	static const int START_POS_Y = SCREEN_HEIGHT - 200;
public:
	TileMaps(string file);
	~TileMaps();

	BgTile* FindBgTile(int x, int y);
	ObjectTile* FindObjectTile(int x, int y);

	void Update();
	void Render();
	void UpdateWorld();

	void PlayerMove();

private:
	void LoadFiles(string file);
	void CreateBgTiles();
	void CreateObjectTiles(BinaryReader* reader);

private:
	vector<int> tests;
	vector<BgTile*> bgTiles;
	vector<ObjectTile*> objectTiles;
	POINT playerPos;

	bool isTeleporting = false;
	int teleportDestX, teleportDestY;
	int teleportStartX, teleportStartY;
	int mapCols = 0;
	int mapRows = 0;
};