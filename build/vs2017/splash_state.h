//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#pragma once
#include "state_base.h"

class SplashState : StateBase
{
public:
	inline SplashState() {};
	inline ~SplashState() {};

	//Overridden functions from state_base.h
	void Init(gef::Platform& platform) override;
	bool Update(gef::InputManager* input_manager, float dt, GameStates& game_state, ErrorCodes& error_code) override;
	void Render(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d_) override;
	void CleanUp() override;

private:
	void Input(gef::InputManager* input_manager, GameStates& game_state) override;

	//Texture to display on the screen
	gef::Texture* m_screen_texture;
	gef::Texture* m_car_texture, *m_flag_texture;
	float car_positionX, flag_size_percentage;
	bool increasing_size;
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
