#include "Framework.h"

BgTile::BgTile(BgType bgType)
{
	SetTile(bgType);
	image->SetParent(this);
	image->SetLocalPosition(Vector2(0, 0));
}

BgTile::~BgTile()
{
	if (image != nullptr)
	{
		delete image;
		image = nullptr;
	}
}

void BgTile::Render()
{
	image->Render();
}

void BgTile::UpdateWorld()
{
	Tile::UpdateWorld();
	image->UpdateWorld();
}

void BgTile::SetTile(BgType bgType)
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
