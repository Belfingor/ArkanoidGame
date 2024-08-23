#pragma once
#include <algorithm>
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{

	struct Vector2DCoordinates
	{
		float x = 0;
		float y = 0;
	};

	typedef Vector2DCoordinates Position2D;
	typedef Vector2DCoordinates Vector2DCenter;

	struct Rectangle
	{
		Position2D position;
		Vector2DCoordinates size;
		Vector2DCenter center = {position.x + size.x / 2, position.y + size.y / 2};
	};

	struct Circle
	{
		Position2D position;
		float radius;
		Vector2DCenter center = { position.x, position.y};
	};

	bool DoShapesCollide(const Rectangle& rectangle, const Circle& circle);

}