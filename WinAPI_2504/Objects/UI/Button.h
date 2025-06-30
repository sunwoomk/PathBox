#pragma once

class Button : public RectCollider 
{
public:
	Button(wstring file, Vector2 pos);
	~Button();

	void Update();
	void Render();

	void SetOnClick(function<void()> onClickFunc) { onClick = onClickFunc; }

private:
	Quad* image;
	function<void()> onClick;
};