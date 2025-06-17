#pragma once

class TileManager : public Singleton<TileManager>
{
private:
	enum class BgType
	{
		None = 0,
		Grass = 1,
		Water = 2,
		Sand = 3,
		Stone = 4,
		Wood = 5,
		IcyRoad = 6,
		End = 7
	};
	enum class ObjectType
	{
		None = 0,
		Box = 1,
		Wall = 2,
		Portal = 3,
		Water = 4,
		IcyRoad = 5,
		End = 6
	};
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

	void SetBgTiles(BgType bgType);
	void SetObjectTiles(int y, int x);

	void CreateBgTiles();
	void CreateObjectTiles(ObjectType objectType, int y, int x);

	void SetBgTileMap();
	void SetObjectTileMap();

private:
	vector<vector<BgTile*>> bgTiles;
	vector<vector<ObjectTile*>> objectTiles;
	Quad* image;
	Player* player;
};
