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
#include "MainMenu.h"

void mainMenu(Surface & surface, Event & event, bool * quitGame)
{
    Music music("sounds/StarSpangledBanner.wav");
    music.play();

    //**************************************************************************
    //Title Card
    //**************************************************************************
    Font font("fonts/MarsAttacks.ttf", 150);
    Image line1(font.render("ATTACK OF", RED));
    Image line2(font.render("THE REDS", RED)); 
    Rect rect1 = line1.getRect();
    Rect rect2 = line2.getRect();
    
    //**************************************************************************
    //Play and Quit Buttons
    //**************************************************************************
    Font font2("fonts/Astron.ttf", 40);
    Image playOption(font2.render("[Play]", RED));
    Image quitOption(font2.render("[Quit]", RED));
    Rect playRect = playOption.getRect();
    Rect quitRect = quitOption.getRect();

    
    //**************************************************************************
    //Tells Player to Press Space to Play
    //**************************************************************************
    Font font3("fonts/FreeMonoBold.ttf", 30);
    Image pressSpace(font3.render("Press SPACE!", RED));
    Rect pressRect = pressSpace.getRect();

    
    //**************************************************************************
    //Aliens that come in from the right to the left edge.  The scores are
    //for killing when they are in the fleet or when attacking the player
    //**************************************************************************
    Font font4("fonts/FreeMonoBold.ttf", 15);
    Image aqua("images/galaxian/GalaxianAquaAlien.gif");
    Rect aquaRect = aqua.getRect();

    Image aScore(font4.render("= 30......60", BLUE));
    Rect asRect = aScore.getRect();
    
    Image purple("images/galaxian/GalaxianPurpleAlien.gif");
    Rect purpleRect = purple.getRect();

    Image pScore(font4.render("= 40......80", 255, 0, 255));
    Rect psRect = pScore.getRect();
    
    Image red("images/galaxian/GalaxianRedAlien.gif");
    Rect redRect = red.getRect();

    Image rScore(font4.render("= 50......100", RED));
    Rect rsRect = rScore.getRect();
    
    Image flag("images/galaxian/GalaxianFlagship.gif");
    Rect flagRect = flag.getRect();

    Image fScore(font4.render("= 60......150", YELLOW));
    Rect fsRect = fScore.getRect();


    //**************************************************************************
    //My name
    //**************************************************************************
    Image myName(font4.render("Created By: Caleb Fischer", YELLOW));
    Rect nameRect = myName.getRect();
    
    //**************************************************************************
    //Sets x and y of all the rectangles
    //**************************************************************************
    makeRects(rect1, rect2, playRect, quitRect, pressRect, aquaRect,
              purpleRect, redRect, flagRect, asRect, psRect, rsRect, fsRect,
        nameRect);
    
    int alienDx = -5;
    int sendAlien = 0;
    
    bool aquaScore = 0;
    bool purpleScore = 0;
    bool redScore = 0;
    bool flagScore = 0;
    int blinkDelay = 200;
    
    int changeDelay = 50;
    int option = 0;

    bool startGame = 0;
    int titleFade = 0;
    
    //**************************************************************************
    //The Main Menu loop
    //
    //quitGame is a pointer that will close the window. startGame is a bool that
    //will break the Menu loop to allow the game to start.
    //
    //blinkDelay makes the Press Space string blink
    //
    //changeDelay prevents the game from reading inputs too fast. It is set to
    //read inputs every 50 frames.
    //**************************************************************************
    while (1)
    {
        KeyPressed keypressed = get_keypressed();
        closeGame(event, quitGame);
        if (*quitGame) break;
        
        if (blinkDelay > 0)
        {
            --blinkDelay;    
        }
        else if (blinkDelay == 0)
        {
            blinkDelay = 200;
        }
        
        showAlien(aquaRect, purpleRect, redRect, flagRect, alienDx, sendAlien,
                  aquaScore, purpleScore, redScore, flagScore);

        getAction(keypressed, option, changeDelay, quitGame, startGame);
        if (*quitGame || startGame) break;
        
        if (changeDelay > 0)
        {
            --changeDelay;
        }

        drawScreen(surface);
        drawMenu(aquaScore, purpleScore, redScore, flagScore, myName, nameRect,
                 aScore, asRect, pScore, psRect, rScore, rsRect, fScore, fsRect,
                 line1, rect1, line2, rect2, option, playOption, playRect,
                 quitOption, quitRect, blinkDelay, pressSpace, pressRect, aqua,
                 aquaRect, purple, purpleRect, red, redRect, flag, flagRect,
                 surface, font2, titleFade, font);
        runScreen(surface);
    }
}


