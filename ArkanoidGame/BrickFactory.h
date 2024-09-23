#pragma once
#include "Brick.h"
#include <memory>
#include <SFML/Graphics.hpp>

namespace ArkanoidGame
{
	class Brick;

	class BrickFactory
	{
	protected:
		int createdBreackableBricksCount = 0;
	public:
		virtual std::shared_ptr<Brick> CreateBrick(const sf::Vector2f& position) = 0;
		virtual ~BrickFactory() = default;
		int GetCreatedBreackableBricksCount();
		void ClearCounter();
	};

	class SimpleBrickFactory final : public BrickFactory
	{
	public:
		std::shared_ptr<Brick> CreateBrick(const sf::Vector2f& position) override;
		~SimpleBrickFactory() override = default;
	};

	class MultiHitBrickFactory final : public BrickFactory
	{
	public:
		std::shared_ptr<Brick> CreateBrick(const sf::Vector2f& position) override;
		~MultiHitBrickFactory() override = default;
	};

	class UnbreackableBrickFactory final : public BrickFactory
	{
	public:
		std::shared_ptr<Brick> CreateBrick(const sf::Vector2f& position) override;
		~UnbreackableBrickFactory() override = default;
	};

	class GlassBrickFactory final : public BrickFactory
	{
	public:
		std::shared_ptr<Brick> CreateBrick(const sf::Vector2f& position) override;
		~GlassBrickFactory() override = default;
	};

}