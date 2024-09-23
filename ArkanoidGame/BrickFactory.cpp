#include "BrickFactory.h"
#include "Brick.h"


namespace ArkanoidGame
{
	int BrickFactory::GetCreatedBreackableBricksCount()
	{
		return createdBreackableBricksCount;
	}

	void BrickFactory::ClearCounter()
	{
		createdBreackableBricksCount = 0;
	}

	std::shared_ptr<Brick> SimpleBrickFactory::CreateBrick(const sf::Vector2f& position)
	{
		++createdBreackableBricksCount;
		return std::make_shared<SimpleBrick>(position);
	}

	std::shared_ptr<Brick> MultiHitBrickFactory::CreateBrick(const sf::Vector2f& position)
	{
		++createdBreackableBricksCount;
		return std::make_shared<MultiHitBrick>(position);
	}

	std::shared_ptr<Brick> UnbreackableBrickFactory::CreateBrick(const sf::Vector2f& position)
	{
		return std::make_shared<UnbreackableBrick>(position);
	}

	std::shared_ptr<Brick> GlassBrickFactory::CreateBrick(const sf::Vector2f& position)
	{
		++createdBreackableBricksCount;
		return std::make_shared<GlassBrick>(position);
	}
}