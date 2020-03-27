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
#include "GameOver.h"

void gameOver(Surface & surface, Event & event, bool * quitGame)
{
    Music music("sounds/USSR.wav");
    music.play();
    Font font("fonts/MarsAttacks.ttf", 150);
    Image line1(font.render("Game Over", RED));
    Rect rect1 = line1.getRect();

    Font font2("fonts/FreeMonoBold.ttf", 15);
    std::ifstream getScores("hs.txt", std::ios::in);
    int score1, score2, score3;
    getScores >> score1 >> score2 >> score3;
    char printScore1[20];
    char printScore2[20];
    char printScore3[20];
    sprintf(printScore1, "%d", score1);
    sprintf(printScore2, "%d", score2);
    sprintf(printScore3, "%d", score3);
    Image hs1(font2.render(printScore1, RED));
    Image hs2(font2.render(printScore2, WHITE));
    Image hs3(font2.render(printScore3, BLUE));
    Image highScores(font2.render("High Scores", 255, 255, 0));
    Rect hs1Rect = hs1.getRect();
    Rect hs2Rect = hs2.getRect();
    Rect hs3Rect = hs3.getRect();
    Rect highScoresRect = highScores.getRect();
    
    Font font3("fonts/FreeMonoBold.ttf", 30);
    Image pressSpace(font3.render("Press SPACE to continue", RED));
    Rect pressRect = pressSpace.getRect();

    makeRects(rect1, pressRect, hs1Rect, hs2Rect, hs3Rect, highScoresRect);
    
    int changeDelay = 300;
    while (1)
    {
        KeyPressed keypressed = get_keypressed();
        closeGame(event, quitGame);
        if (*quitGame) break;
        
        if (keypressed[SPACE] && changeDelay == 0)
        {
            break;
        }
        
        if (changeDelay > 0)
        {
            --changeDelay;
        }
        
        drawScreen(surface);
        drawGameOver(line1, rect1, pressSpace, pressRect, highScores,
                     highScoresRect, hs1, hs1Rect, hs2,
                     hs2Rect, hs3, hs3Rect, surface, changeDelay);
        runScreen(surface);
    }
}


void drawGameOver(const Image & line1, const Rect & rect1,
                  const Image & pressSpace, const Rect & pressRect,
                  const Image & highScores, const Rect & highScoresRect,
                  const Image & hs1, const Rect & hs1Rect,
                  const Image & hs2, const Rect & hs2Rect,
                  const Image & hs3, const Rect & hs3Rect,
                  Surface & surface, int & changeDelay)
{
    surface.put_image(line1, rect1);
    surface.put_image(highScores, highScoresRect);
    surface.put_image(hs1, hs1Rect);
    surface.put_image(hs2, hs2Rect);
    surface.put_image(hs3, hs3Rect);
    
    if (changeDelay == 0)
    {
        surface.put_image(pressSpace, pressRect);
    }
}


void makeRects(Rect & rect1, Rect & pressRect, Rect & hs1Rect, Rect & hs2Rect,
               Rect & hs3Rect, Rect & highScoresRect)
{
    rect1.x = W / 2 - rect1.w / 2;
    rect1.y = H / 2 - rect1.h;
    
    pressRect.x = W / 2 - (pressRect.w / 2);
    pressRect.y = H - (pressRect.h * 2);

    highScoresRect.x = W / 2 - (highScoresRect.w / 2);    
    highScoresRect.y = rect1.y + highScoresRect.h * 5;

    hs1Rect.x = W / 2 - (hs1Rect.w / 2);
    hs1Rect.y = highScoresRect.y + hs1Rect.h;

    hs2Rect.x = W / 2 - (hs2Rect.w / 2);
    hs2Rect.y = hs1Rect.y + hs2Rect.h;

    hs3Rect.x = W / 2 - (hs3Rect.w / 2);
    hs3Rect.y = hs2Rect.y + hs3Rect.h;
}
