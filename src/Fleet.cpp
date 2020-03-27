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
#include "RedAlien.h"
#include "PurpleAlien.h"
#include "FlagShip.h"
#include "Fleet.h"
#include "Player.h"
#include "AlienLaser.h"


Fleet::Fleet()
    : numAttackA_(0), numAttackP_(0), aTimer_(rand() % 200 + 300),
      purpleTimer_(rand() % 300 + 400), flagTimer_(rand() % 500 + 650),
      isAlive_(1), level_(1), pauseFrames_(20), respawnTimer_(400),
      isRespawning_(0), changeDelay_(2500), isChanging_(1)
{}


void Fleet::startPlacement(std::vector<AquaAlien> & aaR1,
                           std::vector<AquaAlien> & aaR2,
                           std::vector<AquaAlien> & aaR3,
                           std::vector<PurpleAlien> & paa,
                           std::vector<RedAlien> & raa,
                           std::vector<FlagShip> & fsa)
{
    for (int i = 0; i < NUMAQUA; ++i)
    {
        if (i < NUMAQUA)
        {
            aaR1[i].alienStartPlacement(i, 1);
            aaR2[i].alienStartPlacement(i, 2);
            aaR3[i].alienStartPlacement(i, 3);    
        }
        
        if (i < NUMPURP)
        {
            paa[i].alienStartPlacement(i);
        }

        if (i < NUMRED)
        {
            raa[i].alienStartPlacement(i);
        }

        if (i < NUMFLAG)
        {
            fsa[i].alienStartPlacement(i);
        }
    }
}


void Fleet::move(std::vector<AquaAlien> & aaR1,
                 std::vector<AquaAlien> & aaR2,
                 std::vector<AquaAlien> & aaR3,
                 std::vector<PurpleAlien> & paa,
                 std::vector<RedAlien> & raa,
                 std::vector<FlagShip> & fsa,
                 std::vector<AlienLaser> & alaR1,
                 std::vector<AlienLaser> & alaR2,
                 std::vector<AlienLaser> & alaR3,
                 std::vector<AlienLaser> & alPurp,
                 std::vector<AlienLaser> & alRed,
                 std::vector<AlienLaser> & alFlag,
                 Sound & alienFire)
{
    for (int i = 0; i < NUMAQUA; ++i)
    {
        if (i < NUMAQUA)
        {
            aaR1[i].moveAlien(this->pauseFrames_);
            aaR2[i].moveAlien(this->pauseFrames_);
            aaR3[i].moveAlien(this->pauseFrames_);
            alaR1[i].checkAlien(aaR1[i], alienFire);
            alaR2[i].checkAlien(aaR2[i], alienFire);
            alaR3[i].checkAlien(aaR3[i], alienFire);
            alaR1[i].moveLaser();
            alaR2[i].moveLaser();
            alaR3[i].moveLaser();
        }

        if (i < NUMPURP)
        {
            paa[i].moveAlien(this->pauseFrames_);
            alPurp[i].checkAlien(paa[i], alienFire);
            alPurp[i].moveLaser();
        }
        
        if (i < NUMRED)
        {
            raa[i].moveAlien(this->pauseFrames_);
            alRed[i].checkAlien(raa[i], alienFire);
            alRed[i].moveLaser();
        }

        if (i < NUMFLAG)
        {
            if (i == 0)
            {
                fsa[i].moveAlien(raa, this->pauseFrames_, i);
            }
            else if (i == 1)
            {
                fsa[i].moveAlien(raa, this->pauseFrames_, i);
            }
            alFlag[i].checkAlien(fsa[i], alienFire);
            alFlag[i].moveLaser();
        }
    }
    
    if (this->pauseFrames_ > 0)
    {
        --(this->pauseFrames_);
    }
    else
    {
        this->pauseFrames_ = 20;
    }
}


