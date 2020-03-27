#ifndef STARFIELD_H
#define STARFIELD_H
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

class StarField
{
public:
    
    StarField();
    void createStars(const int i);
    void checkCollision(const int i);
    void moveStars();
    void drawStars(Surface & surface) const;
    ~StarField();
    
private:
    int * starX_;
    int * starY_;
    int * starRad_;
    int * starR_;
    int * starG_;
    int * starB_;
    int * starDy_;
};

#endif

