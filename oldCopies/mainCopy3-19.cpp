/****************************************************************************
 Yihsiang Liow
 Copyright
 ****************************************************************************/
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


/*void test_starfield()
{
    Surface surface(W, H);
    Event event;

    const int NUM_STARS = 100;
    int * starX = new int[NUM_STARS];
    int * starY = new int[NUM_STARS];
    int * starRad = new int[NUM_STARS];
    int * starR = new int[NUM_STARS];
    int * starG = new int[NUM_STARS];
    int * starB = new int[NUM_STARS];
    int * starDy = new int[NUM_STARS];

    for (int i = 0; i < NUM_STARS; ++i)
    {
        starX[i] = rand() % W;
        starY[i] = rand() % H;
        starRad[i] = rand() % 4 + 1;
        switch (starRad[i])
        {
            case 1:
            {
                starR[i] = rand() % 128;
                starG[i] = rand() % 128;
                starB[i] = rand() % 128;
                starDy[i] = 1;
                break;
            }
            case 2:
            {
                starR[i] = rand() % 128 + 50;
                starG[i] = rand() % 128 + 50;
                starB[i] = rand() % 128 + 50;
                starDy[i] = 2;
                break;
            }
            case 3:
            {
                starR[i] = rand() % 128 + 75;
                starG[i] = rand() % 128 + 75;
                starB[i] = rand() % 128 + 75;
                starDy[i] = 3;
                break;
            }
            case 4:
            {
                starR[i] = rand() % 128 + 128;
                starG[i] = rand() % 128 + 128;
                starB[i] = rand() % 128 + 128;
                starDy[i] = 4;
                break;
            }
                    
        }
    }
    //Process events
    //if (event.poll() && event.type() == QUIT) break;

    //Move the stars
    for (int i = 0; i < NUM_STARS; ++i)
    {
        starY[i] += starDy[i];
    }

    //Check collision
    for (int i = 0; i < NUM_STARS; ++i)
    {
        if (starY[i] > H - 1)
        {
            starX[i] = rand() % W;
            starY[i] = 0;
            starRad[i] = rand() % 4 + 1;
            switch (starRad[i])
            {
                case 1:
                {
                    starR[i] = rand() % 128;
                    starG[i] = rand() % 128;
                    starB[i] = rand() % 128;
                    starDy[i] = 1;
                    break;
                }
                case 2:
                {
                    starR[i] = rand() % 128 + 50;
                    starG[i] = rand() % 128 + 50;
                    starB[i] = rand() % 128 + 50;
                    starDy[i] = 2;
                    break;
                }
                case 3:
                {
                    starR[i] = rand() % 128 + 75;
                    starG[i] = rand() % 128 + 75;
                    starB[i] = rand() % 128 + 75;
                    starDy[i] = 3;
                    break;
                }
                case 4:
                {
                    starR[i] = rand() % 128 + 128;
                    starG[i] = rand() % 128 + 128;
                    starB[i] = rand() % 128 + 128;
                    starDy[i] = 4;
                    break;
                }
            }
        }
        
        surface.lock();
        surface.fill(BLACK);
        //Draws screen
        for (int i = 0; i < NUM_STARS; ++i)
        {
            surface.put_circle(starX[i], starY[i], starRad[i], starR[i], starG[i], starB[i]);
        }
        surface.unlock();
        surface.flip();
        
        delay(10);
    }

    delete [] starX;
    delete [] starY;
    delete [] starRad;
    delete [] starR;
    delete [] starG;
    delete [] starB;
    delete [] starDy;
    
    return;
}
*/


class aquaAlien
{
public:
    aquaAlien()
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
    
    void drawAlien(Surface & surface)
    {
        for (int i = 0; i < NUMAQUA; ++i)
        {
            rect_.y = alienY_[i];
            rect_.x = alienX_[i];
            surface.put_image(image_, rect_); // blit image at rect on surface
        }
    }

    int getX() const
    {
        return this->rect_.x;
    }

    int getY() const
    {
        return this->rect_.y;
    }

    int getW() const
    {
        return this->rect_.w;
    }

    int getH() const
    {
        return this->rect_.h;
    }

    void moveAlien()
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
    
private:
    Image image_;
    Rect rect_;
    bool isAlive_[NUMAQUA];
    int alienX_[NUMAQUA];
    int alienY_[NUMAQUA];
    int pauseFrames_;
    int speed_;
    int dx_;
    int dy_;
};


class Player
{
public:
    Player()
        : dx_(0), dy_(0), speed_(0), image_("images/galaxian/GalaxianGalaxip.gif") 
    {
        rect_ = image_.getRect();
        rect_.y = H - rect_.h;
        rect_.x = W / 2 - rect_.w / 2;
    }
    
    void moveShipLeft()
    {
        this->dx_ = -3;
        addMove();
    }

    void moveShipRight()
    {
        this->dx_ = 3;
        addMove();
    }

    void stopShip()
    {
        this->dx_ = 0;
    }

    void addMove()
    {
        this->rect_.x += this->dx_;
    }

    void drawShip(Surface & surface) const
    {
        surface.put_image(image_, rect_); // blit image at rect on surface
    }

    int getX() const
    {
        return this->rect_.x;
    }

    int getY() const
    {
        return this->rect_.y;
    }

    int getW() const
    {
        return this->rect_.w;
    }

