#pragma once
#include <SFML/Graphics.hpp>
#include <cassert>
#include "GameSettings.h"
#include "Sprite.h"
#include "Math.h"
#include "GameObject.h"


namespace ArkanoidGame
{
	class Ball : public GameObject
	{
	public:
		void Init() override;
		void Update(float timeDelta)override;
		//void Draw(sf::RenderWindow& window);
		Circle GetBallCollider();
		void BounceOfPlatform();
		void BounceOfTheWall();

		bool IsGameLost();


	private:
		/*sf::Sprite ballSprite;
		sf::Texture ballTexture;*/
		sf::Vector2f ballPosition;
		int ballVelocityModifierX = 1;
		int ballVelocityModifierY = 1;
	};

}