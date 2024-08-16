#pragma once
#include <algorithm>

namespace ArkanoidGame
{

	struct RandomBLA
	{
		float x = 0;
		float y = 0;
	};

	typedef RandomBLA Position2D;

	struct Rectangle
	{
		Position2D position;
		RandomBLA size;
	};

	struct Circle
	{
		Position2D position;
		float radius;
	};

	bool DoShapesCollide(const Rectangle& rectangle, const Circle& circle);

}