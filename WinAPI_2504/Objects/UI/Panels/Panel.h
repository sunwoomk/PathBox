#pragma once

class Panel : public Transform
{
public:
	enum class ButtonType 
	{
		Resume,
		Restart,
		NextStage,
		SelectStage
	};
public:
	Panel(wstring file);
	~Panel();

	virtual void Update();
	virtual void Render();

	virtual void SetButtons() = 0;
	void CreateButton(ButtonType type, Vector2 pos);

protected:
	vector<Button*> buttons;

private:
	Quad* panelTexture;
};