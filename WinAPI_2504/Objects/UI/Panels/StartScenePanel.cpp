#include "Framework.h"

StartScenePanel::StartScenePanel()
{
	SetLocalPosition(Vector2(CENTER));
	SetButtons();
	UpdateWorld();
}

StartScenePanel::~StartScenePanel()
{
}

void StartScenePanel::Update()
{
	Panel::Update();
}

void StartScenePanel::Render()
{
	Panel::Render();
}

void StartScenePanel::SetButtons()
{
	Panel::CreateButton(L"Resources/UI/StartScene/SelectStage.png", Vector2(0, 0), Vector2(250, 50));
	buttons.back()->SetOnClick([this]() { SelectStageButtonClick(); });

	Panel::CreateButton(L"Resources/UI/StartScene/Options.png", Vector2(0, -100), Vector2(250, 50));
	buttons.back()->SetOnClick([this]() { OptionsButtonClick(); });

	Panel::CreateButton(L"Resources/UI/StartScene/Exit.png", Vector2(0, -200), Vector2(250, 50));
	buttons.back()->SetOnClick([this]() { ExitButtonClick(); });
}

void StartScenePanel::SelectStageButtonClick()
{
	SCENE->ChangeScene("SelectStageScene");
	UIManager::Get()->GetSelectStagePanel()->SetActive(true);
	this->SetActive(false);
}

void StartScenePanel::OptionsButtonClick()
{
}

void StartScenePanel::ExitButtonClick()
{
	exit(0);
}
