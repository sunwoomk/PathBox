#include "Framework.h"
#include "TileEditScene.h"

TileEditScene::TileEditScene()
{
    LoadTextures();
}

TileEditScene::~TileEditScene()
{
    DeleteEditTiles();
}

void TileEditScene::Update()
{
    if (ImGui::GetIO().WantCaptureMouse) return;

    switch (editType)
    {
    case TileEditScene::Bg:
        EditBgTiles();
        break;
    case TileEditScene::Object:
        EditObjectTiles();
        break;
    }
}

void TileEditScene::Render()
{
    for (EditBgTile* bgTile : editBgTiles)
        bgTile->Render();

    for (EditObjectTile* objectTile : editObjectTiles)
        objectTile->Render();
}

void TileEditScene::GUIRender()
{
    ImGui::Text("Map Editor");

    SaveDialog();
    ImGui::SameLine();
    LoadDialog();

    ImGui::DragInt("Cols", &mapCols, 1, 1, 20);
    ImGui::DragInt("Rows", &mapRows, 1, 1, 20);

    const char* editTypeNames[] = { "Bg", "Object" };
    ImGui::ListBox("Edit Type", (int*)&editType, editTypeNames, 2);

    if (ImGui::Button("Create Tiles"))
        CreateEditTiles();

    RenderSampleBgButtons();
    RenderSampleObjectButtons();
}

void TileEditScene::LoadTextures()
{
    WIN32_FIND_DATA findData;
    HANDLE handle = FindFirstFile(L"Resources/Tiles/*.png", &findData);

    bool result = true;
    wstring path = L"Resources/Tiles/";

    while (result)
    {
        wstring fileName = findData.cFileName;
        Texture* texture = Texture::Add(path + fileName);

        if (fileName.find(L"BgTile_") == 0)
            sampleBgTextures.push_back(texture);
        else if (fileName.find(L"ObjectTile_") == 0)
            sampleObjectTextures.push_back(texture);

        result = FindNextFile(handle, &findData);
    }
}

void TileEditScene::RenderSampleBgButtons()
{
    ImGui::Text("BG Sample Buttons");
    int count = 0;
    for (Texture* texture : sampleBgTextures)
    {
        string key = Utility::ToString(texture->GetFile());
        ImTextureID imguiTextureID = (ImTextureID)texture->GetSRV();

        if (ImGui::ImageButton(key.c_str(), imguiTextureID, ImVec2(50, 50)))
        {
            selectBgTexture = texture;
            selectedBgType = GetBgTypeFromFileName(texture->GetFile());
        }
        count++;
        if (count % sampleButtonCols) ImGui::SameLine();
    }
}

void TileEditScene::RenderSampleObjectButtons()
{
    ImGui::Text("Object Sample Buttons");
    int count = 0;
    for (Texture* texture : sampleObjectTextures)
    {
        string key = Utility::ToString(texture->GetFile());
        ImTextureID imguiTextureID = (ImTextureID)texture->GetSRV();

        if (ImGui::ImageButton(key.c_str(), imguiTextureID, ImVec2(50, 50)))
        {
            selectObjectTexture = texture;
            selectedObjectType = GetObjectTypeFromFileName(texture->GetFile());
        }
        count++;
        if (count % sampleButtonCols) ImGui::SameLine();
    }
}

void TileEditScene::CreateEditTiles()
{
    DeleteEditTiles();

    for (int y = 0; y < mapRows; y++)
    {
        for (int x = 0; x < mapCols; x++)
        {
            EditBgTile* bgTile = new EditBgTile();
            bgTile->SetTilePos(x, y);
            bgTile->SetLocalPosition(START_POS_X + x * TILE_SIZE_X, START_POS_Y - y * TILE_SIZE_Y);
            bgTile->SetLocalScale(0.5f, 0.5f);
            bgTile->UpdateWorld();
            editBgTiles.push_back(bgTile);
        }
    }
}

void TileEditScene::DeleteEditTiles()
{
    for (EditBgTile* bgTile : editBgTiles)
        delete bgTile;

    editBgTiles.clear();

    for (EditObjectTile* objecTile : editObjectTiles)
        delete objecTile;

    editObjectTiles.clear();
}

void TileEditScene::EditBgTiles()
{
    for (EditBgTile* bgTile : editBgTiles)
    {
        if (bgTile->GetCollider()->IsPointCollision(mousePos))
        {
            if (Input::Get()->IsKeyPress(VK_LBUTTON) && selectBgTexture)
            {
                bgTile->GetImage()->GetMaterial()->SetBaseMap(selectBgTexture);
                bgTile->SetType(selectedBgType);
            }
        }
    }
}

