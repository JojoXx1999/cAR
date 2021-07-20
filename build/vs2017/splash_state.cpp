//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "splash_state.h"
#include <graphics\texture.h>
#include <graphics\sprite.h>
#include <graphics\sprite_renderer.h>
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

#define CAR_SPEED 180;
#define SIZE_INCREASE 0.4;

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void SplashState::Init(gef::Platform& platform)
{
	//Create texture to render to screen
	m_screen_texture = CreateTextureFromPNG("splash.png", platform);
	m_car_texture = CreateTextureFromPNG("Car.png", platform);
	m_flag_texture = CreateTextureFromPNG("flag.png", platform);
	car_positionX = -400;
	flag_size_percentage = 1.f;
	increasing_size = true;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
bool SplashState::Update(gef::InputManager* input_manager, float dt, GameStates& game_state, ErrorCodes& error_code)
{
	Input(input_manager, game_state);

	//move car from left to right hand side of the screen 
	car_positionX > 1700 ? car_positionX = -400 : car_positionX += dt * CAR_SPEED;

	if (increasing_size == true)
	{
		flag_size_percentage >= 0.8 ? increasing_size = false : flag_size_percentage += dt * SIZE_INCREASE;
	}
	else
	{
		flag_size_percentage <= 0.5 ? increasing_size = true : flag_size_percentage -= dt * SIZE_INCREASE;
	}

	return true;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void SplashState::Input(gef::InputManager* input_manager, GameStates& game_state)
{
	//If user presses start go to game state
	//If user presses select go to menu state
	if (input_handler.ControllerButtonPressed(*input_manager, gef_SONY_CTRL_START))
	{
		game_state = GameStates::GAME;
	}
	else if (input_handler.ControllerButtonPressed(*input_manager, gef_SONY_CTRL_SELECT))
	{
		game_state = GameStates::MENU;
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void SplashState::Render(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d_)
{
	//Create sprite to render texture to screen
	sprite_renderer->Begin();
	if (m_screen_texture)
	{
		gef::Sprite screen_sprite;
		screen_sprite.set_position(gef::Vector4(480.f, 272.f, 0.f));
		screen_sprite.set_height(544);
		screen_sprite.set_width(960);
		screen_sprite.set_texture(m_screen_texture);
		sprite_renderer->DrawSprite(screen_sprite);

		gef::Sprite car_sprite;
		car_sprite.set_position(gef::Vector4(car_positionX, 272.f, 0.f));
		car_sprite.set_height(544);
		car_sprite.set_width(960);
		car_sprite.set_texture(m_car_texture);
		sprite_renderer->DrawSprite(car_sprite);

		gef::Sprite flag_sprite;
		flag_sprite.set_position(gef::Vector4(500.f, 120.f, 0.f));
		flag_sprite.set_height(272 * flag_size_percentage);
		flag_sprite.set_width(480 * flag_size_percentage);
		flag_sprite.set_texture(m_flag_texture);
		sprite_renderer->DrawSprite(flag_sprite);
	}
	sprite_renderer->End();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void SplashState::CleanUp()
{
	if (m_screen_texture)
	{
		delete m_screen_texture;
		m_screen_texture = NULL;
	}

	if (m_car_texture)
	{
		delete m_car_texture;
		m_car_texture = NULL;
	}

	if (m_flag_texture)
	{
		delete m_flag_texture;
		m_flag_texture = NULL;
	}

}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//