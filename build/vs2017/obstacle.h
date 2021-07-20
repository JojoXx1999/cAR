//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#pragma once
#include "game_object.h"
#include <map>

class Obstacle : public GameObject
{
public:
	inline Obstacle() { Init(); }

	void Init();
	bool Update(float frame_time);
	void BuildTransformation();

	inline gef::Vector4 getVelocity() { return m_velocity; }
	inline gef::Vector4 getPosition() { return m_position; }

	void Offset(gef::Matrix44* marker_transform);

	void inline setPosition(gef::Vector4 pos) { m_position = pos; }
	inline void setVelocity(gef::Vector4 velo) { m_velocity = velo; }
	bool stayInWorld(gef::Matrix44 left, gef::Matrix44 right, gef::Matrix44 top, gef::Matrix44 bottom);
	inline void setInitial(gef::Matrix44 init) { m_init = init; }
	inline gef::Matrix44* getInitial() { return &m_init; }

	//Random Y position of the obstacle
	inline float getCurrentY() { return currentY; }
	inline void setChangeY(bool b) { change_Y = b; }
	void ChangeY(float distanceZ);
	float currentY;
	bool change_Y;

private:
	gef::Vector4 m_position;
	gef::Vector4 m_velocity;
	gef::Matrix44 m_init;

};

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
