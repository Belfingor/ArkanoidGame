#pragma once
#include <SFML/Graphics.hpp>
#include <cassert>
#include "GameSettings.h"
#include "Sprite.h"
#include "Math.h"
#include "GameObject.h"
#include "iCollidable.h"
#include "randomizer.h"

namespace ArkanoidGame
{
	class Ball final : public GameObject, public iCollidable
	{
	public:
		Ball(const sf::Vector2f& position);
		~Ball() = default;
		void Update(float timeDelta) override;
		//--------------------------------------------------------------------------------
		void InvertDirectionX();
		void InvertDirectionY();
		//--------------------------------------------------------------------------------
		bool GetCollision(std::shared_ptr<iCollidable> collidable) const override;
		void ChangeAngle(float angle);
		bool IsGameLost();

	private:
		void OnHit();
		sf::Vector2f direction;
		float lastAngle = 90.f;
	};

}