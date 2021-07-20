//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#pragma once
#include "state_base.h"

class EndState : StateBase
{
public:
	inline EndState() {};
	inline ~EndState() {};

	//Overridden functions from state_base.h
	void Init(gef::Platform& platform) override;
	bool Update(gef::InputManager* input_manager, float dt, GameStates& game_state, ErrorCodes& error_code) override;
	void Render(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d_) override;
	void CleanUp() override;

private:
	void Input(gef::InputManager* input_manager, GameStates& game_state) override;

	//Texture to display on the screen
	gef::Texture* m_end_screen_texture, *m_flag_texture;
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
