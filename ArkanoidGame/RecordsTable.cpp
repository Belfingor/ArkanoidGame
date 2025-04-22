#include "RecordsTable.h"


namespace ArkanoidGame
{
	RecordsTable* RecordsTable::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new RecordsTable();
		}
		return instance;
	}
	void RecordsTable::InitRecordsTable()
	{
		assert(font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Roboto-Regular.ttf"));
		recordsTableText.setFont(font);
		recordsTableText.setCharacterSize(24);
		recordsTableText.setFillColor(sf::Color::White);
		recordsTableText.setPosition(SETTINGS.SCREEN_WIDTH / 2, SETTINGS.SCREEN_HEIGHT / 2);
	}

	void RecordsTable::UpdateRecordsTableTextForGameOver(int sizeLimit)
	{
		recordsTableText.setString("Records:\n");
		DeserializeRecordsTable();
		std::reverse(recordsTable.begin(), recordsTable.end());

		int count = 0;
		for (const auto& item : recordsTable)
		{
			if (count == sizeLimit)
			{
				break;
			}
			recordsTableText.setString(recordsTableText.getString() + item.first + " - " + std::to_string(item.second) + "\n");
			count++;
		}
	}

	void RecordsTable::UpdateRecordsTableTextForMainMenu(int sizeLimit)
	{
		recordsTableText.setString("");
		DeserializeRecordsTable();
		std::reverse(recordsTable.begin(), recordsTable.end());

		int count = 0;
		for (const auto& item : recordsTable)
		{
			if (count == sizeLimit)
			{
				break;
			}
			recordsTableText.setString(recordsTableText.getString() + item.first + " - " + std::to_string(item.second) + "\n");
			count++;
		}
	}

	bool RecordsTable::SerializeRecordsTable()
	{
		std::ofstream file(SETTINGS.RECORDS_TABLE_PATH);
		if (file.is_open())
		{
			for (const auto& record : recordsTable)
			{
				file << record.first << " " << record.second << std::endl;
			}
			file.close();
			return true;
		}
	}

	bool RecordsTable::DeserializeRecordsTable()
	{
		std::ifstream file(SETTINGS.RECORDS_TABLE_PATH);
		if (file.is_open())
		{
			recordsTable.clear();
			std::string name;
			int score;

			while (file >> name >> score)
			{
				recordsTable.emplace_back(name, score);
			}
			file.close();
			return true;
		}

	}

	void RecordsTable::AddPlayerScoreToRecordsTable()
	{
		if (!IsPlayerInRecordsTable())
		{
			recordsTable.push_back(std::pair<std::string, int>(playerName, playerScore));
			SerializeRecordsTable();
			SortRecordsTable();
		}
		else
		{
			SerializeRecordsTable();
			SortRecordsTable();
		}
	}

	bool RecordsTable::IsPlayerInRecordsTable()
	{
		for (auto& pair : recordsTable)
		{
			if (pair.first == playerName)
			{
				if (pair.second < playerScore)
				{
					pair.second = playerScore;
				}
				return true; 
			}
		}
		return false;
	}

	void RecordsTable::SortRecordsTable()
	{
		DeserializeRecordsTable();

		for (const auto& item : recordsTable)
		{
			sortedRecordsMap.insert({ item.second, item.first });
		}
		recordsTable.clear();

		for (const auto& item : sortedRecordsMap)
		{
			recordsTable.push_back({ item.second, item.first });
		}

		sortedRecordsMap.clear();
		SerializeRecordsTable();
	}

	std::string RecordsTable::TypePlayerName(const sf::Event& event)
	{
		if (event.text.unicode < 128 && event.text.unicode != ' ') // Handle only ASCII characters
		{
			if (event.text.unicode == '\b') // Handling backspace 
			{
				if (!playerName.empty())
				{
					playerName.pop_back();
				}
			}
			else if (event.text.unicode == 13) // Handling Enter key press 
			{
				//we need to empty player's name, so player can type it again without earsing next time
				playerName = "";
			}
			else
			{
				playerName += static_cast<char>(event.text.unicode);
			}
		}
		return playerName;
	}

	std::vector<sf::Text*> RecordsTable::ConvertRecordsTextToMainMenuText()
	{
		return std::vector<sf::Text*> { &recordsTableText };
	}

	RecordsTable* RecordsTable::instance = nullptr; // Initialize the static instance pointer to nullptr

}
