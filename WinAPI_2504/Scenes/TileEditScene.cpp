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
			if (Input::Get()->IsKeyPress(VK_LBUTTON))
			{
				if (objectTile->GetImage() == nullptr) 
				{
					objectTile->SetTile(ObjectType::Box);
					objectTile->GetImage()->SetParent(objectTile);
					objectTile->GetImage()->SetLocalPosition(Vector2(0, 150));
					objectTile->UpdateWorld();
				}
				objectTile->GetImage()->GetMaterial()->SetBaseMap(selectTexture);
			}
		}
	}
}
