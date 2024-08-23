#pragma once
#include <string>

namespace ArkanoidGame
{
	// Resources path
	const std::string RESOURCES_PATH = "Resources/";
	const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
	const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
	const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";

	// Game settings constants
	const unsigned int SCREEN_WIDTH = 800;
	const unsigned int SCREEN_HEIGHT = 600;
	const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps
	const int MAX_APPLES = 80;

	const float PlATFORM_SIZE = 1.f;
	const float PLATFORM_SPEED = 600.f;
	const float BALL_SIZE = 20.f;
	const float BALL_SPEED = 200.f;
	const float BRICK_WIDTH = 80.f;
	const float BRICK_HEIGHT = 32.f;
	const int NUM_OF_BRICKS = 10;

	const int MAX_RECORDS_TABLE_SIZE = 5;
	extern const char* PLAYER_NAME; // We need to define this constant in some CPP

	const std::string GAME_NAME = "ArkanoidGame";
}
