#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include "Platform.h"
#include "Math.h"

#include <cassert>
#include <sstream>

namespace ArkanoidGame
{
	void GameStatePlayingData::Init()
	{
		// Init game resources (terminate if error)
		assert(font.loadFromFile(SETTINGS.FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "Death.wav"));
		assert(heartTexture.loadFromFile(SETTINGS.HEART_TEXTURE_PATH));

		for (int i = 0; i < SETTINGS.PLAYER_LIVES; i++)
		{
			sf::Sprite sprite; 
			InitSprite(sprite, 63.f, 50.f, heartTexture);
			sprite.setPosition(170.f + i * 60.f, 30.f);
			heartSprites.push_back(std::move(sprite));
		}

		// Init background
		background.setSize(sf::Vector2f(SETTINGS.SCREEN_WIDTH, SETTINGS.SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color::Blue);

		// Init GameObjects
		gameObjects.emplace_back(std::make_shared<Platform>(sf::Vector2f({ SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - SETTINGS.PlATFORM_HEIGHT/ 2.f })));
		auto ball = std::make_shared<Ball>(sf::Vector2f({ SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT / 2.f - SETTINGS.BALL_SIZE / 2.f }));
		ball->AddObserver(weak_from_this());
		gameObjects.emplace_back(ball);

		//Init Brick Factories
		brickFactories.emplace(BrickType::Simple, std::make_unique<SimpleBrickFactory>());
		brickFactories.emplace(BrickType::MultiHit, std::make_unique<MultiHitBrickFactory>());
		brickFactories.emplace(BrickType::Unbreackable, std::make_unique<UnbreackableBrickFactory>());
		brickFactories.emplace(BrickType::Glass, std::make_unique<GlassBrickFactory>());
		CreateBricks();
	
		// Reset score
		RECORDS->playerScore = 0;

		//Init Texts
		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);
		scoreText.setString("Score: " + std::to_string(RECORDS->playerScore));

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
				Application::Instance().GetGame().PauseGame();
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
		
		// Check if need to deactivate any buffs
		UpdateBuffTimer(timeDelta);
		if (isTimeToRemoveFireBall)
		{
			DeactivateFireBallBuff(ball);
		}

		auto isCollision = platform->CheckCollision(ball); 
		if (gameObjects.size() > 2) //only checking collision with platform and modifier if there are any to check with
		{
			for (size_t i = 2; i < gameObjects.size(); i++) 
			{
				std::shared_ptr<Modifier> Mod = std::dynamic_pointer_cast<Modifier>(gameObjects[i]);
				if (Mod->CheckCollision(platform))
				{
					gameObjects.erase(gameObjects.begin() + i);
					switch (Mod->GetModifierType())
					{
					case ModifierType::FireBall:
						ActivateFireBallBuff(ball);
						StartBuffTimer();
						break;
					//-----------------------------------------------------------------------------
					case ModifierType::FragileBricks:
						
						break;
					case ModifierType::SpeedBoost:
						
						break;
					//-----------------------------------------------------------------------------
					default:
						break;
					}
				}
				else if (Mod->DidModReachTheFloor())
				{
					gameObjects.erase(gameObjects.begin() + i);
				}
			}
		}

		bool needInverseDirX = false;
		bool needInverseDirY = false;
		bool hasBrokeOneBrick = false;
		//remove-erase idiom
		bricks.erase(
			std::remove_if(bricks.begin(), bricks.end(),
				[ball, &hasBrokeOneBrick, &needInverseDirX, &needInverseDirY, this](auto brick) 
				{
					if ((!hasBrokeOneBrick) && brick->CheckCollision(ball))
					{
						auto glassBrick = dynamic_cast<GlassBrick*>(brick.get());
						auto unbreackableBrick = dynamic_cast<UnbreackableBrick*>(brick.get());
						if (!glassBrick)
						{
							hasBrokeOneBrick = true;
							const auto ballPos = ball->GetPosition();
							const auto brickRect = brick->GetRect();
							
							if (!isFireBallActive || unbreackableBrick) //FireBall does not invert from bricks
							{
								GetBallInverse(ballPos, brickRect, needInverseDirX, needInverseDirY);
							}
						}
					}
					if (brick->IsBroken())
					{
						RECORDS->playerScore += brick->scoreContainer;
						scoreText.setString("Score: " + std::to_string(RECORDS->playerScore));

						// Init modifier on collision with any brick with 10% chance
						int modifierProcChance = 1 + (rand() % 10);
						if (modifierProcChance > 2) //replace 2 with 5 later on
						{
							ChooseRandomModifierToInit(brick->GetPosition().x, brick->GetPosition().y);
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

		DrawSprites(heartSprites.begin(), heartSprites.end(), window);
	}
	void GameStatePlayingData::LoadNextLevel()
	{
		if (currentLevel >= levelLoader.GetLevelCount() - 1)
		{
			Game& game = Application::Instance().GetGame();
			game.WinGame();
		}
		else
		{
			std::shared_ptr <Platform> platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
			std::shared_ptr <Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
			platform->restart();
			ball->restart();

			bricks.clear();
			++currentLevel;
			CreateBricks();
		}
	}
	void GameStatePlayingData::Notify(std::shared_ptr<IObservable> observable)
	{
		if (auto brick = std::dynamic_pointer_cast<Brick>(observable); brick)
		{
			--breakableBricksCount;
			Game& game = Application::Instance().GetGame();
			if (breakableBricksCount == 0)
			{
				game.LoadNextLevel();
			}
		}
		if (auto ball = std::dynamic_pointer_cast<Ball>(observable); ball)
		{
			if (ball->GetPosition().y > gameObjects.front()->GetRect().top)
			{
				
				--ball->playersLives;
				if (heartSprites.size() == 1)
				{
					heartSprites.pop_back();
					gameOverSound.play();
					Application::Instance().GetGame().LoseGame();
				}
				else
				{
					ball->restart();
					heartSprites.pop_back();
				}
			}
		}
	}
	void GameStatePlayingData::CreateBricks()
	{
		for (const auto& pair : brickFactories)
		{
			pair.second->ClearCounter();
		}
		auto self = weak_from_this();
		auto level = levelLoader.GetLevel(currentLevel);

		for (auto pairPosBrickType : level.m_bricks)
		{
			auto brickType = pairPosBrickType.second;
			sf::Vector2i pos = pairPosBrickType.first;

			sf::Vector2f position
			{
				(float)(SETTINGS.BRICK_WIDTH / 2.f + pos.x * (SETTINGS.BRICK_WIDTH)) ,
				(float)pos.y * SETTINGS.BRICK_HEIGHT
			};
	
			bricks.emplace_back(brickFactories.at(brickType)->CreateBrick(position));
			bricks.back()->AddObserver(self);
		}
		
		for (const auto& pair : brickFactories)
		{
			breakableBricksCount += pair.second->GetCreatedBreackableBricksCount();
		}
	}

	void GameStatePlayingData::GetBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& brickRect, bool& needInverseDirX, bool& needInverseDirY)
	{
		if (ballPos.y > brickRect.top + brickRect.height)
		{
			needInverseDirY = true;
		}
		else if (ballPos.y < brickRect.top)
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
	void GameStatePlayingData::ChooseRandomModifierToInit(float posX, float posY)
	{
		int randomModifier = 1 + (rand() % 3);
		switch (randomModifier)
		{
		case 1:
			gameObjects.emplace_back(std::make_shared<FireBallModifier>(sf::Vector2f({ posX, posY })));
			break;
		case 2:
			gameObjects.emplace_back(std::make_shared<FireBallModifier>(sf::Vector2f({ posX, posY })));
			break;
		case 3:
			gameObjects.emplace_back(std::make_shared<FireBallModifier>(sf::Vector2f({ posX, posY })));
			break;
		default:
			break;
		}
	}

	//-----------------------------------------------------------------------------

	void GameStatePlayingData::ActivateFireBallBuff(std::shared_ptr<Ball> ball)
	{
		ball = std::make_shared<FireBallDecorator>(ball);
		ball->AddObserver(weak_from_this());
		gameObjects[1] = ball;
		isFireBallActive = true;
	}
	void GameStatePlayingData::DeactivateFireBallBuff(std::shared_ptr<Ball> ball)
	{
		ball = std::make_shared<Ball>(ball->GetPosition(), ball->GetDirection());
		gameObjects[1] = ball;
		ball->AddObserver(weak_from_this());
		isFireBallActive = false;
		isTimeToRemoveFireBall = false;
	}
	//-----------------------------------------------------------------------------
}
