#ifndef GAMEOVER_H
#define GAMEOVER_H
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
#include <fstream>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "Screen.h"
//******************************************************************************
//This is the header file for the Game Over screen
//
//gameOver is the game over screen loop
//
//drawGameOver draws the "Game Over" text as well as "Press Space to Continue"
//text once the changeDelay timer runs out
//
//makeRects sets the x and y of the text displayed
//******************************************************************************
void gameOver(Surface & surface, Event & event, bool * quitGame);

void drawGameOver(const Image & line1, const Rect & rect1,
                  const Image & pressSpace, const Rect & pressRect,
                  const Image & highScores, const Rect & highScoresRect,
                  const Image & hs1, const Rect & hs1Rect,
                  const Image & hs2, const Rect & hs2Rect,
                  const Image & hs3, const Rect & hs3Rect,
                  Surface & surface, int & changeDelay);
    
void makeRects(Rect & rect1, Rect & pressRect, Rect & hs1Rect, Rect & hs2Rect,
               Rect & hs3Rect, Rect & highScoresRect);
#endif

