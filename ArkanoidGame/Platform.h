#pragma once
#include <cassert>
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Sprite.h"
#include "Math.h"
#include "GameObject.h"
#include "iCollidable.h"
#include "Ball.h"

namespace ArkanoidGame
{

	class Platform : public GameObject, public iCollidable
	{
	public:
		Platform(const sf::Vector2f& position);
		~Platform() = default;
		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<iCollidable> collidable)const override;
		void OnHit() override
		{
			// Nothing to change here regarding the platform
		}
		bool CheckCollision(std::shared_ptr<iCollidable> collidable) override;

	private:

		void MovePlatform(float speed);
 	};

	//----------------------------------------------------------------------------- Platform Decorator -----------------------------------------------------------------------------//

	class WidePlatformDecorator final : public Platform
	{
	protected:
		std::shared_ptr<Platform> decoratedPlatform;
	public:
		WidePlatformDecorator(std::shared_ptr<Platform> platform);
	};


}