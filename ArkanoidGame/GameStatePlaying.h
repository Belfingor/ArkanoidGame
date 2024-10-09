#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"
#include "Brick.h"
#include <vector>
#include "GameStateData.h"
#include "BrickFactory.h"
#include "LevelLoader.h"
#include "IObserver.h"
#include "RecordsTable.h"

#include <unordered_map>


namespace ArkanoidGame
{
	class Game;
	class Brick;
	class BrickFactory;

	class GameStatePlayingData : public GameStateData, public IObserver, public std::enable_shared_from_this<GameStatePlayingData>
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		void LoadNextLevel();
		void Notify(std::shared_ptr<IObservable> observable) override;

	private:
		void CreateBricks();
		void GetBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& brickRect, bool& needInverseDirX, bool& needInverseDirY);


		// Resources
		sf::Font font;
		sf::SoundBuffer gameOverSoundBuffer;

		// Game data
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<Brick>> bricks;

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		// Sounds
		sf::Sound gameOverSound;

		//Bricks Creator
		std::unordered_map<BrickType, std::unique_ptr<BrickFactory>> brickFactories;
		int breakableBricksCount = 0;

		//Levels
		LevelLoader levelLoader;
		int currentLevel = 0;
	};
}
