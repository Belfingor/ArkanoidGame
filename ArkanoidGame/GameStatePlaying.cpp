#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>
#include "Platform.h"
#include "Math.h"

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{	
		// Init game resources (terminate if error)
		assert(font.loadFromFile(SETTINGS.FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "Death.wav"));

		// Init background
		background.setSize(sf::Vector2f(SETTINGS.SCREEN_WIDTH, SETTINGS.SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color::Blue);

		// Init GameObjects
		gameObjects.emplace_back(std::make_shared<Platform>(sf::Vector2f({ SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - SETTINGS.PlATFORM_HEIGHT/ 2.f })));
		gameObjects.emplace_back(std::make_shared<Ball>(sf::Vector2f({ SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - SETTINGS.PlATFORM_HEIGHT - SETTINGS.BALL_SIZE / 2.f })));
		CreateBricks();
	
		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		// Init sounds
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
		static auto updateFunctor = [timeDelta](auto obj) { obj->Update(timeDelta); };

		std::for_each(gameObjects.begin(), gameObjects.end(), updateFunctor);
		std::for_each(bricks.begin(), bricks.end(), updateFunctor);


		std::shared_ptr <Platform> platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
		std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);

		auto isCollision = platform->CheckCollision(ball);

		bool needInverseDirX = false;
		bool needInverseDirY = false;

		bool hasBrokeOneBrick = false;
		//remove-erase idiom
		bricks.erase(
			std::remove_if(bricks.begin(), bricks.end(),
				[ball, &hasBrokeOneBrick, &needInverseDirX, &needInverseDirY, this](auto brick) {
					if ((!hasBrokeOneBrick) && brick->CheckCollision(ball))
					{
						auto glassBrick = dynamic_cast<GlassBrick*>(brick.get());
						if (!glassBrick)
						{
							hasBrokeOneBrick = true;
							const auto ballPos = ball->GetPosition();
							const auto brickRect = brick->GetRect();

							GetBallInverse(ballPos, brickRect, needInverseDirX, needInverseDirY);
						}
					}
					return brick->IsBroken();
				}),
			bricks.end()
		);
		if (needInverseDirX) {
			ball->InvertDirectionX();
		}
		if (needInverseDirY) {
			ball->InvertDirectionY();
		}

		const bool isGameWin = bricks.size() == SETTINGS.NUM_OF_UBREAKABLE_BRICKS;
		const bool isGameOver = !isCollision && ball->GetPosition().y > platform->GetRect().top;
		Game& game = Application::Instance().GetGame();

		if (isGameWin) {					// Will create a gameStateType GameWon later to match the condition
			gameOverSound.play();
			game.PushState(GameStateType::GameOver, false);
		}
		else if (isGameOver) {
			gameOverSound.play();
			game.PushState(GameStateType::GameOver, false);
		}
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		static auto drawFunc = [&window](auto block) { block->Draw(window); };
		// Draw game objects
		std::for_each(gameObjects.begin(), gameObjects.end(), drawFunc);
		std::for_each(bricks.begin(), bricks.end(), drawFunc);

		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
	void GameStatePlayingData::CreateBricks()
	{
		int collumn = 0;
		for (; collumn < SETTINGS.NUM_OF_BRICKS_PER_COLLUMN; ++collumn)
		{
			for (int row = 0; row < SETTINGS.NUM_OF_BRICKS_PER_ROW; ++row)
			{
				bricks.emplace_back(std::make_shared<SmoothDestroyBrick>(sf::Vector2f({ SETTINGS.BRICK_WIDTH / 2.f + row * SETTINGS.BRICK_WIDTH, 100.f + collumn * SETTINGS.BRICK_HEIGHT })));
			}
			
		}
		for (int row = 0; row < SETTINGS.NUM_OF_UBREAKABLE_BRICKS; ++row)
		{
			bricks.emplace_back(std::make_shared<UnbreackableBrick>(sf::Vector2f({ SETTINGS.BRICK_WIDTH / 2.f + row * SETTINGS.BRICK_WIDTH, 100.f + collumn * SETTINGS.BRICK_HEIGHT })));
		}
		for (int row = 3; row < 5; ++row)
		{
			bricks.emplace_back(std::make_shared<MultiHitBrick>(sf::Vector2f({ SETTINGS.BRICK_WIDTH / 2.f + row * SETTINGS.BRICK_WIDTH, 100.f + collumn * SETTINGS.BRICK_HEIGHT })));
		}
		for (int row = 5; row < 10; ++row)
		{
			bricks.emplace_back(std::make_shared<GlassBrick>(sf::Vector2f({ SETTINGS.BRICK_WIDTH / 2.f + row * SETTINGS.BRICK_WIDTH, 100.f + collumn * SETTINGS.BRICK_HEIGHT })));
		}
		

	}
	void GameStatePlayingData::GetBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& brickRect, bool& needInverseDirX, bool& needInverseDirY)
	{
		if (ballPos.y > brickRect.top + brickRect.height)
		{
			needInverseDirY = true;
		}
		if (ballPos.x < brickRect.left)
		{
			needInverseDirX = true;
		}
		if (ballPos.x > brickRect.left + brickRect.width)
		{
			needInverseDirX = true;
		}
	}
}
