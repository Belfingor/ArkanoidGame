#pragma once
#include <SFML/Graphics.hpp>
#include "Sprite.h"

namespace ArkanoidGame
{
	class GameObject
	{
	public:
		virtual void Init() = 0;
		virtual void Update(float timeDelta) = 0;
		virtual void Draw(sf::RenderWindow& window);

	protected:
		sf::Sprite sprite;
		sf::Texture texture;
	};
}