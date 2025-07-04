#include "Framework.h"

GameManager::GameManager()
{
	Create();

	SetStageScenes();

	SCENE->AddScene("EditScene", new TileEditScene());
	SCENE->AddScene("SelectStageScene", new SelectStageScene());

	SCENE->ChangeScene("Stage1");
	//SCENE->ChangeScene("EditScene");
	//SCENE->ChangeScene("SelectStageScene");
}

GameManager::~GameManager()
{
	Release();
}

void GameManager::Update()
{
	if (Input::Get()->IsKeyDown(VK_F1)) 
	{
		SCENE->ChangeScene("Stage1");
	}
	if (Input::Get()->IsKeyDown(VK_F2))
	{
		SCENE->ChangeScene("Stage2");
	}
	if (Input::Get()->IsKeyDown(VK_F3))
	{
		SCENE->ChangeScene("Stage3");
	}
	if (Input::Get()->IsKeyDown(VK_F4))
	{
		SCENE->ChangeScene("Stage4");
	}
	if (Input::Get()->IsKeyDown(VK_F5))
	{
		SCENE->ChangeScene("Stage5");
	}
	if (Input::Get()->IsKeyDown(VK_F6))
	{
		SCENE->ChangeScene("Stage6");
	}
	if (Input::Get()->IsKeyDown(VK_F7))
	{
		SCENE->ChangeScene("Stage7");
	}
	if (Input::Get()->IsKeyDown(VK_F8))
	{
		SCENE->ChangeScene("Stage8");
	}
	if (Input::Get()->IsKeyDown(VK_F9))
	{
		SCENE->ChangeScene("EditScene");
	}
	Timer::Get()->Update();
	Input::Get()->Update();
	Audio::Get()->Update();

	Environment::Get()->Update();

	SCENE->Update();

	InvalidateRect(hWnd, nullptr, false);
}

void GameManager::Render()
{
	SCENE->PreRender();
	
	Environment::Get()->SetViewport();
	Device::Get()->Clear();	

	SCENE->Render();

	Environment::Get()->SetUIViewBuffer();
	SCENE->PostRender();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	string fps = "FPS : " + to_string(Timer::Get()->GetFPS());
	ImGui::Text(fps.c_str());

	SCENE->GUIRender();	

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	Device::Get()->Present();
}

void GameManager::Create()
{
	Timer::Get();
	Input::Get();
	Audio::Get();

	Device::Get();

	SceneManager::Get();

	Environment::Get();

	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX11_Init(DEVICE, DC);
}

void GameManager::Release()
{
	Timer::Delete();
	Input::Delete();

	Device::Delete();
	Shader::Delete();
	Texture::Delete();
	Audio::Delete();

	SceneManager::Delete();

	Environment::Delete();

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();

	ImGui::DestroyContext();
}

void GameManager::CreateStageScene(string file, wstring backgroundFile, string key)
{
	TestScene* stageScene = new TestScene(file, backgroundFile);
	SCENE->AddScene(key, stageScene);
	SCENE->AddStageScene(stageScene);
	stageScene->SetKey(key);
}

void GameManager::SetStageScenes()
{
	CreateStageScene("Resources/StageData/Stage1.map", L"Resources/Background/Meadow1.png", "Stage1");
	CreateStageScene("Resources/StageData/Stage2.map", L"Resources/Background/Mountain1.png", "Stage2");
	CreateStageScene("Resources/StageData/Stage3.map", L"Resources/Background/Meadow2.png", "Stage3");
	CreateStageScene("Resources/StageData/Stage4.map", L"Resources/Background/SnowyMountain4.png", "Stage4");
	CreateStageScene("Resources/StageData/Stage5.map", L"Resources/Background/SnowyMountain2.png", "Stage5");
	CreateStageScene("Resources/StageData/Stage6.map", L"Resources/Background/Meadow3.png", "Stage6");
	CreateStageScene("Resources/StageData/Stage7.map", L"Resources/Background/Beach1.png", "Stage7");
	CreateStageScene("Resources/StageData/Stage8.map", L"Resources/Background/SnowyMountain3.png", "Stage8");
}
