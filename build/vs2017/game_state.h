//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#pragma once
#include "state_base.h"
#include "ar_handler.h"
#include "obstacle.h"
#include "car.h"
#include "physics_Handler.h"
#include "mesh_handler.h"
#include "error_state.h"
#include "../primitive_builder.h"

class GameState : StateBase
{
public:
	inline GameState(): renderer_3d_(NULL),
						primitive_builder_(NULL){};
	inline ~GameState() {};

	//Overridden functions from state_base.h
	void Init(gef::Platform& platform) override;
	bool Update(gef::InputManager* input_manager, float dt, GameStates& game_state, ErrorCodes& error_code) override;
	void Render(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d_) override;
	void CleanUp() override;

	inline void setARHandler(ARHandler& ar) { ar_handler = ar; }

	//Return the current score to the state_handler
	inline int getScore() { return score; }

	//Return if the player is currently colliding with something
	inline bool isColliding() { return colliding; }

	ErrorState error_state;

private:
	inline void Input(gef::InputManager* input_manager, GameStates& game_state) override;

	//Detect which markers are most left, right, top and bottom
	void getCorners(gef::Matrix44& left, gef::Matrix44& right, gef::Matrix44& bottom, gef::Matrix44& top, int ID, int ID2);

	//Render 3D objects
	class gef::Renderer3D* renderer_3d_;
	PrimitiveBuilder* primitive_builder_;

	//Display 2D sprites and textures
	gef::Texture* m_screen_texture;
	gef::Sprite* m_screen_sprite;
	float distanceZ;

	//AR handler to control all ar specific elements such as finding markers and displaying the camera feed to the screen
	ARHandler ar_handler;

	//enum of error codes
	ErrorCodes error_codes;

	//Player car object
	Car player_car;

	//Obstacles available in the game
	Obstacle* obstacles[2];
	Obstacle* oil;
	std::string obstacle_names[2] = { "Car", "Invert" };

	//Obstacles currently in use
	std::map<std::string, Obstacle*> ObstaclesInPlay_;

	//Map of markers in play with ID numbers
	std::map<int, gef::Matrix44> markerMap;

	bool init_toggle;
	int zAxis;

	//Current player score updated every 50 frames
	int score;
	int counter;

	//Detect collisions between objects
	Colliding collision_handler;
	bool colliding;

	//Load meshes
	MeshHandler mesh_handler;
	gef::Mesh* m_mesh;
	gef::Scene* m_model_scene;

	//Create a copy of the platform object
	gef::Platform* platform_cpy;

	//Create a copy of the error code
	ErrorCodes error_code_cpy;

	//Markers
	gef::Matrix44 left, right, top, bottom, car_marker, previous_marker;

	//Random X and Z positions for obstacles
	float random_obstacle_Z;
	float obstacle_Y;

	//Marker reliability check
	int marker_truth;

	//Obstacle meshes
	gef::Mesh* car_mesh, *oil_mesh;

	//Materials for objects
	gef::Texture* road_texture, *checker_texture, *oil_texture, *car_marker_texture, *oil_marker_texture;
	gef::Material road_material, checker_material, oil_material, car_marker_material, oil_marker_material;

	//Game objects not using models
	GameObject* road, *Show_Car_marker, *Show_Obstacle_marker[3];

	//Invert player controls
	int invertor;
	float inverted_counter;

	//Road placement
	gef::Matrix44 final_road_matrix;


};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
