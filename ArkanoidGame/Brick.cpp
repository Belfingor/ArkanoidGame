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
	Brick::Brick(const sf::Vector2f& position, const sf::Color& color) : GameObject(SETTINGS.RESOURCES_PATH + TEXTURE_PATH, position, SETTINGS.BRICK_WIDTH, SETTINGS.BRICK_HEIGHT)
	{
		sprite.setColor(color);
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
	MultiHitBrick::MultiHitBrick(const sf::Vector2f& position, const sf::Color& color) : Brick(position, color)
	{
		hitCount = SETTINGS.MULTIHIT_BRICK_HITPOINTS;
		scoreContainer = SETTINGS.MYLTIHIT_BRICK_SCORE;
	}
	void MultiHitBrick::OnHit()
	{
		--hitCount;
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
			break;
		default:
			break;
		}
	}
	//--------------------------------------------------------------------------------//--------------------------------------------------------------------------------
	GlassBrick::GlassBrick(const sf::Vector2f& position, const sf::Color& color) : Brick(position, color)
	{

	}
}
	