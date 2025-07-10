#pragma once

class StartScene : public Scene
{
public:
	StartScene();
	~StartScene();

	void Update() override;
	void Render() override;

	void Start() override { Audio::Get()->PlayBGM("MenuBGM"); }

	void SetQuads();

private:
	Quad* pathBoxQuad;
	Quad* pressToStartQuad;
};