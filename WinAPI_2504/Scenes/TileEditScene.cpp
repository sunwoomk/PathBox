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

	RenderSampleButtons();
}

void TileEditScene::LoadTextures()
{
	WIN32_FIND_DATA findData;

	HANDLE handle = FindFirstFile(L"Resources/Textures/Tiles/*.png", &findData);

	bool result = true;
	wstring path = L"Resources/Textures/Tiles/";

	while (result) 
	{
		Texture* texture = Texture::Add(path + findData.cFileName);
		sampleTextures.push_back(texture);

		result = FindNextFile(handle, &findData);
	}
}

void TileEditScene::RenderSampleButtons()
{
	ImGui::DragInt("Col", &sampleButtonCols);

	if (ImGui::TreeNode("Sample Buttons")) 
	{
		int count = 0;

		for (Texture* texture : sampleTextures) 
		{
			string key = Utility::ToString(texture->GetFile());
			ImTextureID imguiTextureID = (ImTextureID)texture->GetSRV();

			if (ImGui::ImageButton(key.c_str(), imguiTextureID, ImVec2(50, 50))) 
			{
				selectTexture = texture;
			}

			count++;

			if (count % sampleButtonCols)
				ImGui::SameLine();
		}

		ImGui::TreePop();
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
			bgTile->SetLocalPosition(200 + x * TILE_SIZE_X, 200 + (mapRows - 1 - y) * TILE_SIZE_Y);
			bgTile->SetLocalScale(0.5f, 0.5f);
			bgTile->UpdateWorld();
			editBgTiles.push_back(bgTile);
		}
	}

	for (int y = 0; y < mapRows; y++)
	{
		for (int x = 0; x < mapCols; x++)
		{
			EditObjectTile* objectTile = new EditObjectTile();
			objectTile->SetTilePos(x, y);
			objectTile->SetLocalPosition(200 + x * TILE_SIZE_X, 185 + (mapRows - 1 - y) * TILE_SIZE_Y);
			objectTile->SetLocalScale(0.5f, 0.5f);
			objectTile->UpdateWorld();
			editObjectTiles.push_back(objectTile);
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
			if (Input::Get()->IsKeyPress(VK_LBUTTON))
			{
				bgTile->GetImage()->GetMaterial()->SetBaseMap(selectTexture);
			}
		}
	}
}

void TileEditScene::EditObjectTiles()
{
	for (EditObjectTile* objectTile : editObjectTiles)
	{
		if (objectTile->GetCollider()->IsPointCollision(mousePos))
		{
			if (Input::Get()->IsKeyDown(VK_LBUTTON))
			{
				if (objectTile->GetImage() == nullptr)
				{
					objectTile->SetTile(ObjectType::Box);
					objectTile->GetImage()->SetParent(objectTile);
					objectTile->GetImage()->SetLocalPosition(Vector2(0, 140));
					objectTile->UpdateWorld();
				}
				objectTile->GetImage()->GetMaterial()->SetBaseMap(selectTexture);
			}

			if (Input::Get()->IsKeyDown(VK_RBUTTON)) 
			{
				if (objectTile->GetImage() != nullptr)
				{
					objectTile->SetTile(ObjectType::None);
					objectTile->UpdateWorld();
				}
			}
		}
	}
}

void TileEditScene::Save(string file)
{
	BinaryWriter* writer = new BinaryWriter(file);

	writer->Int(mapCols);
	writer->Int(mapRows);

	for (EditBgTile* bgTile : editBgTiles) 
	{
		writer->WString(bgTile->GetImage()->GetMaterial()->GetBaseMap()->GetFile());
	}
	writer->Int(editObjectTiles.size());
	for (EditObjectTile* objectTile : editObjectTiles)
	{
		writer->Vector(objectTile->GetLocalPosition());
		if (objectTile->GetImage() != nullptr)
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
		wstring file = reader->WString();
		bgTile->GetImage()->GetMaterial()->SetBaseMap(file);
	}

	int objectTileCount = reader->Int();

	for (int i = 0; i < objectTileCount; i++)
	{
		Vector2 pos = reader->Vector();
		wstring file = reader->WString();
		if(editObjectTiles[i]->GetImage() != nullptr)
			editObjectTiles[i]->GetImage()->GetMaterial()->SetBaseMap(file);
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
