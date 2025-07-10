#pragma once

class StartScene : public Scene
{
public:
	StartScene();
	~StartScene();

	void Update() override;
	void Render() override;

	void Start() override { Audio::Get()->Play("MenuBGM"); }
	void End() override { Audio::Get()->Stop("MenuBGM"); }

	void SetQuads();

private:
	Quad* pathBoxQuad;
	Quad* pressToStartQuad;
};