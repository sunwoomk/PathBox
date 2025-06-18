#include "Framework.h"

ObjectTile::ObjectTile(ObjectType objectType)
{
	SetTile(objectType);
	this->objectType = objectType;
	if (objectType != ObjectType::None && objectType != ObjectType::Water && objectType != ObjectType::IcyRoad)
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

void ObjectTile::SetTile(ObjectType objectType)
{
    // ���� image �����ϰ� ����
    if (image != nullptr) 
    {
        delete image;
        image = nullptr;
    }

    this->objectType = objectType;

    switch (objectType)
    {
    case ObjectType::None:
        image = nullptr;
        break;
    case ObjectType::Box:
        image = new Quad(L"Resources/Textures/Tiles/tileBuilding_sand.png");
        break;
    case ObjectType::Wall:
        image = new Quad(L"Resources/Textures/Tiles/tileStone.png");
        break;
    case ObjectType::Portal:
        // image = new Quad(...);
        break;
    case ObjectType::Water:
        //�渷�� ����
        break;
    case ObjectType::IcyRoad:
        //�̲������� ����
        break;
    case ObjectType::Player:
        image = new Quad(L"Resources/Textures/Tiles/cart_top.png");
        break;
    }

    // image�� ���� ��������ٸ� �θ�/��ġ ����
    if (image != nullptr) 
    {
        image->SetParent(this);
        image->SetLocalPosition(Vector2(0, 50));
    }
}
