//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#ifndef _RENDER_TARGET_APP_H
#define _RENDER_TARGET_APP_H

#include <system/application.h>
#include <maths/vector2.h>
#include <vector>
#include <graphics/mesh_instance.h>
#include "primitive_builder.h"
#include "build\vs2017\car.h"
#include "build\vs2017\mesh_handler.h"
#include "build\vs2017\obstacle.h"
#include "build\vs2017\physics_Handler.h"
#include "build\vs2017\ar_handler.h"
#include <map>
#include <unordered_map>
#include "build\vs2017\state_handler.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class Renderer3D;
	class Mesh;
	class RenderTarget;
	class TextureVita;
	class InputManager;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
class ARApp : public gef::Application
{
public:
	ARApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
private:
	//Game states to be displayed to screen
	char* game_states_array[5] = { "SPLASH", "GAME", "END", "MENU" };

	void InitFont();
	void CleanUpFont();
	void DrawHUD();

	void RenderOverlay();
	void SetupLights();

	//Detect user input
	gef::InputManager* input_manager_;
	InputHandler input_handler;

	//Render sprites and 3D objects
	gef::SpriteRenderer* sprite_renderer_;
	gef::Renderer3D* renderer_3d_;
	gef::Font* font_;
	gef::Sprite sprite;

	//Obstacle types
	Obstacle box_obstacle, inverter_obstacle;

	//map of all obstacles
	std::map<std::string, Obstacle> obstacles_map_;

	float fps_;

	//Display meshes
	MeshHandler mesh_handler;
	gef::Mesh* m_mesh;
	gef::Scene* m_model_scene;

	bool input_toggleX, input_toggleS, input_toggle_start, input_toggle_select;

	//Handler state machine
	StateHandler* state_handler;
};
#endif // _RENDER_TARGET_APP_H
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//