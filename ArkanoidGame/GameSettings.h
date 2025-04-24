#pragma once
#include <string>
#define SETTINGS GameWorld::Instance()

namespace ArkanoidGame
{

	class GameWorld
	{
	private:
		GameWorld() = default;

	public:
		static GameWorld& Instance()
		{
			static GameWorld gameWorld;
			return gameWorld;
		}

		// Resources path
		const std::string RESOURCES_PATH = "Resources/";
		const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
		const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
		const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";
		const std::string LELEVS_CONFIG_PATH = RESOURCES_PATH + "levels.config";
		const std::string RECORDS_TABLE_PATH = RESOURCES_PATH + "Records.dat";
		const std::string HEART_TEXTURE_PATH = TEXTURES_PATH + "Heart.png";
		const std::string FIREBALL_MODIFIER_TEXTURE_PATH = TEXTURES_PATH + "FireBallMod.png";
		const std::string FRAGILEBRICKS_MODIFIER_TEXTURE_PATH = TEXTURES_PATH + "FragileBricksMod.png";
		const std::string SPEEDBOOST_MODIFIER_TEXTURE_PATH = TEXTURES_PATH + "SpeedBoostMod.png";
		const std::string FIREBALL_TEXTURE_PATH = TEXTURES_PATH + "FireBall.png";

		// Game settings constants
		const unsigned int SCREEN_WIDTH = 800;
		const unsigned int SCREEN_HEIGHT = 600;
		const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps

		//--------------------------------------------------------------------------------
		const float PLATFORM_WIDTH = 64.f;
		const float PlATFORM_HEIGHT = 24.f;
		const float PLATFORM_SPEED = 600.f;

		const float WIDE_PLATFORM_WDTH = 96.f;
		const float WIDE_PLATFORM_HEIGHT = PlATFORM_HEIGHT;
		//----------------------------------------------
		const float BALL_SIZE = 20.f;
		const float BALL_SPEED = 300.f;
		//----------------------------------------------
		const float MODIFIER_SIZE = 10.f;
		const float MODIFIER_SPEED = 300.f;
		const float FIREBALL_SPEED = 400.f;
		const float BUFF_DURATION = 10.f; // in seconds
		//----------------------------------------------
		const float BRICK_WIDTH = 80.f;
		const float BRICK_HEIGHT = 32.f;
		const int NUM_OF_BRICKS_PER_COLLUMN = 2;
		const int NUM_OF_BRICKS_PER_ROW = 15;
		const float BRICK_BREAK_DELAY = .3f;
		const int MULTIHIT_BRICK_HITPOINTS = 2;
		const int NUM_OF_UBREAKABLE_BRICKS = 3;
		//--------------------------------------------------------------------------------
		const int MAX_RECORDS_TABLE_SIZE_MAIN_MENU = 10;
		const int MAX_RECORDS_TABLE_SIZE_GAME_OVER = 5;
		//--------------------------------------------------------------------------------
		const int MULTIHIT_BRICK_SCORE = 3;
		const int PLAYER_LIVES = 3;
		//--------------------------------------------------------------------------------
		const std::string GAME_NAME = "ArkanoidGame";
	};
}