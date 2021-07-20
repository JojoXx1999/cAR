//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "state_handler.h"
#include <graphics\sprite_renderer.h>
#include <graphics\renderer_3d.h>
#include <graphics\font.h>
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void StateHandler::Init(gef::Platform& platform, gef::Font* font)
{
	//Initilaise all states
	game_states = GameStates::SPLASH;

	m_splash_state = new SplashState();
	m_menu_state = new MenuState();
	m_game_state = new GameState();
	m_end_state = new EndState();

	m_splash_state->Init(platform);
	m_game_state->Init(platform);
	m_menu_state->Init(platform);
	m_end_state->Init(platform);

	ar_handler.Init();
	m_game_state->setARHandler(ar_handler);

	platform_cpy = &platform;
	font_cpy = font;
	debounce = false;
	color = 0xff000000;
	alpha_mask = 0xff000000;
	transparency = 0.f;
	increasing_transparency = true;

	text_height = 70.f;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
bool StateHandler::Update(gef::InputManager* input_manager, float dt)
{
	//Update current state
	switch (game_states)
	{
	case SPLASH:
		color = 0xff000000;
		m_splash_state->Update(input_manager, dt, game_states, error_code);
		if (increasing_transparency == true)
		{
			transparency += 1 * dt;
			if (transparency >= 1)
				increasing_transparency = false;
		}
		else
		{
			transparency -= 1 * dt;
			if (transparency <= 0)
				increasing_transparency = true;
		}

		transprent_color = (color | alpha_mask)&((UInt32)(alpha_mask*transparency) | (~alpha_mask));

		if (game_states == GAME)
		{
			m_game_state->Init(*platform_cpy);
		}
		break;

	case MENU:
		color = 0xffffffff;
		m_menu_state->Update(input_manager, dt, game_states, error_code);

		float tmp = input_handler.LeftStickY(*input_manager);

		if (text_height + (10 * tmp) > -2000 && text_height + (10 * tmp) < 200)
		{
			text_height += 10 * tmp;
			m_menu_state->height += 10 * tmp;
		}		
		break;

	case GAME:
		color = 0xff000000;
		m_game_state->Update(input_manager, dt, game_states, error_code);

		if (game_states == END)
		{
			m_game_state->CleanUp();
		}
		break;

	case END:
		color = 0xffffffff;
		m_end_state->Update(input_manager, dt, game_states, error_code);
		break;

	default: break;

	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void StateHandler::Render(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d)
{
	//Render current state
	switch (game_states)
	{
	case SPLASH:
		m_splash_state->Render(sprite_renderer, renderer_3d);
		break;

	case GAME:
		m_game_state->Render(sprite_renderer, renderer_3d);
		break;

	case MENU:
		m_menu_state->Render(sprite_renderer, renderer_3d);
		break;

	case END:
		m_end_state->Render(sprite_renderer, renderer_3d);
		break;
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//Display HUD information to the screen
void StateHandler::HUD(gef::SpriteRenderer* sprite_renderer)
{
		font_cpy->RenderText(sprite_renderer, gef::Vector4(700.0f, 480.0f, -0.9f), 1.0f, color, gef::TJ_LEFT, "GameState: %s", game_states_array[(int)game_states]);

		if (game_states == SPLASH)
		{
			font_cpy->RenderText(sprite_renderer, gef::Vector4(500.0f, 20.0f, -0.9f), 1.0f, transprent_color, gef::TJ_CENTRE, "Press Start to Begin");
			font_cpy->RenderText(sprite_renderer, gef::Vector4(0.0f, 480.0f, -0.9f), 1.0f, color, gef::TJ_LEFT, "Press Select for the Menu");
		}
		else if (game_states == GAME)
		{
			font_cpy->RenderText(sprite_renderer, gef::Vector4(500.0f, 20.0f, -0.9f), 1.0f, color, gef::TJ_CENTRE, "Score: %d", m_game_state->getScore());
			if (error_code != NO_ERROR)
			{
				std::string tmp = m_game_state->error_state.DisplayError();
				font_cpy->RenderText(sprite_renderer, gef::Vector4(480.0f, 292.0f, 0.0f), 1.0f, color, gef::TJ_CENTRE, &tmp[0]);
			}
			if (m_game_state->isColliding())
			{
				font_cpy->RenderText(sprite_renderer, gef::Vector4(700.0f, 450.0f, -0.9f), 1.0f, color, gef::TJ_LEFT, "COLLIDING");
			}		
		}
		else if (game_states == END)
		{
			font_cpy->RenderText(sprite_renderer, gef::Vector4(0.0f, 480.0f, -0.9f), 1.0f, color, gef::TJ_LEFT, "Press Start for the Splash Screen");
			font_cpy->RenderText(sprite_renderer, gef::Vector4(500.0f, 250.0f, -0.9f), 2.0f, color, gef::TJ_CENTRE, "CRASH!");
			font_cpy->RenderText(sprite_renderer, gef::Vector4(500.0f, 320.0f, -0.9f), 1.0f, color, gef::TJ_CENTRE, "Your Final Score Was: %d", m_game_state->getScore());
		}
		else if (game_states == MENU)
		{
			font_cpy->RenderText(sprite_renderer, gef::Vector4(0.0f, 480.0f, -0.9f), 1.0f, color, gef::TJ_LEFT, "Press Select for the Splash Screen");
			font_cpy->RenderText(sprite_renderer, gef::Vector4(480.0f, text_height, -0.9f), 2.0f, color, gef::TJ_CENTRE, "How to Play");
			font_cpy->RenderText(sprite_renderer, gef::Vector4(480.0f, text_height + 1300, -0.9f), 1.0f, color, gef::TJ_CENTRE, "Example Marker Layouts:");
			font_cpy->RenderText(sprite_renderer, gef::Vector4(0.0f, 510.0f, -1.f), 1.0f, 0xff0000ff, gef::TJ_LEFT, "Use the left analogue stick to scroll");

			for (int i = 0; i < 3; ++i)
				font_cpy->RenderText(sprite_renderer, gef::Vector4(480.0f, text_height + 1320 + (i * 370), -0.9f), 1.0f, color, gef::TJ_CENTRE, "---------------------------------------------------------------------------------------");
		}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//