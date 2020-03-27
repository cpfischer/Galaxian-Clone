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
#include <vector>

#include "Includes.h"
#include "Constants.h"
#include "compgeom.h"
#include "Surface.h"
#include "Event.h"
#include "AquaAlien.h"
#include "PurpleAlien.h"
#include "Player.h"
#include "PlayerLaser.h"
#include "StarField.h"
#include "Fleet.h"
#include "AlienLaser.h"
#include "RedAlien.h"
#include "FlagShip.h"
#include "Explosion.h"
#include "Build.h"
#include "PLives.h"
#include "GameOver.h"
#include "MainMenu.h"
#include "GameLoop.h"


int main(int argc, char* argv[])
{
    Surface surface(W, H);
    Event event;
    bool isQuit = 0;
    bool * quitGame = &isQuit;
    srand((unsigned int) time(NULL));
    
    while(1)
    {
        mainMenu(surface, event, quitGame);
        if (*quitGame) break;
        gameLoop(surface, event, quitGame);
        if (*quitGame) break;
        gameOver(surface, event, quitGame);
        if (*quitGame) break;
    }
    
    return 0;
}
