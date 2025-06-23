#pragma once

class SampleTileGameScene : public Scene
{
public:
	SampleTileGameScene();
	~SampleTileGameScene();	

	void Update() override;
	void Render() override;
	void GUIRender() override;

private:
	AStar* aStar = nullptr;
	TileMap* tileMap = nullptr;
	Tank* tank;
};