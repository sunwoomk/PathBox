#include "Framework.h"

Button::Button(wstring file, Vector2 pos)
{
	image = new Quad(file);
	image->SetParent(this);
	SetLocalPosition(pos);
	UpdateWorld();
}

Button::~Button()
{
	delete image;
}

void Button::Update()
{
	if (IsPointCollision(mousePos)) 
	{
		if (Input::Get()->IsKeyPress(VK_LBUTTON)) 
		{
			image->SetColor(0.5f, 0.5f, 0.5f, 1.0f);
		}
		else if (Input::Get()->IsKeyUp(VK_LBUTTON)) 
		{
			image->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			if (onClick) 
				onClick();
		}
		else 
		{
			image->SetColor(0.8f, 0.8f, 0.8f, 1.0f);
		}


	}
	else 
	{
		image->SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	}
	image->UpdateWorld();
	RectCollider::UpdateWorld();
}

void Button::Render()
{
	RectCollider::Render();
	image->Render();
}
