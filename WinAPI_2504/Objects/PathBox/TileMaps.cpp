#include "Framework.h"

TileMaps::TileMaps(string file)
{
    LoadFiles(file);
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

ObjectTile* TileMaps::FindObjectTile(ObjectType objectType)
{
    for (ObjectTile* objectTile : objectTiles)
    {
        ObjectType type = objectTile->GetType();
        if (type == objectType)
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
        ObjectTile* player = FindObjectTile(ObjectType::Player);
        if (player && !player->IsMoving()) 
        {
            Teleport(player);
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
    sort(objectTiles.begin(), objectTiles.end(), ObjectTile::IsCompare);
    ObjectTile* player = FindObjectTile(playerPos.x, playerPos.y);
    if (!player || player->IsMoving() || UIManager::Get()->GetPanelActive("MenuPanel")) return;

    int dx = 0, dy = 0;
    if (Input::Get()->IsKeyDown('W')) dy = -1;
    else if (Input::Get()->IsKeyDown('A')) dx = -1;
    else if (Input::Get()->IsKeyDown('S')) dy = 1;
    else if (Input::Get()->IsKeyDown('D')) dx = 1;

    if (dx == 0 && dy == 0) return;

    int newX = playerPos.x + dx;
    int newY = playerPos.y + dy;

    if (newX < 0 || newX >= mapCols || newY < 0 || newY >= mapRows)
        return;

    BgTile* targetBg = FindBgTile(newX, newY);
    ObjectTile* targetObject = FindObjectTile(newX, newY);

    if (targetObject == nullptr)
    {
        if (targetBg->GetType() == BgType::IcyRoad)
        {
            int destX = newX;
            int destY = newY;
            int nextX = newX + dx;
            int nextY = newY + dy;

            while (true)
            {
                if (nextX < 0 || nextX >= mapCols || nextY < 0 || nextY >= mapRows) 
                {
                    destX = nextX - dx;
                    destY = nextY - dy;
                    break;
                }
                BgTile* nextBg = FindBgTile(nextX, nextY);
                ObjectTile* nextObject = FindObjectTile(nextX, nextY);

                if (nextBg->GetType() == BgType::IcyRoad)
                {
                    nextX = nextX + dx;
                    nextY = nextY + dy;
                    //continue;
                }
                else if (nextBg->GetType() == BgType::Water) 
                {
                    destX = nextX - dx;
                    destY = nextY - dy;
                    break;
                }
                else
                {
                    if (nextObject != nullptr) 
                    {
                        if (nextObject->GetType() == ObjectType::Box || nextObject->GetType() == ObjectType::Wall || nextObject->GetType() == ObjectType::Goal)
                        {
                            destX = nextX - dx;
                            destY = nextY - dy;
                            break;
                        }
                    }
                    else if(nextObject == nullptr)
                    {
                        destX = nextX;
                        destY = nextY;
                        break;
                    }
                }
            }

            player->StartMove(destX, destY);
            player->SetTilePos(destX, destY);
            playerPos = { destX, destY };
            return;
        }

        if (targetBg->GetType() == BgType::Water)
            return;

        player->StartMove(newX, newY);
        player->SetTilePos(newX, newY);
        playerPos = { newX, newY };
        return;
    }
    if (targetObject->GetType() == ObjectType::Box)
    {
        ObjectTile* box = FindObjectTile(newX, newY);
        int boxX = newX + dx;
        int boxY = newY + dy;
        if (boxX < 0 || boxX >= mapCols || boxY < 0 || boxY >= mapRows)
            return;
        BgTile* beyondBg = FindBgTile(boxX, boxY);
        if (beyondBg->GetType() == BgType::IcyRoad || beyondBg->GetType() == BgType::Water)
            return;
        ObjectTile* beyondObject = FindObjectTile(boxX, boxY);
        if (beyondObject == nullptr)
        {
            box->StartMove(boxX, boxY);
            box->SetTilePos(boxX, boxY);
            player->StartMove(newX, newY);
            player->SetTilePos(newX, newY);
            playerPos = { newX, newY };
            return;
        }
    }

    if (targetObject->GetType() == ObjectType::Portal_Start) 
    {
        ObjectTile* endPortal = FindObjectTile(ObjectType::Portal_End);
        if (endPortal == nullptr) return;
        tpStartPosX = newX;
        tpStartPosY = newY;
        tpEndPosX = endPortal->GetTilePos().x;
        tpEndPosY = endPortal->GetTilePos().y;
        destPos = endPortal->GetLocalPosition();
        player->StartMove(tpStartPosX, tpStartPosY);
        isTeleporting = true;
        return;
    }

    if (targetObject->GetType() == ObjectType::Goal) 
    {
        player->StartMove(newX, newY);
        player->SetTilePos(newX, newY);
        playerPos = { newX, newY };
        UIManager::Get()->SetPanelActive("StageClearPanel", true);
		int index = SceneManager::Get()->GetCurrentStageIndex();
        SelectStagePanel* selectStagePanel = UIManager::Get()->GetSelectStagePanel();
        if (selectStagePanel)
            selectStagePanel->UnlockStage(static_cast<int>(index + 1));
		return;
    }
}

void TileMaps::Teleport(ObjectTile* player)
{
    player->SetTilePos(tpEndPosX, tpEndPosY + 1);
    player->SetLocalPosition(destPos - Vector2(0, TILE_SIZE_Y));
    player->UpdateWorld();
    playerPos = { tpEndPosX, tpEndPosY + 1 };
    isTeleporting = false;
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
        tests.push_back(bgType);
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
            bgTile->SetLocalPosition(START_POS_X + x * TILE_SIZE_X, START_POS_Y - y * TILE_SIZE_Y);
            bgTile->SetLocalScale(0.5f, 0.5f);
            bgTile->UpdateWorld();
            bgTiles.push_back(bgTile);
        }
    }
}

void TileMaps::CreateObjectTiles(BinaryReader* reader)
{
    int objectTileCount = reader->Int();
    for (int i = 0; i < objectTileCount; i++) 
    {
        Vector2 pos = reader->Vector();
        int type = reader->Int();
        wstring file = reader->WString();

        int x = static_cast<int>((pos.x - START_POS_X) / TILE_SIZE_X);
        int y = static_cast<int>((START_POS_Y - pos.y) / TILE_SIZE_Y);

        ObjectTile* objectTile = new ObjectTile((ObjectType)type);
        objectTile->SetTilePos(x, y);
        objectTile->SetLocalPosition(pos.x, pos.y);
        objectTile->SetLocalScale(0.5f, 0.5f);
        objectTile->UpdateWorld();
		objectTile->SetId(i);
        objectTiles.push_back(objectTile);

        if (type == (int)ObjectType::Player)
            playerPos = { x, y };

		ObjectTileState objectTileState;
		objectTileState.id = objectTile->GetId();
		objectTileState.tilePos = { x, y };
        SaveObjectTilePos(objectTileState);
    }
	objectTiles.push_back(new ObjectTile(ObjectType::Portal_Start));
    sort(objectTiles.begin(), objectTiles.end(), ObjectTile::IsCompare);
}

void TileMaps::Restart() 
{
    for (int i = 0; i < objectTiles.size(); i++)
    {
		for (ObjectTileState& state : objectTileStates)
		{
			if (state.id == objectTiles[i]->GetId())
			{
				int x = state.tilePos.x;
				int y = state.tilePos.y;
				objectTiles[i]->SetTilePos(x, y);
				objectTiles[i]->SetLocalPosition(Vector2(START_POS_X + x * TILE_SIZE_X, START_POS_Y - y * TILE_SIZE_Y));
				objectTiles[i]->UpdateWorld();
                break;
			}
		}
    }
    for (ObjectTile* objectTile : objectTiles) 
    {
        if (objectTile->GetType() == ObjectType::Player) 
        {
            playerPos = objectTile->GetTilePos();
            break;
        }
    }
}
