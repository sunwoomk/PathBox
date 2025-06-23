#pragma once

class EditObjectTile : public Tile 
{
public:
	EditObjectTile(ObjectType objectType = ObjectType::None);
	~EditObjectTile();

	void Render();
	void UpdateWorld();

	void SetTile(ObjectType objectType);

	RectCollider* GetCollider() { return rectCollider; }
	Quad* GetImage() { return image; }
	ObjectType GetType() { return objectType; }
	void SetType(ObjectType objectType) { this->objectType = objectType; }

	static bool IsCompare(EditObjectTile* a, EditObjectTile* b)
	{
		return a->GetLocalPosition().y > b->GetLocalPosition().y;
	}

private:
	Quad* image = nullptr;
	RectCollider* rectCollider = nullptr;
	ObjectType objectType;
};
