#pragma once
#include "GameObject.h"
#include <cassert>
#include <SFML/Graphics.hpp>
#include "iCollidable.h"
#include "GameSettings.h"
#include "Sprite.h"


namespace ArkanoidGame
{
	enum class ModifierType //to identify which modifier to apply
	{
		FireBall,
		FragileBricks,
		WidePlatform,
		Default
	};


	class Modifier : public GameObject, public iCollidable
	{
	public:
		Modifier(const sf::Vector2f& position, const std::string& texturePath);
		~Modifier() = default;
		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<iCollidable> collidable) const override;
		void OnHit() override;
		bool DidModReachTheFloor();
		virtual ModifierType GetModifierType() const { return ModifierType::Default; }
	};
	//-----------------------------------------------------------------------------
	class FireBallModifier final : public Modifier
	{
	public:
		FireBallModifier(const sf::Vector2f& position, const std::string& texturePath = SETTINGS.FIREBALL_MODIFIER_TEXTURE_PATH);
		~FireBallModifier() = default;
		ModifierType GetModifierType() const override;
	};
	//-----------------------------------------------------------------------------
	class FragileBricksModifier final : public Modifier
	{
	public:
		FragileBricksModifier(const sf::Vector2f& position, const std::string& texturePath = SETTINGS.FRAGILEBRICKS_MODIFIER_TEXTURE_PATH);
		~FragileBricksModifier() = default;
		ModifierType GetModifierType() const override;
	};
	//-----------------------------------------------------------------------------
	class WidePlatformModifier final : public Modifier
	{
	public:
		WidePlatformModifier(const sf::Vector2f& position, const std::string& texturePath = SETTINGS.SPEEDBOOST_MODIFIER_TEXTURE_PATH);
		~WidePlatformModifier() = default;
		ModifierType GetModifierType() const override;
	};
}