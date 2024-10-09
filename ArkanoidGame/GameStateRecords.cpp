#include "GameStateRecords.h"
#include "Application.h"
#include "Text.h"
#include "Game.h"
#include "GameSettings.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	void GameStateRecordsData::Init()
	{
		assert(font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		titleText.setString("RECORDS");
		titleText.setFont(font);
		titleText.setFillColor(sf::Color::Red);
		titleText.setCharacterSize(48);

		RECORDS->InitRecordsTable();
		RECORDS->SortRecordsTable();
		RECORDS->DeserializeRecordsTable();
		RECORDS->UpdateRecordsTableTextForMainMenu(SETTINGS.MAX_RECORDS_TABLE_SIZE_MAIN_MENU);

		hintText.setString("Press ESC to return back to main menu");
		hintText.setFont(font);
		hintText.setFillColor(sf::Color::White);
		hintText.setCharacterSize(24);
	}

	void GameStateRecordsData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PopState();
			}
		}
	}

	void GameStateRecordsData::Update(float timeDelta)
	{

	}

	void GameStateRecordsData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		titleText.setOrigin(GetTextOrigin(titleText, { 0.5f, 0.f }));
		titleText.setPosition(viewSize.x / 2.f, 50.f);
		window.draw(titleText);

		sf::Vector2f tablePosition = { titleText.getGlobalBounds().left, viewSize.y / 2.f };
		DrawTextList(window, RECORDS->ConvertRecordsTextToMainMenuText(), 10.f, Orientation::Vertical, Alignment::Max, tablePosition, {-0.3f, 0.5f});

		hintText.setOrigin(GetTextOrigin(hintText, { 0.5f, 1.f }));
		hintText.setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
		window.draw(hintText);
	}

}
