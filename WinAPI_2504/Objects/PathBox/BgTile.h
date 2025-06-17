#pragma once

class BgTile : public Tile 
{
public:
	enum class BgTileType
	{
		Grass = 1,
		Water = 2,
		Sand = 3,
		Stone = 4,
		Wood = 5,
		IcyRoad = 6,
		End = 7
	};
public:
	BgTile(BgTileType bgTileType);
	~BgTile();

	void Render();
	void UpdateWorld();

	void SetTile(BgTileType bgTileType);

private:
	Quad* image;
};