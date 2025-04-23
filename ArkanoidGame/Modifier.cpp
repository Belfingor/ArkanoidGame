#include "Modifier.h"
#include <algorithm>

namespace ArkanoidGame
{
	Modifier::Modifier(const sf::Vector2f& position, const std::string& texturePath)
		: GameObject(texturePath, position, SETTINGS.MODIFIER_SIZE, SETTINGS.MODIFIER_SIZE)
	{
		assert(texture.loadFromFile(texturePath));
		InitSprite(sprite, SETTINGS.MODIFIER_SIZE, SETTINGS.MODIFIER_SIZE, texture);
		sprite.setPosition(position);
	}
	void Modifier::Update(float timeDelta)
	{
		auto position = sprite.getPosition();
		position.y += SETTINGS.MODIFIER_SPEED * timeDelta;
		sprite.setPosition(position);
	}
	bool Modifier::GetCollision(std::shared_ptr<iCollidable> collidable) const
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject> (collidable);
		assert(gameObject);
		return GetRect().intersects(gameObject->GetRect());
	}

	void Modifier::OnHit()
	{
		// Nothing to change here regarding the platform
	}

	bool Modifier::DidModReachTheFloor()
	{
		return sprite.getPosition().y >= SETTINGS.SCREEN_HEIGHT;
	}

	//-----------------------------------------------------------------------------
	FireBallModifier::FireBallModifier(const sf::Vector2f& position, const std::string& texturePath)
		: Modifier(position, texturePath)
	{

	}
	ModifierType FireBallModifier::GetModifierType() const { return ModifierType::FireBall; }
	//-----------------------------------------------------------------------------
	FragileBricksModifier::FragileBricksModifier(const sf::Vector2f& position, const std::string& texturePath)
		: Modifier(position, texturePath)
	{
		
	}
	ModifierType FragileBricksModifier::GetModifierType() const { return ModifierType::FragileBricks; }
	//-----------------------------------------------------------------------------
	WidePlatformModifier::WidePlatformModifier(const sf::Vector2f& position, const std::string& texturePath)
		: Modifier(position, texturePath)
	{

	}
	ModifierType WidePlatformModifier::GetModifierType() const { return ModifierType::WidePlatform; }
}
