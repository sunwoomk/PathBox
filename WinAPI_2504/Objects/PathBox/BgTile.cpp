#include "Framework.h"

BgTile::BgTile(BgTileType bgTileType)
{
	SetTile(bgTileType);
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

void BgTile::SetTile(BgTileType bgTileType)
{
	switch (bgTileType)
	{
	case BgTileType::Grass:
		image = new Quad(L"Resources/Textures/Tiles/tileGrass.png");
		break;
	case BgTileType::Water:
		image = new Quad(L"Resources/Textures/Tiles/tileWater_1.png");
		break;
	case BgTileType::Sand:
		image = new Quad(L"Resources/Textures/Tiles/tileSand.png");
		break;
	case BgTileType::Stone:
		image = new Quad(L"Resources/Textures/Tiles/tileStone.png");
		break;
	case BgTileType::Wood:
		image = new Quad(L"Resources/Textures/Tiles/tileWood.png");
		break;
	case BgTileType::IcyRoad:
		image = new Quad(L"Resources/Textures/Tiles/tileSnow.png");
		break;
	}
}
