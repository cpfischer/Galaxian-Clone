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
#include "Player.h"
#include "PlayerLaser.h"
#include "AquaAlien.h"
#include "PurpleAlien.h"
#include "RedAlien.h"
#include "FlagShip.h"


PlayerLaser::PlayerLaser()
    : speed_(PLASERSPEED), laserW_(5), laserH_(10), isAlive_(0), laserX_(0),
      laserY_(0)
{}


void PlayerLaser::startLaser(const Player & player)
{
    if (!isAlive_)
    {
        this->isAlive_ = 1;
        this->laserX_ = (player.getX() + player.getW() / 2) - (laserW_ / 2);
        this->laserY_ = H - (player.getH() + player.getH() / 2);
    }
}


void PlayerLaser::checkCollision(std::vector<AquaAlien> & aaR1,
                                 std::vector<AquaAlien> & aaR2,
                                 std::vector<AquaAlien> & aaR3,
                                 std::vector<PurpleAlien> & paa,
                                 std::vector<RedAlien> & raa,
                                 std::vector<FlagShip> & fsa,
                                 int * score)
{
    int laserx1 = this->laserX_;
    int lasery1 = this->laserY_;
    int laserx2 = laserx1 + laserW_;
    int lasery2 = lasery1 + laserH_;
    
    for (int i = 0; i < NUMAQUA; ++i)
    {
        int aaR1x1 = aaR1[i].getX();
        int aaR1y1 = aaR1[i].getY();
        int aaR1x2 = aaR1x1 + aaR1[i].getW();
        int aaR1y2 = aaR1y1 + aaR1[i].getH();

        int aaR2x1 = aaR2[i].getX();
        int aaR2y1 = aaR2[i].getY();
        int aaR2x2 = aaR2x1 + aaR2[i].getW();
        int aaR2y2 = aaR2y1 + aaR2[i].getH();

        int aaR3x1 = aaR3[i].getX();
        int aaR3y1 = aaR3[i].getY();
        int aaR3x2 = aaR3x1 + aaR3[i].getW();
        int aaR3y2 = aaR3y1 + aaR3[i].getH();
    
        if (((aaR1x1 >= laserx1 && aaR1x1 <= laserx2)
             || (laserx1 >= aaR1x1 && laserx1 <= aaR1x2))
             && ((aaR1y1 >= lasery1 && aaR1y1 <= lasery2)
             || (lasery1 >= aaR1y1 && lasery1 <= aaR1y2)))
        {
            if ((aaR1[i].state() == 0 || aaR1[i].state() == 1)
                && this->isAlive_ == 1)
            {
                aaR1[i].dying(score);
                this->isAlive_ = 0;
            }
        }

        if (((aaR2x1 >= laserx1 && aaR2x1 <= laserx2)
             || (laserx1 >= aaR2x1 && laserx1 <= aaR2x2))
             && ((aaR2y1 >= lasery1 && aaR2y1 <= lasery2)
             || (lasery1 >= aaR2y1 && lasery1 <= aaR2y2)))
        {
            if ((aaR2[i].state() == 0 || aaR2[i].state() == 1)
                && this->isAlive_ == 1)
            {
                aaR2[i].dying(score);
                this->isAlive_ = 0;
            }
        }

        if (((aaR3x1 >= laserx1 && aaR3x1 <= laserx2)
             || (laserx1 >= aaR3x1 && laserx1 <= aaR3x2))
             && ((aaR3y1 >= lasery1 && aaR3y1 <= lasery2)
             || (lasery1 >= aaR3y1 && lasery1 <= aaR3y2)))
        {
            if ((aaR3[i].state() == 0 || aaR3[i].state() == 1)
                && this->isAlive_ == 1)
            {
                aaR3[i].dying(score);
                this->isAlive_ = 0;
            }
        }
    }
    
    for (int i = 0; i < NUMPURP; ++i)
    {
        int paax1 = paa[i].getX();
        int paay1 = paa[i].getY();
        int paax2 = paax1 + paa[i].getW();
        int paay2 = paay1 + paa[i].getH();

        if (((paax1 >= laserx1 && paax1 <= laserx2)
             || (laserx1 >= paax1 && laserx1 <= paax2))
             && ((paay1 >= lasery1 && paay1 <= lasery2)
             || (lasery1 >= paay1 && lasery1 <= paay2)))
        {
            if ((paa[i].state() == 0 || paa[i].state() == 1)
                && this->isAlive_ == 1)
            {
                paa[i].dying(score);
                this->isAlive_ = 0;
            }
        }
    }

    for (int i = 0; i < NUMRED; ++i)
    {
        int raax1 = raa[i].getX();
        int raay1 = raa[i].getY();
        int raax2 = raax1 + raa[i].getW();
        int raay2 = raay1 + raa[i].getH();

        if (((raax1 >= laserx1 && raax1 <= laserx2)
             || (laserx1 >= raax1 && laserx1 <= raax2))
             && ((raay1 >= lasery1 && raay1 <= lasery2)
             || (lasery1 >= raay1 && lasery1 <= raay2)))
        {
            if ((raa[i].state() == 0 || raa[i].state() == 1)
                && this->isAlive_ == 1)
            {
                raa[i].dying(score);
                this->isAlive_ = 0;
            }
        }
    }

    for (int i = 0; i < NUMFLAG; ++i)
    {
        int fsax1 = fsa[i].getX();
        int fsay1 = fsa[i].getY();
        int fsax2 = fsax1 + fsa[i].getW();
        int fsay2 = fsay1 + fsa[i].getH();

        if (((fsax1 >= laserx1 && fsax1 <= laserx2)
             || (laserx1 >= fsax1 && laserx1 <= fsax2))
             && ((fsay1 >= lasery1 && fsay1 <= lasery2)
             || (lasery1 >= fsay1 && lasery1 <= fsay2)))
        {
            if ((fsa[i].state() == 0 || fsa[i].state() == 1)
                && this->isAlive_ == 1)
            {
                fsa[i].dying(score);
                this->isAlive_ = 0;
            }
        }
    }
}



void PlayerLaser::moveLaser()
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


void PlayerLaser::drawLaser(Surface & surface)
{
    if (this->isAlive_)
    {
        if (this->laserY_ > 0)
        {       
            surface.put_rect(this->laserX_, this->laserY_, this->laserW_,
                             this->laserH_, 0, 0, 255);
        }
    }
}


PlayerLaser::~PlayerLaser()
{}


bool PlayerLaser::alive() const
{
    return this->isAlive_;
}
