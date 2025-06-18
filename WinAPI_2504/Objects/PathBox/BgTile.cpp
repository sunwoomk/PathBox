#include "Framework.h"

BgTile::BgTile(BgType bgType)
{
	SetTile(bgType);
	image->SetParent(this);
	image->SetLocalPosition(Vector2(0, 50));
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