void Fleet::reset(std::vector<AquaAlien> & aaR1,
                  std::vector<AquaAlien> & aaR2,
                  std::vector<AquaAlien> & aaR3,
                  std::vector<PurpleAlien> & paa,
                  std::vector<RedAlien> & raa,
                  std::vector<FlagShip> & fsa)
{
    this->isAlive_ = 0;
    for (int i = 0; i < NUMAQUA; ++i)
    {
        if (i < NUMAQUA)
        {
            if (aaR1[i].alive() || aaR2[i].alive() || aaR3[i].alive())
            {
                //std::cout << "BlueAlive\n";
                this->isAlive_ = 1;
                break;
            }
        }

        if (i < NUMPURP)
        {
            if (paa[i].alive())
            {
                //std::cout << "PurpleAlive\n";
                this->isAlive_ = 1;
                break;
            }
        }

        if (i < NUMRED)
        {
            if (raa[i].alive())
            {
                //std::cout << "RedAlive\n";
                this->isAlive_ = 1;
                break;
            }
        }

        if (i < NUMFLAG)
        {
            if (fsa[i].alive())
            {
                //std::cout << "FlagAlive\n";
                this->isAlive_ = 1;
                break;
            }
        }
    }
    if (!(this->isAlive_) && !(this->isRespawning_))
    {
        this->isRespawning_ = 1;
    }
    
    if (this->isRespawning_ && this->respawnTimer_ > 0)
    {
        --(this->respawnTimer_);
    }
    else if (this->isRespawning_ && this->respawnTimer_ == 0)
    {
        ++(this->level_);
        this->isAlive_ = 1;
        this->respawnTimer_ = 400;
        this->isRespawning_ = 0;
        this->startPlacement(aaR1, aaR2, aaR3, paa, raa, fsa);
    }
}


void Fleet::changeDirection(std::vector<AquaAlien> & aaR1,
                            std::vector<AquaAlien> & aaR2,
                            std::vector<AquaAlien> & aaR3,
                            std::vector<PurpleAlien> & paa,
                            std::vector<RedAlien> & raa,
                            std::vector<FlagShip> & fsa)
{
    for (int i = 0; i < NUMAQUA; ++i)
    {
        //Checks if any rows or the memory x of that row is past the change
        //direction line
        if (i < NUMAQUA)
        {
            if (((aaR1[i].getX() + aaR1[i].getW() >= (W - 5) ||
                  aaR1[i].getX() <= 5) && aaR1[i].state() == 0) ||
                ((aaR1[i].getMemX() + aaR1[i].getW() >= (W - 5) ||
                  aaR1[i].getMemX() <= 5) && aaR1[i].state() == 2))
            {
                if (!isChanging_)
                {
                    //std::cout << changeDelay_ << '\n';
                    changeAllDirection(aaR1, aaR2, aaR3, paa, raa, fsa);
                    isChanging_ = 1;
                    break;
                }
            }
            
            if (((aaR2[i].getX() + aaR2[i].getW() >= (W - 5) ||
                  aaR2[i].getX() <= 5) && aaR2[i].state() == 0) ||
                ((aaR2[i].getMemX() + aaR2[i].getW() >= (W - 5) ||
                  aaR2[i].getMemX() <= 5) && aaR2[i].state() == 2))
            {
                if (!isChanging_)
                {
                    changeAllDirection(aaR1, aaR2, aaR3, paa, raa, fsa);
                    isChanging_ = 1;
                    break;
                }
            }
            
            if (((aaR3[i].getX() + aaR3[i].getW() >= (W - 5) ||
                  aaR3[i].getX() <= 5) && aaR3[i].state() == 0) ||
                ((aaR3[i].getMemX() + aaR3[i].getW() >= (W - 5) ||
                  aaR3[i].getMemX() <= 5) && aaR3[i].state() == 2))
            {
                if (!isChanging_)
                {
                    changeAllDirection(aaR1, aaR2, aaR3, paa, raa, fsa);
                    isChanging_ = 1;
                    break;
                }
            }
        }
        
        if (i < NUMPURP)
        {
            if ((((paa[i].getX() + paa[i].getW() >= (W - 5) ||
                 paa[i].getX() <= 5) && paa[i].state() == 0) ||
                 ((paa[i].getMemX() + paa[i].getW() >= (W - 5) ||
                   paa[i].getMemX() <= 5) && paa[i].state() == 2)))
            {
                if (!isChanging_)
                {
                    changeAllDirection(aaR1, aaR2, aaR3, paa, raa, fsa);
                    isChanging_ = 1;
                    break;
                }
            }
        }

        if (i < NUMRED)
        {
            if ((((raa[i].getX() + raa[i].getW() >= (W - 5) ||
                 raa[i].getX() <= 5) && raa[i].state() == 0) ||
                 ((raa[i].getMemX() + raa[i].getW() >= (W - 5) ||
                   raa[i].getMemX() <= 5) && raa[i].state() == 2)))
            {
                if (!isChanging_)
                {
                    changeAllDirection(aaR1, aaR2, aaR3, paa, raa, fsa);
                    isChanging_ = 1;
                    break;
                }
            }
        }

        if (i < NUMFLAG)
        {
            if ((((fsa[i].getX() + fsa[i].getW() >= (W - 5) ||
                 fsa[i].getX() <= 5) && fsa[i].state() == 0) ||
                 ((fsa[i].getMemX() + fsa[i].getW() >= (W - 5) ||
                   fsa[i].getMemX() <= 5) && fsa[i].state() == 2)))
            {
                if (!isChanging_)
                {
                    changeAllDirection(aaR1, aaR2, aaR3, paa, raa, fsa);
                    isChanging_ = 1;
                    break;
                }
            }
        }

        if (isChanging_ && changeDelay_ == 0)
        {
            //std::cout << "RESET";
            isChanging_ = 0;   
            this->changeDelay_ = 2500;
        }
        else if (isChanging_ && changeDelay_ > 0)
        {
            //std::cout << "changeDelay: " << changeDelay_ << '\n';
            --(this->changeDelay_);
        }
    }
}

