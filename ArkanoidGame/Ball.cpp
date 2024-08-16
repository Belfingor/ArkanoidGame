#include "Ball.h"


namespace ArkanoidGame
{



	void ArkanoidGame::Ball::Init()
	{
		assert(ballTexture.loadFromFile(RESOURCES_PATH + "Textures/" + "Ball.png"));
		InitSprite(ballSprite, BALL_SIZE, BALL_SIZE, ballTexture);
		ballPosition = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		ballSprite.setPosition(ballPosition.x, ballPosition.y);
	}

	void Ball::Update(float timeDelta)
	{
		ballPosition = { (ballPosition.x + BALL_SPEED * ballVelocityXModifier * timeDelta) ,
						 (ballPosition.y + BALL_SPEED * ballVelocityYModifier * timeDelta) };
		ballSprite.setPosition(ballPosition.x, ballPosition.y);
		Ball::BounceOfTheWall();
	}

	void Ball::Draw(sf::RenderWindow& window)
	{
		window.draw(ballSprite);
	}

	Circle Ball::GetBallCollider()
	{
		return{ { ballPosition.x, ballPosition.y }, BALL_SIZE / 2 };
	}

	void Ball::BounceOfPlatform()
	{
		ballVelocityYModifier *= -1;
	}

	void Ball::BounceOfTheWall()
	{
		if (ballPosition.x > SCREEN_WIDTH - BALL_SIZE / 2 || ballPosition.x < BALL_SIZE / 2)
		{
			ballVelocityXModifier *= -1;
		}
		if (ballPosition.y < BALL_SIZE / 2)
		{
			ballVelocityYModifier *= -1;
		}
	}

	bool Ball::IsGameLost()
	{
		return ballPosition.y > SCREEN_HEIGHT;
	}

}