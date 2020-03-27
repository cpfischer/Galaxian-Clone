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
#include "GameLoop.h"
#include "Screen.h"

void gameLoop(Surface & surface, Event & event, bool * quitGame)
{
    Music music("sounds/AmericaFYeah.wav");
    music.play();
    Sound playerFire("sounds/laser.wav");
    Sound alienFire("sounds/laser.wav");

    Font font("fonts/MarsAttacks.ttf", 75);
    Image warning(font.render("Attention: Next Wave Incoming!", RED));
    Rect warRect = warning.getRect();
    warRect.x = W / 2 - warRect.w / 2;
    warRect.y = H / 2 - warRect.h;
    
    Player player;
    std::vector<PLives> playerLives;
     
    std::vector<AquaAlien> aquaAlienArrayR1;
    std::vector<AquaAlien> aquaAlienArrayR2;
    std::vector<AquaAlien> aquaAlienArrayR3;
    std::vector<PurpleAlien> purpleAlienArray;
    std::vector<RedAlien> redAlienArray;
    std::vector<FlagShip> flagShipArray;
    
    Fleet fleet;
    
    StarField starField;
    std::vector<PlayerLaser> playerLaserArray;

    std::vector<AlienLaser> alienLaserArrayAR1;
    std::vector<AlienLaser> alienLaserArrayAR2;
    std::vector<AlienLaser> alienLaserArrayAR3;
    
    std::vector<AlienLaser> alienLaserArrayPurp;
    std::vector<AlienLaser> alienLaserArrayRed;
    std::vector<AlienLaser> alienLaserArrayFlag;

    std::vector<Explosion> explosionArrayAR1;
    std::vector<Explosion> explosionArrayAR2;
    std::vector<Explosion> explosionArrayAR3;
    std::vector<Explosion> explosionArrayPurp;
    std::vector<Explosion> explosionArrayRed;
    std::vector<Explosion> explosionArrayFlag;

    buildPlayerObjs(playerLives, playerLaserArray);
    
    buildAliens(aquaAlienArrayR1, aquaAlienArrayR2, aquaAlienArrayR3,
                purpleAlienArray, redAlienArray, flagShipArray);
    buildAlienLasers(alienLaserArrayAR1, alienLaserArrayAR2, alienLaserArrayAR2,
    alienLaserArrayPurp, alienLaserArrayRed, alienLaserArrayFlag);

    buildExplosions(explosionArrayAR1, explosionArrayAR2, explosionArrayAR3,
                    explosionArrayPurp, explosionArrayRed, explosionArrayFlag);
    
    buildAlienLaser(alienLaserArrayAR3, NUMAQUA);
    buildAlienLaser(alienLaserArrayPurp, NUMPURP);
    
    Explosion * playerExplosion = new Explosion;
    int * score = new int;
    
    bool testLaser = 1;
    int laserDelay = 20;
    int respawnTimer = 50;
    *score = 0;
    
    fleet.startPlacement(aquaAlienArrayR1, aquaAlienArrayR2,
                         aquaAlienArrayR3, purpleAlienArray,
                         redAlienArray, flagShipArray);

    std::vector<int> hs;
    buildHighScore(hs);
    
    bool haveBonus = 1; 
    while (player.lives() > 0)
    {
        //Scoring
        int sLen = 0;
        int tempScore = *score;
        while (tempScore > 0)
        {
            tempScore /= 10;
            ++sLen;
        }
        --sLen;
        Font scoreFont("fonts/FreeMonoBold.ttf", 15);
        char printScore[20];
        sprintf(printScore, "Score: %d", *score);
        Image showScore(scoreFont.render(printScore, WHITE));
        Rect scoreRect = showScore.getRect();
        scoreRect.x = 2;
        scoreRect.y = 0;

        //"High Score" Text
        Image hsText(scoreFont.render("High Score", RED));
        Rect hsRect = hsText.getRect();
        hsRect.x = (W / 2) - (hsRect.w / 2);
        hsRect.y = 0;

        //Actual High Score
        char printHigh[20];
        if ((*score) >= hs[0])
        {
            sprintf(printHigh, "%d", *score);
        }
        else
        {
            sprintf(printHigh, "%d", hs[0]);
        }

        //Bonus life!
        if (((*score) >= 5000) && haveBonus)
        {
            player.bonusLife();
            haveBonus = 0;
        }
        
        //Deals with invincible after respawn
        if (player.state() == 3)
        {
            player.invincible();
        }
        
        Image showHigh(scoreFont.render(printHigh, WHITE));
        Rect highRect = showHigh.getRect();
        highRect.x = (W / 2) - (highRect.w / 2);
        highRect.y = hsRect.h /2 + 2;
        
        KeyPressed keypressed = get_keypressed();
        closeGame(event, quitGame);
        if (*quitGame) break;
        
        if (keypressed[SPACE])
        {
            if (laserDelay == 0 && !(fleet.isRespawning()))
            {
                for (int i = 0; i < PLAYERLASERS; ++i)
                {
                    if (!(playerLaserArray[i].alive()))
                    {
                        playerFire.play();
                        playerLaserArray[i].startLaser(player);
                        laserDelay = 40;
                        break;
                    }
                }
            }
        }
        
        if (player.getX() > 0 && keypressed[LEFTARROW])
        {
            player.moveShipLeft();
        }
        else if (player.getX() < W - player.getW() && keypressed[RIGHTARROW])
        {
            player.moveShipRight();
        }
        else
        {
            player.stopShip();
        }

        if (laserDelay > 0)
        {
            --laserDelay;
        }

        for (int i = 0; i < PLAYERLASERS; ++i)
        {
            playerLaserArray[i].moveLaser();
        }
        starField.moveStars();
        fleet.changeDirection(aquaAlienArrayR1, aquaAlienArrayR2,
                              aquaAlienArrayR3, purpleAlienArray,
                              redAlienArray, flagShipArray);
        
        fleet.alienAttack(aquaAlienArrayR1, aquaAlienArrayR2,
                          aquaAlienArrayR3, purpleAlienArray,
                          redAlienArray, flagShipArray);

        fleet.move(aquaAlienArrayR1, aquaAlienArrayR2,
                   aquaAlienArrayR3, purpleAlienArray,
                   redAlienArray, flagShipArray, alienLaserArrayAR1,
                   alienLaserArrayAR2, alienLaserArrayAR3,
                   alienLaserArrayPurp, alienLaserArrayRed,
                   alienLaserArrayFlag, alienFire);
        for (int i = 0; i < NUMAQUA; ++i)
        {
            if (i < NUMAQUA)
            {
                alienLaserArrayAR1[i].checkCollision(player);
                alienLaserArrayAR2[i].checkCollision(player);
                alienLaserArrayAR3[i].checkCollision(player);
            }
            if (i < NUMPURP)
            {
                alienLaserArrayPurp[i].checkCollision(player);
            }
            if (i < NUMRED)
            {
                alienLaserArrayRed[i].checkCollision(player);
            }
            if (i < NUMFLAG)
            {
                alienLaserArrayFlag[i].checkCollision(player);
            }

            if (i < PLAYERLASERS)
            {
                playerLaserArray[i].checkCollision(aquaAlienArrayR1,
                                                   aquaAlienArrayR2,
                                                   aquaAlienArrayR3,
                                                   purpleAlienArray,
                                                   redAlienArray,
                                                   flagShipArray,
                                                   score);
            }
        }
        fleet.checkCollision(player,
                             aquaAlienArrayR1, aquaAlienArrayR2,
                             aquaAlienArrayR3, purpleAlienArray,
                             redAlienArray, flagShipArray, score);
        fleet.reset( aquaAlienArrayR1, aquaAlienArrayR2,
                     aquaAlienArrayR3, purpleAlienArray,
                     redAlienArray, flagShipArray);

        char printLevel[10];
        sprintf(printLevel, "Stage: %d", fleet.level());
        Image showLevel(scoreFont.render(printLevel, WHITE));
        Rect levelRect = showLevel.getRect();
        levelRect.x = W - levelRect.w;
        levelRect.y = H - levelRect.h;
        
        drawScreen(surface);
        drawGame(player, playerExplosion, starField, aquaAlienArrayR1,
                 aquaAlienArrayR2, aquaAlienArrayR3, purpleAlienArray,
                 redAlienArray, flagShipArray, playerLaserArray,
                 alienLaserArrayAR1, alienLaserArrayAR2, alienLaserArrayAR3,
                 alienLaserArrayPurp, alienLaserArrayRed, alienLaserArrayFlag,
                 explosionArrayAR1, explosionArrayAR2, explosionArrayAR3,
                 explosionArrayPurp, explosionArrayRed, explosionArrayFlag,
                 surface);
        //PRINT LEVEL AND SCORE
        surface.put_image(showScore, scoreRect);
        surface.put_image(showLevel, levelRect);
        surface.put_image(hsText, hsRect);
        surface.put_image(showHigh, highRect);
        
        if (fleet.isRespawning())
        {
            surface.put_image(warning, warRect);
        }
        
        for (int i = 0; i < player.lives() - 1; ++i)
        {
            playerLives[i].drawLives(surface);
        }

       
        
        if (player.state() != 0 && respawnTimer > 0)
        {
            --respawnTimer;
        }
        else if (player.state() == 2 && respawnTimer == 0)
        {
            respawnTimer = 50;
            player.respawn();
            player.drawShip(surface, *playerExplosion);
        }

        runScreen(surface);
        //endGameLoop
    }

    //HighScores on Game Over screen
    std::ifstream getScores("hs.txt", std::ios::in);
    int score1, score2, score3;
    getScores >> score1 >> score2 >> score3;
    bool canWrite = 1;
    for (int i = 0; i < 3; ++i)
    {   
        if ((*score) >= score1 && canWrite)
        {
            int oldScore;
            oldScore = score2;
            score2 = score1;
            score3 = oldScore;
            score1 = *score;
            canWrite = 0;
        }
        else if ((*score) >= score2 && canWrite)
        {
            score3 = score2;
            score2 = *score;
            canWrite = 0;
        }
        else if ((*score) >= score3 && canWrite)
        {
            score3 = *score;
            canWrite = 0;
        }
        std::ofstream writeScore("hs.txt", std::ios::out);
        writeScore << score1 << '\n' << score2 << '\n' << score3 << std::endl;
        
    }
    
    delete playerExplosion;
    delete score;
    return;
}


