#include "Ball.h"


namespace
{
	const std::string TEXTURE_PATH = "Textures/Ball.png";
}

namespace ArkanoidGame
{
	Ball::Ball(const sf::Vector2f& position, const sf::Vector2f& direction) : GameObject(SETTINGS.RESOURCES_PATH + TEXTURE_PATH, position, SETTINGS.BALL_SIZE, SETTINGS.BALL_SIZE)
	{
		const float angle = 90;
		const auto pi = std::acos(-1.f);
		if (direction == sf::Vector2f(0, 1))
		{
			this->direction.x = std::cos(pi / 180.f * angle);
			this->direction.y = std::sin(pi / 180.f * angle);
		}
		else
		{
			this->direction = direction;
		}
		
		SetBallSpeed(SETTINGS.BALL_SPEED);
	}

	void Ball::Update(float timeDelta)
	{
		const auto pos = sprite.getPosition() + ballSpeed * timeDelta * direction;
		sprite.setPosition(pos);

		if (pos.x - SETTINGS.BALL_SIZE / 2.f <= 0 || pos.x + SETTINGS.BALL_SIZE / 2.f >= SETTINGS.SCREEN_WIDTH)
		{
			direction.x *= -1;
		}
		else if (pos.y - SETTINGS.BALL_SIZE / 2.f <= 0 || pos.y + SETTINGS.BALL_SIZE / 2.f >= SETTINGS.SCREEN_HEIGHT)
		{
			direction.y *= -1;
		}
		Emit();
	}

	void Ball::InvertDirectionX()
	{
		direction.x *= -1;
	}

	void Ball::InvertDirectionY()
	{
		direction.y *= -1;
	}

	bool Ball::GetCollision(std::shared_ptr<iCollidable> collidable) const
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

	void Ball::restart()
	{
		GameObject::sprite.setPosition(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT / 2.f);
		const float angle = 90;
		const auto pi = std::acos(-1.f);
		direction.x = std::cos(pi / 180.f * angle);
		direction.y = std::sin(pi / 180.f * angle);
	}

	sf::Vector2f Ball::GetDirection() const { return direction; }

	void Ball::SetBallSpeed(float speed)
	{
		ballSpeed = speed;
	}

	void Ball::OnHit()
	{
		lastAngle += random<float>(-5, 5);
		ChangeAngle(lastAngle);
	}

	//-----------------------------------------------------------------------------//-----------------------------------------------------------------------------

	FireBallDecorator::FireBallDecorator(std::shared_ptr<Ball> ball) : Ball(ball->GetPosition(), ball->GetDirection()), decoratedBall(ball)
	{
		assert(decoratedBall);
		assert(texture.loadFromFile(SETTINGS.FIREBALL_TEXTURE_PATH));
		SetBallSpeed(SETTINGS.FIREBALL_SPEED);
	}
}