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
	SetType(bgType);
	switch (bgType)
	{
	case BgType::Grass:
		image = new Quad(L"Resources/Tiles/BgTile_Grass.png");
		break;
	case BgType::Water:
		image = new Quad(L"Resources/Tiles/BgTile_Water.png");
		break;
	case BgType::Sand:
		image = new Quad(L"Resources/Tiles/BgTile_Sand.png");
		break;
	case BgType::Stone:
		image = new Quad(L"Resources/Tiles/BgTile_Stone.png");
		break;
	case BgType::Wood:
		image = new Quad(L"Resources/Tiles/BgTile_Wood.png");
		break;
	case BgType::IcyRoad:
		image = new Quad(L"Resources/Tiles/BgTile_IcyRoad.png");
		break;
	}
}
