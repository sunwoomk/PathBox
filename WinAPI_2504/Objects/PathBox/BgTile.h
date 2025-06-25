#pragma once

class BgTile : public Tile 
{
public:
	BgTile(BgType bgType = BgType::Grass);
	~BgTile();

	void Render();
	void UpdateWorld();

	Quad* GetImage() { return image; }

	void SetTile(BgType bgType);

private:
	Quad* image;
};