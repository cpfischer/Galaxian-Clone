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
#include "StarField.h"

StarField::StarField()
    : starX_(new int[NUM_STARS]), starY_(new int[NUM_STARS]),
      starRad_(new int [NUM_STARS]), starR_(new int[NUM_STARS]),
      starG_(new int [NUM_STARS]), starB_(new int[NUM_STARS]),
      starDy_(new int[NUM_STARS])
{
    for (int i = 0; i < NUM_STARS; ++i)
    {
        createStars(i);
        starY_[i] = rand() % H;
    }
}


void StarField::createStars(const int i)
{
    starX_[i] = rand() % W;
    starY_[i] = 0;
    starRad_[i] = rand() % 3 + 1;
    starR_[i] = 200;
    starG_[i] = 0;
    starB_[i] = 0;
    starDy_[i] = starRad_[i];
}


void StarField::checkCollision(const int i)
{
    if (starY_[i] > H - 1)
    {
        createStars(i);
    }
}


void StarField::moveStars()
{
    for (int i = 0; i < NUM_STARS; ++i)
    {
        checkCollision(i);
        starY_[i] += starDy_[i];
    }
}


void StarField::drawStars(Surface & surface) const
{
    for (int i = 0; i < NUM_STARS; ++i)
    {
        surface.put_circle(starX_[i], starY_[i], starRad_[i], starR_[i],
                           starG_[i], starB_[i]);
    }
}


StarField::~StarField()
{
    delete [] starX_;
    delete [] starY_;
    delete [] starRad_;
    delete [] starR_;
    delete [] starG_;
    delete [] starB_;
    delete [] starDy_;
}
