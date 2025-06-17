#include "Framework.h"

ObjectTile::ObjectTile(ObjectTileType objectTileType)
{
	SetTile(objectTileType);
	this->objectTileType = objectTileType;
	if (objectTileType != ObjectTileType::None) 
	{
		image->SetParent(this);
		image->SetLocalPosition(Vector2(0, 50));
	}
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
    if (image != nullptr)
        image->Render();
}

void ObjectTile::UpdateWorld()
{
	Tile::UpdateWorld();
    if (image != nullptr)
        image->UpdateWorld();
}

void ObjectTile::SetTile(ObjectTileType objectTileType)
{
    // 기존 image 안전하게 해제
    if (image != nullptr) {
        delete image;
        image = nullptr;
    }

    this->objectTileType = objectTileType;

    switch (objectTileType)
    {
    case ObjectTileType::None:
        image = nullptr;
        break;
    case ObjectTileType::Box:
        image = new Quad(L"Resources/Textures/Tiles/tileBuilding_sand.png");
        break;
    case ObjectTileType::Wall:
        image = new Quad(L"Resources/Textures/Tiles/tileStone.png");
        break;
    case ObjectTileType::Portal:
        // image = new Quad(...);
        break;
    }
    // image가 새로 만들어졌다면 부모/위치 세팅
    if (image != nullptr) {
        image->SetParent(this);
        image->SetLocalPosition(Vector2(0, 50));
    }
}
