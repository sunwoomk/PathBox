#include "Framework.h"

Panel::Panel()
{
	this->SetActive(false);
	buttons.clear();
}

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
	if (panelTexture != nullptr)
		delete panelTexture;
}

void Panel::Update()
{
	for (Button* button : buttons)
	{
		button->Update();
	}
	if (panelTexture != nullptr)
		panelTexture->UpdateWorld();
}

void Panel::Render()
{
	if (panelTexture != nullptr)
		panelTexture->Render();
	for (Button* button : buttons)
	{
		button->Render();
	}
}

void Panel::CreateButton(wstring file, Vector2 pos, Vector2 size)
{
	Button* button = new Button(file, size);
	button->SetParent(this);
	button->SetLocalPosition(pos);
	button->UpdateWorld();
	buttons.push_back(button);
}
