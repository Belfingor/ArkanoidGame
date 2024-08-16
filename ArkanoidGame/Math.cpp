#include "Math.h"


namespace ArkanoidGame
{
	bool DoShapesCollide(const Rectangle& rectangle, const Circle& circle)
	{
		float dx = circle.position.x - std::max(rectangle.position.x, std::min(circle.position.x, rectangle.position.x + rectangle.size.x));
		float dy = circle.position.y - std::max(rectangle.position.y, std::min(circle.position.y, rectangle.position.y + rectangle.size.y));
		return (dx * dx + dy * dy) < (circle.radius * circle.radius);
	}
}