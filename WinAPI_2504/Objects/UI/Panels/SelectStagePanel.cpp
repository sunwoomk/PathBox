#include "Framework.h"

SelectStagePanel::SelectStagePanel() : Panel(L"Resources/UI/Panel/SelectStagePanel.png")
{
	SetLocalPosition(Vector2(CENTER));
	SetButtons();
}

SelectStagePanel::~SelectStagePanel()
{
}

void SelectStagePanel::Update()
{
	Panel::Update();
}

void SelectStagePanel::Render()
{
	Panel::Render();
	for (Quad* unlockTexture : unlockTextures)
	{
		if (unlockTexture->IsActive())
			unlockTexture->Render();
	}
}

void SelectStagePanel::SetButtons()
{
	unlockTextures.clear();
	unlockTextures.resize(STAGE_COUNT);
	for (int i = 0; i < STAGE_COUNT; i++) 
	{
		Quad* unlockTexture = new Quad(L"Resources/UI/Button/UnlockStage.png");
		unlockTexture->SetParent(this);
		unlockTexture->SetLocalPosition(Vector2(390 + (i % 5) * 130, 450 - (i / 5) * 200));
		unlockTexture->UpdateWorld();
		unlockTextures[i] = unlockTexture;
		if (i == 0)
			unlockTexture->SetActive(false);
	}

	for (int i = 0; i < STAGE_COUNT; i++)
	{
		Panel::CreateButton(L"Resources/UI/Button/Stage" + to_wstring(i + 1) + L".png", Vector2(-250 + (i % 5) * 130, 90 - (i / 5) * 200));
		buttons.back()->SetOnClick([this, i]()
			{
				if (unlockTextures[i]->IsActive() == false)
				{
					SCENE->ChangeScene("Stage" + to_string(i + 1));
					this->SetActive(false);
				}
			});
	}
}

void SelectStagePanel::UnlockStage(int index)
{
	if (index < 0 || index >= STAGE_COUNT) return;
	unlockTextures[index]->SetActive(false);
}
