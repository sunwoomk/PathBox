#pragma once

class SampleGameTile : public RectCollider
{
public:
	SampleGameTile(wstring textureFile, Vector2 size);
	~SampleGameTile();
	
	void Render();

	void UpdateWorld();
	

private:
	Quad* image;
};