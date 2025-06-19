#pragma once

class ObjectTile : public Tile
{
public:
	ObjectTile(ObjectType objectType);
	~ObjectTile();

	void Update();
	void Render();
	void UpdateWorld();

	void SetTile(ObjectType objectType);
	void SetObjectType(ObjectType objectType) { this->objectType = objectType; }

	void StartMove(int toX, int toY);
	bool IsMoving() const { return isMoving; }

	ObjectType GetType() { return objectType; }

private:
	Quad* image;
	ObjectType objectType;
	Vector2 currentPos;
	Vector2 targetPos;
	bool isMoving = false;
	float moveSpeed = 300.0f;
};
