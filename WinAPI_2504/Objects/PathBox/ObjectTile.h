#pragma once

class ObjectTile : public Tile
{
public:
	ObjectTile(ObjectType objectType);
	~ObjectTile();

	void Render();
	void UpdateWorld();

	void SetTile(ObjectType objectType);

	ObjectType GetType() { return objectType; }

private:
	Quad* image;
	ObjectType objectType;
};
