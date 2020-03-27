#ifndef GAMELOOP_H
#define GAMELOOP_H
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "AquaAlien.h"
#include "PurpleAlien.h"
#include "Player.h"
#include "PlayerLaser.h"
#include "StarField.h"
#include "Fleet.h"
#include "AlienLaser.h"
#include "RedAlien.h"
#include "FlagShip.h"
#include "Explosion.h"
#include "Build.h"
#include "Screen.h"
//******************************************************************************
//Header file to GameLoop.  The game loop controls the drawing, movement, and
//collision of all the game objects (lasers, aliens, player, stars,
//and explosions)
//The draw function draws all of these objects every frame refresh
//******************************************************************************
void gameLoop(Surface & surface, Event & event, bool * quitGame);
void drawGame(Player & player,
              Explosion * playerExplosion,
              StarField & starField,
              std::vector<AquaAlien> & aaR1,
              std::vector<AquaAlien> & aaR2,
              std::vector<AquaAlien> & aaR3,
              std::vector<PurpleAlien> & paa,
              std::vector<RedAlien> & raa,
              std::vector<FlagShip> & fsa,
              std::vector<PlayerLaser> & playerLaserArray,
              std::vector<AlienLaser> & alienLaserArrayAR1,
              std::vector<AlienLaser> & alienLaserArrayAR2,
              std::vector<AlienLaser> & alienLaserArrayAR3,
              std::vector<AlienLaser> & alienLaserArrayPurp,
              std::vector<AlienLaser> & alienLaserArrayRed,
              std::vector<AlienLaser> & alienLaserArrayFlag,
              std::vector<Explosion> & explosionArrayAR1,
              std::vector<Explosion> & explosionArrayAR2,
              std::vector<Explosion> & explosionArrayAR3,
              std::vector<Explosion> & explosionArrayPurp,
              std::vector<Explosion> & explosionArrayRed,
              std::vector<Explosion> & explosionArrayFlag,
              Surface & surface);
    
#endif
