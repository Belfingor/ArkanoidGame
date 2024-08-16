#pragma once
#include <SFML/Graphics.hpp>
#include <cassert>
#include "GameSettings.h"
#include "Sprite.h"
#include "Math.h"


namespace ArkanoidGame
{
	class Ball
	{
	public:
		void Init();
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
		Circle GetBallCollider();
		void BounceOfPlatform();
		void BounceOfTheWall();

		bool IsGameLost();


	private:
		sf::Sprite ballSprite;
		sf::Texture ballTexture;
		sf::Vector2f ballPosition;
		int ballVelocityXModifier = 1;
		int ballVelocityYModifier = 1;
	};

}