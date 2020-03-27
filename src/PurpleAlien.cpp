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
#include "PurpleAlien.h"
#include "Explosion.h"
#include "GameObject.h"

Image PurpleAlien::image_("images/galaxian/GalaxianPurpleAlien.gif");


PurpleAlien::PurpleAlien()
    : GameObject(ALIENSPEED), dy_(0), speed_(ALIENSPEED), isAlive_(1),
      state_(0), memoryX_(SPACING), memoryY_(SPACING)
{
    
    rect_ = PurpleAlien::image_.getRect();
}


void PurpleAlien::drawAlien(Surface & surface, Explosion & e)
{
        // blit image at rect on surface
    if (this->state_ != 4 && this->state_ != 3)
    {
        this->rect_.y = this->alienY_;
        this->rect_.x = this->alienX_;
        surface.put_image(PurpleAlien::image_, this->rect_);
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


int PurpleAlien::getX() const
{
    return this->rect_.x;
}


int PurpleAlien::getY() const
{
    return this->rect_.y;
}


int PurpleAlien::getW() const
{
    return this->rect_.w;
}


int PurpleAlien::getH() const
{
    return this->rect_.h;
}


int PurpleAlien::getMemX() const
{
    return this->memoryX_;
}


int PurpleAlien::getMemY() const
{
    return this->memoryY_;
}


void PurpleAlien::moveAlien(const int pauseFrames)
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
            this->alienX_ = 75 * sin(this->alienY_/50.0) + median_;
            
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

bool PurpleAlien::alive() const
{
    return this->isAlive_;
}


void PurpleAlien::alienStartPlacement(int i)
{
    this->isAlive_ = 1;
    this->state_ = 0;
    if (i == 0)
    {
        this->alienX_ = PURPSTART + W / NUMPURP - rect_.w / 2;
    }
    else
    {
        this->alienX_ = (i * SPACING) + PURPSTART + W / NUMPURP - rect_.w / 2;
    }
    this->alienY_ = COLSPACE * 3;
}


void PurpleAlien::reset()
{
    this->state_ = 2;
    this->alienX_ = this->memoryX_;
    this->alienY_ = 0;
}


void PurpleAlien::changeDirection(PurpleAlien & a)
{
    a.setDx() = -(a.getDx());
}


void PurpleAlien::attack()
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


int PurpleAlien::state() const
{
    return this->state_;
}


void PurpleAlien::dying(int * score)
{
    if (this->state_ == 0 || this->state_ == 2)
    {
        *score += PURPSCORE;
    }
    else if (this->state_ == 1)
    {
        *score += PURPSCORE * 2;
    }
    
    this->state_ = 3;
    this->isAlive_ = 0;
}

