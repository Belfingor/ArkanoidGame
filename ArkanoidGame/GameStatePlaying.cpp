#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{	
		// Init game resources (terminate if error)
		LoadSnakeTextures(snake);
		assert(appleTexture.loadFromFile(TEXTURES_PATH + "Apple.png"));
		assert(rockTexture.loadFromFile(TEXTURES_PATH + "Rock.png"));
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(eatAppleSoundBuffer.loadFromFile(SOUNDS_PATH + "AppleEat.wav"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 200, 0));

		// Init snake
		InitSnake(snake);

		// Init apple
		InitSprite(apple, APPLE_SIZE, APPLE_SIZE, appleTexture);
		SetSpriteRandomPosition(apple, background.getGlobalBounds(), snake.body);

		// Init rocks
		rocks.resize(ROCKS_COUNT);
		for (sf::Sprite& rock : rocks) {
			InitSprite(rock, ROCK_SIZE, ROCK_SIZE, rockTexture);
			SetSpriteRandomPosition(rock, background.getGlobalBounds(), snake.body);
		}

		numEatenApples = 0;

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		// Init sounds
		eatAppleSound.setBuffer(eatAppleSoundBuffer);
		gameOverSound.setBuffer(gameOverSoundBuffer);
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushState(GameStateType::PauseMenu, false);
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			snake.direction = SnakeDirection::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			snake.direction = SnakeDirection::Right;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			snake.direction = SnakeDirection::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			snake.direction = SnakeDirection::Left;
		}

		// Update snake
		MoveSnake(snake, timeDelta);

		if (CheckSpriteIntersection(*snake.head, apple)) {
			eatAppleSound.play();

			GrowSnake(snake);

			// Increase eaten apples counter
			numEatenApples++;
			
			// Move apple to a new random position
			SetSpriteRandomPosition(apple, background.getGlobalBounds(), snake.body);

			// Increase snake speed
			if (Application::Instance().GetGame().IsEnableOptions(GameOptions::WithAcceleration)) {
				snake.speed += ACCELERATION;
			}
		}

		const bool isGameFinished = numEatenApples == MAX_APPLES && !Application::Instance().GetGame().IsEnableOptions(GameOptions::InfiniteApples);
		
		if (isGameFinished
			|| !HasSnakeCollisionWithRect(snake, background.getGlobalBounds()) // Check collision with screen border
			|| CheckSnakeCollisionWithHimself(snake)		// Check collision with screen border
			|| FullCheckCollisions(rocks.begin(), rocks.end(), *snake.head)) // Check collision with rocks
		{
			gameOverSound.play();
			
			Game& game = Application::Instance().GetGame();

			// Find snake in records table and update his score
			game.UpdateRecord(PLAYER_NAME, numEatenApples);
			game.PushState(GameStateType::GameOver, false);
		}

		scoreText.setString("Apples eaten: " + std::to_string(numEatenApples));
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		// Draw snake
		DrawSnake(snake, window);
		// Draw apples
		DrawSprite(apple, window);
		// Draw rocks
		DrawSprites(rocks.begin(), rocks.end(), window);

		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
}
