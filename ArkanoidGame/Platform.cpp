#include "Platform.h"

namespace ArkanoidGame
{

	void Platform::Init()
	{
		platformPosition.x = SCREEN_WIDTH / 2.f;
		platformPosition.y = SCREEN_HEIGHT - platformHeight / 2.f;
		assert(texture.loadFromFile(RESOURCES_PATH + "Textures/" + "Platform_A.png"));
		InitSprite(sprite, platformWidth, platformHeight, texture);
		sprite.setPosition(platformPosition.x, platformPosition.y);
	}

	void Platform::MovePlatform(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && platformPosition.x > platformWidth / 2)
		{
			platformPosition.x -= PLATFORM_SPEED * timeDelta;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && platformPosition.x <SCREEN_WIDTH - platformWidth / 2)
		{
			platformPosition.x += PLATFORM_SPEED * timeDelta;
		}
	}

	//void Draw(sf::RenderWindow& window);

	Rectangle Platform::GetPlatformCollider()
	{
		return { { platformPosition.x - platformWidth / 2.f, platformPosition.y - platformHeight / 2.f },{ platformWidth, platformHeight } };
	}

	void Platform::Update(float timeDelta)
	{
		MovePlatform(timeDelta);
		sprite.setPosition(platformPosition.x, platformPosition.y);
	}

	//void Platform::Draw(sf::RenderWindow& window)
	//{
	//	window.draw(platformSprite);
	//}

}