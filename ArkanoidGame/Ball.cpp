#include "Ball.h"


namespace ArkanoidGame
{
	void ArkanoidGame::Ball::Init()
	{
		assert(texture.loadFromFile(RESOURCES_PATH + "Textures/" + "Ball.png"));
		InitSprite(sprite, BALL_SIZE, BALL_SIZE, texture);
		ballPosition = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		sprite.setPosition(ballPosition.x, ballPosition.y);
	}

	void Ball::Update(float timeDelta)
	{
		ballPosition = { (ballPosition.x + BALL_SPEED * ballVelocityModifierX * timeDelta) ,
						 (ballPosition.y + BALL_SPEED * ballVelocityModifierY * timeDelta) };
		sprite.setPosition(ballPosition.x, ballPosition.y);
		Ball::BounceOfTheWall();
	}

	Circle Ball::GetBallCollider()
	{
		return{ { ballPosition.x, ballPosition.y }, BALL_SIZE / 2 };
	}

	void Ball::BounceOfPlatform()
	{
		ballVelocityModifierY *= -1;
	}

	void Ball::BounceOfTheWall()
	{
		if (ballPosition.x > SCREEN_WIDTH - BALL_SIZE / 2 || ballPosition.x < BALL_SIZE / 2)
		{
			ballVelocityModifierX *= -1;
		}
		if (ballPosition.y < BALL_SIZE / 2)
		{
			ballVelocityModifierY *= -1;
		}
	}

	void Ball::BounceOfBrick(const Rectangle& brickCollider, const Circle& ballCollider)
	{
		 // Calculate the normal vector to the brick
		float brickNormalX = (ballCollider.center.x - brickCollider.center.x);
		float brickNormalY = (ballCollider.center.y - brickCollider.center.y);

		// If the ball collided with the left or right of the brick, reverse the x velocity
		if (brickNormalX + ballCollider.radius> BRICK_WIDTH / 2 || brickNormalX - ballCollider.radius < -BRICK_WIDTH / 2)
		{
			ballVelocityModifierX *= -1;
		}

		// Same for y velocity
		if (brickNormalY + ballCollider.radius > BRICK_HEIGHT / 2 || brickNormalY - ballCollider.radius < -BRICK_HEIGHT / 2)
		{
			ballVelocityModifierY *= -1;
		}
	
	}

	bool Ball::IsGameLost()
	{
		return ballPosition.y > SCREEN_HEIGHT;
	}

}