#include "GameStateGameWon.h"

void ArkanoidGame::GameStateGameWon::Init()
{
	assert(font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

	timeSinceGameOver = 0.f;

	sf::Color backgroundColor = sf::Color::Black;
	backgroundColor.a = 200; // a means Alfa, opacity
	background.setFillColor(backgroundColor);

	gameWonText.setFont(font);
	gameWonText.setCharacterSize(48);
	gameWonText.setStyle(sf::Text::Bold);
	gameWonText.setFillColor(sf::Color::Green);
	gameWonText.setString("YOU WIN");

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

void ArkanoidGame::GameStateGameWon::HandleWindowEvent(const sf::Event& event)
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

void ArkanoidGame::GameStateGameWon::Update(float timeDelta)
{
	if (!wasRecoredAdded)
	{
		Application::Instance().GetGame().AddScoreToRecordsTable();
		wasRecoredAdded = true;
	}

	timeSinceGameOver += timeDelta;

	sf::Color gameWonTextColor = (int)timeSinceGameOver % 2 ? sf::Color::Green : sf::Color::Yellow;
	gameWonText.setFillColor(gameWonTextColor);

	RECORDS->UpdateRecordsTableTextForGameOver(SETTINGS.MAX_RECORDS_TABLE_SIZE_GAME_OVER);
	RECORDS->SortRecordsTable();
}

void ArkanoidGame::GameStateGameWon::Draw(sf::RenderWindow& window)
{
	sf::Vector2f viewSize = window.getView().getSize();

	background.setOrigin(0.f, 0.f);
	background.setSize(viewSize);
	window.draw(background);

	gameWonText.setOrigin(GetTextOrigin(gameWonText, { 0.5f, 3.5f }));
	gameWonText.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 50.f);
	window.draw(gameWonText);

	sf::Vector2f tablePosition = { viewSize.x / 10.f, viewSize.y / 2.f };
	DrawTextList(window, RECORDS->ConvertRecordsTextToMainMenuText(), 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { .5f, .0f });

	window.draw(hintText);
}
