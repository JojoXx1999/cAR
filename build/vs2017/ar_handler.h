//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#pragma once
#include "game_object.h"

// Vita AR includes
#include <camera.h>
#include <gxm.h>
#include <motion.h>
#include <libdbg.h>
#include <libsmart.h>

#include <platform/vita/graphics/texture_vita.h>
#include <graphics/sprite.h>

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//forward declaration
class AppData;

namespace gef
{
	class Platform;
	class SpriteRenderer;
	class TextureVita;
	class Sprite;
	class Renderer3D;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
class ARHandler
{
public:
	inline ARHandler() { }
	inline ~ARHandler() {  }

	void Init();
	void CleanUp();
	void Update();

	//Detect if a specific marker is detected
	bool isMarkerFound(int markerID);

	//Over loaded functions to place an object at the marker object with or without an offset
	void placeMarkerTransform(GameObject& obj, int markerID);
	void placeMarkerTransform(GameObject& obj, gef::Matrix44& matrix, float offsetX, float offsetY);

	//Get the transform of a specific marker
	gef::Matrix44& getMarkerTransform(int markerID);

	//Render the camera feed to the screen
	void RenderCamera(gef::Platform& platform, gef::Renderer3D& renderer_3d, gef::SpriteRenderer* sprite_renderer);
	void EndRender();

	void UpdateEnd();
private:
	float VerticalImageScaleFactor(float width, float height, float near, float far);

	//To display camera feed on the screen
	gef::SpriteRenderer* sprite_renderer_;
	gef::TextureVita camera_image_texture;
	gef::Renderer3D* renderer_ptr;
	AppData* dat_copy;

	int markerID_;
};
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
