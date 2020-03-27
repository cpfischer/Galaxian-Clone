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
#include "Player.h"
#include "AquaAlien.h"
#include "PurpleAlien.h"
#include "RedAlien.h"
#include "FlagShip.h"
#include "vector"

Image Explosion::image1_("images/galaxian/explosion1.gif");
Image Explosion::image2_("images/galaxian/explosion2.gif");
Image Explosion::image3_("images/galaxian/explosion3.gif");
Image Explosion::image4_("images/galaxian/explosion4.gif");
Image Explosion::image5_("images/galaxian/explosion5.gif");
Image Explosion::image6_("images/galaxian/explosion6.gif");
Sound Explosion::boom_("sounds/explosion.wav");

Explosion::Explosion()
    : isAlive_(0), state_(0), delay_(5)
{
    rect_ = Explosion::image1_.getRect();
}

void Explosion::changeState()
{
    if (this->delay_ != 0)
    {
        --(this->delay_);
    }
    else if (this->delay_ == 0)
    {
        this->delay_ = 5;
        ++(this->state_);
    }
}

void Explosion::drawExplosion(Surface & surface)
{
    // blit image at rect on surface
    if (this->isAlive_)
    {
        switch(this->state_)
        {
            case 0:
                boom_.play();
                surface.put_image(Explosion::image1_, this->rect_);
                changeState();
                break;
            case 1:
                surface.put_image(Explosion::image2_, this->rect_);
                changeState();
                break;
            case 2:
                surface.put_image(Explosion::image3_, this->rect_);
                changeState();
                break;
            case 3:
                surface.put_image(Explosion::image4_, this->rect_);
                changeState();
                break;
            case 4:
                surface.put_image(Explosion::image5_, this->rect_);
                changeState();
                break;
            case 5:
                surface.put_image(Explosion::image6_, this->rect_);
                this->state_ = 0;
                this->isAlive_ = 0;
                break;
        }
    }
}


void Explosion::setCoords(int x, int y)
{
    rect_.x = x;
    rect_.y = y;
    this->isAlive_ = 1;
}


bool Explosion::alive()
{
    return this->isAlive_;
}


int Explosion::state()
{
    return this->state_;
}
