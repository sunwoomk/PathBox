#include "Framework.h"

Panel::Panel(wstring file)
{
	panelTexture = new Quad(file);
	panelTexture->SetParent(this);
	panelTexture->SetLocalPosition(Vector2(0, 0));
	panelTexture->UpdateWorld();
	this->SetActive(false);
	buttons.clear();
}

Panel::~Panel()
{
	delete panelTexture;
}

void Panel::Update()
{
	for (Button* button : buttons)
	{
		button->Update();
	}
	panelTexture->UpdateWorld();
}

void Panel::Render()
{
	panelTexture->Render();
	for (Button* button : buttons)
	{
		button->Render();
	}
}

void Panel::CreateButton(wstring file, Vector2 pos)
{
	Button* button = new Button(file);
	button->SetParent(this);
	button->SetLocalPosition(pos);
	button->UpdateWorld();
	buttons.push_back(button);
}
