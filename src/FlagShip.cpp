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
#include "FlagShip.h"
#include "RedAlien.h"
#include "Explosion.h"
#include "GameObject.h"

Image FlagShip::image_("images/galaxian/GalaxianFlagship.gif");


FlagShip::FlagShip()
    : GameObject(ALIENSPEED), dy_(0), speed_(ALIENSPEED), isAlive_(1), state_(0),
      memoryX_(SPACING), memoryY_(SPACING)
{
    
    rect_ = image_.getRect();
}


void FlagShip::drawAlien(Surface & surface, Explosion & e)
{
        // blit image at rect on surface
    if (this->state_ != 4 && this->state_ != 3)
    {
        this->rect_.y = this->alienY_;
        this->rect_.x = this->alienX_;
        surface.put_image(FlagShip::image_, this->rect_);
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


int FlagShip::getX() const
{
    return this->rect_.x;
}


int FlagShip::getY() const
{
    return this->rect_.y;
}


int FlagShip::getW() const
{
    return this->rect_.w;
}


int FlagShip::getH() const
{
    return this->rect_.h;
}


int FlagShip::getMemX() const
{
    return this->memoryX_;
}


int FlagShip::getMemY() const
{
    return this->memoryY_;
}


void FlagShip::moveAlien(std::vector<RedAlien> & raa, const int pauseFrames,
                         int fNum)
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

            if (fNum == 0)
            {
                for (int i = 0; i <= NUMRED / 2; ++i)
                {
                    if (raa[i].alive() && i == 0)
                    {
                        this->alienX_ = raa[i].getX() + SPACING;
                        break;
                    }
                    else if (raa[i].alive() && i == 1)
                    {
                        this->alienX_ = raa[i].getX();
                        break;
                    }
                    else if (raa[i].alive() && i == 2)
                    {
                        this->alienX_ = raa[i].getX() - SPACING;
                        break;
                    }
                    else if (i == NUMRED / 2)
                    {
                        this->alienX_ = 100 * sin(this->alienY_/80.0) + median_;
                        break;
                    }
                }
            }
            else if (fNum == 1)
            {
                for (int i = NUMRED / 2; i <= NUMRED; ++i)
                {
                    if (raa[i].alive() && i == 3)
                    {
                        this->alienX_ = raa[i].getX() + SPACING;
                        break;
                    }
                    else if (raa[i].alive() && i == 4)
                    {
                        this->alienX_ = raa[i].getX();
                        break;
                    }
                    else if (raa[i].alive() && i == 5)
                    {
                        this->alienX_ = raa[i].getX() - SPACING;
                        break;
                    }
                    else if (i == NUMRED)
                    {
                        this->alienX_ = 100 * sin(this->alienY_/80.0) + median_;
                        break;
                    }
                }
            }
            
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

bool FlagShip::alive() const
{
    return this->isAlive_;
}


void FlagShip::alienStartPlacement(int i)
{
    this->isAlive_ = 1;
    this->state_ = 0;
    if (i == 0)
    {
        this->alienX_ = FLAGSTART1;
    }
    else
    {
        this->alienX_ = FLAGSTART2;
    }
    this->alienY_ = COLSPACE;
}


void FlagShip::reset()
{
    this->state_ = 2;
    this->alienX_ = this->memoryX_;
    this->alienY_ = 0;
}


void FlagShip::changeDirection(FlagShip & a)
{
    a.setDx() = -(a.getDx());
}


void FlagShip::attack()
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


int FlagShip::state() const
{
    return this->state_;
}


void FlagShip::dying(int * score)
{
    if (this->state_ == 0 || this->state_ == 2)
    {
        *score += FLAGSCORE;
    }
    else if (this->state_ == 1)
    {
        *score += (FLAGSCORE * 2) + (FLAGSCORE / 2);
    }

    this->state_ = 3;
    this->isAlive_ = 0;
}
