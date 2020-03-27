#ifndef PLAYER_H
#define PLAYER_H
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
#include "Explosion.h"
#include "vector"

class Player
{
public:
    Player();
    
    void moveShipLeft();
    void moveShipRight();
    void stopShip();
    void addMove();
    void drawShip(Surface & surface, Explosion & e);
    void dying();
    void respawn();
    int state() const;
    int getX() const;
    int getY() const;
    int getW() const;
    int getH() const;
    int lives() const;
    void bonusLife();
    int invincible();

private:
    static Image image_;
    Rect rect_;
    int state_;
    int speed_;
    int dx_;
    int dy_;
    int lives_;
    int invincible_;
};

#endif
