#pragma once
#include <SFML/Graphics.hpp>
#include <cassert>
#include "GameSettings.h"
#include "Sprite.h"
#include "Math.h"
#include "GameObject.h"
#include "Collidable.h"
#include "randomizer.h"

namespace ArkanoidGame
{
	class Ball final : public GameObject, public Collidable
	{
	public:
		Ball(const sf::Vector2f& position);
		~Ball() = default;
		void Update(float timeDelta) override;
		//--------------------------------------------------------------------------------
		void InvertDirectionX();
		void InvertDirectionY();
		//--------------------------------------------------------------------------------
		bool GetCollision(std::shared_ptr<Collidable> collidable) const override;
		void ChangeAngle(float angle);
		bool IsGameLost();

	private:
		void OnHit();
		sf::Vector2f direction;
		float lastAngle = 90.f;
	};

}