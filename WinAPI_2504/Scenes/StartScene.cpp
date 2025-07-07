#include "Framework.h"

StartScene::StartScene()
{
	SetQuads();

	UIManager::Get()->SetPanels();
}

StartScene::~StartScene()
{
	delete pathBoxQuad;
	delete pressToStartQuad;
}

void StartScene::Update()
{
	UIManager::Get()->Update();
	if (Input::Get()->IsKeyDown(VK_LBUTTON)) 
	{
		pressToStartQuad->SetActive(false);
		UIManager::Get()->SetPanelActive("StartScenePanel", true);
	}
}

void StartScene::Render()
{
	float ivory[4] = { 1.0f, 0.97f, 0.90f, 1.0f };
	Device::Get()->Clear(ivory);
	pathBoxQuad->Render();
	pressToStartQuad->Render();
	UIManager::Get()->Render();
}

void StartScene::SetQuads()
{
	pathBoxQuad = new Quad(L"Resources/UI/StartScene/PathBox.png");
	pathBoxQuad->SetLocalPosition(CENTER + Vector2(0, 200));
	pathBoxQuad->SetActive(true);
	pathBoxQuad->UpdateWorld();

	pressToStartQuad = new Quad(L"Resources/UI/StartScene/PressToStart.png");
	pressToStartQuad->SetLocalPosition(CENTER - Vector2(0, 100));
	pressToStartQuad->SetActive(true);
	pressToStartQuad->UpdateWorld();
}
