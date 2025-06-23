#include "Framework.h"
#include "SampleTileEditScene.h"

SampleTileEditScene::SampleTileEditScene()
{
	LoadTextures();
}

SampleTileEditScene::~SampleTileEditScene()
{
	DeleteEditTiles();
}

void SampleTileEditScene::Update()
{
	if (ImGui::GetIO().WantCaptureMouse) return;

	switch (editType)
	{
	case SampleTileEditScene::BG:
		EditBGTiles();
		break;
	case SampleTileEditScene::OBJ:
		EditObjTiles();
		break;	
	}	
}

void SampleTileEditScene::Render()
{
	for (SampleEditTile* tile : bgEditTiles)
	{
		tile->Render();
	}

	for (SampleEditTile* tile : objEditTiles)
	{
		tile->Render();
	}
}

void SampleTileEditScene::GUIRender()
{
	ImGui::Text("Map Editor");
	SaveDialog();	
	ImGui::SameLine();
	LoadDialog();

	ImGui::DragInt("Cols", &mapCols, 1, 1, 20);
	ImGui::DragInt("Rows", &mapRows, 1, 1, 20);

	const char* editTypeNames[] = { "BG", "OBJ" };

	ImGui::ListBox("Edit Type", (int*)&editType, editTypeNames, 2);

	if (ImGui::Button("Create Tiles"))
	{
		CreateEditTiles();
	}
	
	RenderSampleButtons();
}

void SampleTileEditScene::LoadTextures()
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

void SampleTileEditScene::RenderSampleButtons()
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

			if(count % sampleButtonCols)
			{
				ImGui::SameLine();
			}
		}

		ImGui::TreePop();
	}
}

void SampleTileEditScene::CreateEditTiles()
{
	DeleteEditTiles();

	Vector2 size = sampleTextures[0]->GetSize();
	Vector2 startPos = Vector2(size.x * 0.5f, SCREEN_HEIGHT - size.y * 0.5f);

	imageSize = size;

	for (int y = 0; y < mapRows; y++)
	{
		for (int x = 0; x < mapCols; x++)
		{
			SampleEditTile* tile = new SampleEditTile();
			Vector2 pos = startPos + Vector2(x * tile->Size().x, -y * tile->Size().y);
			tile->SetLocalPosition(pos);
			tile->UpdateWorld();

			bgEditTiles.push_back(tile);
		}
	}

	tileSize = bgEditTiles.front()->Size();
}

void SampleTileEditScene::DeleteEditTiles()
{
	for (SampleEditTile* tile : bgEditTiles)
	{
		delete tile;
	}

	bgEditTiles.clear();
}

void SampleTileEditScene::EditBGTiles()
{
	if (Input::Get()->IsKeyPress(VK_LBUTTON) == false)
		return;

	for (SampleEditTile* tile : bgEditTiles)
	{
		if (tile->IsPointCollision(mousePos))
		{			
			tile->GetImage()->GetMaterial()->SetBaseMap(selectTexture);			
		}
	}
}

void SampleTileEditScene::EditObjTiles()
{
	if (Input::Get()->IsKeyDown(VK_LBUTTON) == false)
		return;

	for (SampleEditTile* tile : bgEditTiles)
	{
		if (tile->IsPointCollision(mousePos))
		{
			Vector2 pos = tile->GetLocalPosition();

			SampleEditTile* objTile = new SampleEditTile();
			objTile->GetImage()->GetMaterial()->SetBaseMap(selectTexture);
			objTile->SetLocalPosition(pos);
			objTile->UpdateWorld();

			objEditTiles.push_back(objTile);

			sort(objEditTiles.begin(), objEditTiles.end(), SampleEditTile::IsCompare);
		}
	}
}

void SampleTileEditScene::Save(string file)
{
	BinaryWriter* writer = new BinaryWriter(file);

	writer->Int(mapCols);
	writer->Int(mapRows);

	writer->Vector(tileSize);
	writer->Vector(imageSize);

	for (SampleEditTile* tile : bgEditTiles)
	{
		writer->WString(tile->GetImage()->GetMaterial()->GetBaseMap()->GetFile());
	}

	writer->Int(objEditTiles.size());
	for (SampleEditTile* tile : objEditTiles)
	{
		writer->Vector(tile->GetLocalPosition());
		writer->WString(tile->GetImage()->GetMaterial()->GetBaseMap()->GetFile());
	}

	delete writer;
}

void SampleTileEditScene::Load(string file)
{
	BinaryReader* reader = new BinaryReader(file);

	if (reader->IsFailed())
	{
		delete reader;
		return;
	}

	mapCols = reader->Int();
	mapRows = reader->Int();

	tileSize = reader->Vector();
	imageSize = reader->Vector();

	CreateEditTiles();

	for (SampleEditTile* tile : bgEditTiles)
	{
		wstring file = reader->WString();
		tile->GetImage()->GetMaterial()->SetBaseMap(file);
	}

	int objTileCount = reader->Int();

	for (int i = 0; i < objTileCount; i++)
	{
		Vector2 pos = reader->Vector();
		wstring file = reader->WString();
		SampleEditTile* objTile = new SampleEditTile();
		objTile->GetImage()->GetMaterial()->SetBaseMap(file);
		objTile->SetLocalPosition(pos);
		objTile->UpdateWorld();

		objEditTiles.push_back(objTile);
	}

	delete reader;
}

void SampleTileEditScene::SaveDialog()
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

void SampleTileEditScene::LoadDialog()
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
