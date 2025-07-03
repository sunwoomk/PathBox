#include "Framework.h"

MenuPanel::MenuPanel(TileMaps* tileMaps) : Panel(L"Resources/UI/Panel/MenuPanel.png")
{
	this->tileMaps = tileMaps;
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
	Panel::CreateButton(L"Resources/UI/Button/Restart.png", Vector2(-60, -40));
	//buttons.back()->SetOnClick(bind(&TileMaps::Restart, tileMaps));
	buttons.back()->SetOnClick([this]() { tileMaps->Restart(); this->SetActive(false); });

	Panel::CreateButton(L"Resources/UI/Button/Resume.png", Vector2(-10, 10));
	buttons.back()->SetOnClick([this]() { this->SetActive(false); });

	Panel::CreateButton(L"Resources/UI/Button/SelectStage.png", Vector2(40, -40));
	buttons.back()->SetOnClick([this]() { SCENE->ChangeScene("SelectStageScene"); this->SetActive(false); });
}
