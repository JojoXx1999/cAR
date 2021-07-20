//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#pragma once
#include <graphics\mesh_instance.h>
#include <graphics\mesh.h>
#include "maths\matrix33.h"

class GameObject : public gef::MeshInstance
{
public:
	//Functions reprensenting all game objects in the application
	inline GameObject() { Init(); }
	inline ~GameObject() {}
	 void Init();
	 bool Update(float frame_time);
	 void BuildTransformation();
	 void Offset(gef::Matrix44* marker_transform);
	 void SetScale(gef::Vector4 s);
	 inline gef::Vector4 getPosition() { return m_position; }
	 inline void setPosition(gef::Vector4 pos) { m_position = pos; }
	 inline void setVelocity(gef::Vector4 velo) { m_velocity = velo; }
	 inline void setInitial(gef::Matrix44 init) { m_init = init; }
	 inline gef::Matrix44* getInitial() { return &m_init; }
	inline gef::Matrix44 getTransform() { return m_transform; ; }
	gef::Matrix44 setTransform(gef::Vector4 S, gef::Quaternion R, gef::Vector4 T);
	gef::Matrix44 setTransform(gef::Vector4 S, gef::Vector4 T);
private:
	gef::Vector4 m_position;
	gef::Vector4 m_velocity;
	gef::Matrix44 m_init;
	gef::Vector4 m_scale;
	gef::Matrix44 m_transform;
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//