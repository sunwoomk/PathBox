#pragma once

class SelectStageScene : public Scene
{
public:
	SelectStageScene();
	~SelectStageScene();

	void Update() override;
	void Render() override;

private:
	SelectStagePanel* selectStagePanel = nullptr;
};