#include "Framework.h"

MenuPanel::MenuPanel() : Panel(L"Resources/UI/Panel/MenuPanel.png")
{
	SetButtons();
}

MenuPanel::~MenuPanel()
{
}

void MenuPanel::Update()
{
}

void MenuPanel::Render()
{
}

void MenuPanel::SetButtons()
{
	float panelWidth = GetLocalScale().x;
	float panelHeight = GetLocalScale().y;
	float buttonWidth = 64.0f;
	float buttonHeight = 64.0f;

	Panel::CreateButton(ButtonType::Restart, Vector2(buttonWidth, buttonHeight));
	Panel::CreateButton(ButtonType::Resume, Vector2(panelWidth * 0.5f, panelHeight * 0.5f));
	Panel::CreateButton(ButtonType::SelectStage, Vector2(panelWidth - buttonWidth, panelHeight - buttonHeight));
}
