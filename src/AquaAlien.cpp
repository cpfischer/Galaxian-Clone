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
#include "Explosion.h"
#include "GameObject.h"

Image AquaAlien::image_("images/galaxian/GalaxianAquaAlien.gif");


AquaAlien::AquaAlien()
    : GameObject(ALIENSPEED), dy_(0), speed_(ALIENSPEED), isAlive_(1),
      state_(0), memoryX_(SPACING), memoryY_(SPACING)      
{
    rect_ = AquaAlien::image_.getRect();
}


void AquaAlien::drawAlien(Surface & surface, Explosion & e)
{
        // blit image at rect on surface
    if (this->state_ != 4 && this->state_ != 3)
    {
        this->rect_.y = this->alienY_;
        this->rect_.x = this->alienX_;
        surface.put_image(AquaAlien::image_, this->rect_);
    }
    else if (this->state_ == 3)
    {
        if (!(e.alive()))
        {
            e.setCoords(this->rect_.x, this->rect_.y);
        }
        
        if (e.state() == 5)
        {
            this->state_ = 4;
        }
    }
}

int AquaAlien::getX() const
{
    return this->rect_.x;
}


int AquaAlien::getY() const
{
    return this->rect_.y;
}


int AquaAlien::getW() const
{
    return this->rect_.w;
}


int AquaAlien::getH() const
{
    return this->rect_.h;
}


int AquaAlien::getMemX() const
{
    return this->memoryX_;
}


int AquaAlien::getMemY() const
{
    return this->memoryY_;
}


void AquaAlien::moveAlien(const int pauseFrames)
{
    //0: normal 1: attacking 2: resetting 3: dying 4:dead
    switch(this->state_)
    {
        case 0:
            if (pauseFrames == 0)
            {
                this->alienX_ += this->getDx();
            }
            break;
            
        case 1:
            this->alienY_ += this->dy_;
            this->alienX_ = 50 * sin(this->alienY_/100.0) + median_;
            
            if (this->alienY_ > H)
            {
                this->reset();
            }
            
            if (pauseFrames == 0)
            {
                this->memoryX_ += this->getDx();
            }
            break;
            
        case 2:
            if (this->alienY_ >= this->memoryY_)
            {
                this->alienY_ = this->memoryY_;
                this->state_ = 0;
                this->dy_ = 0;
            }
            else
            {
                this->alienY_ += dy_;
            }

            if (pauseFrames == 0)
            {
                this->memoryX_ += this->getDx();
            }
            this->alienX_ = this->memoryX_;
    }
}

bool AquaAlien::alive() const
{
    return this->isAlive_;
}


void AquaAlien::alienStartPlacement(int i, int r)
{
    this->isAlive_ = 1;
    this->state_ = 0;
    alienX_ = (i * SPACING) + W / NUMAQUA - rect_.w / 2;
    alienY_ = ((r + 1) * COLSPACE) + rect_.h + COLSPACE;
}


void AquaAlien::reset()
{
    this->state_ = 2;
    this->alienY_ = 0;
    this->dy_ = ALIENSPEED / 2;
}


void AquaAlien::changeDirection(AquaAlien & a)
{
    a.setDx() = -(a.getDx());
}


void AquaAlien::attack()
{
    if (this->state_ == 0)
    {
        this->state_ = 1;
        this->memoryX_ = this->alienX_;
        this->memoryY_ = this->alienY_;
        this->dy_ = this->speed_ / 2;
        this->median_ = this->alienX_;
    }
}


void AquaAlien::dying(int * score)
{
    //0: normal 1:attack 2:reset 3:dying 4:dead
    if (this->state_ == 0 || this->state_ == 2)
    {
        *score += AQUASCORE;
    }
    else if (this->state_ == 1)
    {
        *score += AQUASCORE * 2;
    }
    //std::cout << "Hit!  New score: " << *score << '\n';
    this->state_ = 3;
    this->isAlive_ = 0;
}


int AquaAlien::state() const
{
    return this->state_;
}
