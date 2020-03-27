#ifndef ALIENLASER_H
#define ALIENLASER_H
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
#include "Player.h"
#include "AquaAlien.h"
#include "PurpleAlien.h"
#include "RedAlien.h"
#include "FlagShip.h"
#include "vector"

class AlienLaser
{
public:
    AlienLaser();
    ~AlienLaser();
    void startLaser(const AquaAlien & a);
    void startLaser(const PurpleAlien & a);
    void startLaser(const RedAlien & a);
    void startLaser(const FlagShip & a);
    void moveLaser();
    bool alive() const;
    void drawLaser(Surface & surface);
    void checkAlien(const AquaAlien & a, Sound & alienFire);
    void checkAlien(const PurpleAlien & a, Sound & alienFire);
    void checkAlien(const RedAlien & a, Sound & alienFire);
    void checkAlien(const FlagShip & a, Sound & alienFire);
    void checkCollision(Player & player);
    
private:
    bool isAlive_;
    int speed_;
    int laserW_;
    int laserH_;
    int laserX_;
    int laserY_;
};

#endif
