#include "Framework.h"

ObjectTile::ObjectTile(ObjectTileType objectTileType)
{
	SetTile(objectTileType);
}

ObjectTile::~ObjectTile()
{
	if (image != nullptr)
	{
		delete image;
		image = nullptr;
	}
}

void ObjectTile::Render()
{
	image->Render();
}

void ObjectTile::UpdateWorld()
{
	image->UpdateWorld();
}

void ObjectTile::SetTile(ObjectTileType objectTileType)
{
	switch (objectTileType)
	{
	case ObjectTileType::Box:
		image = new Quad(L"Resources/Textures/Tiles/tileBuilding_sand.png");
		break;
	case ObjectTileType::Wall:
		image = new Quad(L"Resources/Textures/Tiles/tileStone.png");
		break;
	case ObjectTileType::Portal:
		//image = new Quad(L"Resources/Textures/Tiles/tilePortal.png");
		break;
	}
}
