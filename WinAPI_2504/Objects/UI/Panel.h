#pragma once

class Panel : public Transform
{
public:
	Panel(wstring file);
	~Panel();

	void Update();
	void Render();

private:
	Quad* panelTexture;
};