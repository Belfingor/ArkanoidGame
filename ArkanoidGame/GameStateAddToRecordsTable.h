#pragma once
#include "GameState.h"
#include "Menu.h"
#include <SFML/Graphics.hpp>
#include "GameSettings.h"


namespace ArkanoidGame
{
	class GameStateAddToRecordsTableData : public GameStateData
	{
	public:
		void Init() override;

		void HandleWindowEvent(const sf::Event& event) override;

		void Update(float deltaTime) override;

		void Draw(sf::RenderWindow& window) override;
	private:
		sf::Text typingPlayerNameText;

		sf::Font font;
		Menu menu;
	};
}