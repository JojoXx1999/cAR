//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#pragma once
#include "state_base.h"
#include "splash_state.h"
#include "menu_state.h"
#include "game_state.h"
#include "end_state.h"
#include "input_handler.h"

class StateHandler
{
public:
	inline StateHandler::StateHandler() {}
	inline StateHandler::~StateHandler() {}

	//Standard functions
	void Init(gef::Platform& platform, gef::Font* font);
	bool Update(gef::InputManager* input_manager, float dt);
	void Render(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d);
	void HUD(gef::SpriteRenderer* sprite_renderer);

private:
	//Contain all possible states
	StateBase* m_state_base;
	SplashState* m_splash_state;
	GameState* m_game_state;
	MenuState* m_menu_state;
	EndState* m_end_state;

	//GameStates game_state;
	char* game_states_array[5] = { "SPLASH", "GAME", "END", "ERROR", "MENU" };

	bool debounce;

	//current state
	GameStates game_states;

	//current error
	ErrorCodes error_code;

	//Variables for text
	gef::Font* font_cpy;
	UInt32 color, alpha_mask, transprent_color;
	float transparency;
	gef::Platform* platform_cpy;
	bool increasing_transparency;
	float text_height;

	//Get user input
	InputHandler input_handler;

	//Handle AR
	ARHandler ar_handler;
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//