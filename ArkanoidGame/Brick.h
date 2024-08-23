#pragma once
#include <SFML/Graphics.hpp>
#include <cassert>
#include "GameSettings.h"
#include "Sprite.h"
#include "Math.h"
#include "GameObject.h"

namespace ArkanoidGame
{
	class Brick : public GameObject
	{
	public:
		void Init() override;
		void Update(float timeDelta) override;
		Rectangle GetBrickCollider();
		void SetPosition(sf::Vector2f position);

	private:
		sf::Vector2f brickPosition;
	};
}