#pragma once

class BgTile : public Tile 
{
public:
	BgTile(BgType bgType);
	~BgTile();

	void Render();
	void UpdateWorld();

	void SetTile(BgType bgType);

private:
	Quad* image;
};