#pragma once

class ObjectTile : public Tile
{
public:
	ObjectTile(ObjectType objectType = ObjectType::None);
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

private:
	Quad* image;
	ObjectType objectType;
	Vector2 currentPos;
	Vector2 targetPos;
	bool isMoving = false;
	float moveSpeed = 300.0f;
};
