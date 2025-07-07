#include "Framework.h"

StartScene::StartScene()
{
	pressToStartQuad = new Quad(L"Resources/UI/PressToStart.png");
	pressToStartQuad->SetLocalPosition(CENTER);
	pressToStartQuad->SetActive(true);
	pressToStartQuad->UpdateWorld();

	UIManager::Get()->SetPanels();
}

StartScene::~StartScene()
{
	delete pressToStartQuad;
}

void StartScene::Update()
{
	UIManager::Get()->Update();
	if (Input::Get()->IsKeyDown(VK_LBUTTON)) 
	{
		pressToStartQuad->SetActive(false);
	}
}

void StartScene::Render()
{
	float mint[4] = { 0.67f, 1.0f, 0.93f, 1.0f };
	Device::Get()->Clear(mint);
	pressToStartQuad->Render();
}
