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
#include "RedAlien.h"
#include "Explosion.h"
#include "GameObject.h"

Image RedAlien::image_("images/galaxian/GalaxianRedAlien.gif");


RedAlien::RedAlien()
    : GameObject(ALIENSPEED), dy_(0), speed_(ALIENSPEED), isAlive_(1),
      state_(0), memoryX_(SPACING), memoryY_(SPACING)
{
    
    rect_ = image_.getRect();
}


void RedAlien::drawAlien(Surface & surface, Explosion & e)
{
        // blit image at rect on surface
    if (this->state_ != 4 && this->state_ != 3)
    {
        this->rect_.y = this->alienY_;
        this->rect_.x = this->alienX_;
        surface.put_image(RedAlien::image_, this->rect_);
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


int RedAlien::getX() const
{
    return this->rect_.x;
}


int RedAlien::getY() const
{
    return this->rect_.y;
}


int RedAlien::getW() const
{
    return this->rect_.w;
}


int RedAlien::getH() const
{
    return this->rect_.h;
}


int RedAlien::getMemX() const
{
    return this->memoryX_;
}


int RedAlien::getMemY() const
{
    return this->memoryY_;
}


void RedAlien::moveAlien(const int pauseFrames)
{
    //0: normal 1: attacking 2: resetting 3: dead
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
            this->alienX_ = 100 * sin(this->alienY_/80.0) + median_;
           
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

bool RedAlien::alive() const
{
    return this->isAlive_;
}


void RedAlien::alienStartPlacement(int i)
{
    this->isAlive_ = 1;
    this->state_ = 0;
    if (i == 0)
    {
        this->alienX_ = REDSTART +  W / NUMRED - rect_.w / 2;
    }
    else
    {
        this->alienX_ = (i * SPACING) + REDSTART + W / NUMRED - rect_.w / 2;
    }
    this->alienY_ = COLSPACE * 2;
}


void RedAlien::reset()
{
    this->state_ = 2;
    this->alienX_ = this->memoryX_;
    this->alienY_ = 0;
}


void RedAlien::changeDirection(RedAlien & a)
{
    a.setDx() = -(a.getDx());
}


void RedAlien::attack()
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


int RedAlien::state() const
{
    return this->state_;
}


void RedAlien::dying(int * score)
{
    if (this->state_ == 0 || this->state_ == 2)
    {
        *score += REDSCORE;
    }
    else if (this->state_ == 1)
    {
        *score += REDSCORE * 2;
    }
    
    this->state_ = 3;
    this->isAlive_ = 0;
}
