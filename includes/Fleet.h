#ifndef FLEET_H
#define FLEET_H
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <vector>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "AquaAlien.h"
#include "RedAlien.h"
#include "PurpleAlien.h"
#include "FlagShip.h"
#include "Player.h"
#include "AlienLaser.h"
//******************************************************************************
//This is the header file for the Fleet class.
//changeDirection changes the direction of all the aliens when they reach the
//left or right side of the window.
//
//startPlacement centers the fleet and sets all aliens to alive state
//
//move moves all aliens and spawns lasers when they reach a certain point
//
//alienAttack randomly makes aliens attack based on timers for all the aqua
//aliens, purple aliens, and flagship/red aliens.  The more level increases,
//the more aqua aliens and purple aliens can attack at once.
//
//checkCollision checks if an alien hit the player ship, causing both to die
//
//reset resets spawns in a new fleet if the old one was completely destroyed.
//this increases the level and calls startPlacement when the fleet is dead.
//
//int numAttackA_ - counts all attacking aqua aliens
//int numAttackP_ - counts all attacking purple aliens
//int aTimer_ - randomized int timer for aqua attack rate
//int purpleTimer_ - randomized int timer for purple attack rate
//int pauseFrames_ - pauses fleet for 20 frames to create a stutter effect
//int flagTimer_ - randomized int timer for flagship/red attack rate
//bool isAlive_ - 1 for fleet being alive, 0 for dead
//int level_ - keeps track of level count
//int respawnTimer_ - delay for fleet to respawn
//bool isRespawning_ - 1 fleet is respawning, 0 it is not
//int changeDelay_ - delay between checks for changing direction
//bool isChanging_ - 1 fleet is changing direction, 0 it is not
//******************************************************************************
class Fleet
{
public:
    Fleet();
    
    void changeDirection(std::vector<AquaAlien> & aaR1,
                         std::vector<AquaAlien> & aaR2,
                         std::vector<AquaAlien> & aaR3,
                         std::vector<PurpleAlien> & paa,
                         std::vector<RedAlien> & raa,
                         std::vector<FlagShip> & fsa);
    
    void startPlacement(std::vector<AquaAlien> & aaR1,
                        std::vector<AquaAlien> & aaR2,
                        std::vector<AquaAlien> & aaR3,
                        std::vector<PurpleAlien> & paa,
                        std::vector<RedAlien> & raa,
                        std::vector<FlagShip> & fsa);

    void move(std::vector<AquaAlien> & aaR1,
               std::vector<AquaAlien> & aaR2,
               std::vector<AquaAlien> & aaR3,
               std::vector<PurpleAlien> & paa,
               std::vector<RedAlien> & raa,
               std::vector<FlagShip> & fsa,
               std::vector<AlienLaser> & alaR1,
               std::vector<AlienLaser> & alaR2,
               std::vector<AlienLaser> & alaR3,
               std::vector<AlienLaser> & alPurp,
               std::vector<AlienLaser> & alRed,
               std::vector<AlienLaser> & alFlag,
               Sound & alienFire);
    
    void alienAttack(std::vector<AquaAlien> & aaR1,
                     std::vector<AquaAlien> & aaR2,
                     std::vector<AquaAlien> & aaR3,
                     std::vector<PurpleAlien> & paa,
                     std::vector<RedAlien> & raa,
                     std::vector<FlagShip> & fsa);

    void checkCollision(Player & player,
                        std::vector<AquaAlien> & aaR1,
                        std::vector<AquaAlien> & aaR2,
                        std::vector<AquaAlien> & aaR3,
                        std::vector<PurpleAlien> & paa,
                        std::vector<RedAlien> & raa,
                        std::vector<FlagShip> & fsa,
                        int * score);
    
    void reset(std::vector<AquaAlien> & aaR1,
               std::vector<AquaAlien> & aaR2,
               std::vector<AquaAlien> & aaR3,
               std::vector<PurpleAlien> & paa,
               std::vector<RedAlien> & raa,
               std::vector<FlagShip> & fsa);
    
    bool isRespawning();
    int level();
private:
    int numAttackA_;
    int numAttackP_;
    int aTimer_;
    int purpleTimer_;
    int pauseFrames_;
    int flagTimer_;
    bool isAlive_;
    int level_;
    int respawnTimer_;
    bool isRespawning_;
    int changeDelay_;
    bool isChanging_;
};

void changeAllDirection(std::vector<AquaAlien> & aaR1,
                        std::vector<AquaAlien> & aaR2,
                        std::vector<AquaAlien> & aaR3,
                        std::vector<PurpleAlien> & paa,
                        std::vector<RedAlien> & raa,
                        std::vector<FlagShip> & fsa);
#endif
