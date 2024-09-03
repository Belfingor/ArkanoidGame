#include "Platform.h"
#include <algorithm>

namespace
{
	const std::string TEXTURE_PATH = "Textures/Platform_A.png";
}

namespace ArkanoidGame
{
	Platform::Platform(const sf::Vector2f& position) : GameObject(RESOURCES_PATH + TEXTURE_PATH, position, PLATFORM_WIDTH, PlATFORM_HEIGHT)
	{
		// Initiating evetyrhing what's needed in GameObject constructor
	}

	bool Platform::CheckCollision(std::shared_ptr<Collidable> collidable)
	{
		auto ball = std::static_pointer_cast<Ball>(collidable);
		if (!ball) return false;

		if (GetCollision(ball))
		{
			auto rect = GetRect();
			auto ballPosOnPlatform = (ball->GetPosition().x - (rect.left + rect.width / 2.f)) / (rect.width / 2);
			ball->ChangeAngle(90 - 20 * ballPosOnPlatform);
			return true;
		}
	}

	void Platform::MovePlatform(float speed)
	{
		auto position = sprite.getPosition();
		position.x = std::clamp(position.x + speed, PLATFORM_WIDTH / 2, SCREEN_WIDTH - PlATFORM_HEIGHT / 2.f);
		sprite.setPosition(position);
	}

	void Platform::Update(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			MovePlatform(-timeDelta * PLATFORM_SPEED);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			MovePlatform(timeDelta * PLATFORM_SPEED);
		}
	}

	bool Platform::GetCollision(std::shared_ptr<Collidable> collidable) const
	{
		auto ball = std::static_pointer_cast<Ball>(collidable);
		if (!ball) return false;

		auto sqr = [](float x)
			{
				return x * x;
			};
		const auto rect = sprite.getGlobalBounds();
		const auto ballPos = ball->GetPosition();
		if (ballPos.x < rect.left)
		{
			return sqr(ballPos.x - rect.left) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.f);
		}
		if (ballPos.x > rect.left + rect.width)
		{
			return sqr(ballPos.x - rect.left - rect.width) + sqr(ballPos.y - rect.top) < sqr(BALL_SIZE / 2.f);
		}
		return std::fabs(ballPos.y - rect.top) <= BALL_SIZE / 2.f;
	}

}