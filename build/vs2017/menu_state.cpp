//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "menu_state.h"
#include <graphics\texture.h>
#include <graphics\sprite.h>
#include <graphics\sprite_renderer.h>
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void MenuState::Init(gef::Platform& platform)
{
	//texture to display to screen
	m_screen_texture = CreateTextureFromPNG("menu.png", platform);
	m_flag_texture = CreateTextureFromPNG("flag.png", platform);
	m_instructions_texture = CreateTextureFromPNG("instructions.png", platform);
	m_example1 = CreateTextureFromPNG("marker_example_1.png", platform);
	m_example2 = CreateTextureFromPNG("marker_example_2.png", platform);
	m_example3 = CreateTextureFromPNG("marker_example_3.png", platform);

	height = 660.f;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
bool MenuState::Update(gef::InputManager* input_manager, float dt, GameStates& game_state, ErrorCodes& error_code)
{
	Input(input_manager, game_state);
	return true;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void MenuState::Input(gef::InputManager* input_manager, GameStates& game_state)
{
	//If user presses select go to splash screen
	if (input_handler.ControllerButtonPressed(*input_manager, gef_SONY_CTRL_SELECT))
	{
		game_state = GameStates::SPLASH;
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void MenuState::Render(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d_)
{
	//Create sprite to render to screen
	sprite_renderer->Begin();
	if (m_screen_texture)
	{
		gef::Sprite screen_sprite;
		screen_sprite.set_position(gef::Vector4(480.f, 272.f, 0.f));
		screen_sprite.set_height(544);
		screen_sprite.set_width(960);
		screen_sprite.set_texture(m_screen_texture);
		sprite_renderer->DrawSprite(screen_sprite);

		//Render how to play text
		gef::Sprite m_instructions_sprite;
		m_instructions_sprite.set_position(gef::Vector4(480.f, height, 0.f));
		m_instructions_sprite.set_height(1232);
		m_instructions_sprite.set_width(720);
		m_instructions_sprite.set_texture(m_instructions_texture);
		sprite_renderer->DrawSprite(m_instructions_sprite);

		gef::Sprite flag_sprite;
		flag_sprite.set_position(gef::Vector4(480.f, height + 600, 0.f));
		flag_sprite.set_height(328);
		flag_sprite.set_width(480);
		flag_sprite.set_texture(m_flag_texture);
		sprite_renderer->DrawSprite(flag_sprite);

		//Render marker layout examples
		gef::Sprite example1_sprite;
		example1_sprite.set_position(gef::Vector4(480.f, height + 930, 0.f));
		example1_sprite.set_height(340);
		example1_sprite.set_width(432);
		example1_sprite.set_texture(m_example1);
		sprite_renderer->DrawSprite(example1_sprite);

		gef::Sprite example2_sprite;
		example2_sprite.set_position(gef::Vector4(480.f, height + (1300), 0.f));
		example2_sprite.set_height(340);
		example2_sprite.set_width(432);
		example2_sprite.set_texture(m_example2);
		sprite_renderer->DrawSprite(example2_sprite);

		gef::Sprite example3_sprite;
		example3_sprite.set_position(gef::Vector4(480.f, height + (1670), 0.f));
		example3_sprite.set_height(340);
		example3_sprite.set_width(432);
		example3_sprite.set_texture(m_example3);
		sprite_renderer->DrawSprite(example3_sprite);
	}
	sprite_renderer->End();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void MenuState::CleanUp()
{
	if (m_screen_texture)
	{
		delete m_screen_texture;
		m_screen_texture = NULL;
	}

	if (m_flag_texture)
	{
		delete m_flag_texture;
		m_flag_texture = NULL;
	}

	if (m_instructions_texture)
	{
		delete m_instructions_texture;
		m_instructions_texture = NULL;
	}

	if (m_example1)
	{
		delete m_example1;
		m_example1 = NULL;
	}

	if (m_example2)
	{
		delete m_example2;
		m_example2 = NULL;
	}

	if (m_example3)
	{
		delete m_example3;
		m_example3 = NULL;
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//