void drawGame(Player & player,
              Explosion * playerExplosion,
              StarField & starField,
              std::vector<AquaAlien> & aaR1,
              std::vector<AquaAlien> & aaR2,
              std::vector<AquaAlien> & aaR3,
              std::vector<PurpleAlien> & paa,
              std::vector<RedAlien> & raa,
              std::vector<FlagShip> & fsa,
              std::vector<PlayerLaser> & playerLaserArray,
              std::vector<AlienLaser> & alienLaserArrayAR1,
              std::vector<AlienLaser> & alienLaserArrayAR2,
              std::vector<AlienLaser> & alienLaserArrayAR3,
              std::vector<AlienLaser> & alienLaserArrayPurp,
              std::vector<AlienLaser> & alienLaserArrayRed,
              std::vector<AlienLaser> & alienLaserArrayFlag,
              std::vector<Explosion> & explosionArrayAR1,
              std::vector<Explosion> & explosionArrayAR2,
              std::vector<Explosion> & explosionArrayAR3,
              std::vector<Explosion> & explosionArrayPurp,
              std::vector<Explosion> & explosionArrayRed,
              std::vector<Explosion> & explosionArrayFlag,
              Surface & surface)
{
    starField.drawStars(surface);
    
    for (int i = 0; i < NUMAQUA; ++i)
    {
        if (i < PLAYERLASERS)
        {
            playerLaserArray[i].drawLaser(surface);
        }

        if (i < NUMAQUA)
        {
            aaR1[i].drawAlien(surface, explosionArrayAR1[i]);
            aaR2[i].drawAlien(surface, explosionArrayAR2[i]);
            aaR3[i].drawAlien(surface, explosionArrayAR3[i]);
            alienLaserArrayAR1[i].drawLaser(surface);
            alienLaserArrayAR2[i].drawLaser(surface);
            alienLaserArrayAR3[i].drawLaser(surface);
        }
        
        
        explosionArrayAR1[i].drawExplosion(surface);
        explosionArrayAR2[i].drawExplosion(surface);
        explosionArrayAR3[i].drawExplosion(surface);
            
        if (i < NUMPURP)
        {
            paa[i].drawAlien(surface, explosionArrayPurp[i]);
            alienLaserArrayPurp[i].drawLaser(surface);
            explosionArrayPurp[i].drawExplosion(surface);
        }
            
        if (i < NUMRED)
        {
            raa[i].drawAlien(surface, explosionArrayRed[i]);
            alienLaserArrayRed[i].drawLaser(surface);
            explosionArrayRed[i].drawExplosion(surface);
        }
            
        if (i < NUMFLAG)
        {
            fsa[i].drawAlien(surface, explosionArrayFlag[i]);
            alienLaserArrayFlag[i].drawLaser(surface);
            explosionArrayFlag[i].drawExplosion(surface);
        }
    }

    player.drawShip(surface, *playerExplosion);
    playerExplosion->drawExplosion(surface);
}
