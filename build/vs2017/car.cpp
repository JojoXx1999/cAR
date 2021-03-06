//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "car.h"
#include "physics_Handler.h"
#include <input/input_manager.h>
#include "maths\math_utils.h"
#include <iostream>

#define SPEED 0.05
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void Car::Init()
{
	m_velocity = gef::Vector4(0.0f, 0.0f, 0.0f); //0.1f = 10cm
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
bool Car::Update(float frame_time, gef::InputManager* input_manager)
{
	BuildTransformation();
	return true;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void Car::BuildTransformation()
{	
	gef::Matrix44 scale;
	scale.Scale(m_scale);

	gef::Matrix44 transform;
	transform.SetIdentity();

	transform.SetTranslation(m_position);
	set_transform(scale * transform);
	
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
bool Car::stayInWorld(gef::Matrix44 left, gef::Matrix44 right, gef::Matrix44 top, gef::Matrix44 bottom, gef::Matrix44 marker)
{
	//Dont let the player go beyond the world bounds
	if (marker.GetTranslation().x() < left.GetTranslation().x() ||
		marker.GetTranslation().x() > right.GetTranslation().x() ||
		marker.GetTranslation().y() > bottom.GetTranslation().y() ||
		marker.GetTranslation().y() < top.GetTranslation().y())
	{
		setVelocity(gef::Vector4(0.f, 0.f, 0.f));
		return true;
	}

	return false;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//Move the car with speed depending on analogue inputs
void Car::Move(gef::InputManager& input_manager, float dt, float invertor)
{
	if (input_handler.LeftStickX(input_manager) > 0 || input_handler.LeftStickX(input_manager) < 0 ||
		input_handler.LeftStickY(input_manager) > 0 || input_handler.LeftStickY(input_manager) < 0)
	{
		if (invertor == 1)
		{
			m_velocity = gef::Vector4(m_velocity.x() + (((input_handler.LeftStickX(input_manager)) * dt)*(float)invertor),
			m_velocity.y() + (((input_handler.LeftStickY(input_manager)) * dt) * (float)invertor), m_velocity.z());
		}
		else
		m_velocity = gef::Vector4(m_velocity.x() - ((input_handler.LeftStickX(input_manager)) * dt), m_velocity.y() - ((input_handler.LeftStickY(input_manager)) * dt), m_velocity.z());

	}
	else if (std::fabs(input_handler.LeftStickX(input_manager)) < 0.00001)
	{
		m_velocity = gef::Vector4(m_velocity.x(), m_velocity.y() + ((input_handler.LeftStickY(input_manager)) * dt), m_velocity.z());
	}
	else if (std::fabs(input_handler.LeftStickY(input_manager)) < 0.00001)
	{
		m_velocity = gef::Vector4(m_velocity.x() + ((input_handler.LeftStickX(input_manager)) * dt), m_velocity.y(), m_velocity.z());
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
