#ifndef BUILD_H
#define BUILD_H
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
#include "PurpleAlien.h"
#include "Player.h"
#include "PlayerLaser.h"
#include "Fleet.h"
#include "AlienLaser.h"
#include "RedAlien.h"
#include "FlagShip.h"
#include "Explosion.h"
#include "PLives.h"

inline void buildAqua(std::vector<AquaAlien> & aquaVec)
{
    for (int i = 0; i < NUMAQUA; ++i)
    {
        AquaAlien a;
        aquaVec.push_back(a);
    }
    aquaVec.shrink_to_fit();
}


inline void buildPurple(std::vector<PurpleAlien> & purpleVec)
{
    for (int i = 0; i < NUMPURP; ++i)
    {
        PurpleAlien a;
        purpleVec.push_back(a);
    }
    purpleVec.shrink_to_fit();
}


inline void buildRed(std::vector<RedAlien> & redVec)
{
    for (int i = 0; i < NUMPURP; ++i)
    {
        RedAlien a;
        redVec.push_back(a);
    }
    redVec.shrink_to_fit();
}


inline void buildFlag(std::vector<FlagShip> & fsVec)
{
    for (int i = 0; i < NUMFLAG; ++i)
    {
        FlagShip fs;
        fsVec.push_back(fs);
    }
    fsVec.shrink_to_fit();
}


inline void buildPlayerLaser(std::vector<PlayerLaser> & plVec)
{
    for (int i = 0; i < PLAYERLASERS; ++i)
    {
        PlayerLaser pl;
        plVec.push_back(pl);
    }
    plVec.shrink_to_fit();
}


inline void buildAlienLaser(std::vector<AlienLaser> & alVec, int n)
{
    for (int i = 0; i < n; ++i)
    {
        AlienLaser al;
        alVec.push_back(al);
    }
    alVec.shrink_to_fit();
}


inline void buildExplosion(std::vector<Explosion> & eVec, int n)
{
    for (int i = 0; i < n; ++i)
    {
        Explosion e;
        eVec.push_back(e);
    }
    eVec.shrink_to_fit();
}


inline void buildLives(std::vector<PLives> & playerLives)
{
    for (int i = 0; i < NUMLIVES; ++i)
    {
        PLives p(i);
        playerLives.push_back(p);
    }
    playerLives.shrink_to_fit();
}


inline void buildPlayerObjs(std::vector<PLives> & playerLives,
                            std::vector<PlayerLaser> & playerLaserArray)
{
    buildLives(playerLives);
    buildPlayerLaser(playerLaserArray);
}


inline void buildAliens(std::vector<AquaAlien> & aquaAlienArrayR1,
                        std::vector<AquaAlien> & aquaAlienArrayR2,
                        std::vector<AquaAlien> & aquaAlienArrayR3,
                        std::vector<PurpleAlien> & purpleAlienArray,
                        std::vector<RedAlien> & redAlienArray,
                        std::vector<FlagShip> & flagShipArray)
{
    buildAqua(aquaAlienArrayR1);
    buildAqua(aquaAlienArrayR2);
    buildAqua(aquaAlienArrayR3);
    buildPurple(purpleAlienArray);
    buildRed(redAlienArray);
    buildFlag(flagShipArray);
}


inline void buildAlienLasers(std::vector<AlienLaser> & alienLaserArrayAR1,
                             std::vector<AlienLaser> & alienLaserArrayAR2,
                             std::vector<AlienLaser> & alienLaserArrayAR3,
                             std::vector<AlienLaser> & alienLaserArrayPurp,
                             std::vector<AlienLaser> & alienLaserArrayRed,
                             std::vector<AlienLaser> & alienLaserArrayFlag)
{
    buildAlienLaser(alienLaserArrayAR1, NUMAQUA);
    buildAlienLaser(alienLaserArrayAR2, NUMAQUA);
    //**HELP WHY IS THIS SEG FAULT
    //buildAlienLaser(alienLaserArrayAR3, NUMAQUA);
    
//buildAlienLaser(alienLaserArrayPurp, NUMPURP);
    buildAlienLaser(alienLaserArrayRed, NUMRED);
    buildAlienLaser(alienLaserArrayFlag, NUMFLAG);
}


inline void buildExplosions(std::vector<Explosion> & explosionArrayAR1,
                            std::vector<Explosion> & explosionArrayAR2,
                            std::vector<Explosion> & explosionArrayAR3,
                            std::vector<Explosion> & explosionArrayPurp,
                            std::vector<Explosion> & explosionArrayRed,
                            std::vector<Explosion> & explosionArrayFlag)
{
    buildExplosion(explosionArrayAR1, NUMAQUA);
    buildExplosion(explosionArrayAR2, NUMAQUA);
    buildExplosion(explosionArrayAR3, NUMAQUA);
    buildExplosion(explosionArrayPurp, NUMPURP);
    buildExplosion(explosionArrayRed, NUMRED);
    buildExplosion(explosionArrayFlag, NUMFLAG);
}             


inline void buildHighScore(std::vector<int> & hs)
{
    std::ifstream getScore("hs.txt", std::ios::in);
    for (int i = 0; i < 3; ++i)
    {
        int a;
        getScore >> a;
        hs.push_back(a);
    }
    hs.shrink_to_fit();
}


#endif
