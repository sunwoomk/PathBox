#pragma once

class Button : public RectCollider 
{
public:
	Button(wstring file, Vector2 pos = Vector2(0, 0));
	~Button();

	virtual void Update();
	virtual void Render();

	void SetOnClick(function<void()> onClickFunc) { onClick = onClickFunc; }

private:
	Quad* buttonTexture;
	function<void()> onClick;
};