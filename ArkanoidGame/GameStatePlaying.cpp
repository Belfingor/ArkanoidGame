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
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color::Blue);

		// Init platform
		platform.Init();
		ball.Init();

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
		platform.Update(timeDelta);
		ball.Update(timeDelta);
		if (DoShapesCollide(platform.GetPlatformCollider(), ball.GetBallCollider()))
		{
			ball.BounceOfPlatform();
		}

		if (ball.IsGameLost())
		{
			Game& game = Application::Instance().GetGame();
			game.PushState(GameStateType::GameOver, false);
			gameOverSound.play();
		}
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		// Draw snake
		platform.Draw(window);
		ball.Draw(window);

		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}
}
