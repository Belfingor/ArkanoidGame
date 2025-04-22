#pragma once
#include <SFML/Graphics.hpp>
#include <cassert>
#include <memory> 
#include "GameSettings.h"
#include "Sprite.h"
#include "Math.h"
#include "GameObject.h"
#include "iCollidable.h"
#include "iDelayedAction.h"
#include "Iobserver.h"
#include "iBrickState.h"

namespace ArkanoidGame
{
	class Brick : public GameObject, public iCollidable, public IObservable  //,public iBrickState
	{
	protected:
		void OnHit() override;
		int originalHitCount = 1;
		int hitCount = originalHitCount;

	private:
		std::unique_ptr<iBrickState> brickState; //Pointer to the current state
		
	public:
		Brick (const sf::Vector2f& position, const sf::Color& color = sf::Color::White);
		virtual ~Brick();
		bool GetCollision(std::shared_ptr<iCollidable> collidable) const override;
		void Update(float timeDelta) override;
		bool IsBroken();
		int GetOriginalHitCount()const;

		//------States------//
		iBrickState* GetState() const { return brickState.get(); }
		void SetState(std::unique_ptr<iBrickState> newState);
		void ApplySingleHitBuff();
		void RevertSingleHitBuff();
		void SetHitCount(int hitCount);
		//------------------//

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