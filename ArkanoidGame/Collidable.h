#pragma once
#include "SFML/Graphics.hpp"
#include <memory>

namespace ArkanoidGame
{
	// Collision interface
	class Collidable
	{
	protected:
		virtual void OnHit() = 0;
	public:
		virtual bool GetCollision(std::shared_ptr<Collidable> collidable) const = 0;
		virtual bool CheckCollision(std::shared_ptr<Collidable> collidable)
		{
			if (GetCollision(collidable))
			{
				OnHit();
				collidable->OnHit();
				return true;
			}
			return false;
		}
	};
}