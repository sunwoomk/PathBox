#pragma once

class ObjectTile : public Tile
{
private:
	static const int TILE_SIZE_X = 64;
	static const int TILE_SIZE_Y = 44;
	static const int START_POS_X = 200;
	static const int START_POS_Y = SCREEN_HEIGHT - 200;
public:
	ObjectTile(ObjectType objectType);
	~ObjectTile();

	void Update();
	void Render();
	void UpdateWorld();

	Quad* GetImage() { return image; }

	void SetTile(ObjectType objectType);

	void StartMove(int toX, int toY);
	bool IsMoving() const { return isMoving; }

	ObjectType GetType() { return objectType; }
	void SetType(ObjectType objectType) { this->objectType = objectType; }

	static bool IsCompare(ObjectTile* a, ObjectTile* b)
	{
		return a->GetLocalPosition().y > b->GetLocalPosition().y;
	}

private:
	Quad* image;
	ObjectType objectType;
	Vector2 currentPos;
	Vector2 targetPos;
	bool isMoving = false;
	float moveSpeed = 300.0f;
};
