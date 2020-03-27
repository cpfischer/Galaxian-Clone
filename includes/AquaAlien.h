#ifndef AQUAALIEN_H
#define AQUAALIEN_H
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
#include "Explosion.h"
#include "GameObject.h"

class AquaAlien: public GameObject
{
public:
    AquaAlien();
    
    void drawAlien(Surface & surface, Explosion & e);
    void alienStartPlacement(int i, int r);

    int getX() const;
    int getY() const;
    int getW() const;
    int getH() const;
    bool alive() const;
    int state() const;
    int getMemX() const;
    int getMemY() const;
    void dying(int * score);
    void attack();
    void reset();
    void changeDirection(AquaAlien & a);
    void moveAlien(const int pauseFrames);
    
private:
    static Image image_;
    Rect rect_;
    bool isAlive_;
    int alienX_;
    int alienY_;
    int speed_;
    //int dx_;
    int dy_;
    int state_;
    int memoryX_;
    int memoryY_;
    int median_;
};

#endif
