#include "Ball.h"


namespace
{
	const std::string TEXTURE_PATH = "Textures/Ball.png";
}

namespace ArkanoidGame
{
	Ball::Ball(const sf::Vector2f& position) : GameObject(RESOURCES_PATH + TEXTURE_PATH, position, BALL_SIZE, BALL_SIZE)
	{
		const float angle = 90;
		const auto pi = std::acos(-1.f);
		direction.x = std::cos(pi / 180.f * angle);
		direction.y = std::sin(pi / 180.f * angle);
	}

	void Ball::Update(float timeDelta)
	{
		const auto pos = sprite.getPosition() + BALL_SPEED * timeDelta * direction;
		sprite.setPosition(pos);
 
		if (pos.x - BALL_SIZE / 2.f <= 0 || pos.x + BALL_SIZE / 2.f >= SCREEN_WIDTH)
		{
			direction.x *= -1;
		}
		if (pos.y - BALL_SIZE / 2.f <= 0 || pos.y + BALL_SIZE / 2.f >= SCREEN_HEIGHT)
		{
			direction.y *= -1;
		}
	}

	void Ball::InvertDirectionX()
	{
		direction.x *= -1;
	}

	void Ball::InvertDirectionY()
	{
		direction.y *= -1;
	}

	bool Ball::GetCollision(std::shared_ptr<Collidable> collidable) const
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidable);
		assert(gameObject);
		return GetRect().intersects(gameObject->GetRect());
	}

	void Ball::ChangeAngle(float angle)
	{
		lastAngle = angle;
		const auto pi = std::acos(-1.f);
		direction.x = (angle / abs(angle)) * std::cos(pi / 180.f * angle);
		direction.y = -1 * abs(std::sin(pi / 180.f * angle));
	}

	bool Ball::IsGameLost()
	{
		return direction.y > SCREEN_HEIGHT;
	}

	void Ball::OnHit()
	{
		lastAngle += random<float>(-5, 5);
		ChangeAngle(lastAngle);
	}

}