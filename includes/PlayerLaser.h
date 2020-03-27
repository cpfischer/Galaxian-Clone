#ifndef PLAYERLASER_H
#define PLAYERLASER_H
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
#include "Player.h"
#include "AquaAlien.h"
#include "PurpleAlien.h"
#include "RedAlien.h"
#include "FlagShip.h"


class PlayerLaser
{
public:
    PlayerLaser();
    ~PlayerLaser();
    void startLaser(const Player & player);
    void moveLaser();
    bool alive() const;
    void drawLaser(Surface & surface);
    void checkCollision(std::vector<AquaAlien> & aaR1,
                        std::vector<AquaAlien> & aaR2,
                        std::vector<AquaAlien> & aaR3,
                        std::vector<PurpleAlien> & paa,
                        std::vector<RedAlien> & raa,
                        std::vector<FlagShip> & fsa,
                        int * score);
private:
    bool isAlive_;
    int speed_;
    int laserW_;
    int laserH_;
    int laserX_;
    int laserY_;
};

#endif
