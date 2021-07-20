//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#pragma once
#include "state_base.h"
#include "ar_handler.h"
#include <map>

class ErrorState : StateBase
{
public:
	inline ErrorState() {};
	inline ~ErrorState() {};

	//Overridden functions from state_base.h
	inline void Init(gef::Platform& platform) override {};
	inline bool Update(gef::InputManager* input_manager, float dt, GameStates& game_state, ErrorCodes& error_code) override { return true; };
	inline void Render(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d_) override {};
	inline void CleanUp() override {};

	//Detect any errors
	void DetectError(ErrorCodes& error_code, std::map<int, gef::Matrix44>& markerMap, ARHandler& ar_handler, gef::Matrix44 car_marker, gef::Matrix44 top,
					 gef::Matrix44 bottom, gef::Matrix44 left, gef::Matrix44 right);

	//Display error message depending on error
	std::string DisplayError();
private:
	inline void Input(gef::InputManager* input_manager, GameStates& game_state) override {};
	ErrorCodes error_code_cpy;
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
