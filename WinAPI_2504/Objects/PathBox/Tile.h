#pragma once

class Tile : public Transform
{
public:
	Tile();
	~Tile();
	void Render();
	void UpdateWorld();

	POINT GetTilePos() { return tilePos; }
	void SetTilePos(int x, int y) { tilePos = { x, y }; }

private:
	POINT tilePos;
};
