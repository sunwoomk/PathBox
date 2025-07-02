#pragma once

class TileMaps : public Transform
{
private:
	struct ObjectTileState 
	{
		int id;
		POINT tilePos;
	};
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
	ObjectTile* FindObjectTile(ObjectType objectType);

	void Update();
	void Render();
	void UpdateWorld();

	void PlayerMove();
	void Teleport(ObjectTile* player);

	void Restart();

private:
	void LoadFiles(string file);
	void CreateBgTiles();
	void CreateObjectTiles(BinaryReader* reader);
	void SaveObjectTilePos(ObjectTileState objectTileState) { objectTileStates.push_back(objectTileState); }


private:
	vector<int> tests;
	vector<BgTile*> bgTiles;
	vector<ObjectTile*> objectTiles;
	vector<ObjectTileState> objectTileStates;
	
	POINT playerPos;
	bool isTeleporting = false;
	int tpStartPosX, tpStartPosY;
	int tpEndPosX, tpEndPosY;
	Vector2 destPos;
	int mapCols = 0;
	int mapRows = 0;
};