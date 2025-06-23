#include "Framework.h"

EditBgTile::EditBgTile(BgType bgType)
{
	SetTile(bgType);
	image->SetParent(this);
	image->SetLocalPosition(Vector2(0, 50));

	rectCollider = new RectCollider(Vector2(128, 100));
	rectCollider->SetLocalPosition(0, 50);
	rectCollider->SetParent(this);
	rectCollider->UpdateWorld();
}

EditBgTile::~EditBgTile()
{
	if (image != nullptr)
	{
		delete image;
		image = nullptr;
	}

	delete rectCollider;
}

void EditBgTile::Render()
{
	image->Render();
	rectCollider->Render();
}

void EditBgTile::UpdateWorld()
{
	Tile::UpdateWorld();
	rectCollider->UpdateWorld();
	image->UpdateWorld();
}

void EditBgTile::SetTile(BgType bgType)
{
	switch (bgType)
	{
	case BgType::Grass:
		image = new Quad(L"Resources/Textures/Tiles/tileGrass.png");
		break;
	case BgType::Water:
		image = new Quad(L"Resources/Textures/Tiles/tileWater_1.png");
		break;
	case BgType::Sand:
		image = new Quad(L"Resources/Textures/Tiles/tileSand.png");
		break;
	case BgType::Stone:
		image = new Quad(L"Resources/Textures/Tiles/tileStone.png");
		break;
	case BgType::Wood:
		image = new Quad(L"Resources/Textures/Tiles/tileWood.png");
		break;
	case BgType::IcyRoad:
		image = new Quad(L"Resources/Textures/Tiles/tileSnow.png");
		break;
	}
}