void changeAllDirection(std::vector<AquaAlien> & aaR1,
                        std::vector<AquaAlien> & aaR2,
                        std::vector<AquaAlien> & aaR3,
                        std::vector<PurpleAlien> & paa,
                        std::vector<RedAlien> & raa,
                        std::vector<FlagShip> & fsa)
{
    
    for (int i = 0; i < NUMAQUA; ++i)
    {
        if (i < NUMAQUA)
        {
            aaR1[i].changeDirection(aaR1[i]);
            aaR2[i].changeDirection(aaR2[i]);
            aaR3[i].changeDirection(aaR3[i]);
        }

        if (i < NUMPURP)
        {
            paa[i].changeDirection(paa[i]);
        }

        if (i < NUMRED)
        {
            raa[i].changeDirection(raa[i]);
        }

        if (i < NUMFLAG)
        {
            fsa[i].changeDirection(fsa[i]);
        }
    }
}

void Fleet::alienAttack(std::vector<AquaAlien> & aaR1,
                        std::vector<AquaAlien> & aaR2,
                        std::vector<AquaAlien> & aaR3,
                        std::vector<PurpleAlien> & paa,
                        std::vector<RedAlien> & raa,
                        std::vector<FlagShip> & fsa)
{
    int maxAttackA = this->level_ + 2;
    int maxAttackP = this->level_;
    this->numAttackA_ = 0;
    this->numAttackP_ = 0;
    if (aTimer_ > 0)
    {
        --aTimer_;
    }
    else
    {
        aTimer_ = rand() % 200 + 300;
    }

    if (purpleTimer_ > 0)
    {
        --purpleTimer_;
    }
    else
    {
        purpleTimer_ = rand() % 300 + 400;
    }

    if (flagTimer_ > 0)
    {
        --flagTimer_;
    }
    else
    {
        flagTimer_ = rand() % 500 + 650;
    }
    for (int i = 0; i < NUMAQUA; ++i)
    {
        if (i < NUMAQUA && aTimer_ == 0)
        {
            int goAttack1 = rand() % 10;
            int goAttack2 = rand() % 10;
            int goAttack3 = rand() % 10;
            if ((goAttack1 == 1 || goAttack1 == 2) && numAttackA_ < maxAttackA)
            {
                aaR1[i].attack();
                if (aaR1[i].state() == 1)
                {
                    ++(this->numAttackA_);
                }
            }

            if ((goAttack2 == 1 || goAttack2 == 2) && numAttackA_ < maxAttackA)
            {
                aaR2[i].attack();
                if (aaR2[i].state() == 1)
                {
                    ++(this->numAttackA_);
                }
            }

            if ((goAttack3 == 1 || goAttack3 == 2) && numAttackA_ < maxAttackA)
            {
                aaR3[i].attack();
                if (aaR3[i].state() == 1)
                {
                    ++(this->numAttackA_);
                }
            }
        }

        if (i < NUMPURP && purpleTimer_ == 0)
        {
            int goAttack = rand() % 10;
            if ((goAttack == 1 || goAttack == 2) && numAttackP_ < maxAttackP)
            {
                paa[i].attack();
                ++(this->numAttackP_);
            }
        }
        
        if (i < 1 && flagTimer_ == 0)
        {
            int fsaRand = rand() % NUMFLAG;
            if (fsaRand == 0)
            {
                raa[0].attack();
                raa[1].attack();
                raa[2].attack();
            }
            else if (fsaRand == 1)
            {
                raa[3].attack();
                raa[4].attack();
                raa[5].attack();
            }
            fsa[fsaRand].attack();
        }   
    }
}

