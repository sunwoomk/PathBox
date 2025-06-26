#pragma once

class TileEditScene : public Scene 
{
private:
	enum EditType
	{
		Bg,
		Object
	};
private:
	static const int TILE_SIZE_X = 64;
	static const int TILE_SIZE_Y = 44;	
	static const int START_POS_X = 200;
	static const int START_POS_Y = SCREEN_HEIGHT - 200;

public:
	TileEditScene();
	~TileEditScene();

	void Update() override;
	void Render() override;
	void GUIRender() override; 

private:
	void LoadTextures();
	void RenderSampleBgButtons();
	void RenderSampleObjectButtons();
	void CreateEditTiles();
	void DeleteEditTiles();

	void EditBgTiles();
	void EditObjectTiles();
	void CreateObjectTile(Vector2 pos, ObjectType type);

	BgType GetBgTypeFromFileName(const wstring& fileName);
	ObjectType GetObjectTypeFromFileName(const wstring& fileName);

	void Save(string file);
	void Load(string file);

	void SaveDialog();
	void LoadDialog();

private:
	int sampleButtonCols = 6;
	int mapCols = 10;
	int mapRows = 10;

	EditType editType = Bg;

	vector<Texture*> sampleBgTextures;
	vector<Texture*> sampleObjectTextures;

	Texture* selectBgTexture = nullptr;
	Texture* selectObjectTexture = nullptr;

	vector<EditBgTile*> editBgTiles;
	vector<EditObjectTile*> editObjectTiles;

	BgType selectedBgType = BgType::None;
	ObjectType selectedObjectType;
};