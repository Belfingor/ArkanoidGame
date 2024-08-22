#include "GameObject.h"


namespace ArkanoidGame
{
	void GameObject::Draw(sf::RenderWindow& window)
	{
		DrawSprite(sprite, window);
	}
}