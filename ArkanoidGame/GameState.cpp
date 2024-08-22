#include <cassert>
#include "GameState.h"
#include "GameStateGameOver.h"
#include "GameStateMainMenu.h"
#include "GameStatePauseMenu.h"
#include "GameStatePlaying.h"
#include "GameStateRecords.h"
#include "GameStateData.h"


namespace ArkanoidGame
{
	GameState::GameState(GameStateType type, bool isExclusivelyVisible) : type(type), isExclusivelyVisible(isExclusivelyVisible)
	{
		switch (type)
		{
		case GameStateType::GameOver:
		{
			data = std::make_unique<GameStateGameOverData>();
			break;
		}
		case GameStateType::MainMenu:
		{
			data = std::make_unique<GameStateMainMenuData>();
			break;
		}
		case GameStateType::PauseMenu:
		{
			data = std::make_unique<GameStatePauseMenuData>();
			break;
		}
		case GameStateType::Playing:
		{
			data = std::make_unique<GameStatePlayingData>();
			break;
		}
		case GameStateType::Records:
		{
			data = std::make_unique<GameStateRecordsData>();
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
		if (data)
		{
			data->Init();
		}
	}

	GameState::~GameState()
	{
		if (data)
		{
			data = nullptr;
		}
	}

	void GameState::Update(float timeDelta)
	{
		data->Update(timeDelta);
	}

	void GameState::Draw(sf::RenderWindow& window)
	{
		data->Draw(window);
	}

	void GameState::HandleWindowEvent(sf::Event& event)
	{
		data -> HandleWindowEvent(event);
	}
}

