#include "Game.h"
#include <cassert>
#include <algorithm>
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"
#include "GameStateAddToRecordsTable.h"

namespace ArkanoidGame
{
	void Game::StartGame()
	{
		SwitchStateTo(GameStateType::Playing);
	}
	void Game::PauseGame()
	{
		PushState(GameStateType::PauseMenu, false);
	}
	void Game::WinGame()
	{
		PushState(GameStateType::GameWon, false);
	}
	void Game::LoseGame()
	{
		PushState(GameStateType::GameOver, false);
	}
	void Game::AddScoreToRecordsTable()
	{
		PushState(GameStateType::AddToRecords, false);
	}
	void Game::UpdateGame(float timeDelta, sf::RenderWindow& window)
	{
		HandleWindowEvents(window);

		if (Update(timeDelta))
		{
			// Draw everything here
			// Clear the window first
			window.clear();
			Draw(window);

			// End the current frame, display window contents on screen
			window.display();
		}
		else
		{
			window.close();
		}
	}
	void Game::ExitGame()
	{
		SwitchStateTo(GameStateType::MainMenu);
	}
	void Game::QuitGame()
	{
		SwitchStateTo(GameStateType::None);
	}
	void Game::ShowRecords()
	{
		PushState(GameStateType::Records, true);
	}
	void Game::LoadNextLevel()
	{
		assert(stateStack.back().GetType() == GameStateType::Playing);
		auto playingData = (stateStack.back().GetData<GameStatePlayingData>());
		playingData->LoadNextLevel();
	}
	Game::Game()
	{
		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		SwitchStateTo(GameStateType::MainMenu);
	}

	Game::~Game()
	{
		Shutdown();
	}

	void Game::HandleWindowEvents(sf::RenderWindow& window)
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window if close button or Escape key pressed
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}

			if (stateStack.size() > 0)
			{
				stateStack.back().HandleWindowEvent(event);
			}
		}
	}

	bool Game::Update(float timeDelta)
	{
		if (stateChangeType == GameStateChangeType::Switch)
		{
			// Shutdown all game states
			while (stateStack.size() > 0)
			{
				stateStack.pop_back();
			}
		}
		else if (stateChangeType == GameStateChangeType::Pop)
		{
			// Shutdown only current game state
			if (stateStack.size() > 0)
			{
				stateStack.pop_back();
			}
		}

		// Initialize new game state if needed
		if (pendingGameStateType != GameStateType::None)
		{
			stateStack.push_back(GameState(pendingGameStateType, pendingGameStateIsExclusivelyVisible));
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;

		if (stateStack.size() > 0)
		{
			stateStack.back().Update(timeDelta);
			return true;
		}

		return false;
	}

	void Game::Draw(sf::RenderWindow& window)
	{
		if (stateStack.size() > 0)
		{
			std::vector<GameState*> visibleGameStates;
			for (auto it = stateStack.rbegin(); it != stateStack.rend(); ++it)
			{
				visibleGameStates.push_back(&(*it));
				if (it->IsExclusivelyVisible())
				{
					break;
				}
			}

			for (auto it = visibleGameStates.rbegin(); it != visibleGameStates.rend(); ++it)
			{
				(*it)->Draw(window);
			}
		}
	}

	void Game::Shutdown()
	{
		// Shutdown all game states
		while (stateStack.size() > 0)
		{
			stateStack.pop_back();
		}

		stateChangeType = GameStateChangeType::None;
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
	}

	void Game::PushState(GameStateType stateType, bool isExclusivelyVisible)
	{
		pendingGameStateType = stateType;
		pendingGameStateIsExclusivelyVisible = isExclusivelyVisible;
		stateChangeType = GameStateChangeType::Push;
	}

	void Game::PopState()
	{
		pendingGameStateType = GameStateType::None;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Pop;
	}

	void Game::SwitchStateTo(GameStateType newState)
	{
		pendingGameStateType = newState;
		pendingGameStateIsExclusivelyVisible = false;
		stateChangeType = GameStateChangeType::Switch;
	}
}
