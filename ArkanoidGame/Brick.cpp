#include "Brick.h"

namespace
{
	const std::string TEXTURE_PATH = "Textures/Standard_Brick.png";
}

namespace ArkanoidGame
{
	void Brick::OnHit()
	{
		hitCount -= 1;
	}
	Brick::Brick(const sf::Vector2f& position) : GameObject(RESOURCES_PATH + TEXTURE_PATH, position, BRICK_WIDTH, BRICK_HEIGHT)
	{
	}
	Brick::~Brick()
	{

	}
	bool Brick::GetCollision(std::shared_ptr<Collidable> collidable) const
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidable);
		assert(gameObject);
		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1;
		return GetRect().intersects(gameObject->GetRect());
	}
	void Brick::Update(float timeDelta)
	{

	}
	bool Brick::IsBroken()
	{
		return hitCount <= 0;
	}
	/*Rectangle Brick::GetBrickCollider()
	{
		return { { brickPosition.x - BRICK_WIDTH / 2.f, brickPosition.y - BRICK_HEIGHT / 2.f },{ BRICK_WIDTH, BRICK_HEIGHT } };
	}
	void Brick::SetPosition(sf::Vector2f position)
	{
		brickPosition = position;
	}*/
}