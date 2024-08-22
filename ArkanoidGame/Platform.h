#pragma once
#include <cassert>
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Sprite.h"
#include "Math.h"
#include "GameObject.h"

namespace ArkanoidGame
{

	class Platform : public GameObject
	{
	public:
		void Init() override;
		void Update(float timeDelta) override;
		void MovePlatform(float timeDelta);
		//void Draw(sf::RenderWindow& window);
		Rectangle GetPlatformCollider();

	private:
		/*sf::Sprite platformSprite;
		sf::Texture platformTexture;*/
		sf::Vector2f platformPosition{ SCREEN_WIDTH / 2.f - platformWidth / 2.f, SCREEN_HEIGHT - platformHeight / 2 };
		float platformHeight = PlATFORM_SIZE * 24.f;
		float platformWidth = PlATFORM_SIZE * 64.f;
 	};
}