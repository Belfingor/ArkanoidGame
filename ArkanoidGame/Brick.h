#pragma once
#include <SFML/Graphics.hpp>
#include <cassert>
#include "GameSettings.h"
#include "Sprite.h"
#include "Math.h"
#include "GameObject.h"
#include "Collidable.h"

namespace ArkanoidGame
{
	class Brick : public GameObject, public Collidable
	{
	protected:
		void OnHit() override;
		int hitCount = 1;
	public:
		Brick (const sf::Vector2f& position);
		virtual ~Brick();
		bool GetCollision(std::shared_ptr<Collidable> collidable) const override;

		void Update(float timeDelta) override;
		bool IsBroken();



		//Rectangle GetBrickCollider();
		//void SetPosition(sf::Vector2f position);
	/*private:
		sf::Vector2f brickPosition;*/
	};
}