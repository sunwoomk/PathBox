#include "Framework.h"

StageClearPanel::StageClearPanel() : Panel(L"Resources/UI/Panel/ClearPanel.png")
{
	SetLocalPosition(Vector2(CENTER));
	SetButtons();
}

StageClearPanel::~StageClearPanel()
{
}

void StageClearPanel::Update()
{
	Panel::Update();
}

void StageClearPanel::Render()
{
	Panel::Render();
}

void StageClearPanel::SetButtons()
{
	Panel::CreateButton(ButtonType::SelectStage, Vector2(-50, -40));
	//buttons.back()->SetOnClick([this]() { UIManager::Get()->SwitchMenuPanel(); });
	Panel::CreateButton(ButtonType::NextStage, Vector2(50, -40));
}
