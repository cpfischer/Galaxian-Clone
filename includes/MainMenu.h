#ifndef MAINMENU_H
#define MAINMENU_H
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
#include "Screen.h"
//******************************************************************************
//This file is the header for the main menu of the game
//The mainMenu function calls the main menu loop
//
//The showAlien function calls in the aliens to move from the right side
//to the left based on bool flags. When an alien reaches the left, the score
//it counts for shows up
//
//getAction determines what keys the player pressed and what to do. if option
//is 0 the game starts when the spacebar is pressed. If it is 1, the game closes
//There is a small delay on how many actions can be detected. Currently it is a
//50 frame pause between actions to prevent the system from detecting too many
//actions at once
//
//makeRects sets all the rectangle x and y's for the text and alien images
//
//drawMenu draws the menu based on what is supposed to show up or not depeding
//on bool values
//******************************************************************************
void mainMenu(Surface & surface, Event & event, bool * quitGame);

void showAlien(Rect & aquaRect, Rect & purpleRect, Rect & redRect,
               Rect & flagRect, const int alienDx, int & sendAlien,
               bool & aquaScore, bool & purpleScore, bool & redScore,
               bool & flagScore);

void getAction(const KeyPressed & keypressed, int & option,
               int & changeDelay, bool * quitGame, bool & startGame);

void makeRects(Rect & rect1, Rect & rect2, Rect & playRect, Rect & quitRect,
               Rect & pressRect, Rect & aquaRect, Rect & purpleRect,
               Rect & redRect, Rect & flagRect, Rect & asRect, Rect & psRect,
               Rect & rsRect, Rect & fsRect, Rect & nameRect);

void drawMenu(const bool aquaScore, const bool purpleScore, const bool redScore,
              const bool flagScore, const Image & myName, const Rect & nameRect,
              const Image & aScore, const Rect & asRect,
              const Image & pScore, const Rect & psRect,
              const Image & rScore, const Rect & rsRect,
              const Image & fScore, const Rect & fsRect,
              const Image & line1, const Rect & rect1,
              const Image & line2, const Rect & rect2,
              const int option,
              const Image & playOption, const Rect & playRect,
              const Image & quitOption, const Rect & quitRect,
              const int blinkDelay,
              const Image & pressSpace, const Rect & pressRect,
              const Image & aqua, const Rect & aquaRect,
              const Image & purple, const Rect & purpleRect,
              const Image & red, const Rect & redRect,
              const Image & flag, const Rect & flagRect,
              Surface & surface, Font & font2, int & titleFade, Font & font);
#endif