void Fleet::checkCollision(Player & player,
                           std::vector<AquaAlien> & aaR1,
                           std::vector<AquaAlien> & aaR2,
                           std::vector<AquaAlien> & aaR3,
                           std::vector<PurpleAlien> & paa,
                           std::vector<RedAlien> & raa,
                           std::vector<FlagShip> & fsa,
                           int * score)
{
    for (int i = 0; i < NUMAQUA; ++i)
    {
        int playerx1 = player.getX();
        int playery1 = player.getY();
        int playerx2 = player.getX() + player.getW();
        int playery2 = player.getY() + player.getH();
            
        if (i < NUMAQUA)
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
        
            if (((aaR1x1 >= playerx1 && aaR1x1 <= playerx2)
                 || (playerx1 >= aaR1x1 && playerx1 <= aaR1x2))
                && ((aaR1y1 >= playery1 && aaR1y1 <= playery2)
                    || (playery1 >= aaR1y1 && playery1 <= aaR1y2)))
            {
                if (player.state() == 0 && aaR1[i].state() == 1)
                {
                    aaR1[i].dying(score);
                    player.dying();
                }
            }

            if (((aaR2x1 >= playerx1 && aaR2x1 <= playerx2)
                 || (playerx1 >= aaR2x1 && playerx1 <= aaR2x2))
                && ((aaR2y1 >= playery1 && aaR2y1 <= playery2)
                    || (playery1 >= aaR2y1 && playery1 <= aaR2y2)))
            {
                if (player.state() == 0 && aaR2[i].state() == 1)
                {
                    aaR2[i].dying(score);
                    player.dying();
                }
            }

            if (((aaR3x1 >= playerx1 && aaR3x1 <= playerx2)
                 || (playerx1 >= aaR3x1 && playerx1 <= aaR3x2))
                && ((aaR3y1 >= playery1 && aaR3y1 <= playery2)
                    || (playery1 >= aaR3y1 && playery1 <= aaR3y2)))
            {
                if (player.state() == 0 && aaR3[i].state() == 1)
                {
                    aaR3[i].dying(score);
                    player.dying();
                }
            }
        }
    
    
        if (i < NUMPURP)
        {
            int paax1 = paa[i].getX();
            int paay1 = paa[i].getY();
            int paax2 = paax1 + paa[i].getW();
            int paay2 = paay1 + paa[i].getH();

            int playerx1 = player.getX();
            int playery1 = player.getY();
            int playerx2 = player.getX() + player.getW();
            int playery2 = player.getY() + player.getH();
        
            if (((paax1 >= playerx1 && paax1 <= playerx2)
                 || (playerx1 >= paax1 && playerx1 <= paax2))
                && ((paay1 >= playery1 && paay1 <= playery2)
                    || (playery1 >= paay1 && playery1 <= paay2)))
            {
                if (player.state() == 0 && paa[i].state() == 1)
                {
                    paa[i].dying(score);
                    player.dying();
                }
            }
        }
    
        if (i < NUMRED)
        {
            int raax1 = raa[i].getX();
            int raay1 = raa[i].getY();
            int raax2 = raax1 + raa[i].getW();
            int raay2 = raay1 + raa[i].getH();

            int playerx1 = player.getX();
            int playery1 = player.getY();
            int playerx2 = player.getX() + player.getW();
            int playery2 = player.getY() + player.getH();
        
            if (((raax1 >= playerx1 && raax1 <= playerx2)
                 || (playerx1 >= raax1 && playerx1 <= raax2))
                && ((raay1 >= playery1 && raay1 <= playery2)
                    || (playery1 >= raay1 && playery1 <= raay2)))
            {
                if (player.state() == 0 && raa[i].state() == 1)
                {
                    raa[i].dying(score);
                    player.dying();
                }
            }
        }

        if (i < NUMFLAG)
        {
            int fsax1 = fsa[i].getX();
            int fsay1 = fsa[i].getY();
            int fsax2 = fsax1 + fsa[i].getW();
            int fsay2 = fsay1 + fsa[i].getH();

            int playerx1 = player.getX();
            int playery1 = player.getY();
            int playerx2 = player.getX() + player.getW();
            int playery2 = player.getY() + player.getH();
        
            if (((fsax1 >= playerx1 && fsax1 <= playerx2)
                 || (playerx1 >= fsax1 && playerx1 <= fsax2))
                && ((fsay1 >= playery1 && fsay1 <= playery2)
                    || (playery1 >= fsay1 && playery1 <= fsay2)))
            {
                if (player.state() == 0 && fsa[i].state() == 1)
                {
                    fsa[i].dying(score);
                    player.dying();
                }
            }
        }
    }
}

bool Fleet::isRespawning()
{
    return this->isRespawning_;
}


int Fleet::level()
{
    return this->level_;
}