    int getH() const
    {
        return this->rect_.h;
    }
    
private:
    Image image_;
    Rect rect_;
    int speed_;
    int dx_;
    int dy_;
};

/*
  int numLasers;
    int totalAlive_;
    bool isAlive_[numLasers];
    int speed_;
    int laserW_[numLasers];
    int laserH_[numLasers];
    int laserX_[numLasers];
    int laserY_[numLasers];
*/
class PlayerLaser
{
public:
    PlayerLaser()
        : totalAlive_(0), speed_(5), laserW_(5), laserH_(10)
    {
        for (int i = 0; i < PLAYERLASERS; ++i)
        {
            isAlive_[i] = 0;
            laserX_[i] = 0;
            laserY_[i] = 0;
        }
    }
    
    void startLaser(const Player & player)
    {
        if (totalAlive_ <= PLAYERLASERS)
        {
            ++totalAlive_;
            for (int i = 0; i < totalAlive_; ++i)
            {
                if (isAlive_[i] == 0)
                {
                    isAlive_[i] = 1;
                    laserX_[i] = (player.getX() + player.getW() / 2) - (laserW_ / 2);
                    laserY_[i] = H - player.getH();
                    // std::cout << "playerX: " << player.getX() << '\n';
                    // std::cout << "playerW: " << player.getW() << '\n';
                    // std::cout << "isAlive_[" << i << "]: " << isAlive_[i] << '\n';
                    // std::cout << "laserX_[" << i << "]: " << laserX_[i] << '\n';
                    // std::cout << "laserY_[" << i << "]: " << laserY_[i] << '\n';
                }
            }
        }
    }
    
    void moveLaser()
    {
        for (int i = 0; i < PLAYERLASERS; ++i)
        {
            if (isAlive_[i])
            {
                if (laserY_[i] > 0)
                {
                    laserY_[i] -= speed_;
                    //std::cout << "laserY_[" << i << "]: " << laserY_[i] << '\n';
                }
                else
                {
                    killLaser(i);
                    --totalAlive_;
                }
            }
            
        }
    }


    void killLaser(int i)
    {
        isAlive_[i] = 0;
        laserX_[i] = 0;
        laserY_[i] = 0;
    }

    void drawLaser(Surface & surface)
    {
        for (int i = 0; i < PLAYERLASERS; ++i)
        {
            if (isAlive_[i])
            {
                this->moveLaser();
                if (laserY_[i] > 0)
                {
                    
                    surface.put_rect(laserX_[i], laserY_[i], laserW_, laserH_,
                                     rand() % 256, rand() % 256 , rand() % 256);
                }
            }
        }
        // if (laserY_ < 0)
        // {
        //     surface.put_rect(laserX_, laserY_, laserW_, laserH_,
        //                      rand() % 256, rand() % 256 , rand() % 256);
        // }
    }

private:
    int totalAlive_ = 0;
    bool isAlive_[PLAYERLASERS];
    int speed_;
    int laserW_;
    int laserH_;
    int laserX_[PLAYERLASERS];
    int laserY_[PLAYERLASERS];
};


class Starfield
{
public:

private:
    // const int NUM_STARS = 100;
    // int * starX = new int[NUM_STARS];
    // int * starY = new int[NUM_STARS];
    // int * starRad = new int[NUM_STARS];
    // int * starR = new int[NUM_STARS];
    // int * starG = new int[NUM_STARS];
    // int * starB = new int[NUM_STARS];
    // int * starDy = new int[NUM_STARS];
};


void drawScreen(Surface & surface)
{
    surface.lock();
    surface.fill(BLACK);
}

void runScreen(Surface & surface)
{
    surface.unlock();
    surface.flip();
    delay(20); 
}

void test_player()
{
    //test_starfield();
    
    
    Surface surface(W, H);
    
    Player player;
    Event event;
    aquaAlien aquaAlien;
    PlayerLaser playerLaser;
    bool testLaser = 1;
    int laserDelay = 20;
    while (1)
    {
        KeyPressed keypressed = get_keypressed();
        if (event.poll() && event.type() == QUIT) break;
        
      
        if (keypressed[SPACE])
        {
            if (laserDelay == 0)
            {
                playerLaser.startLaser(player);
                laserDelay = 20;
            }
        }
        
        if (player.getX() > 0 && keypressed[LEFTARROW])
        {
            player.moveShipLeft();
        }
        else if (player.getX() < W - player.getW() && keypressed[RIGHTARROW])
        {
            player.moveShipRight();
        }
        else
        {
            player.stopShip();
        }

        if (laserDelay > 0)
        {
            --laserDelay;
        }
        //playerLaser.moveLaser();
        drawScreen(surface);
        playerLaser.drawLaser(surface);
        aquaAlien.moveAlien();
        aquaAlien.drawAlien(surface);
        player.drawShip(surface);
        runScreen(surface);
        // // if (laserTrue)
        // // {
        // //     playerLaser(surface, laserStart, laserHeight, laserTrue);
        // // }
    }
    return;
}

void gameLoop()
{
    Surface surface(W, H);
    
    Event event;
    while (1)
    {
        if (event.poll() && event.type() == QUIT) break;
        
        //test_player();
        //test_starfield();
    }
}

int main(int argc, char* argv[])
{
    //gameLoop();
    test_player();
    //test_alien();
    return 0;
}
