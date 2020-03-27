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
#include "AlienLaser.h"
#include "AquaAlien.h"
#include "PurpleAlien.h"
#include "RedAlien.h"
#include "FlagShip.h"
#include "Player.h"
#include "vector"

AlienLaser::AlienLaser()
    : speed_(ALASERSPEED), laserW_(5), laserH_(10), isAlive_(0), laserX_(0),
      laserY_(0)
{}


void AlienLaser::startLaser(const AquaAlien & a)
{
    this->isAlive_ = 1;
    this->laserX_ = (a.getX() + a.getW() / 2) - (laserW_ / 2);
    this->laserY_ = a.getY() + a.getH();
}


void AlienLaser::startLaser(const PurpleAlien & a)
{
    this->isAlive_ = 1;
    this->laserX_ = (a.getX() + a.getW() / 2) - (laserW_ / 2);
    this->laserY_ = a.getY() + a.getH();
}


void AlienLaser::startLaser(const RedAlien & a)
{
    this->isAlive_ = 1;
    this->laserX_ = (a.getX() + a.getW() / 2) - (laserW_ / 2);
    this->laserY_ = a.getY() + a.getH();
}


void AlienLaser::startLaser(const FlagShip & a)
{
    this->isAlive_ = 1;
    this->laserX_ = (a.getX() + a.getW() / 2) - (laserW_ / 2);
    this->laserY_ = a.getY() + a.getH();
}


void AlienLaser::checkCollision(Player & player)
{
    int laserx1 = this->laserX_;
    int lasery1 = this->laserY_;
    int laserx2 = laserx1 + laserW_;
    int lasery2 = lasery1 + laserH_;
    int playerx1 = player.getX();
    int playery1 = player.getY();
    int playerx2 = player.getX() + player.getW();
    int playery2 = player.getY() + player.getH();
    
    if (((laserx1 >= playerx1 && laserx1 <= playerx2)
        || (playerx1 >= laserx1 && playerx1 <= laserx2))
        && ((lasery1 >= playery1 && lasery1 <= playery2)
        || (playery1 >= lasery1 && playery1 <= lasery2)))
    {
        if (player.state() == 0)
        {
            this->isAlive_ = 0;
            this->laserY_ = 0;
            player.dying();
        }
    }
}


void AlienLaser::checkAlien(const AquaAlien & a, Sound & alienFire)
{
    if (a.getY() >= FIREY && a.getY() <= FIREY + 10 && a.state() == 1)
    {
        if (!(this->alive()))
        {
            alienFire.play();
            this->startLaser(a);
        }   
    }
}


void AlienLaser::checkAlien(const PurpleAlien & a, Sound & alienFire)
{
    if (a.getY() >= FIREY && a.getY() <= FIREY + 10 && a.state() == 1)
    {
        if (!(this->alive()))
        {
            alienFire.play();
            this->startLaser(a);
        }   
    }
}


void AlienLaser::checkAlien(const RedAlien & a, Sound & alienFire)
{
    if (a.getY() >= FIREY && a.getY() <= FIREY + 10 && a.state() == 1)
    {
        if (!(this->alive()))
        {
            alienFire.play();
            this->startLaser(a);
        }   
    }
}


void AlienLaser::checkAlien(const FlagShip & a, Sound & alienFire)
{
    if (a.getY() >= FIREY && a.getY() <= FIREY + 10 && a.state() == 1)
    {
        if (!(this->alive()))
        {
            alienFire.play();
            this->startLaser(a);
        }   
    }
}


void AlienLaser::moveLaser()
{
    if (this->laserY_ < H && this->isAlive_)
    {
        this->laserY_ += this->speed_;
    }
    else
    {
        this->isAlive_ = 0;
        this->laserY_ = 0;
    }
}


void AlienLaser::drawLaser(Surface & surface)
{
    if (this->isAlive_)
    {
        if (this->laserY_ < H)
        {
            //std::cout << "laserY: " << this->laserY_ << '\n';
            surface.put_rect(this->laserX_, this->laserY_, this->laserW_,
                             this->laserH_, 255, 255, 0);
        }
    }   
}


AlienLaser::~AlienLaser()
{}


bool AlienLaser::alive() const
{
    return this->isAlive_;
}
