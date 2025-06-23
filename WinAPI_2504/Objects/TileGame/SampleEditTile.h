#pragma once

class SampleEditTile : public RectCollider
{
public:
	SampleEditTile();
	~SampleEditTile();

	void UpdateWorld();
	void Render();
	
	Quad* GetImage() { return image; }

	static bool IsCompare(SampleEditTile* a, SampleEditTile* b)
	{
		return a->GetLocalPosition().y > b->GetLocalPosition().y;
	}
private:
	Quad* image;
};