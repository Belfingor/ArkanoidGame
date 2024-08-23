#pragma once
#include <SFML/Graphics.hpp>
#include <utility>
#include "GameStateData.h"

namespace ArkanoidGame
{
	enum class GameStateType
	{
		None = 0,
		MainMenu,
		Playing,
		GameOver,
		PauseMenu,
		Records
	};


	class GameState
	{
	public:
		GameState() = default;
		GameState(GameStateType type, bool isExclusivelyVisible);
		GameState(const GameState& state) = delete;
		GameState(GameState&& state) { operator=(std::move(state)); }

		~GameState();

		GameState& operator= (const GameState& state) = delete;
		GameState& operator= (GameState&& state) noexcept {
			type = state.type;
			data = std::move(state.data);
			isExclusivelyVisible = state.isExclusivelyVisible;
			state.data = nullptr;
			return *this;
		}

		GameStateType GetType() const { return type; }
		bool IsExclusivelyVisible() const { return isExclusivelyVisible; }

		template<class T>
		T* GetData() const
		{
			return static_cast<T>(data);
		}

		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);
		void HandleWindowEvent(sf::Event& event);

	private:
		GameStateType type = GameStateType::None;
		std::unique_ptr<GameStateData> data = nullptr;
		bool isExclusivelyVisible = false;
		
	};
}