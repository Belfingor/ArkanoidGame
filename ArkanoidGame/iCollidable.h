#pragma once
#include "SFML/Graphics.hpp"
#include <memory>

namespace ArkanoidGame
{
	// Collision interface
	class iCollidable
	{
	protected:
		virtual void OnHit() = 0;
	public:
		virtual bool GetCollision(std::shared_ptr<iCollidable> collidable) const = 0;
		virtual bool CheckCollision(std::shared_ptr<iCollidable> collidable)
		{
			if (GetCollision(collidable))
			{
				OnHit();
				return true;
			}
			return false;
		}
	};
}