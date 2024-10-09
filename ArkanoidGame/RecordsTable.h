#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cassert>
#include "GameSettings.h"
#include <memory>
#define RECORDS RecordsTable::GetInstance()


namespace ArkanoidGame
{
	//Creating RecordsTable class using Singleton pattern
	class RecordsTable
	{
	private:
		std::multimap<int, std::string> sortedRecordsMap; //Sorting records here
		std::vector<std::pair<std::string, int>> recordsTable; //Player name and score
		static RecordsTable* instance; //Instance of class
		RecordsTable() = default;

		sf::Font font;
		sf::Text recordsTableText;

	public:
		
		std::string playerName; // lcoated in public so that it can be accessed in GameStatePlaying
		int playerScore = 0;

		RecordsTable& operator = (const RecordsTable&) = delete;

		static RecordsTable* GetInstance();

		void InitRecordsTable();
		void UpdateRecordsTableTextForGameOver(int sizeLimit);
		void UpdateRecordsTableTextForMainMenu(int sizeLimit);
		bool SerializeRecordsTable();
		bool DeserializeRecordsTable();
		void AddPlayerScoreToRecordsTable();
		bool IsPlayerInRecordsTable();
		void SortRecordsTable();
		std::string TypePlayerName(const sf::Event& event);
		std::vector<sf::Text*> ConvertRecordsTextToMainMenuText();

		
	};
}