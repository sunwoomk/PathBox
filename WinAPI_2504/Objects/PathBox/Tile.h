#pragma once

class Tile : public Transform
{
public:
	Tile();
	~Tile();
	void Render();
	void UpdateWorld();
};
