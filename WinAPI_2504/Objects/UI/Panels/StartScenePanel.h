#pragma once

class StartScenePanel : public Panel
{
public:
	StartScenePanel();
	~StartScenePanel();

	void Update() override;
	void Render() override;

private:
	void SetButtons() override;
	void SelectStageButtonClick();
	void OptionsButtonClick();
	void ExitButtonClick();
};
