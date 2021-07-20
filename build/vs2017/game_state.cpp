//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
#include "game_state.h"
#include <graphics\texture.h>
#include <graphics\sprite.h>
#include <graphics\sprite_renderer.h>
#include <graphics\renderer_3d.h>
#include <maths\math_utils.h>
#include <maths\quaternion.h>
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//Define
typedef std::pair<std::string, Obstacle> str_obstacle;
#define CAR_SPEED 0.01 
#define OBSTACLE_SPEED 0.07
#define OUT_WORLD_PENALTY 2
#define RELIABILITY_LOST 10
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void GameState::Init(gef::Platform& platform)
{
	platform_cpy = &platform;
	primitive_builder_ = new PrimitiveBuilder(platform);

	//Load in car mesh
	m_mesh->Create(*platform_cpy);
	m_mesh = primitive_builder_->CreateBoxMesh(gef::Vector4(0.0155, 0.0155, 0.0155), gef::Vector4(0, 0, 0));
	
	car_mesh->Create(*platform_cpy);
	mesh_handler.AssignFirstMesh("car2.scn", &m_model_scene, &car_mesh, &platform);

	road = new GameObject();
	road->setPosition(gef::Vector4(0.0f, 0.0f, 0.0f));
	road->SetScale(gef::Vector4(1.0f, 1.0f, 1.0f));
	road->set_mesh(primitive_builder_->CreateBoxMesh(gef::Vector4(0.1, 0.1, 0.0005), gef::Vector4(0, 0, 0)));

	road_texture = CreateTextureFromPNG("road2.png", platform);
	road_material.set_texture(road_texture);

	//Create object to show where the car marker is
	Show_Car_marker = new GameObject();
	Show_Car_marker->setPosition(gef::Vector4(0.0f, 0.0f, 0.0f));
	Show_Car_marker->SetScale(gef::Vector4(1.0f, 1.0f, 1.0f));
	Show_Car_marker->set_mesh(primitive_builder_->CreateBoxMesh(gef::Vector4(0.0155, 0.0155, 0.0005), gef::Vector4(0, 0, 0)));

	checker_texture = CreateTextureFromPNG("checker.png", platform);
	checker_material.set_texture(checker_texture);

	car_marker_texture = CreateTextureFromPNG("car_marker.png", platform);
	car_marker_material.set_texture(car_marker_texture);

	oil_marker_texture = CreateTextureFromPNG("oil_marker.png", platform);
	oil_marker_material.set_texture(oil_marker_texture);

	invertor = 1;
	inverted_counter = 0;

	init_toggle = false;
	colliding = false;

	//Set car mesh
	player_car.set_mesh(m_mesh);
	player_car.setPosition(gef::Vector4(0.f, 0.f, 0.f, 0.f));
	player_car.SetScale(gef::Vector4(0.2f, 0.2f, 0.2f));

	gef::Matrix44 S;
	S.SetIdentity();
	S.Scale(gef::Vector4(0.2, 0.2, 0.2));
	//player_car.mesh.transform

	//Reset variables
	counter = 0;
	score = 0;
	marker_truth = 0;
	random_obstacle_Z = 0;
	
	//Create objects and assign mesh
	for (int i = 0; i < obstacle_names->size(); i++)
	{
		obstacles[i] = new Obstacle();
		obstacles[i]->setPosition(gef::Vector4(0.0f, 0.0f, 0.0f));
		obstacles[i]->SetScale(gef::Vector4(1.0f, 1.0f, 1.0f));
		obstacles[i]->set_mesh(primitive_builder_->CreateBoxMesh(gef::Vector4(0.0185, 0.0185, 0.0155), gef::Vector4(0, 0, 0)));
		obstacles[i]->setChangeY(true);

		Show_Obstacle_marker[i] = new GameObject;
		Show_Obstacle_marker[i]->setPosition(gef::Vector4(0.0f, 0.0f, 0.0f));
		Show_Obstacle_marker[i]->SetScale(gef::Vector4(1.0f, 1.0f, 1.0f));
		Show_Obstacle_marker[i]->set_mesh(primitive_builder_->CreateBoxMesh(gef::Vector4(0.0155, 0.0155, 0.0005), gef::Vector4(0, 0, 0)));
	}

	oil_mesh->Create(*platform_cpy);
	mesh_handler.AssignFirstMesh("oil.scn", &m_model_scene, &oil_mesh, &platform);

	oil_texture = CreateTextureFromPNG("oil.png", platform);
	oil_material.set_texture(oil_texture);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
bool GameState::Update(gef::InputManager* input_manager, float dt, GameStates& game_state, ErrorCodes& error_code)
{

	ar_handler.Update();
	Input(input_manager, game_state);

	//Add every marker currently found into a map
	//If marker can't be found remove it fom the map
	for (int i = 0; i < 5; i++)
	{
		if (ar_handler.isMarkerFound(i))
		{
			if (markerMap.find(i) == markerMap.end())
			{
				gef::Matrix44 marker_transform;
				marker_transform = ar_handler.getMarkerTransform(i);
				markerMap.insert(std::pair<int, gef::Matrix44>(i, marker_transform));
			}
		}
		else if (markerMap.find(i) != markerMap.end())
		{
			//marker_truth = 0;
			markerMap.erase(i);
		}
	}

	//Detect any errors
	error_state.DetectError(error_code, markerMap, ar_handler, car_marker, top, bottom, left, right);

	//If game world can be found
	if (error_code != NO_WORLD)
	{
			//Detect corner markers
			getCorners(left, right, top, bottom, markerMap.begin()->first, std::next(markerMap.begin(), 1)->first);

			//Calculate X and Z distance between corner markers
			float distanceX = std::fabsf(right.GetTranslation().x() - left.GetTranslation().x());
			float distanceZ = std::fabsf(top.GetTranslation().y() - bottom.GetTranslation().y());

			float X = (distanceX) / (0.2);
			float Y = (distanceZ) / (0.2);

			if (left.GetTranslation().y() > right.GetTranslation().y())
				final_road_matrix = road->setTransform(gef::Vector4(X, Y, 0), gef::Vector4(left.GetTranslation().x() + (distanceX / 2), left.GetTranslation().y() - (distanceZ / 2), left.GetTranslation().z() - (distanceZ / 2)));
			else
				final_road_matrix = road->setTransform(gef::Vector4(X, Y, 0), gef::Vector4(left.GetTranslation().x() + (distanceX / 2), left.GetTranslation().y() + (distanceZ / 2), left.GetTranslation().z() - (distanceZ / 2)));

			road->set_transform(final_road_matrix);

			//If car can be found
			if (error_code!= NO_CAR)
			{
				if (marker_truth == 0)
				{
					//Place car at the car marker
					car_marker = ar_handler.getMarkerTransform(std::next(markerMap.begin(), 2)->first);
					previous_marker = car_marker;
				}
				else
					car_marker = previous_marker;

				gef::Matrix44 car_marker_matrix;
				car_marker_matrix = Show_Car_marker->setTransform(car_marker.GetScale(), car_marker.GetTranslation());
				Show_Car_marker->set_transform(car_marker_matrix);

					//If car is within the game bounds
					if (error_code != CAR_OUT_OF_BOUNDS)
					{
							player_car.Move(*input_manager, dt, invertor);

							//Offset the car from the car marker
							ar_handler.placeMarkerTransform(player_car, car_marker, player_car.getVelocity().x(), player_car.getVelocity().y());

							player_car.stayInWorld(left, right, top, bottom, car_marker);
							//If car is outside of game world place the car back to the car marker
							//and deduct penalty from the score, clamped to 0
							if (player_car.stayInWorld(left, right, top, bottom, car_marker))
							{
								ar_handler.placeMarkerTransform(player_car, car_marker, 0, 0);
								counter = 0;	
								score - OUT_WORLD_PENALTY < 0 ? score = 0 : score -= OUT_WORLD_PENALTY;
							}

								//If there is at least one obstacle
								if (error_code != NO_OBSTACLES)
								{
									//Update player score
									counter++;
									if (counter % 50 == 0)
									{
										score += 1;
									}

									gef::Matrix44 mark1, mark2;
									gef::Matrix44 tmp = right;

									//Move the obstacle to a random Z position between markers
									for (int i = 0; i < obstacle_names->size(); ++i)
									{
										obstacles[i]->ChangeY(distanceZ);
									}

									//Detect collidion between player and obstacle
									colliding = collision_handler.IsColliding_AABBToAABB(player_car, *obstacles[0]);
									
									if (colliding)
									{
										ar_handler.UpdateEnd();
										game_state = GameStates::END;
										return true;
									}

									//If player collides with an oil slick invert their controls for a short time
									colliding = collision_handler.IsColliding_AABBToAABB(player_car, *obstacles[1]);

									if (invertor == -1)
									{
										inverted_counter += (1.f * dt);
										if (inverted_counter >= 10)
											invertor = 1;
									}

									if (colliding)
									{
										inverted_counter = 0;
										invertor = -1;
									}

									//Move obstacle towards the left of the screen
									obstacles[0]->setVelocity(gef::Vector4(obstacles[0]->getVelocity().x() - OBSTACLE_SPEED * dt * 2, 0, 0));

									if (right.GetTranslation().y() > left.GetTranslation().y())
										ar_handler.placeMarkerTransform(*obstacles[0], tmp, obstacles[0]->getVelocity().x(), -obstacles[0]->getCurrentY()); //random z between range
									else
										ar_handler.placeMarkerTransform(*obstacles[0], tmp, obstacles[0]->getVelocity().x(), obstacles[0]->getCurrentY());

									if (ObstaclesInPlay_.find(obstacle_names[0]) == ObstaclesInPlay_.end())
										ObstaclesInPlay_.insert(std::pair<std::string, Obstacle*>(obstacle_names[0], obstacles[0]));

									//If obstacle is off the left hand side of the screen
									//Move obstacle to the right with  random X offset to create variable time
									if (tmp.GetTranslation().x() < left.GetTranslation().x() - 0.2)
									{
										obstacles[0]->setChangeY(true);
										float random_respawn_distance = rand() % (6 + 3);
										random_respawn_distance /= 10;
										ar_handler.placeMarkerTransform(*obstacles[0], tmp, obstacles[0]->getVelocity().x(), 0); //random y between range
										obstacles[0]->setVelocity(gef::Vector4(random_respawn_distance, 0.f, obstacles[0]->getCurrentY()));
									}

									//2nd Obsstacle in play
									if (markerMap.size() > 4 && markerMap.size() < 6)
									{
										gef::Matrix44 tmp = right;
										//Move obstacle towards the left of the screen
										obstacles[1]->setVelocity(gef::Vector4(obstacles[1]->getVelocity().x() - OBSTACLE_SPEED * dt * 1.2, 0, 0));

										if (right.GetTranslation().y() > left.GetTranslation().y())
											ar_handler.placeMarkerTransform(*obstacles[1], tmp, obstacles[1]->getVelocity().x(), -obstacles[1]->getCurrentY()); //random y between range
										else
											ar_handler.placeMarkerTransform(*obstacles[1], tmp, obstacles[1]->getVelocity().x(), obstacles[1]->getCurrentY());

										if (ObstaclesInPlay_.find(obstacle_names[1]) == ObstaclesInPlay_.end())
											ObstaclesInPlay_.insert(std::pair<std::string, Obstacle*>(obstacle_names[1], obstacles[1]));

										//If obstacle is off the left hand side of the screen
										//Move obstacle to the right with  random X offset to create variable time
										if (tmp.GetTranslation().x() < left.GetTranslation().x() - 0.2)
										{
											obstacles[1]->setChangeY(true);
											float random_respawn_distance = rand() % (8 + 5);
											random_respawn_distance /= 10;
											ar_handler.placeMarkerTransform(*obstacles[1], tmp, obstacles[1]->getVelocity().x(), 0); //random z between range
											obstacles[1]->setVelocity(gef::Vector4(random_respawn_distance, 0.f, obstacles[1]->getCurrentY()));
										}	
									}

									//Display object ontop of markers to show their location 
									for (int i = 0; i < ObstaclesInPlay_.size(); ++i)
									{
										gef::Matrix44 mark = ar_handler.getMarkerTransform(std::next(markerMap.begin(), i+3)->first);
										gef::Matrix44 obstacle_marker_matrix;
										obstacle_marker_matrix = Show_Obstacle_marker[i]->setTransform(mark.GetScale(), mark.GetTranslation());
										Show_Obstacle_marker[i]->set_transform(obstacle_marker_matrix);
									}
								}
					}
			}
	}

	if (error_code_cpy != error_code)
		error_code_cpy = error_code;

	ar_handler.UpdateEnd();

	return true;
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void GameState::getCorners(gef::Matrix44& left, gef::Matrix44& right, gef::Matrix44& bottom, gef::Matrix44& top, int ID, int ID2)
{
	gef::Matrix44 tmp, tmp2;

	tmp = ar_handler.getMarkerTransform(ID);
	tmp2 = ar_handler.getMarkerTransform(ID2);

	//Detect which markers are left, right, bottom and top
	if (tmp.GetTranslation().x() <= tmp2.GetTranslation().x())
	{
		left = ar_handler.getMarkerTransform(ID);
		right = ar_handler.getMarkerTransform(ID2);
	}
	else
	{
		left = ar_handler.getMarkerTransform(ID2);
		right = ar_handler.getMarkerTransform(ID);
	}

	if (tmp.GetTranslation().z() <= tmp2.GetTranslation().z())
	{
		top = ar_handler.getMarkerTransform(ID);
		bottom = ar_handler.getMarkerTransform(ID2);
	}
	else
	{
		top = ar_handler.getMarkerTransform(ID2);
		bottom = ar_handler.getMarkerTransform(ID);
	}
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void GameState::Input(gef::InputManager* input_manager, GameStates& game_state)
{

}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void GameState::Render(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d_)
{
	ar_handler.RenderCamera(*platform_cpy, *renderer_3d_, sprite_renderer);

	if (error_codes != NO_WORLD)
	{
		renderer_3d_->set_override_material(&road_material);
		renderer_3d_->DrawMesh(*road);
		renderer_3d_->set_override_material(NULL);

		if (error_codes != NO_CAR && error_codes != CAR_OUT_OF_BOUNDS)
		{
			//Display car
			renderer_3d_->set_override_material(&checker_material);
			renderer_3d_->DrawMesh(*Show_Car_marker);
			renderer_3d_->set_override_material(NULL);

			gef::Matrix44 Car_final_matrix = player_car.setTransform(gef::Vector4(0.01, 0.01, 0.01), gef::Quaternion(0, 0, 90, 0), player_car.transform().GetTranslation());

			renderer_3d_->DrawMesh(*car_mesh, Car_final_matrix);

			if (error_codes != NO_OBSTACLES)
			{
				//Display Obstacles
				for (int i = 0; i < obstacle_names->size(); ++i)
				{
					if (ObstaclesInPlay_.find(obstacle_names[i]) != ObstaclesInPlay_.end())
					{
						Obstacle obstcle = *ObstaclesInPlay_.find(obstacle_names[i])->second;

						gef::Matrix44 Car_final_matrix = player_car.setTransform(gef::Vector4(0.01, 0.01, 0.01), gef::Quaternion(0, -90, -90, 0), obstcle.transform().GetTranslation());

						if ( i == 0)
							renderer_3d_->DrawMesh(*car_mesh, Car_final_matrix);
						else if (i == 1)
						{
						//	obstcle.tra
							gef::Matrix44 Oil_final_matrix = obstacles[i]->setTransform(gef::Vector4(0.0025, 0.0025, 0.0025), gef::Quaternion(20, 20, 0, 0), obstacles[i]->transform().GetTranslation());
							
							gef::Matrix44 S, R, T, fin;
							S.SetIdentity(); R.SetIdentity(); T.SetIdentity(), fin.SetIdentity();
							S.Scale(gef::Vector4(0.002, 0.004, 0.0025));
							R.RotationX(90);
							T.SetTranslation(gef::Vector4(obstacles[i]->transform().GetTranslation().x(), obstacles[i]->transform().GetTranslation().y() + 0.02, obstacles[i]->transform().GetTranslation().z()));
							fin = S * R * T;

							renderer_3d_->set_override_material(&oil_material);
							renderer_3d_->DrawMesh(*oil_mesh, fin);
							renderer_3d_->set_override_material(NULL);
						}

						//renderer_3d_->set_override_material(&primitive_builder_->red_material());
						for (int i = 0; i < ObstaclesInPlay_.size(); ++i)
						{
							i == 0 ? renderer_3d_->set_override_material(&car_marker_material) : renderer_3d_->set_override_material(&oil_marker_material);

							renderer_3d_->DrawMesh(*Show_Obstacle_marker[i]);

							renderer_3d_->set_override_material(NULL);
						}
					
					}
				}

			}
		}
	}

	ar_handler.EndRender();
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
void GameState::CleanUp()
{
	//Clean up game_state
	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;
	
	for (int i = 0; i < obstacle_names->size(); ++i)
	{
		delete obstacles[i];
		obstacles[i] = NULL;
	}

	markerMap.clear();
	ObstaclesInPlay_.clear();

	player_car.setVelocity(gef::Vector4(0.f, 0.f, 0.f));
	
	delete road_texture;
	road_texture = NULL;

	delete oil_texture;
	oil_texture = NULL;

	delete Show_Car_marker;
	Show_Car_marker = NULL;
	
	delete[] Show_Obstacle_marker;

}
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//
//-----------------------------------------------------------------------------------------------------------------------------------------------------------//