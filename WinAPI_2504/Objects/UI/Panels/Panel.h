#pragma once

class Panel : public Quad
{
//public:
//	enum class ButtonType 
//	{
//		Resume,
//		Restart,
//		NextStage,
//		SelectStage
//	};
public:
	Panel();
	Panel(wstring file);
	~Panel();

	virtual void Update();
	virtual void Render();

	virtual void SetButtons() = 0;
	void CreateButton(wstring file, Vector2 pos, Vector2 size = Vector2(50, 50));

protected:
	vector<Button*> buttons;

private:
	Quad* panelTexture = nullptr;
};