#include "GameStateAddToRecordsTable.h"
#include <cassert>
#include "Application.h"
#include "RecordsTable.h"

namespace ArkanoidGame
{
	void GameStateAddToRecordsTableData::Init()
	{
		assert(font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));

		MenuItem enterPlayerName;
		enterPlayerName.text.setString("");
		enterPlayerName.text.setFont(font);
		enterPlayerName.text.setCharacterSize(24);
		enterPlayerName.onPressCallback = [](MenuItem&)
			{
				RECORDS->AddPlayerScoreToRecordsTable();
				Application::Instance().GetGame().PopState();
			};

		
		typingPlayerNameText.setString(RECORDS->playerName);
		typingPlayerNameText.setFont(font);
		typingPlayerNameText.setCharacterSize(24);

		MenuItem yesAddToRecords;
		yesAddToRecords.hintText.setString("Enter your name and press Enter");
		yesAddToRecords.hintText.setFont(font);
		yesAddToRecords.hintText.setCharacterSize(48);
		yesAddToRecords.hintText.setFillColor(sf::Color::White);
		yesAddToRecords.text.setString("Yes");
		yesAddToRecords.text.setFont(font);
		yesAddToRecords.text.setCharacterSize(24);
		yesAddToRecords.childrens.push_back(enterPlayerName);

		MenuItem noAddToRecords;
		noAddToRecords.text.setString("No");
		noAddToRecords.text.setFont(font);
		noAddToRecords.text.setCharacterSize(24);
		noAddToRecords.onPressCallback = [](MenuItem&)
			{
				Application::Instance().GetGame().PopState();
			};

		MenuItem addToRecordsTable;
		addToRecordsTable.hintText.setString("Add your score to Records Table?");
		addToRecordsTable.hintText.setFont(font);
		addToRecordsTable.hintText.setCharacterSize(48);
		addToRecordsTable.hintText.setFillColor(sf::Color::White);
		addToRecordsTable.childrenOrientation = Orientation::Vertical;
		addToRecordsTable.childrenAlignment = Alignment::Middle;
		addToRecordsTable.childrenSpacing = 10.f;
		addToRecordsTable.childrens.push_back(noAddToRecords);
		addToRecordsTable.childrens.push_back(yesAddToRecords);

		menu.Init(addToRecordsTable);
	}

	void GameStateAddToRecordsTableData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{

			if (event.key.code == sf::Keyboard::Enter)
			{
				menu.PressOnSelectedItem();
			}

			Orientation orientation = menu.GetCurrentContext().childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				menu.SwitchToPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				menu.SwitchToNextMenuItem();
			}
		}
		if (event.type == sf::Event::TextEntered)
		{
			typingPlayerNameText.setString(RECORDS->TypePlayerName(event));
		}
		
	}

	void GameStateAddToRecordsTableData::Update(float deltaTime)
	{

	}

	void GameStateAddToRecordsTableData::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();

		sf::Text* hintText = &menu.GetCurrentContext().hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		menu.Draw(window, viewSize / 2.f, { 0.5f, 0.f });

		typingPlayerNameText.setPosition(viewSize.x / 2.3f, viewSize.y /2.f);
		
		window.draw(typingPlayerNameText);
	}
}