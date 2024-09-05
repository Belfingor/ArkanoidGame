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
	Brick::Brick(const sf::Vector2f& position, const sf::Color& color) : GameObject(RESOURCES_PATH + TEXTURE_PATH, position, BRICK_WIDTH, BRICK_HEIGHT)
	{
		sprite.setColor(color);
	}
	Brick::~Brick()
	{

	}
	bool Brick::GetCollision(std::shared_ptr<iCollidable> collidable) const
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
	void SmoothDestroyBrick::OnHit()
	{
		StartTimer(BRICK_BREAK_DELAY);
	}

	//--------------------------------------------------------------------------------//--------------------------------------------------------------------------------
	SmoothDestroyBrick::SmoothDestroyBrick(const sf::Vector2f& position, const sf::Color& color) : Brick(position, color), color(color) 
	{

	}
	void SmoothDestroyBrick::Update(float timeDelta)
	{
		UpdateTimer(timeDelta);
	}
	bool SmoothDestroyBrick::GetCollision(std::shared_ptr<iCollidable> collidableObject) const
	{
		if (isTimerStarted_)
		{
			return false;
		}

		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1f;
		return GetRect().intersects(gameObject->GetRect());
	}
	void SmoothDestroyBrick::FinalAction()
	{
		--hitCount;
	}
	void SmoothDestroyBrick::EachTickAction(float deltaTime)
	{
		color.a = 255 * currentTime_ / destroyTime_;
		sprite.setColor(color);
	}
	//--------------------------------------------------------------------------------//--------------------------------------------------------------------------------
	UnbreackableBrick::UnbreackableBrick(const sf::Vector2f& position) : Brick(position, sf::Color::Color(105, 105, 105))
	{

	}
	void UnbreackableBrick::OnHit()
	{
		// Not changing hitCount here as brick is unbeakable
	}
	void UnbreackableBrick::Update(float deltaTime)
	{
		// Do nothing
	}
}
	