void TileEditScene::EditObjectTiles()
{
    if (Input::Get()->IsKeyDown(VK_RBUTTON))
    {
        for (auto it = editObjectTiles.begin(); it != editObjectTiles.end(); )
        {
            if ((*it)->GetCollider()->IsPointCollision(mousePos))
            {
                delete* it;
                it = editObjectTiles.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }

    if (!Input::Get()->IsKeyDown(VK_LBUTTON)) return;

    for (EditBgTile* bgTile : editBgTiles)
    {
        if (bgTile->GetCollider()->IsPointCollision(mousePos))
        {
            Vector2 pos = bgTile->GetLocalPosition();
            EditObjectTile* target = nullptr;

            for (EditObjectTile* objectTile : editObjectTiles)
            {
                if (objectTile->GetLocalPosition() == pos)
                {
                    target = objectTile;
                    break;
                }
            }

            if (target)
            {
                target->SetType(selectedObjectType);
                if (selectObjectTexture)
                    target->GetImage()->GetMaterial()->SetBaseMap(selectObjectTexture);
                target->UpdateWorld();
            }
            else
            {
                CreateObjectTile(pos, selectedObjectType);
            }
        }
    }

    sort(editObjectTiles.begin(), editObjectTiles.end(), EditObjectTile::IsCompare);
}

void TileEditScene::CreateObjectTile(Vector2 pos, ObjectType type)
{
    EditObjectTile* objectTile = new EditObjectTile(type);
    objectTile->SetLocalPosition(pos);
    objectTile->SetLocalScale(0.5f, 0.5f);
    if (selectObjectTexture)
        objectTile->GetImage()->GetMaterial()->SetBaseMap(selectObjectTexture);
    objectTile->UpdateWorld();
    editObjectTiles.push_back(objectTile);
}

BgType TileEditScene::GetBgTypeFromFileName(const wstring& fileName)
{
    if (fileName.find(L"BgTile_Grass") != wstring::npos)
        return BgType::Grass;
    if (fileName.find(L"BgTile_IcyRoad") != wstring::npos)
        return BgType::IcyRoad;
    if (fileName.find(L"BgTile_Water") != wstring::npos)
        return BgType::Water;
    return BgType::None;
}

ObjectType TileEditScene::GetObjectTypeFromFileName(const wstring& fileName)
{
    if (fileName.find(L"ObjectTile_Box") != wstring::npos)
        return ObjectType::Box;
    if (fileName.find(L"ObjectTile_Wall") != wstring::npos)
        return ObjectType::Wall;
    if (fileName.find(L"ObjectTile_Portal_Start") != wstring::npos)
        return ObjectType::Portal_Start;
    if (fileName.find(L"ObjectTile_Portal_End") != wstring::npos)
        return ObjectType::Portal_End;
    if (fileName.find(L"ObjectTile_Goal") != wstring::npos)
        return ObjectType::Goal;
    if (fileName.find(L"ObjectTile_Player") != wstring::npos)
        return ObjectType::Player;
    if (fileName.find(L"ObjectTile_End") != wstring::npos)
        return ObjectType::End;
}

void TileEditScene::Save(string file)
{
    BinaryWriter* writer = new BinaryWriter(file);

    writer->Int(mapCols);
    writer->Int(mapRows);

    for (EditBgTile* bgTile : editBgTiles)
    {
        int bgType = (int)bgTile->GetType();
        writer->Int(bgType);
        writer->WString(bgTile->GetImage()->GetMaterial()->GetBaseMap()->GetFile());
    }

    writer->Int(editObjectTiles.size());
    for (EditObjectTile* objectTile : editObjectTiles)
    {
        writer->Vector(objectTile->GetLocalPosition());
        writer->Int((int)objectTile->GetType());
        writer->WString(objectTile->GetImage()->GetMaterial()->GetBaseMap()->GetFile());
    }

    delete writer;
}

void TileEditScene::Load(string file)
{
    BinaryReader* reader = new BinaryReader(file);

    if (reader->IsFailed())
    {
        delete reader;
        return;
    }

    mapCols = reader->Int();
    mapRows = reader->Int();

    CreateEditTiles();

    for (EditBgTile* bgTile : editBgTiles)
    {
        int bgType = reader->Int();
        bgTile->SetType((BgType)bgType);
        wstring file = reader->WString();
        bgTile->GetImage()->GetMaterial()->SetBaseMap(file);
    }

    int objectTileCount = reader->Int();
    for (int i = 0; i < objectTileCount; i++)
    {
        Vector2 pos = reader->Vector();
        int type = reader->Int();
        wstring file = reader->WString();
        EditObjectTile* objectTile = new EditObjectTile((ObjectType)type);
        objectTile->SetLocalPosition(pos);
        objectTile->SetLocalScale(0.5f, 0.5f);
        objectTile->UpdateWorld();
        editObjectTiles.push_back(objectTile);
    }

    delete reader;
}

void TileEditScene::SaveDialog()
{
    string key = "Save";

    if (ImGui::Button(key.c_str()))
    {
        DIALOG->OpenDialog(key, key, ".map");
    }

    if (DIALOG->Display(key))
    {
        if (DIALOG->IsOk())
        {
            char temp[256] = {};
            GetCurrentDirectoryA(256, temp);
            string path = temp;
            string file = DIALOG->GetFilePathName();
            file = file.substr(path.size() + 1);
            Save(file);
        }

        DIALOG->Close();
    }
}

void TileEditScene::LoadDialog()
{
    string key = "Load";

    if (ImGui::Button(key.c_str()))
    {
        DIALOG->OpenDialog(key, key, ".map");
    }

    if (DIALOG->Display(key))
    {
        if (DIALOG->IsOk())
        {
            char temp[256] = {};
            GetCurrentDirectoryA(256, temp);
            string path = temp;
            string file = DIALOG->GetFilePathName();
            file = file.substr(path.size() + 1);
            Load(file);
        }

        DIALOG->Close();
    }
}
