#pragma once

class GameManager
{
public:
	GameManager();
	~GameManager();

	void Update();
	void Render();

private:
	void Create();
	void Release();

	void CreateStageScene(string file, string key);
	void SetScenes();
	void SetStageScenes();

private:
	HDC hdc;	

	HDC backBufferDC;
	HBITMAP backBufferBitmap;
};