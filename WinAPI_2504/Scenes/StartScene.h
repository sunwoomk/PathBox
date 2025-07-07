#pragma once

class StartScene : public Scene
{
public:
	StartScene();
	~StartScene();

	void Update() override;
	void Render() override;

	void SetQuads();

private:
	Quad* pathBoxQuad;
	Quad* pressToStartQuad;
};