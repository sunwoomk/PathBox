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

	void CreateScene(string file, string key);
	void SetScenes();

private:
	HDC hdc;	

	HDC backBufferDC;
	HBITMAP backBufferBitmap;
};