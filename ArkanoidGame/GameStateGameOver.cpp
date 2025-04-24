#include "GameStateGameOver.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>
#include "RecordsTable.h"

namespace ArkanoidGame
{
	const char* PLAYER_NAME = "Player";

	void GameStateGameOverData::Init()
	{
		assert(font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		timeSinceGameOver = 0.f;

		sf::Color backgroundColor = sf::Color::Black;
		backgroundColor.a = 200; // a means Alfa, opacity
		background.setFillColor(backgroundColor);

		gameOverText.setFont(font);
		gameOverText.setCharacterSize(48);
		gameOverText.setStyle(sf::Text::Bold);
		gameOverText.setFillColor(sf::Color::Red);
		gameOverText.setString("GAME OVER");

		gainedScoreText.setFont(font);
		gainedScoreText.setCharacterSize(24);
		gainedScoreText.setString("Score: " + std::to_string(RECORDS->playerScore));

		std::multimap<int, std::string> sortedRecordsTable;
		Game& game = Application::Instance().GetGame();
		for (const auto& item : game.GetRecordsTable())
		{
			sortedRecordsTable.insert(std::make_pair(item.second, item.first));
		}

		RECORDS->InitRecordsTable();

		hintText.setFont(font);
		hintText.setCharacterSize(24);
		hintText.setFillColor(sf::Color::White);
		hintText.setString("Press Space to restart\nEsc to exit to main menu");
		
	}

	void GameStateGameOverData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				Application::Instance().GetGame().StartGame();
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().ExitGame();
			}
		}
	}

	void GameStateGameOverData::Update(float timeDelta)
	{
		if (!wasRecoredAdded)
		{
			Application::Instance().GetGame().AddScoreToRecordsTable();
			wasRecoredAdded = true;
		}

		timeSinceGameOver += timeDelta;

		sf::Color gameOverTextColor = (int)timeSinceGameOver % 2 ? sf::Color::Red : sf::Color::Yellow;
		gameOverText.setFillColor(gameOverTextColor);

		RECORDS->UpdateRecordsTableTextForGameOver(SETTINGS.MAX_RECORDS_TABLE_SIZE_GAME_OVER);
		RECORDS->SortRecordsTable();
	}

	void GameStateGameOverData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		background.setOrigin(0.f, 0.f);
		background.setSize(viewSize);
		window.draw(background);
		gameOverText.setOrigin(GetTextOrigin(gameOverText, { 0.5f, 3.5f }));

		gameOverText.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 50.f);
		window.draw(gameOverText);

		gainedScoreText.setOrigin(.7f, .5f);
		gainedScoreText.setPosition(gameOverText.getPosition().x - 40.f, gameOverText.getPosition().y);
		window.draw(gainedScoreText);

		sf::Vector2f tablePosition = { viewSize.x / 10.f, viewSize.y / 2.f };
		DrawTextList(window, RECORDS->ConvertRecordsTextToMainMenuText(), 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { .5f, .0f });

		window.draw(hintText);
	}
}
