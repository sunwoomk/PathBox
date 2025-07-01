#pragma once

class TestScene : public Scene
{
private:
	static const int TILE_SIZE_X = 64;
	static const int TILE_SIZE_Y = 44;
	static const int MAP_COLS = 10;
	static const int MAP_ROWS = 10;
public:
	TestScene(string file);
	~TestScene();

	void Update() override;
	void UpdateWorld();
	void Render() override;
	void PostRender() override;

	void SetKey(const string& k) { key = k; }
	string GetKey() const { return key; }

private:
	string key;
	TileMaps* tileMaps;
};

