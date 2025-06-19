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

void ObjectTile::Update()
{
    if (isMoving) 
    {
        Vector2 dir = targetPos - GetLocalPosition();
        float distance = dir.Magnitude();

        float moveStep = moveSpeed * DELTA;

        if (moveStep >= distance) 
        {
            SetLocalPosition(targetPos);
            isMoving = false;
        }
        else 
        {
            dir.Normalize();
            Vector2 newPos = GetLocalPosition() + dir * moveStep;
            SetLocalPosition(newPos);
        }
        UpdateWorld();
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
        //길막기 로직
        break;
    case ObjectType::IcyRoad:
        //미끄러지기 로직
        break;
    case ObjectType::Player:
        image = new Quad(L"Resources/Textures/Tiles/cart_top.png");
        break;
    }

    if (image != nullptr) 
    {
        image->SetParent(this);
        image->SetLocalPosition(Vector2(0, 50));
    }
}

void ObjectTile::StartMove(int toX, int toY)
{
    targetPos = Vector2(200 + toX * 64, 185 + (9 - toY) * 44);
    isMoving = true;
}
