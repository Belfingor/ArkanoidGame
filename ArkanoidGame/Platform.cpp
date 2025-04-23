#include "Platform.h"
#include <algorithm>

namespace
{
	const std::string TEXTURE_PATH = "Textures/Platform_A.png";
}

namespace ArkanoidGame
{
	Platform::Platform(const sf::Vector2f& position) : GameObject(SETTINGS.RESOURCES_PATH + TEXTURE_PATH, position, SETTINGS.PLATFORM_WIDTH, SETTINGS.PlATFORM_HEIGHT)
	{
		// Initiating evetyrhing what's needed in GameObject constructor
	}

	bool Platform::CheckCollision(std::shared_ptr<iCollidable> collidable)
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
		position.x = std::clamp(position.x + speed, SETTINGS.PLATFORM_WIDTH / 2, SETTINGS.SCREEN_WIDTH - SETTINGS.PlATFORM_HEIGHT / 2.f);
		sprite.setPosition(position);
	}

	void Platform::Update(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			MovePlatform(-timeDelta * SETTINGS.PLATFORM_SPEED);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			MovePlatform(timeDelta * SETTINGS.PLATFORM_SPEED);
		}
	}

	bool Platform::GetCollision(std::shared_ptr<iCollidable> collidable) const
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
			return sqr(ballPos.x - rect.left) + sqr(ballPos.y - rect.top) < sqr(SETTINGS.BALL_SIZE / 2.f);
		}
		if (ballPos.x > rect.left + rect.width)
		{
			return sqr(ballPos.x - rect.left - rect.width) + sqr(ballPos.y - rect.top) < sqr(SETTINGS.BALL_SIZE / 2.f);
		}
		return std::fabs(ballPos.y - rect.top) <= SETTINGS.BALL_SIZE / 2.f;
	}

	//----------------------------------------------------------------------------- Platform Decorator -----------------------------------------------------------------------------//

	WidePlatformDecorator::WidePlatformDecorator(std::shared_ptr<Platform> platform) : Platform(platform->GetPosition()), decoratedPlatform(platform)
	{
		assert(decoratedPlatform);
		SetSpriteSize(sprite, SETTINGS.WIDE_PLATFORM_WDTH, SETTINGS.WIDE_PLATFORM_HEIGHT);
	}

}