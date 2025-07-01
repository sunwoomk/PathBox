#include "Framework.h"

Button::Button(wstring file)
{
	buttonTexture = new Quad(file);
	buttonTexture->SetParent(this);
}

Button::~Button()
{
	delete buttonTexture;
}

void Button::Update()
{
	if (IsPointCollision(mousePos)) 
	{
		if (Input::Get()->IsKeyPress(VK_LBUTTON)) 
		{
			buttonTexture->SetColor(0.5f, 0.5f, 0.5f, 1.0f);
		}
		else if (Input::Get()->IsKeyUp(VK_LBUTTON)) 
		{
			buttonTexture->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			if (onClick) 
				onClick();
		}
		else 
		{
			buttonTexture->SetColor(0.8f, 0.8f, 0.8f, 1.0f);
		}


	}
	else 
	{
		buttonTexture->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	buttonTexture->UpdateWorld();
	RectCollider::UpdateWorld();
}

void Button::Render()
{
	RectCollider::Render();
	buttonTexture->Render();
}
