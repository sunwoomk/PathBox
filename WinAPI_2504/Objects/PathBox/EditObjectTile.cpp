#include "Framework.h"

EditObjectTile::EditObjectTile(ObjectType objectType)
{
	SetTile(objectType);
    image->SetParent(this);
    image->SetLocalPosition(Vector2(0, 60));

    rectCollider = new RectCollider(Vector2(128, 100));
    rectCollider->SetLocalPosition(0, 0);
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
    case ObjectType::Box:
        image = new Quad(L"Resources/Tiles/ObjectTile_Box.png");
        break;
    case ObjectType::Wall:
        image = new Quad(L"Resources/Tiles/ObjectTile_Wall.png");
        break;
    case ObjectType::Portal_Start:
        image = new Quad(L"Resources/Tiles/ObjectTile_Portal_Start.png");
        break;
    case ObjectType::Portal_End:
        image = new Quad(L"Resources/Tiles/ObjectTile_Portal_End.png");
        break;
    case ObjectType::Goal:
        image = new Quad(L"Resources/Tiles/ObjectTile_Goal.png");
        break;
    case ObjectType::Player:
        image = new Quad(L"Resources/Tiles/ObjectTile_Player.png");
        break;
    }
}
