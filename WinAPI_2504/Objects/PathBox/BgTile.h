#pragma once

class BgTile : public Tile 
{
public:
	BgTile(BgType bgType = BgType::Grass);
	~BgTile();

	void Render();
	void UpdateWorld();

	Quad* GetImage() { return image; }

	BgType GetType() { return bgType; }
	void SetType(BgType bgType) { this->bgType = bgType; }

	void SetTile(BgType bgType);

private:
	BgType bgType;
	Quad* image;
};