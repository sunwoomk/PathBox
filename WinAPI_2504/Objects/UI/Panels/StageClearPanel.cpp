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
	Panel::CreateButton(L"Resources/UI/Button/SelectStage.png", Vector2(-50, -40));
	buttons.back()->SetOnClick([this]() { SelectStageButtonClick(); });

	Panel::CreateButton(L"Resources/UI/Button/NextStage.png", Vector2(50, -40));
	buttons.back()->SetOnClick([this]() { NextStageButtonClick(); });
}

void StageClearPanel::SelectStageButtonClick()
{
	SCENE->ChangeScene("SelectStageScene"); 
	this->SetActive(false);
}

void StageClearPanel::NextStageButtonClick()
{
	int currentIndex = SCENE->GetCurrentStageIndex();
	int nextIndex = currentIndex + 1;

	SelectStagePanel* selectStagePanel = UIManager::Get()->GetSelectStagePanel();
	if (selectStagePanel && nextIndex < 10)
	{
		selectStagePanel->UnlockStage(nextIndex);
	}
	SCENE->ChangeNextStageScene();
	this->SetActive(false);
}
