#include "Framework.h"

SampleGameTile::SampleGameTile(wstring textureFile, Vector2 size)
	: RectCollider(size)	
{
	image = new Quad(textureFile);
	image->SetParent(this);	
	image->SetLocalPosition(Vector2(0, 50));
}

SampleGameTile::~SampleGameTile()
{
	delete image;
}

void SampleGameTile::Render()
{
	image->Render();
	RectCollider::Render();
}

void SampleGameTile::UpdateWorld()
{
	RectCollider::UpdateWorld();
	image->UpdateWorld();
}
