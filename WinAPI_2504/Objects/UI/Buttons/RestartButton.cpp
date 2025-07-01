#include "Framework.h"

RestartButton::RestartButton() : Button(L"Resources/UI/Button/Restart.png")
{
}

RestartButton::~RestartButton()
{
}

void RestartButton::Update()
{
	Button::Update();
}

void RestartButton::Render()
{
	Button::Render();
}
