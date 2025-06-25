#include "Framework.h"

TileMaps::TileMaps(string file)
{
    LoadFiles(file);

    for (ObjectTile* objectTile : objectTiles)
    {
        if (objectTile->GetType() == ObjectType::Player)
        {
            playerPos = objectTile->GetTilePos();
            break;
        }
    }
}

TileMaps::~TileMaps()
{
    for (BgTile* bgTile : bgTiles)
    {
        delete bgTile;
    }
    bgTiles.clear();

    for (ObjectTile* objectTile : objectTiles)
    {
        delete objectTile;
    }
    objectTiles.clear();
}

BgTile* TileMaps::FindBgTile(int x, int y)
{
    for (BgTile* bgTile : bgTiles)
    {
        POINT pos = bgTile->GetTilePos();
        if (pos.x == x && pos.y == y)
            return bgTile;
    }
    return nullptr;
}

ObjectTile* TileMaps::FindObjectTile(int x, int y)
{
    for (ObjectTile* objectTile : objectTiles)
    {
        POINT pos = objectTile->GetTilePos();
        if (pos.x == x && pos.y == y)
            return objectTile;
    }
    return nullptr;
}

void TileMaps::Update()
{
    for (ObjectTile* objectTile : objectTiles)
    {
        objectTile->Update();
    }

    if (isTeleporting)
    {
        ObjectTile* player = FindObjectTile(teleportStartX, teleportStartY);
        if (player && !player->IsMoving())
        {
            Teleport(teleportStartY, teleportStartX, teleportDestY, teleportDestX);
            isTeleporting = false;
        }
    }

    PlayerMove();
}

void TileMaps::Render()
{
    for (BgTile* bgTile : bgTiles)
    {
        bgTile->Render();
    }

    for (ObjectTile* objectTile : objectTiles)
    {
        objectTile->Render();
    }
}

void TileMaps::UpdateWorld()
{
    Transform::UpdateWorld();

    for (BgTile* bgTile : bgTiles)
    {
        bgTile->UpdateWorld();
    }

    for (ObjectTile* objectTile : objectTiles)
    {
        objectTile->UpdateWorld();
    }
}

void TileMaps::PlayerMove()
{
    ObjectTile* player = FindObjectTile(playerPos.x, playerPos.y);
    if (!player || player->IsMoving()) return;

    int dx = 0, dy = 0;
    if (Input::Get()->IsKeyDown('W')) dy = -1;
    else if (Input::Get()->IsKeyDown('A')) dx = -1;
    else if (Input::Get()->IsKeyDown('S')) dy = 1;
    else if (Input::Get()->IsKeyDown('D')) dx = 1;

    int newX = playerPos.x + dx;
    int newY = playerPos.y + dy;

    if (newX < 0 || newX >= mapCols || newY < 0 || newY >= mapRows)
        return;

    ObjectTile* target = FindObjectTile(newX, newY);
    if (!target || target->GetType() == ObjectType::Player) return;

    switch (target->GetType()) {
    case ObjectType::None:
        SwapAndMove(playerPos.y, playerPos.x, newY, newX);
        playerPos = { newX, newY };
        break;

    case ObjectType::Box: {
        int boxX = newX + dx;
        int boxY = newY + dy;
        if (boxX < 0 || boxX >= mapCols || boxY < 0 || boxY >= mapRows)
            return;
        ObjectTile* beyond = FindObjectTile(boxX, boxY);
        if (beyond && beyond->GetType() == ObjectType::None) {
            SwapAndMove(newY, newX, boxY, boxX);
            SwapAndMove(playerPos.y, playerPos.x, newY, newX);
            playerPos = { newX, newY };
        }
        break;
    }

    case ObjectType::IcyRoad: {
        int destX = newX;
        int destY = newY;
        int nextX = newX + dx;
        int nextY = newY + dy;
        while (true) 
        {
            if (nextX < 0 || nextX >= mapCols || nextY < 0 || nextY >= mapRows)
                break;
            ObjectTile* next = FindObjectTile(nextX, nextY);
            if (next->GetType() == ObjectType::None)
            {
                destX = nextX;
                destY = nextY;
                break;
            }
            else if (next->GetType() == ObjectType::IcyRoad)
            {
                nextX = nextX + dx;
                nextY = nextY + dy;
            }
            else
                break;
        }
        SwapAndMove(playerPos.y, playerPos.x, destY, destX);
        playerPos = { destX, destY };
        break;
        //int slideX = newX, slideY = newY;
        //while (true) {
        //    int nextX = slideX + dx, nextY = slideY + dy;
        //    if (nextX < 0 || nextX >= mapCols || nextY < 0 || nextY >= mapRows) break;
        //    ObjectTile* next = FindObjectTile(nextX, nextY);
        //    if (!next || next->GetType() != ObjectType::None) break;
        //    slideX = nextX; slideY = nextY;
        //}
        //SwapAndMove(playerPos.y, playerPos.x, slideY, slideX);
        //playerPos = { slideX, slideY };
        //break;
    }

    case ObjectType::Portal:
        isTeleporting = true;
        teleportStartX = playerPos.x;
        teleportStartY = playerPos.y;
        teleportDestX = 7; // 예시
        teleportDestY = 1; // 예시
        player->StartMove(newX, newY);
        break;
    default:
        break;
    }

    sort(objectTiles.begin(), objectTiles.end(), ObjectTile::IsCompare);
}

