#include "LevelLoader.h"
#include "GameSettings.h"

#include<fstream>
#include<cassert>
#include<filesystem>

namespace ArkanoidGame
{
	Level& LevelLoader::GetLevel(int i)
	{
		return levels.at(i);
	}

	int LevelLoader::GetLevelCount()
	{
		return levels.size();
	}

	void LevelLoader::LoadLevelsFromFile()
	{
		std::string filepath = SETTINGS.LELEVS_CONFIG_PATH;
		std::string line;
		std::ifstream file(filepath);
		int y = 0;
		while (getline(file, line))
		{
			if (line.rfind("level", 0) == 0)
			{
				auto level = std::stoi(line.substr(6, line.size() - 6));
				levels.emplace_back(Level());
				y = 0;
			}
			else
			{
				int x = 0;
				for (char c : line)
				{
					if (c != ' ')
					{
						levels.back().m_bricks.emplace_back(std::make_pair(sf::Vector2i{ x,y }, CharToBrickType(c)));
					}
					++x;
				}
			}
			++y;
		}
		file.close();
	}

	BrickType LevelLoader::CharToBrickType(char symbol)
	{
		BrickType brickType;
		switch (symbol)
		{
		case '0':
			brickType = BrickType::Simple;
			break;
		case '1':
			brickType = BrickType::MultiHit;
			break;
		case'2':
			brickType = BrickType::Unbreackable;
			break;
		case'3':
			brickType = BrickType::Glass;
			break;
		default:
			assert(false);
			break;
		}
		return brickType;
	}




}

