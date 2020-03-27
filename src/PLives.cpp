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
#include "PLives.h"

Image PLives::image_("images/galaxian/GalaxianGalaxip.gif");

PLives::PLives()
    : isAlive_(1)
{}

PLives::PLives(const int n)
    : isAlive_(1)
{
        rect_ = image_.getRect();
        rect_.y = H - rect_.h;
        rect_.x = 1 + (n * (rect_.w));
}


void PLives::drawLives(Surface & surface)
{
    if (this->isAlive_)
    {
        surface.put_image(image_, rect_); // blit image at rect on surface
    }
}
