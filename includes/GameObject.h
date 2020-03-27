#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
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

class GameObject
{
public:
    GameObject(int dx);

    int getDx() const;
    int & setDx();
    
    /* void draw(Surface & surface, Explosion & e); */
//void startPlacement(int i, int r);

    /* int getX() const; */
    /* int getY() const; */
    /* int getW() const; */
    /* int getH() const; */
    
    /* bool alive() const; */
    /* int state() const; */
    /* int & setX(); */
    /* int & setY(); */
    /* bool & setAlive(); */
    /* int & setState(); */
    /* int getMemX() const; */
    /* int getMemY() const; */
    /* void attack(); */
    /* void reset(); */
    //void changeDirection(AquaAlien aquaAlienArray[NUMAQUA]);
    //void move();
    
private:
    int dx_;
/* static Image image_; */
    /* Rect rect_; */
    /* bool isAlive_; */
    /* int x_; */
    /* int y_; */
    /* int speed_; */
    /* int dy_; */
    /* int state_; */
    /* int memoryX_; */
    /* int memoryY_; */
    /* int median_; */
};

#endif
