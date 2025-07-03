#pragma once

class SelectStagePanel : public Panel
{
private:
	const int STAGE_COUNT = 10;
public:
	SelectStagePanel();
	~SelectStagePanel();
	void Update() override;
	void Render() override;

	void SetButtons() override;
	void UnlockStage(int index);

private:
	vector<Quad*> unlockTextures;
};