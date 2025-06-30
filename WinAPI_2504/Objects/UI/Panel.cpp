#include "Framework.h"

Panel::Panel(wstring file)
{
	panelTexture = new Quad(file);
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
