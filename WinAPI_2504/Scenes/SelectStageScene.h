#pragma once

class SelectStageScene : public Scene
{
public:
	SelectStageScene();
	~SelectStageScene();

	void Update() override;
	void Render() override;

	void Start() override { Audio::Get()->PlayBGM("MenuBGM"); }
};