#pragma once

class StageScene : public Scene
{
private:
	static const int TILE_SIZE_X = 64;
	static const int TILE_SIZE_Y = 44;
	static const int MAP_COLS = 10;
	static const int MAP_ROWS = 10;
public:
	StageScene(string file);
	~StageScene();

	void Update() override;
	void UpdateWorld();
	void Render() override;
	void PostRender() override;

	void Start() override { Audio::Get()->PlayBGM("StageBGM"); }

	void SetTileMaps(string file);

	void SetKey(const string& k) { key = k; }
	string GetKey() const { return key; }

	TileMaps* GetTileMaps() const { return tileMaps; }

private:
	string key;
	TileMaps* tileMaps;
	Quad* background;
};

