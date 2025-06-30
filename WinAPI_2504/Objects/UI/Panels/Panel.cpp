#include "Framework.h"

Panel::Panel(wstring file)
{
	panelTexture = new Quad(file);
	buttons.clear();
}

Panel::~Panel()
{
	delete panelTexture;
}

void Panel::Update()
{
}

void Panel::Render()
{
	panelTexture->Render();
}

void Panel::CreateButton(ButtonType type, Vector2 pos)
{
	Button* button = nullptr;
	switch (type)
	{
	case Panel::ButtonType::Resume:
		button = new ResumeButton();
		break;
	case Panel::ButtonType::Restart:
		button = new RestartButton();
		break;
	case Panel::ButtonType::NextStage:
		button = new NextStageButton();
		break;
	case Panel::ButtonType::SelectStage:
		button = new SelectStageButton();
		break;
	}

	if (button) 
	{
		button->SetParent(this);
		button->SetLocalPosition(pos);
		button->UpdateWorld();
		buttons.push_back(button);
	}
}