void TileMaps::SwapAndMove(int fromY, int fromX, int toY, int toX)
{
    ObjectTile* from = FindObjectTile(fromX, fromY);
    ObjectTile* to = FindObjectTile(toX, toY);

    if (!from || !to) return;

    POINT tempPos = from->GetTilePos();
    from->SetTilePos(to->GetTilePos().x, to->GetTilePos().y);
    to->SetTilePos(tempPos.x, tempPos.y);

    from->StartMove(toX, toY);
    to->StartMove(fromX, fromY);
}

void TileMaps::Teleport(int curY, int curX, int destY, int destX)
{
    ObjectTile* player = FindObjectTile(curX, curY);
    ObjectTile* dest = FindObjectTile(destX, destY);

    if (!player || !dest) return;

    POINT tempPos = player->GetTilePos();
    player->SetTilePos(dest->GetTilePos().x, dest->GetTilePos().y);
    dest->SetTilePos(tempPos.x, tempPos.y);

    player->StartMove(destX, destY);
    dest->StartMove(curX, curY);

    playerPos = { destX, destY };
}

void TileMaps::LoadFiles(string file)
{
    BinaryReader* reader = new BinaryReader(file);

    if (reader->IsFailed())
    {
        delete reader;
        return;
    }

    mapCols = reader->Int();
    mapRows = reader->Int();

    CreateBgTiles();

    for (BgTile* bgTile : bgTiles)
    {
        int bgType = reader->Int();
        bgTile->SetType((BgType)bgType);
        wstring file = reader->WString();
        bgTile->GetImage()->GetMaterial()->SetBaseMap(file);
    }

    CreateObjectTiles(reader);

    delete reader;
}

void TileMaps::CreateBgTiles()
{
    for (int y = 0; y < mapRows; y++)
    {
        for (int x = 0; x < mapCols; x++)
        {
            BgTile* bgTile = new BgTile();
            bgTile->SetTilePos(x, y);
            bgTile->SetLocalPosition(200 + x * TILE_SIZE_X, 200 + (mapRows - 1 - y) * TILE_SIZE_Y);
            bgTile->SetLocalScale(0.5f, 0.5f);
            bgTile->UpdateWorld();
            bgTiles.push_back(bgTile);
        }
    }
}

void TileMaps::CreateObjectTiles(BinaryReader* reader)
{
    for (int y = 0; y < mapRows; y++) 
    {
        for (int x = 0; x < mapCols; x++) 
        {
            ObjectTile* objectTile = new ObjectTile();
            objectTile->SetTilePos(x, y);
            objectTile->SetLocalPosition(200 + x * TILE_SIZE_X, 185 + (mapRows - 1 - y) * TILE_SIZE_Y);
            objectTile->SetLocalScale(0.5f, 0.5f);
            objectTile->UpdateWorld();
            objectTiles.push_back(objectTile);
        }
    }

    for (int y = 0; y < mapRows; y++)
    {
        for (int x = 0; x < mapCols; x++)
        {
            BgTile* bgTile = FindBgTile(x, y);
            ObjectTile* objectTile = FindObjectTile(x, y);

            if (!bgTile || !objectTile) continue;

            BgType bgType = bgTile->GetType();
            // 배경 타입에 따른 오브젝트 타입 매핑
            switch (bgType) 
            {
            case BgType::IcyRoad:
                objectTile->SetType(ObjectType::IcyRoad);
                //objectTile->UpdateWorld();
                break;
            case BgType::Water:
                objectTile->SetType(ObjectType::Water);
                //objectTile->UpdateWorld();
                break;
                // 다른 배경 타입에 대한 매핑 추가 가능
            default:
                // 기본값 유지
                break;
            }
        }
    }

    int objectTileCount = reader->Int();
    for (int i = 0; i < objectTileCount; i++) 
    {
        Vector2 pos = reader->Vector();
        int type = reader->Int();
        wstring file = reader->WString();

        int x = static_cast<int>((pos.x - 200) / TILE_SIZE_X);
        int y = mapRows - 1 - static_cast<int>((pos.y - 200) / TILE_SIZE_Y);

        ObjectTile* objectTile = FindObjectTile(x, y);
        if (objectTile) 
        {
            objectTile->SetTile((ObjectType)type);
            objectTile->GetImage()->SetParent(objectTile);
            objectTile->GetImage()->SetLocalPosition(Vector2(0, 140));
            objectTile->UpdateWorld();
        }
    }
    sort(objectTiles.begin(), objectTiles.end(), ObjectTile::IsCompare);
}
