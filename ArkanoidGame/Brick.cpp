#include "Brick.h"

namespace ArkanoidGame
{
	void Brick::Init()
	{
		assert(texture.loadFromFile(RESOURCES_PATH + "Textures/" + "Standard_Brick.png"));
		InitSprite(sprite, BRICK_WIDTH, BRICK_HEIGHT, texture);
		sprite.setPosition(brickPosition.x, brickPosition.y);
	}
	void Brick::Update(float timeDelta)
	{

	}
	Rectangle Brick::GetBrickCollider()
	{
		return { { brickPosition.x - BRICK_WIDTH / 2.f, brickPosition.y - BRICK_HEIGHT / 2.f },{ BRICK_WIDTH, BRICK_HEIGHT } };
	}
	void Brick::SetPosition(sf::Vector2f position)
	{
		brickPosition = position;
	}
}