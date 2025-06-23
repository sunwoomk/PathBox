#include "Framework.h"

SampleEditTile::SampleEditTile() : RectCollider(Vector2(128, 90))
{
	image = new Quad(L"Resources/Textures/Tiles/tileDirt.png");
	image->SetParent(this);
	image->SetLocalPosition(Vector2(0, 50));
}

SampleEditTile::~SampleEditTile()
{
}

void SampleEditTile::UpdateWorld()
{
	RectCollider::UpdateWorld();
	image->UpdateWorld();	
}

void SampleEditTile::Render()
{
	image->Render();
	RectCollider::Render();
}
