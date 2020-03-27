#ifndef PLIVES_H
#define PLIVES_H
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

class PLives
{
public:
    PLives();
    PLives(const int n);

    void drawLives(Surface & surface);
    bool alive();
private:
    static Image image_;
    Rect rect_;
    bool isAlive_;
};

#endif
