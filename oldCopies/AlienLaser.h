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
#include "AquaAlien.h"

class AlienLaser
{
public:
    AlienLaser();
    ~AlienLaser();
    void startLaser();
    void test(AquaAlien & a);
/*void moveLaser();
    bool alive() const;
    
    void drawLaser(Surface & surface);
*/
private:
    bool isAlive_;
    int speed_;
    int laserW_;
    int laserH_;
    int laserX_;
    int laserY_;
};

#endif
