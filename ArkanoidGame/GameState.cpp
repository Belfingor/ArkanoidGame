#include <cassert>
#include "GameState.h"
#include "GameStateGameOver.h"
#include "GameStateMainMenu.h"
#include "GameStatePauseMenu.h"
#include "GameStatePlaying.h"
#include "GameStateRecords.h"


namespace ArkanoidGame
{
	GameState::GameState(GameStateType type, bool isExclusivelyVisible) : type(type), isExclusivelyVisible(isExclusivelyVisible)
	{
		switch (type)
		{
		case GameStateType::GameOver:
		{
			data = new GameStateGameOverData();
			((GameStateGameOverData*)data)->Init();
			break;
		}
		case GameStateType::MainMenu:
		{
			data = new GameStateMainMenuData();
			((GameStateMainMenuData*)data)->Init();
			break;
		}
		case GameStateType::PauseMenu:
		{
			data = new GameStatePauseMenuData();
			((GameStatePauseMenuData*)data)->Init();
			break;
		}
		case GameStateType::Playing:
			data = new GameStatePlayingData();
			((GameStatePlayingData*)data)->Init();
			break;
		case GameStateType::Records:
		{
			data = new GameStateRecordsData();
			((GameStateRecordsData*)data)->Init();
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	GameState::~GameState()
	{
		if (data)
		{
			switch (type)
			{
			case GameStateType::GameOver:
			{
				delete ((GameStateGameOverData*)data);
				break;
			}
			case GameStateType::MainMenu:
			{
				delete ((GameStateMainMenuData*)data);
				break;
			}
			case GameStateType::PauseMenu:
			{
				delete ((GameStatePauseMenuData*)data);
				break;
			}
			case GameStateType::Playing:
			{
				delete ((GameStatePlayingData*)data);
				break;
			}
			case GameStateType::Records:
			{
				delete ((GameStateRecordsData*)data);
				break;
			}
			default:
				assert(false); // We want to know if we forgot to implement new game state
				break;
			}
			data = nullptr;
		}
	}

	void GameState::Update(float timeDelta)
	{
		switch (type)
		{
		case GameStateType::GameOver:
		{
			((GameStateGameOverData*)data) ->Update(timeDelta);
			break;
		}
		case GameStateType::MainMenu:
		{
			((GameStateMainMenuData*)data) ->Update(timeDelta);
			break;
		}
		case GameStateType::PauseMenu:
		{
			((GameStatePauseMenuData*)data) ->Update(timeDelta);
			break;
		}
		case GameStateType::Playing:
		{
			((GameStatePlayingData*)data) ->Update(timeDelta);
			break;
		}
		case GameStateType::Records:
		{
			((GameStateRecordsData*)data) ->Update(timeDelta);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void GameState::Draw(sf::RenderWindow& window)
	{
		switch (type)
		{
		case GameStateType::GameOver:
		{
			((GameStateGameOverData*)data)->Draw(window);
			break;
		}
		case GameStateType::MainMenu:
		{
			((GameStateMainMenuData*)data)->Draw(window);
			break;
		}
		case GameStateType::PauseMenu:
		{
			((GameStatePauseMenuData*)data)->Draw(window);
			break;
		}
		case GameStateType::Playing:
		{
			((GameStatePlayingData*)data)->Draw(window);
			break;
		}
		case GameStateType::Records:
		{
			((GameStateRecordsData*)data)->Draw(window);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}

	void GameState::HandleWindowEvent(sf::Event& event)
	{
		switch (type)
		{
		case GameStateType::GameOver:
		{
			((GameStateGameOverData*)data)->HandleWindowEvent(event);
			break;
		}
		case GameStateType::MainMenu:
		{
			((GameStateMainMenuData*)data)->HandleWindowEvent(event);
			break;
		}
		case GameStateType::PauseMenu:
		{
			((GameStatePauseMenuData*)data)->HandleWindowEvent(event);
			break;
		}
		case GameStateType::Playing:
		{
			((GameStatePlayingData*)data)->HandleWindowEvent(event);
			break;
		}
		case GameStateType::Records:
		{
			((GameStateRecordsData*)data)->HandleWindowEvent(event);
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
	}
	void* GameState::CopyData(const GameState& state) const
	{
		void* data = nullptr;
		switch (state.type)
		{
		case GameStateType::MainMenu:
		{
			data = new GameStateMainMenuData();
			*((GameStateMainMenuData*)data) = *(GameStateMainMenuData*)state.data;
			break;
		}
		default:
			assert(false);
			break;
		}
		return data;
	}	
}

