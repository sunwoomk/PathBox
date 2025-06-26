#include "Framework.h"

ObjectTile::ObjectTile(ObjectType objectType)
{
	SetTile(objectType);
    image->SetParent(this);
    image->SetLocalPosition(Vector2(0, 60));
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

void ObjectTile::StartMove(int toX, int toY)
{
    targetPos = Vector2(START_POS_X + toX * TILE_SIZE_X, START_POS_Y - toY * TILE_SIZE_Y);
    isMoving = true;
}
