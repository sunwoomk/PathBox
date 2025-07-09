#pragma once

class MenuPanel : public Panel
{
public:
	MenuPanel(TileMaps* tileMaps);
	~MenuPanel();

	void Update() override;
	void Render() override;

	void SetButtons() override;
	void SelectStageButtonClick();

	void SetTileMaps(TileMaps* tileMaps) { this->tileMaps = tileMaps; }

private:
	TileMaps* tileMaps;
};