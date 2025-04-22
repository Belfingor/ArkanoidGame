#include "Brick.h"

namespace
{
	const std::string TEXTURE_PATH = "Textures/Standard_Brick.png";
}

namespace ArkanoidGame
{
	void Brick::OnHit()
	{
		hitCount -= 1;
		Emit();
	}
	Brick::Brick(const sf::Vector2f& position, const sf::Color& color) : 
		GameObject(SETTINGS.RESOURCES_PATH + TEXTURE_PATH, position, SETTINGS.BRICK_WIDTH, SETTINGS.BRICK_HEIGHT)
	{
		sprite.setColor(color);
		brickState = std::make_unique<NormalBrickState>(hitCount);
	}
	Brick::~Brick()
	{
		
	}
	bool Brick::GetCollision(std::shared_ptr<iCollidable> collidable) const
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidable);
		assert(gameObject);
		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1;
		return GetRect().intersects(gameObject->GetRect());
	}
	void Brick::Update(float timeDelta)
	{

	}
	bool Brick::IsBroken()
	{
		return hitCount <= 0;
	}

	int Brick::GetOriginalHitCount() const { return originalHitCount; }

	//------States------//

	void Brick::SetState(std::unique_ptr<iBrickState> newState)
	{
		brickState = std::move(newState);
	}
	void Brick::ApplySingleHitBuff()
	{
		brickState->ApplySingleHitBuff(*this);
	}
	void Brick::RevertSingleHitBuff()
	{
		brickState->RevertSingleHitBuff(*this);
	}
	void Brick::SetHitCount(int hitCount)
	{
		this->hitCount = hitCount;
	}
	//--------------------------------------------------------------------------------//--------------------------------------------------------------------------------
	void SimpleBrick::OnHit()
	{
		StartTimer(SETTINGS.BRICK_BREAK_DELAY);
	}
	SimpleBrick::SimpleBrick(const sf::Vector2f& position, const sf::Color& color) : Brick(position, color), color(color) 
	{

	}
	void SimpleBrick::Update(float timeDelta)
	{
		UpdateTimer(timeDelta);
	}
	bool SimpleBrick::GetCollision(std::shared_ptr<iCollidable> collidableObject) const
	{
		if (isTimerStarted_)
		{
			return false;
		}

		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1f;
		return GetRect().intersects(gameObject->GetRect());
	}
	void SimpleBrick::FinalAction()
	{
		hitCount -=1;
		Emit();
	}
	void SimpleBrick::EachTickAction(float deltaTime)
	{
		color.a = 255 * currentTime_ / destroyTime_;
		sprite.setColor(color);
	}
	//--------------------------------------------------------------------------------//--------------------------------------------------------------------------------
	UnbreackableBrick::UnbreackableBrick(const sf::Vector2f& position) : Brick(position, sf::Color::Color(105, 105, 105))
	{

	}
	void UnbreackableBrick::OnHit()
	{
		// Not changing hitCount here as brick is unbeakable
	}
	void UnbreackableBrick::Update(float deltaTime)
	{
		// Do nothing
	}

	//--------------------------------------------------------------------------------//--------------------------------------------------------------------------------
	MultiHitBrick::MultiHitBrick(const sf::Vector2f& position, const sf::Color& color) : Brick(position, color), color(color)
	{
		scoreContainer = SETTINGS.MULTIHIT_BRICK_SCORE;
		originalHitCount = SETTINGS.MULTIHIT_BRICK_HITPOINTS;
		hitCount = originalHitCount;
	}
	void MultiHitBrick::OnHit()
	{
		if (hitCount == 1)
		{
			StartTimer(SETTINGS.BRICK_BREAK_DELAY);
		}
		else
		{
			hitCount -= 1;
		}
	}
	void MultiHitBrick::Update(float deltaTime)
	{
		switch (hitCount)
		{
		case 2:
			//set FullHP texture
			Brick::texture.loadFromFile(SETTINGS.RESOURCES_PATH + "Textures/Standard_Brick.png");
			break;
		case 1:
			//set CrackedTexture
			Brick::texture.loadFromFile(SETTINGS.RESOURCES_PATH + "Textures/Damaged_Brick.png");
			UpdateTimer(deltaTime);
			break;
		default:
			break;
		}
	}
	bool MultiHitBrick::GetCollision(std::shared_ptr<iCollidable> collidableObject) const
	{
		if (isTimerStarted_)
		{
			return false;
		}

		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1f;
		return GetRect().intersects(gameObject->GetRect());
	}
	void MultiHitBrick::FinalAction()
	{
		hitCount -= 1;
		Emit();
	}
	void MultiHitBrick::EachTickAction(float deltaTime)
	{
		color.a = 255 * currentTime_ / destroyTime_;
		sprite.setColor(color);
	}
	void GlassBrick::OnHit()
	{
		StartTimer(SETTINGS.BRICK_BREAK_DELAY);
	}
	//--------------------------------------------------------------------------------//--------------------------------------------------------------------------------
	GlassBrick::GlassBrick(const sf::Vector2f& position, const sf::Color& color) : Brick(position, color), color(color)
	{

	}
	void GlassBrick::Update(float deltaTime)
	{
		UpdateTimer(deltaTime);
	}
	bool GlassBrick::GetCollision(std::shared_ptr<iCollidable> collidableObject) const
	{
		if (isTimerStarted_)
		{
			return false;
		}

		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidableObject);
		assert(gameObject);
		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1f;
		return GetRect().intersects(gameObject->GetRect());
	}
	void GlassBrick::FinalAction()
	{
		hitCount -= 1;
		Emit();
	}
	void GlassBrick::EachTickAction(float deltaTime)
	{
		color.a = 255 * currentTime_ / destroyTime_;
		sprite.setColor(color);
	}
}
	