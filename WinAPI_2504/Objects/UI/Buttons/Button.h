#pragma once

class Button : public RectCollider 
{
public:
	Button(wstring file, Vector2 size);
	~Button();

	virtual void Update();
	virtual void Render();

	void SetOnClick(function<void()> onClickFunc) { onClick = onClickFunc; }

private:
	Quad* buttonTexture;
	function<void()> onClick;
};