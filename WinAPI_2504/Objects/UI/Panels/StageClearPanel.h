#pragma once

class StageClearPanel : public Panel
{
public:
	StageClearPanel();
	~StageClearPanel();

	void Update() override;
	void Render() override;

private:
	void SetButtons() override;
	void SelectStageButtonClick();
	void NextStageButtonClick();
};
