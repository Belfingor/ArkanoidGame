#pragma once
#include <cassert>
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Sprite.h"
#include "Math.h"

namespace ArkanoidGame
{

	class Platform
	{
	public:
		void Init();
		void MovePlatform(float timeDelta);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
		Rectangle GetPlatformCollider()
		{
			return {{platformPosition.x - platformWidth / 2.f, platformPosition.y - platformHeight / 2.f}, {platformWidth, platformHeight}};
		}

	private:
		sf::Sprite platformSprite;
		sf::Texture platformTexture;
		sf::Vector2f platformPosition{ SCREEN_WIDTH / 2.f - platformWidth / 2.f, SCREEN_HEIGHT - platformHeight / 2 };
		float platformHeight = PlATFORM_SIZE * 24.f;
		float platformWidth = PlATFORM_SIZE * 64.f;
 	};
}