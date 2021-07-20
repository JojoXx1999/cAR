//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#pragma once
#include "state_base.h"

class MenuState : StateBase
{
public:
	inline MenuState() {};
	inline ~MenuState() {};

	//Overridden functions from state_base.h
	void Init(gef::Platform& platform) override;
	bool Update(gef::InputManager* input_manager, float dt, GameStates& game_state, ErrorCodes& error_code) override;
	void Render(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d_) override;
	void CleanUp() override;

	//Height of text
	float height;

private:
	void Input(gef::InputManager* input_manager, GameStates& game_state) override;

	//Texture to display on the screen
	gef::Texture* m_screen_texture, *m_flag_texture, *m_instructions_texture, *m_example1, *m_example2, *m_example3;
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
