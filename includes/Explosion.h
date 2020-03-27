#ifndef EXPLOSION_H
#define EXPLOSION_H
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
#include "vector"

class Explosion
{
public:
    Explosion();
    void drawExplosion(Surface & surface);
    void changeState();
    void setCoords(int x, int y);
    bool alive();
    int state();
    
private:
    static Image image1_;
    static Image image2_;
    static Image image3_;
    static Image image4_;
    static Image image5_;
    static Image image6_;
    static Sound boom_;
    bool isAlive_;
    Rect rect_;
    int state_;
    int delay_;
};

#endif
