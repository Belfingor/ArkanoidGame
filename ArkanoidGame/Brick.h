#pragma once
#include <SFML/Graphics.hpp>
#include <cassert>
#include "GameSettings.h"
#include "Sprite.h"
#include "Math.h"
#include "GameObject.h"
#include "iCollidable.h"
#include "iDelayedAction.h"
#include "Iobserver.h"

namespace ArkanoidGame
{
	class Brick : public GameObject, public iCollidable, public IObservable
	{
	protected:
		void OnHit() override;
		int hitCount = 1;
		
	public:
		Brick (const sf::Vector2f& position, const sf::Color& color = sf::Color::White);
		virtual ~Brick();
		bool GetCollision(std::shared_ptr<iCollidable> collidable) const override;
		void Update(float timeDelta) override;
		bool IsBroken();

		int scoreContainer = 1;
	};
	//--------------------------------------------------------------------------------
	class SimpleBrick : public Brick, public iDelayedAction
	{
	protected:
		void OnHit() override;
		sf::Color color;

	public:
		SimpleBrick(const sf::Vector2f& position, const sf::Color& color = sf::Color::Green);
		~SimpleBrick() = default;

		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<iCollidable> collidableObject) const;
		void FinalAction() override;
		void EachTickAction(float deltaTime) override;
	};
	//--------------------------------------------------------------------------------
	class UnbreackableBrick : public Brick
	{
	protected:
		void OnHit() override;

	public:
		UnbreackableBrick(const sf::Vector2f& position);
		~UnbreackableBrick() = default;
		
		void Update(float deltaTime) override;
	};
	//--------------------------------------------------------------------------------
	class MultiHitBrick : public Brick , public iDelayedAction
	{
	protected:
		void OnHit() override;
		sf::Color color;
	public:
		MultiHitBrick(const sf::Vector2f& position, const sf::Color& color = sf::Color::White);
		~MultiHitBrick() = default;
		void Update(float deltaTime) override;
		bool GetCollision(std::shared_ptr<iCollidable> collidableObject) const override;
		void FinalAction();
		void EachTickAction(float deltaTime);


	};
	//--------------------------------------------------------------------------------
	class GlassBrick : public Brick, public iDelayedAction
	{
	protected:
		void OnHit() override;
		sf::Color color;

	public:
		GlassBrick(const sf::Vector2f& position, const sf::Color& color = sf::Color::Blue);
		~GlassBrick() = default; 

		void Update(float deltaTime) override;
		bool GetCollision(std::shared_ptr<iCollidable> collidableObject) const override;
		void FinalAction() override;
		void EachTickAction(float deltaTime) override;
	};
}