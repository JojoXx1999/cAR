//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "error_state.h"
#include <graphics\texture.h>
#include <graphics\sprite.h>
#include <graphics\sprite_renderer.h>
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void ErrorState::DetectError(ErrorCodes& error_code, std::map<int, gef::Matrix44>& markerMap, ARHandler& ar_handler, gef::Matrix44 car_marker, gef::Matrix44 top,
	gef::Matrix44 bottom, gef::Matrix44 left, gef::Matrix44 right)
{
	error_code = ErrorCodes::NO_ERROR;

	//Set error codes to be displayed to screen
	if (markerMap.size() < 2 ||
		(!ar_handler.isMarkerFound(markerMap.begin()->first) &&
			!ar_handler.isMarkerFound(std::next(markerMap.begin(), 1)->first)))
	{
		error_code = NO_WORLD;
	}
	else if (markerMap.size() < 3 || (!ar_handler.isMarkerFound(std::next(markerMap.begin(), 2)->first)))
	{
		error_code = NO_CAR;
	}
	else if (markerMap.size() == 3 || (!ar_handler.isMarkerFound(std::next(markerMap.begin(), 3)->first)))
	{
		error_code = NO_OBSTACLES;
	}
	else if (markerMap.size() > 3 && (car_marker.GetTranslation().x() < left.GetTranslation().x()
		|| car_marker.GetTranslation().x() > right.GetTranslation().x()
		|| car_marker.GetTranslation().z() < bottom.GetTranslation().z()
		|| car_marker.GetTranslation().z() > top.GetTranslation().z()))
	{
		error_code = CAR_OUT_OF_BOUNDS;
	}

	if (error_code_cpy != error_code)
		error_code_cpy = error_code;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
std::string ErrorState::DisplayError()
{
	std::string error_msg;

	//Return error message depending on the detected error
	switch (error_code_cpy)
	{
	case NO_WORLD:
		error_msg = "NO GAME WORLD DETECTED";
		break;
	case NO_CAR:
		error_msg = "PLEASE ADD A CAR";
		break;
	case CAR_OUT_OF_BOUNDS:
		error_msg = "THE CAR YOU ARE TRYING TO PLACE IS OUTSIDE THE GAME WORLD";
		break;
	case NO_OBSTACLES:
		error_msg = "THERE MUST BE AT LEAST ONE OBSTACLE IN PLAY";
		break;
	default:
		error_msg = "";
		break;
	}

	return error_msg;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//