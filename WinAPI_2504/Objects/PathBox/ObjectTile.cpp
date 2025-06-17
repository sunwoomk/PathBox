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
    // ���� image �����ϰ� ����
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
    // image�� ���� ��������ٸ� �θ�/��ġ ����
    if (image != nullptr) {
        image->SetParent(this);
        image->SetLocalPosition(Vector2(0, 50));
    }
}