void showAlien(Rect & aquaRect, Rect & purpleRect, Rect & redRect,
               Rect & flagRect, const int alienDx, int & sendAlien,
               bool & aquaScore, bool & purpleScore, bool & redScore,
               bool & flagScore)
{
    switch(sendAlien)
    {
        case 0:
            if (aquaRect.x > -alienDx * 2)
            {
                aquaRect.x += alienDx;
            }
            else if (aquaRect.x <= -alienDx * 2)
            {
                ++sendAlien;
                aquaScore = 1;
            }
            break;
        case 1:
            if (purpleRect.x > -alienDx * 2)
            {
                purpleRect.x += alienDx;
            }
            else
            {
                ++sendAlien;
                purpleScore = 1;
            }
            break;
        case 2:
            if (redRect.x > -alienDx * 2)
            {
                redRect.x += alienDx;
            }
            else
            {
                ++sendAlien;
                redScore = 1;
            }
            break;
        case 3:
            if (flagRect.x > -alienDx * 2)
            {
                flagRect.x += alienDx;
            }
            else
            {
                flagScore = 1;
            }
            break;
    }
}


void getAction(const KeyPressed & keypressed, int & option,
               int & changeDelay, bool * quitGame, bool & startGame)
{
    if (keypressed[SPACE] && option == 0 && changeDelay == 0)
    {
        startGame = 1;
    }
    else if (keypressed[SPACE] && option == 1 && changeDelay == 0)
    {
        *quitGame = 1;
    }
    else if ((keypressed[DOWNARROW] || keypressed[UPARROW]) && option == 0 && changeDelay == 0)
    {
        changeDelay = 20;
        option = 1;
    }
    else if ((keypressed[DOWNARROW] || keypressed[UPARROW]) && option == 1 && changeDelay == 0)
    {
        changeDelay = 20;
        option = 0;
    }
}


void makeRects(Rect & rect1, Rect & rect2, Rect & playRect, Rect & quitRect,
               Rect & pressRect, Rect & aquaRect, Rect & purpleRect,
               Rect & redRect, Rect & flagRect, Rect & asRect, Rect & psRect,
               Rect & rsRect, Rect & fsRect, Rect & nameRect)
{
    rect1.x = W / 2 - rect1.w / 2;
    rect1.y = H / 2 - rect1.h;
    rect2.x = W / 2 - rect2.w / 2;
    rect2.y = H / 2 - rect2.h + rect1.h;

    playRect.x = W / 2 - playRect.w / 2;
    playRect.y = rect2.y + playRect.h + 30;
    quitRect.x = W / 2 - quitRect.w / 2;
    quitRect.y = playRect.y + quitRect.h;

    pressRect.x = W / 2 - pressRect.w / 2;
    pressRect.y = H - pressRect.h * 2;
    
    aquaRect.x = W;
    aquaRect.y = 0;
    
    asRect.x = 0 + aquaRect.w * 2;
    asRect.y = aquaRect.y;

    purpleRect.x = W;
    purpleRect.y = aquaRect.y + purpleRect.h * 2;

    psRect.x = 0 + purpleRect.w * 2;
    psRect.y = purpleRect.y;

    redRect.x = W;
    redRect.y = purpleRect.y + redRect.h * 2;

    rsRect.x = 0 + redRect.w * 2;
    rsRect.y = redRect.y;

    flagRect.x = W;
    flagRect.y = redRect.y + flagRect.h * 2;

    fsRect.x = 0 + flagRect.w * 2;
    fsRect.y = flagRect.y;

    nameRect.x = 5;
    nameRect.y = H - (nameRect.h + 5);
}


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
              Surface & surface, Font & font2, int & titleFade, Font & font)
{
    if (aquaScore) surface.put_image(aScore, asRect);
        if (purpleScore) surface.put_image(pScore, psRect);
        if (redScore) surface.put_image(rScore, rsRect);
        if (flagScore) surface.put_image(fScore, fsRect);

        if (titleFade < 255)
        {
            ++titleFade;
            Image line1(font.render("ATTACK OF", titleFade, 0, 0));
            Image line2(font.render("THE REDS", titleFade, 0, 0)); 
            surface.put_image(line1, rect1);
            surface.put_image(line2, rect2);
        }
        else if (titleFade == 255)
        {
            Image line1(font.render("ATTACK OF", RED));
            Image line2(font.render("THE REDS", RED)); 
            surface.put_image(line1, rect1);
            surface.put_image(line2, rect2);
        }
        
        if (option == 0)
        {
            Image playOption(font2.render("[Play]", ORANGE));
            surface.put_image(playOption, playRect);
            surface.put_image(quitOption, quitRect);
        }
        else if (option == 1)
        {
            Image quitOption(font2.render("[Quit]", ORANGE));
            surface.put_image(playOption, playRect);
            surface.put_image(quitOption, quitRect);
        }
        
        if (blinkDelay > 100)
        {
            surface.put_image(pressSpace, pressRect);
        }

        surface.put_image(aqua, aquaRect);
        surface.put_image(purple, purpleRect);
        surface.put_image(red, redRect);
        surface.put_image(flag, flagRect);
        surface.put_image(myName, nameRect);
}
