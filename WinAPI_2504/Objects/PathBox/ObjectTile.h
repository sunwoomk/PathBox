#pragma once

class ObjectTile : public Tile
{
private:
	enum class ObjectTileType
	{
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
};
