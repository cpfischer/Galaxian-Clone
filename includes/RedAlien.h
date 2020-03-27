#ifndef REDALIEN_H
#define REDALIEN_H
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

class RedAlien: public GameObject
{
public:
    RedAlien();
    
    void drawAlien(Surface & surface, Explosion & e);
    void alienStartPlacement(int i);

    int getX() const;
    int getY() const;
    int getW() const;
    int getH() const;
    int getMemX() const;
    int getMemY() const;
    bool alive() const;
    int state() const;
    void dying(int * score);
    void attack();
    void reset();
    void changeDirection(RedAlien & a);
    void moveAlien(const int pauseFrames);
    
private:
    static Image image_;
    Rect rect_;
    bool isAlive_;
    int alienX_;
    int alienY_;
    int speed_;
    int dy_;
    int state_;
    int memoryX_;
    int memoryY_;
    int median_;
};

#endif
