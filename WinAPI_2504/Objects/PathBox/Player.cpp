#include "Framework.h"

Player::Player()
{
	image = new Quad(L"Resources/Textures/Tiles/cart_top.png");
	image->SetParent(this);
	//image->SetLocalPosition(Vector2(startX, startY));
}

Player::~Player()
{
	delete image;
}

void Player::Render()
{	
	image->Render();
}

void Player::UpdateWorld()
{
	Transform::UpdateWorld();
	image->UpdateWorld();
}

void Player::Move()
{	

}
