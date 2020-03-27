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

aquaAlien::aquaAlien()
    : dx_(20), dy_(0), speed_(20), pauseFrames_(20),
      image_("images/galaxian/GalaxianAquaAlien.gif")
{
    for (int i = 0; i < NUMAQUA; ++i)
    {
        rect_ = image_.getRect();
        alienY_[i] = 0 + rect_.h;
        alienX_[i] = (i * 50) + W / 2 - rect_.w / 2;
        isAlive_[i] = 1;
    }
}


void aquaAlien::drawAlien(Surface & surface)
{
    for (int i = 0; i < NUMAQUA; ++i)
    {
        rect_.y = alienY_[i];
        rect_.x = alienX_[i];
        surface.put_image(image_, rect_); // blit image at rect on surface
    }
}


int aquaAlien::getX() const
{
    return this->rect_.x;
}


int aquaAlien::getY() const
{
    return this->rect_.y;
}


int aquaAlien::getW() const
{
    return this->rect_.w;
}


int aquaAlien::getH() const
{
    return this->rect_.h;
}


void aquaAlien::moveAlien()
{
    if (this->pauseFrames_ == 0)
    {
        for (int i = 0; i < NUMAQUA; ++i)
        {
            alienX_[i] += this->dx_;
            this->pauseFrames_ = 20;
        }
    }
    else
    {
        --(this->pauseFrames_);
    }

    for (int i = 0; i < NUMAQUA; ++i)
    {
        if (alienX_[i] + rect_.w >= W)
        {
            this->dx_ = -(this->speed_);
        }
        else if (alienX_[i] + rect_.w / 2 <= 0)
        {
            // CASE: right side of image touches the right side of surface
            this->dx_ = this->speed_;
        }
    }
}
