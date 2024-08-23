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
		Circle GetBallCollider();
		void BounceOfPlatform();
		void BounceOfTheWall();
		void BounceOfBrick(const Rectangle& brickCollider, const Circle& ballCollider);


		bool IsGameLost();


	private:
		sf::Vector2f ballPosition;
		int ballVelocityModifierX = 1;
		int ballVelocityModifierY = 1;
	};

}