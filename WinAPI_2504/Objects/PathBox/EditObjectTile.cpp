#include "Framework.h"

EditObjectTile::EditObjectTile(ObjectType objectType)
{
	SetTile(objectType);
    if (image != nullptr) image->SetParent(this);
    if (image != nullptr) image->SetLocalPosition(Vector2(0, 50));
    if (image != nullptr) image->SetLocalScale(64, 44);

    rectCollider = new RectCollider(Vector2(128, 100));
    rectCollider->SetLocalPosition(0, 80);
    rectCollider->SetParent(this);
    rectCollider->UpdateWorld();
}

EditObjectTile::~EditObjectTile()
{
    if (image != nullptr)
    {
        delete image;
        image = nullptr;
    }

    delete rectCollider;
}

void EditObjectTile::Render()
{
    if (image != nullptr) image->Render();
    rectCollider->Render();
}

void EditObjectTile::UpdateWorld()
{
    Tile::UpdateWorld();
    rectCollider->UpdateWorld();
    if (image != nullptr) image->UpdateWorld();
}

void EditObjectTile::SetTile(ObjectType objectType)
{
    SetType(objectType);
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
        image = new Quad(L"Resources/Textures/Tiles/door_open.png");
        break;
    case ObjectType::Water:
        //길막기 로직
        break;
    case ObjectType::IcyRoad:
        image = nullptr;
        //미끄러지기 로직
        break;
    case ObjectType::Player:
        image = new Quad(L"Resources/Textures/Tiles/cart_top.png");
        break;
    }
}
