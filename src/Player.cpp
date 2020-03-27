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
#include "Player.h"
#include "Explosion.h"

Image Player::image_("images/galaxian/GalaxianGalaxip.gif");


//States: 0 = normal, 1 = exploding, 2 = respawn, 3 = invincible
Player::Player()
    : dx_(0), dy_(0), speed_(0), state_(0), lives_(NUMLIVES), invincible_(0)
{
    rect_ = image_.getRect();
    rect_.y = H - (rect_.h * 2) + 2;
    rect_.x = W / 2 - rect_.w / 2;
}


void Player::moveShipLeft()
{
    this->dx_ = -(PLAYERSPEED);
    addMove();
}


void Player::moveShipRight()
{
    this->dx_ = PLAYERSPEED;
    addMove();
}


void Player::stopShip()
{
    this->dx_ = 0;
}


int Player::state() const
{
    return this->state_;
}


void Player::dying()
{
    this->state_ = 1;
}

int Player::lives() const
{
    return this->lives_;
}

void Player::bonusLife()
{
    ++(this->lives_);
}

void Player::respawn()
{
    this->dx_ = 0;
    this->dy_ = 0;
    this->speed_ = 0;
    this->state_ = 3;
    this->invincible_ = 60;
    this->rect_.x = W / 2 - rect_.w / 2;
    this->lives_ -= 1;
}


void Player::addMove()
{
    this->rect_.x += this->dx_;
}


void Player::drawShip(Surface & surface, Explosion & e)
{
    if (this->state_ == 0 || this->state_ == 3)
    {
        surface.put_image(image_, rect_); // blit image at rect on surface
    }
    else if (this->state_ == 1)
    {
        if (!(e.alive()) && e.state() != 5)
        {
            e.setCoords(this->rect_.x, this->rect_.y);
        }
        if (e.state() == 5)
        {
            this->state_ = 2;
        }
    }
}


int Player::getX() const
{
    return this->rect_.x;
}


int Player::getY() const
{
    return this->rect_.y;
}


int Player::getW() const
{
    return this->rect_.w;
}


int Player::getH() const
{
    return this->rect_.h;
}


int Player::invincible()
{
    if (this->invincible_ > 0)
    {
        --(this->invincible_);
    }
    else if (this->invincible_ == 0 && this->state_ == 3)
    {
        this->state_ = 0;
    }
}
