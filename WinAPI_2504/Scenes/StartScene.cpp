#include "Framework.h"

StartScene::StartScene()
{
}

StartScene::~StartScene()
{
}

void StartScene::Update()
{
}

void StartScene::Render()
{
	float mint[4] = { 0.67f, 1.0f, 0.93f, 1.0f };
	Device::Get()->Clear(mint);
}
