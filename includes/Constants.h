#ifndef CONSTANTS_H
#define CONSTANTS_H

// Constants for whole surface
const int W = 550;
const int H = 650;

// Constants for player ship
const int PLAYERLASERS = 3;
const int NUMLIVES = 3;
const int PLAYERSPEED = 4;
const int PLASERSPEED = 6;
const int ALIENSPEED = 9;
//Alien Laser constants
const int FIREY = H / 3;
const int ALASERSPEED = 6;
//Spacing for aliens
const int FLAGSTART1 = 160;
const int FLAGSTART2 =  280;
const int PURPSTART = 27;
const int REDSTART = PURPSTART * 2 - 9;
const int SPACING = 40;
const int COLSPACE = 34;
// Constants for aqua aliens
const int NUMAQUA = 10;
const int AQUAROWS = 3;
const int AQUASCORE = 30;
//Constants for purple aliens
const int NUMPURP = 8;
const int PURPSCORE = 40;
//Constants for red aliens
const int NUMRED = 6;
const int REDSCORE = 50;
//Constants for flaghships
//Flagship attack score = 150, the rest are double
const int NUMFLAG = 2;
const int FLAGSCORE = 60;
// Constants for stars
const int NUM_STARS = 50;
#endif

