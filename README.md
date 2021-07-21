# cAR
AR game using markers

Note: 	I do not own the code inside the ar_vita folder
This game was made for the PSVita and will not run on PC

The ar_handler.cpp inside build/vs2017 sets up the ar functionality for this project
including rendering the PSVita camera to the screen and getting the position of markers.

the physics_handler deals with collisions between the player and an obstacle, this file can
handle AABB to AABB and sphere to sphere collisions.  

The state_handler controls the 4 game states: splash, menu, game and end this will call the correct
update or render function depending on the games current state.

car.cpp controls the player allowing them to move around the world while also confining them to the
edge of the map which is chosen by the position of the first two ar markers

more information can be found here: http://www.jodieduff.co.uk/car_augmented_reality_game.html