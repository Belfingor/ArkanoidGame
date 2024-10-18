#pragma once
#include <SFML/Graphics.hpp>
#include <cassert>
#include "GameSettings.h"
#include "Sprite.h"
#include "Math.h"
#include "GameObject.h"
#include "iCollidable.h"
#include "randomizer.h"
#include "IObserver.h"

namespace ArkanoidGame
{
	class Ball final : public GameObject, public iCollidable, public IObservable
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
		bool IsGameLost();    //////Delete this func from here, to be replaced in Game.h
		void restart() override;
		int playersLives = SETTINGS.PLAYER_LIVES;

	private:
		void OnHit();
		sf::Vector2f direction;
		float lastAngle = 90.f;
	};

}