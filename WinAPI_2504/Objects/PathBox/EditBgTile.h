#pragma once

class EditBgTile : public Tile 
{
public:
	EditBgTile(BgType bgType = BgType::Grass);
	~EditBgTile();

	void Render();
	void UpdateWorld();

	void SetTile(BgType bgType);

	RectCollider* GetCollider() { return rectCollider; }
	Quad* GetImage() { return image; }

private:
	Quad* image = nullptr;
	RectCollider* rectCollider = nullptr;
};