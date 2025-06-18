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

private:

};

