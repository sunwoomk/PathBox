#include "Framework.h"

MenuPanel::MenuPanel() : Panel(L"Resources/UI/Panel/MenuPanel.png")
{
	SetLocalPosition(Vector2(CENTER));
	SetButtons();
}

MenuPanel::~MenuPanel()
{
}

void MenuPanel::Update()
{
	Panel::Update();
}

void MenuPanel::Render()
{
	Panel::Render();
}

void MenuPanel::SetButtons()
{
	Panel::CreateButton(ButtonType::Restart, Vector2(-60, -40));
	Panel::CreateButton(ButtonType::Resume, Vector2(-10, 10));
	Panel::CreateButton(ButtonType::SelectStage, Vector2(40, -40));
}
