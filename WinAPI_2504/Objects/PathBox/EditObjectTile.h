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

private:
	Quad* image = nullptr;
	RectCollider* rectCollider = nullptr;
};
