#pragma once
#include <cassert>
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Sprite.h"
#include "Math.h"
#include "GameObject.h"
#include "Collidable.h"
#include "Ball.h"

namespace ArkanoidGame
{

	class Platform final : public GameObject, public Collidable
	{
	public:
		Platform(const sf::Vector2f& position);
		~Platform() = default;
		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<Collidable> collidable)const override;
		void OnHit() override
		{
			// Nothing to change here regarding the platform
		}
		bool CheckCollision(std::shared_ptr<Collidable> collidable) override;

	private:

		void MovePlatform(float speed);
 	};
}