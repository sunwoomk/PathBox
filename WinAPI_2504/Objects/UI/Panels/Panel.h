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
	Panel(wstring file);
	~Panel();

	virtual void Update();
	virtual void Render();

	virtual void SetButtons() = 0;
	void CreateButton(wstring file, Vector2 pos);

protected:
	vector<Button*> buttons;

private:
	Quad* panelTexture;
};