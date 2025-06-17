#pragma once

class Player : public Transform 
{
public:
	Player();
	~Player();

	void Render();
	void UpdateWorld();
	void Move();

private:
	Quad* image;
};