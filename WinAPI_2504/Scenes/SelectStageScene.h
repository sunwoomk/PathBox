#pragma once

class SelectStageScene : public Scene
{
public:
	SelectStageScene();
	~SelectStageScene();

	void Update() override;
	void Render() override;

	void Start() override { Audio::Get()->Play("MenuBGM"); }
	void End() override { Audio::Get()->Stop("MenuBGM"); }
};