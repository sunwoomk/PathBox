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
public:
	TileEditScene();
	~TileEditScene();

	void Update() override;
	void Render() override;
	void GUIRender() override; 

private:
	void LoadTextures();
	void RenderSampleButtons();
	void CreateEditTiles();
	void DeleteEditTiles();

	void EditBgTiles();
	void EditObjectTiles();

	void Save(string file);
	void Load(string file);

	void SaveDialog();
	void LoadDialog();

private:
	int sampleButtonCols = 5;
	int mapCols = 10;
	int mapRows = 10;

	EditType editType = Bg;

	vector<Texture*> sampleTextures;
	vector<EditBgTile*> editBgTiles;
	vector<EditObjectTile*> editObjectTiles;

	Texture* selectTexture;
};