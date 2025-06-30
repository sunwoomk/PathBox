#include "Framework.h"

StageClearPanel::StageClearPanel() : Panel(L"Resources/UI/Panel/ClearPanel.png")
{
	SetButtons();
}

StageClearPanel::~StageClearPanel()
{
}

void StageClearPanel::Update()
{
}

void StageClearPanel::Render()
{
}

void StageClearPanel::SetButtons()
{
	float panelWidth = GetLocalScale().x;
	float panelHeight = GetLocalScale().y;
	float buttonWidth = 64.0f;
	float buttonHeight = 64.0f;

	Panel::CreateButton(ButtonType::Restart, Vector2(buttonWidth, buttonHeight));
	Panel::CreateButton(ButtonType::NextStage, Vector2(panelWidth * 0.5f, panelHeight * 0.5f));
	Panel::CreateButton(ButtonType::SelectStage, Vector2(panelWidth - buttonWidth, panelHeight - buttonHeight));
}
