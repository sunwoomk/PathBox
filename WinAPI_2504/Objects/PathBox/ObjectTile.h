#pragma once

class ObjectTile : public Tile
{
public:
	enum class ObjectTileType
	{
		None = 0,
		Box = 1,
		Wall = 2,
		Portal = 3,
		End = 4
	};
public:
	ObjectTile(ObjectTileType objectTileType);
	~ObjectTile();

	void Render();
	void UpdateWorld();

	void SetTile(ObjectTileType objectTileType);

private:
	Quad* image;
	ObjectTileType objectTileType;
};
