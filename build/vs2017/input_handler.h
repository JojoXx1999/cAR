#pragma once
#include <input/sony_controller_input_manager.h>

namespace gef
{
	class SonyControllerInputManager;
	class SonyController;
	class InputManager;
}

class InputHandler
{
public:

	inline InputHandler() { Init(); }
	void Init();

	//Get user input using the vita
	bool IsController(gef::InputManager& input_manager);
	bool ControllerButtonPressed(gef::InputManager& input_manager, int button_ID);
	bool ControllerButtonReleased(gef::InputManager& input_manager, int button_ID);
	float RightStickX(gef::InputManager& input_manager);
	float RightStickY(gef::InputManager& input_manager);
	float LeftStickY(gef::InputManager& input_manager);
	float LeftStickX(gef::InputManager& input_manager);

private:
	float speed;
	gef::SonyControllerInputManager* controller_input;
	const gef::SonyController* controller;
};
