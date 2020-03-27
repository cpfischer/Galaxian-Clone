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
#include "AlienLaser.h"

AlienLaser::AlienLaser()
    : speed_(2), laserW_(2), laserH_(5), isAlive_(0), laserX_(0),
      laserY_(0)
{}


//void AlienLaser::startLaser()
//{
    // this->isAlive_ = 1;
    // this->laserX_ = (aquaAlien.getX() + aquaAlien.getW() / 2)
    //                 - (laserW_ / 2);
    // this->laserY_ = H - aquaAlien.getH();
//}

/*
void AlienLaser::moveLaser()
{
    if (this->isAlive_)
    {
        if (this->laserY_ > 0)
        {
            this->laserY_ -= this->speed_;
        }
        else
        {
            this->isAlive_ = 0;
        }
    }           
}


void AlienLaser::drawLaser(Surface & surface)
{
    if (this->isAlive_)
    {
        if (this->laserY_ > 0)
        {       
            surface.put_rect(this->laserX_, this->laserY_, this->laserW_,
                             this->laserH_, 255, 0, 0);
        }
    }
}




bool AlienLaser::alive() const
{
    return this->isAlive_;
}

*/
AlienLaser::~AlienLaser()
{}
