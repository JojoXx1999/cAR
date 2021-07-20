//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "physics_Handler.h"
#include <graphics\mesh.h>
#include <graphics\mesh_instance.h>
#include "game_object.h"
#include <maths\math_utils.h>
#include <math.h>
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//Detect sphere to sphere collision between mesh instances
bool Colliding::IsColliding_SphereToSphere(const gef::MeshInstance& meshInstance1, const gef::MeshInstance& meshInstance2)
{
	gef::Sphere sphere1 = meshInstance1.mesh()->bounding_sphere();
	gef::Sphere sphere2 = meshInstance2.mesh()->bounding_sphere();

	gef::Sphere sphere1_transformed = sphere1.Transform(meshInstance1.transform());
	gef::Sphere sphere2_transformed = sphere2.Transform(meshInstance2.transform());

	gef::Vector4 offset = sphere1_transformed.position() - sphere2_transformed.position();
	float distance = std::sqrtf(offset.x() * offset.x() + offset.y() * offset.y());
	float combined_radii = sphere1_transformed.radius() + sphere2_transformed.radius();

	return distance < combined_radii;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//Detect AABB collisions between mesh insatnces
bool Colliding::IsColliding_AABBToAABB(const gef::MeshInstance& meshInstance1, const gef::MeshInstance& meshInstance2)
{
	gef::Aabb Aabb1 = meshInstance1.mesh()->aabb();
	gef::Aabb Aabb2 = meshInstance2.mesh()->aabb();

	gef::Aabb Aabb1_transformed = Aabb1.Transform(meshInstance1.transform());
	gef::Aabb Aabb2_transformed = Aabb2.Transform(meshInstance2.transform());

	if (Aabb1_transformed.max_vtx().x() > Aabb2_transformed.min_vtx().x() &&
		Aabb1_transformed.min_vtx().x() < Aabb2_transformed.max_vtx().x() &&
		Aabb1_transformed.max_vtx().y() > Aabb2_transformed.min_vtx().y() &&
		Aabb1_transformed.min_vtx().y() < Aabb2_transformed.max_vtx().y() &&
		Aabb1_transformed.max_vtx().z() > Aabb2_transformed.min_vtx().z() &&
		Aabb1_transformed.min_vtx().z() < Aabb2_transformed.max_vtx().z())
	{
		return true;
	}

	return false;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//Detect AABB collisions between game objects
bool Colliding::IsColliding_AABBToAABB(const GameObject& obj1, const GameObject& obj2)
{
	gef::Aabb Aabb1 = obj1.mesh()->aabb();
	gef::Aabb Aabb2 = obj2.mesh()->aabb();

	gef::Aabb Aabb1_transformed = Aabb1.Transform(obj1.transform());
	gef::Aabb Aabb2_transformed = Aabb2.Transform(obj2.transform());

	if (Aabb1_transformed.max_vtx().x() > Aabb2_transformed.min_vtx().x() &&
		Aabb1_transformed.min_vtx().x() < Aabb2_transformed.max_vtx().x() &&
		Aabb1_transformed.max_vtx().y() > Aabb2_transformed.min_vtx().y() &&
		Aabb1_transformed.min_vtx().y() < Aabb2_transformed.max_vtx().y() &&
		Aabb1_transformed.max_vtx().z() > Aabb2_transformed.min_vtx().z() &&
		Aabb1_transformed.min_vtx().z() < Aabb2_transformed.max_vtx().z())
	{
		return true;
	}

	return false;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//