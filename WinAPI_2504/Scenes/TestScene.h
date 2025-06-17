#pragma once

class TestScene : public Scene
{
private:
	static const int TILE_SIZE_X = 64;
	static const int TILE_SIZE_Y = 44;
	static const int MAP_COLS = 10;
	static const int MAP_ROWS = 10;
public:
	TestScene();
	~TestScene();

	void Update() override;
	void UpdateWorld();
	void Render() override;

	void SetTileMap();
	void SetTilePos(int y, int x);

	Vector2 GetTilePos(int y, int x) const
	{
		return Vector2(200 + x * TILE_SIZE_X, 200 + (MAP_ROWS - 1 - y) * TILE_SIZE_Y);
	}

	void SetPlayerPos(int y, int x);

private:
	vector<vector<BgTile*>> bgTiles;
	Player* player;
};

