//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#pragma once
#include "game_object.h"
#include "input_handler.h"

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
namespace gef
{
	class InputManager;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//Car is child of GameObject
class Car : public GameObject
{
public:
	inline Car() { Init(); }
	void Init();
	bool Update(float frame_time, gef::InputManager* input_manager);

	//Return velocity and position of the car
	inline gef::Vector4 getVelocity() { return m_velocity; }
	inline gef::Vector4 getPosition() { return m_position; }

	//Move the car using the user inputs
	void Move(gef::InputManager& input_manager, float dt, float invertor);

	void BuildTransformation();

	//Set position and velocity of car
	inline void setPosition(gef::Vector4 pos) { m_position = pos; }
	inline void setVelocity(gef::Vector4 velo) { m_velocity = velo; }

	//If car is inside the gameworld
	bool stayInWorld(gef::Matrix44 left, gef::Matrix44 right, gef::Matrix44 top, gef::Matrix44 bottom, gef::Matrix44 marker);

	//Car initial matrix
	inline void setInitial(gef::Matrix44 init) { m_init = init; }
	inline gef::Matrix44* getInitial() { return &m_init; }

	//Scale of Car mesh
	gef::Vector4 m_scale;

private:
	gef::Vector4 m_position;
	gef::Vector4 m_velocity;
	gef::Matrix44 m_init;
	gef::Vector4 m_initDir;

	float m_rotation;

	InputHandler input_handler;
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
