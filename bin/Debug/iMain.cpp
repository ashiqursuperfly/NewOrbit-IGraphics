# include "iGraphics.h"
#include <time.h>
#include <mmsystem.h>
#include <windows.h>
#define true 1
#define false 0



//MACRO
#define BASE_SCORE 100
#define SCREEN_LEN 1000
#define SCREEN_WIDTH 800
#define MAX_ENEMY 18
#define MAX_EXPLOSION 10
#define DEBUG 1
#define SHIPLENTH 80
#define SHIPWIDTH 80
#define BULLET_SPEED 44
#define MAX_BULLET 25
#define BG_SPEED 1
#define BULLETX_ADJ 36
#define BULLETY_ADJ 70
#define ENEMY_LEN 60          //is actually 64 64 but slightly less consider kora better...
#define ENEMY_WIDTH 60
#define MAX_ITEMS 3
#define ITEM_LEN 60
#define ITEM_WIDTH 60
#define ITEM_SPEED 4
#define MENU 0
#define GAME 3
#define INSTRUCTION 1
#define HIGHSCORE 2
#define PAUSE 4
#define CREDITS 6
#define GAMEOVER 7
#define INTRO 8




//MACROS END

//structure declarations

struct explosionStruct
{
    int mode;
    int explosionX;
    int explosionY;
    int explosionIndex;
};

struct bulletStruct
{
    int mode;
    int bulletX;
    int bulletY;

};

struct background
{

    int bgX;
    int bgY;

};

struct itemStruct
{
    int mode;
    int itemX;
    int itemY;
    int maxupgrade;
};

struct highscoreStruct
{
    char name[50];
    int score;
    char highscorePrint[200];  //just used to store the score in character form so it can be printed. just score, not name.

};






//structure declarations end
//animation indexes BEGINNING


char introImage[30][100]={"Intro\\intro1.bmp","Intro\\intro2.bmp","Intro\\intro3.bmp","Intro\\intro4.bmp","Intro\\intro5.bmp","Intro\\intro6.bmp",
"Intro\\intro7.bmp","Intro\\intro8.bmp","Intro\\intro9.bmp","Intro\\intro10.bmp","Intro\\intro11.bmp","Intro\\intro12.bmp","Intro\\intro13.bmp","Intro\\intro14.bmp","Intro\\intro15.bmp","Intro\\intro16.bmp",
"Intro\\intro17.bmp","Intro\\intro18.bmp","Intro\\intro19.bmp","Intro\\intro20.bmp","Intro\\intro21.bmp",
"Intro\\intro22.bmp","Intro\\intro23.bmp","Intro\\intro24.bmp","Intro\\intro25.bmp","Intro\\intro26.bmp","Intro\\intro27.bmp",
"Intro\\intro28.bmp","Intro\\intro29.bmp"};





char enemySprite[9][100] = {"Enemy\\asteroid0.bmp","Enemy\\asteroid1.bmp","Enemy\\asteroid2.bmp","Enemy\\asteroid3.bmp","Enemy\\asteroid4.bmp","Enemy\\asteroid5.bmp",
                            "Enemy\\asteroid6.bmp","Enemy\\asteroid7.bmp","Enemy\\asteroid0.bmp"};

char explosionSprite[8][100] = {"explosions\\explosion0.bmp" , "explosions\\explosion1.bmp" , "explosions\\explosion2.bmp" , "explosions\\explosion3.bmp" ,
                                "explosions\\explosion4.bmp", "explosions\\explosion5.bmp" , "explosions\\explosion6.bmp", "explosions\\explosion6.bmp"
                               };


char bgImage[20][100] = {"Spacebackground\\space01.bmp", "Spacebackground\\space02.bmp", "Spacebackground\\space03.bmp", "Spacebackground\\space04.bmp",
                         "Spacebackground\\space05.bmp", "Spacebackground\\space06.bmp", "Spacebackground\\space07.bmp", "Spacebackground\\space08.bmp",
                         "Spacebackground\\space09.bmp", "Spacebackground\\space10.bmp", "Spacebackground\\space11.bmp", "Spacebackground\\space12.bmp"
                         ,"Spacebackground\\space13.bmp", "Spacebackground\\space14.bmp","Spacebackground\\space15.bmp","Spacebackground\\space16.bmp",
                         "Spacebackground\\space17.bmp","Spacebackground\\space18.bmp", "Spacebackground\\space19.bmp", "Spacebackground\\space20.bmp"
                        };

char itemSprite[4][100] = {"Items\\item0.bmp", "Items\\item1.bmp","Items\\item2.bmp"};  //item 0 is health, 1 is weapon, 2 is speed
//in sturct array: 0 health, 1 weapon, 2 speed.

//variable declaration part
int shipx = 450, shipy = 80, r = 20;
int health = 10;  //game over is toggled from here
long int score = 0;
char scorePrint[100];
int enemyTrack[5][MAX_ENEMY] = {0};  //row 0 is mode, row 1 is x, row 2 is y, row 3 is sprite idx, row 4 is sprite idx
int enemySpeed = 3;
struct explosionStruct explosion[10] = {0};
int enemySpawnTimer = 1500;  //in miliseconds
struct bulletStruct bullet[MAX_BULLET] = {0};
struct background bg[20] = {0};
int playMusic = true;
int level = 1;
char levelPrint[50];
int showLevel = 0;
int bgShiftSpeed = 50;
int levelDrawTimer = 0;
int shipSpeed = 15;
int gunMode = 1;
struct itemStruct items[MAX_ITEMS] = {0};   //struct is called items, but most denominations used throughout is "item".
int spawnTimerValue1, spawnTimerValue2, spawnTimerValue3;  //we have 3 separate spawn timers with separate spawn times. this stores their return
//for use in the pausetimer function
int gamestate = 8;  //0 is menu, 1 is instruction, 2 is highscore, 3 is game.
int spawnState = 1;  //should reflect the value of current spawntimer that's active.
int streak = 1;
int comboMultiplier = 1;
char comboPrint[50];
int comboToggle = 0;
int comboDrawTimer = 0;
struct highscoreStruct highscores[6] = {0};
struct highscoreStruct player ={0};
char namePrint[100];
char nameStack[100],  nameLen = 0;  //namestack 1 is temp preview, namestack 2 holds it at enter press

int scoresRead = 0;  //be very careful with this. it's declared global because scoreDraw will need it. Basically tells you how
                    //many highscore data were successfully read. That's all. Use as the end condition of for loop.
int highscoreFlag = 0;  //flag = 0 means data never read, flag 1 means data already in structure. -1 means failiure to read.







int explosionIndexTimerValue, bulletCollisionDetectorValue, increaseLevelValue, movementValue, createItemValue, shiftBgValue; //pause timer er jonno values.


















//end of variable declaration part

//function declaration part.
//iDraw();
void healthDraw(void);  //IDraw function that draws health bars and health number and health icon
void scoreDraw(void);  //Idraw function that shows Score
void resetEnemy(int enemyNumber);  //Cued from Idraw after enemy reaches its death mark. Sets the array index of that enemy to default value.
void createEnemy(void);  /*is a timer  dependent (not itself a timer function) function that gets called from main.
                                    After every certain interval it creates an enemy.
                                 a) The enemy is assigned an indexed in the enemy Track array. A loop determines the first vacant position.
                                 b) an x co-ordinate is randomly generated for the enemy to spawn from. then calls initialize enemy.
                                    ----------------------------------------------- */
void initializeEnemy(int enemyNumber,int enemyx, int spriteidx);  //called from CreateEnemy. Sets all the configurations of the enemy as instructed by
//createEnemy. turns mode to 1.
void enemyTimer(void);  //Actual timer that calls createEnemy. Does absolutely nothing else.
void resetExplosion(int explosionNumber);
void createExplosion(int explosionX,int explosionY);  /*-------------------------------------------------------------
                                                              Called from enemyDraw EnemyCollisiondetector right before resetting the mode of the destroyed enemy.
                                                              1) Finds first array position in explosion struct array thats empty and sets it to 1.
                                                              2) defines the co-ordinates of the explosion to the last position the
                                                              - enemy was in. These get stored in the explosionx and explosiony integers.
                                                              ---------------------------------------------- */

void explosionIndexTimer(void);  /*-------------------------------------------------------------
                                            1. Basically gets called at a certain frequncy that determines explosion sprite change rate.
                                            2. Increments explosionIndex which is just sprite array er index.
                                            3. After hitting final sprite, cues resetExplosion to set this explosion back to mode 0 (off)
                                                              ---------------------------------------------- */
void enemyDraw(void);/*Idraw function that ----------------------------------------------
                               1.Has the codes to draw every single enemy.
                               2. Starts drawing when mode is set to active.
                               3. Has a y axis incrementor that moves the enemies forward.
                               4. Has a mark check to tell when the enemy is suppose to be destroyed.
                               5. When the mark check is reached it  - a) Cues createExplosion to generate explosion sprite
                                                                       b) checks if it is to be just destroyed or also reduce health
                                                                       c) Finally calls resetEnemy to clear that specific enemy.
                                ------------------------------------------------------------------*/
void explosionDraw(void); /*-------------------------------------------------------------
                                            1. Has the draw codes for all the explosions. Does not do anything except draw the codes.
                                            2. Each draw has a mode condition checker, only draws if mode is on. index is continuously being shifted
                                            - by explosionIndexTimer.
                                                              ---------------------------------------------- */

void shipCollisionDetector(void);
void bulletCollisionDetector(void);     /* -------------------------------------------------------------
                                                    Detects collision between bullet and enemy and if confirmed then
                                                    - Increases score, resets enemy, resets bullet and cues explosion

                                                -------------------------------------------------------------*/


void createBullet(int bulletX,int bulletY);  /*-------------------------------------------------------------
                                                   no separate initialize bullet created. Create does both create and initialization.
                                                   -Called from Imouse with bullet x,y co-ordinates
                                                   -Finds first empty position in array and initializes bullet.

                                                ------------------------------------------------------------- */
void setBg(void);
void shiftBg(void);
void bgDraw(void);
void bulletDraw(void);                  /* -------------------------------------------------------------
                                                     Draw function that
                                                1.Draws the bullets if mode is 1.
                                                2. Increments y axis of bullet to move it forward
                                                3. Calls resetBullet if it hits top of screen
                                                -------------------------------------------------------------*/
void resetBullet (int bulletNumber);    /* -------------------------------------------------------------
                                                -Resets the bullet, sets mode to 0 and x co-ordinate to fucked up shit.
                                                -called from  1. bulletDraw if it hits screentop
                                                              2. bulletCollisiondetector, if confirmed collision with enemy
                                                -------------------------------------------------------------*/

void increaseLevel(void);
void movement(void);
void levelDraw(void);
void createItem(void); //called by timer function. Randomly generates values of item index and item y co-ordinate
void initializeItem(int itemIndex, int itemY);  //initializes item
void resetItem(int itemIndex);
void itemDraw(void);  //draws item. Movement is controlled by movement function. Later cleared when crosses screen from here by resetitem.
void initializeGame (void); //starts game from menu screen.
void menuDraw(void);
void instructionDraw(void);

void creditDraw(void);
void freezeGame (void);
void resumeGame(void) ;
void pauseDraw (void);
void comboDraw (void);
void gameoverDraw (void);
void highscoreDraw (void);
void highscoreRead (void); //reads high score and sorts it as well. highscores structure is empty if no data was read.
void resetGame (void); //used to set all significant values back to 0 at the end of the game.
void highscoreUpdate(void);


void PlayGameOverMusic(void);
void PlayGameMusic(void);











//end of function declaration part.



//user created functions (will later go into header file perhaps)
//Operational Functions


void PlayGameOverMusic(void){

PlaySound(0,0,0);
PlaySound("gameover.wav",NULL,SND_LOOP | SND_ASYNC);

}
void PlayGameMusic(void){
PlaySound(0,0,0);
PlaySound("bgmusic.wav",NULL,SND_LOOP | SND_ASYNC);

}

void enemyTimer(void)
{
    createEnemy();
}


void createEnemy(void)
{
    int i, enemyx, spriteidx;

    for(i = 0; i < MAX_ENEMY; i++)
    {

        if(enemyTrack[0][i] == 0)
        {
            enemyx = (rand() % 90) + 1;

            spriteidx = (rand() % 8);
            enemyx = enemyx * 10;
            initializeEnemy(i,enemyx,spriteidx);
            return;
        }
    }

    return;

}

void resetEnemy(int enemyNumber)
{
    enemyTrack[0][enemyNumber] = 0;
    enemyTrack[1][enemyNumber] = -100;   //potential source of bugs so be careful.
    enemyTrack[2][enemyNumber] = 800;
    enemyTrack[3][enemyNumber] = 0;
    enemyTrack[4][enemyNumber] = 0;


    return;

}

void initializeEnemy(int enemyNumber,int enemyx, int spriteidx)
{

    enemyTrack[0][enemyNumber] = 1;
    enemyTrack[1][enemyNumber] = enemyx;
    enemyTrack[2][enemyNumber] = 800;
    enemyTrack[3][enemyNumber] = 0;
    enemyTrack[4][enemyNumber] = spriteidx;

    return;

}

void resetExplosion(int explosionNumber)
{

    explosion[explosionNumber].mode = 0;
    explosion[explosionNumber].explosionX = 2000;
    explosion[explosionNumber].explosionY = 5000;
    explosion[explosionNumber].explosionIndex = 0;

}

void createExplosion(int explosionX,int explosionY)
{
    int i = 0;

    for (i = 0; i < MAX_EXPLOSION; i++)
    {
        if(explosion[i].mode == 0)
        {
            explosion[i].explosionX = explosionX;
            explosion[i].explosionY = explosionY;
            explosion[i].explosionIndex = 0;
            explosion[i].mode = 1;

            break;
        }

    }



    return;

}

void explosionIndexTimer(void)
{
    if (explosion[0].mode == 1)
    {
        explosion[0].explosionIndex++;


        if (explosion[0].explosionIndex > 6)
        {
            explosion[0].explosionIndex == 0;
            resetExplosion(0);

        }
    }

    if (explosion[1].mode == 1)
    {
        explosion[1].explosionIndex++;


        if (explosion[1].explosionIndex > 6)
        {
            explosion[1].explosionIndex == 0;
            resetExplosion(1);

        }
    }

    if (explosion[2].mode == 1)
    {
        explosion[2].explosionIndex++;


        if (explosion[2].explosionIndex > 6)
        {
            explosion[2].explosionIndex == 0;
            resetExplosion(2);

        }
    }

    if (explosion[3].mode == 1)
    {
        explosion[3].explosionIndex++;


        if (explosion[3].explosionIndex > 6)
        {
            explosion[3].explosionIndex == 0;
            resetExplosion(3);

        }
    }

    if (explosion[4].mode == 1)
    {
        explosion[4].explosionIndex++;


        if (explosion[4].explosionIndex > 6)
        {
            explosion[4].explosionIndex == 0;
            resetExplosion(4);

        }
    }

    if (explosion[5].mode == 1)
    {
        explosion[5].explosionIndex++;


        if (explosion[5].explosionIndex > 6)
        {
            explosion[5].explosionIndex == 0;
            resetExplosion(5);

        }
    }

    if (explosion[6].mode == 1)
    {
        explosion[6].explosionIndex++;


        if (explosion[6].explosionIndex > 6)
        {
            explosion[6].explosionIndex == 0;
            resetExplosion(6);

        }
    }

    if (explosion[7].mode == 1)
    {
        explosion[7].explosionIndex++;


        if (explosion[7].explosionIndex > 6)
        {
            explosion[7].explosionIndex == 0;
            resetExplosion(7);

        }
    }

    if (explosion[8].mode == 1)
    {
        explosion[8].explosionIndex++;


        if (explosion[8].explosionIndex > 6)
        {
            explosion[8].explosionIndex == 0;
            resetExplosion(8);

        }
    }

    if (explosion[9].mode == 1)
    {
        explosion[9].explosionIndex++;


        if (explosion[9].explosionIndex > 6)
        {
            explosion[9].explosionIndex == 0;
            resetExplosion(9);

        }
    }
    return;
}




void setBg()
{
    int sum=0;
    for(int i=0; i < 20; i++)
    {
        bg[i].bgX= 0;
        bg[i].bgY= sum;
        sum +=40;
    }
}


void shiftBg()
{
    int i;
    for(i=0; i<20; i++)
    {
        bg[i].bgY -= BG_SPEED ;


        if(bg[i].bgY <= 0)
        {
            bg[i].bgY= SCREEN_WIDTH;
        }

    }
}

void createBullet(int bulletX,int bulletY)
{
    int i;

    for(i = 0; i < MAX_BULLET; i++)
    {
        if(bullet[i].mode == 0)
        {
            break;
        }
    }

    bullet[i].mode = 1;
    bullet[i].bulletX = bulletX;
    bullet[i].bulletY = bulletY;




}

void resetBullet(int bulletNumber)
{

    bullet[bulletNumber].mode = 0;
    bullet[bulletNumber].bulletX = 2000;
    bullet[bulletNumber].bulletY = 2000;

}


void bulletCollisionDetector(void)
{
    int i, j;    //j is index for bullet, i is for enemy.


    for(j = 0; j < MAX_BULLET ; j++)
    {
        if(bullet[j].mode == 1)
        {
            for(i = 0; i < MAX_ENEMY; i++)
            {
                if(enemyTrack[0][i] == 1)
                {
                    if(  ( ( bullet[j].bulletX > enemyTrack[1][i] - 10 ) && ( bullet[j].bulletX < enemyTrack[1][i] + ENEMY_LEN)  )  && (  (bullet[j].bulletY > enemyTrack[2][i]) &&  (bullet[j].bulletY < enemyTrack[2][i] + ENEMY_WIDTH)  ) )
                    {
                        streak++;

                        if(streak % 10 == 0 && streak != 0)
                        {
                            comboToggle = 1;

                        }

                        comboMultiplier = (streak / 10) + 1;







                        score += (BASE_SCORE + (50 * level)) * comboMultiplier;
                        createExplosion(enemyTrack[1][i],enemyTrack[2][i]);  //must be done before resetting enemy
                        resetEnemy(i);
                        resetBullet(j);
                    }
                }
            }
        }
    }





//ship part
int shipidx;

    for (shipidx = 0; shipidx < MAX_ENEMY; shipidx++)
    {
        if (enemyTrack[0][shipidx] == 1)
        {
            if( ((enemyTrack[1][shipidx] > (shipx - 40)) && (enemyTrack[1][shipidx] < (shipx + SHIPLENTH))) && ( (enemyTrack[2][shipidx] > (shipy - 40)) && ((enemyTrack[2][shipidx] < (shipy + 80))) ) )
            {
                createExplosion(enemyTrack[1][shipidx],enemyTrack[2][shipidx]);
                health -= 1;
                streak = 1;
                resetEnemy(shipidx);
            }
        }

    }



    //part for itemcollisiondetection

    int index, check = 0;  //index is item index in this case

    for(index = 0; index < MAX_ITEMS; index++)
    {
        if(items[index].mode == 1)
        {
            check = 1;
            break;
        }
    }


    if (check == 1)
    {


        if(((items[index].itemX > (shipx - 60)) && (items[index].itemX < (shipx + SHIPLENTH))) && ( (items[index].itemY > (shipy - 60)) && ((items[index].itemY < (shipy + 80))) ))
        {
            if(index == 0)
            {
                health += 3;

                if (health > 10)
                    health = 10;


                resetItem(0);
            }

            if(index == 1)
            {
                gunMode++;

                if(gunMode == 3)
                {
                    items[1].maxupgrade = 1;
                }


                resetItem(1);

            }


            if(index == 2)
            {
                shipSpeed += 3;

                if(shipSpeed > 30)
                {
                    items[2].maxupgrade = 1;
                }


                resetItem(2);

            }





        }



    }



}







void increaseLevel(void)
{
    level++;

    if(level == 3)
    {
        iPauseTimer(spawnTimerValue1);
        iResumeTimer(spawnTimerValue2);
        spawnState = 2;
        //printf("Spawn timer 2 has been resumed, 1 has been paused");


    }

    if(level == 5)
    {
        iPauseTimer(spawnTimerValue2);
        iResumeTimer(spawnTimerValue3);
        spawnState = 3;
        //printf("Spawn timer 3 has been resumed, 2 has been paused");
        enemySpeed--;

    }




    enemySpeed++;



    showLevel = 1;





}


void movement(void)
{

    if(enemyTrack[0][0] == 1)
    {
        enemyTrack[2][0]-=enemySpeed;
    }


    if(enemyTrack[0][1] == 1)
    {
        enemyTrack[2][1]-=enemySpeed;
    }

    if(enemyTrack[0][2] == 1)
    {
        enemyTrack[2][2]-=enemySpeed;
    }

    if(enemyTrack[0][3] == 1)
    {
        enemyTrack[2][3]-=enemySpeed;
    }

    if(enemyTrack[0][4] == 1)
    {
        enemyTrack[2][4]-=enemySpeed;
    }

    if(enemyTrack[0][5] == 1)
    {
        enemyTrack[2][5]-=enemySpeed;
    }

    if(enemyTrack[0][6] == 1)
    {
        enemyTrack[2][6]-=enemySpeed;
    }

    if(enemyTrack[0][7] == 1)
    {
        enemyTrack[2][7]-=enemySpeed;
    }

    if(enemyTrack[0][8] == 1)
    {
        enemyTrack[2][8]-=enemySpeed;
    }

    if(enemyTrack[0][9] == 1)
    {
        enemyTrack[2][9]-=enemySpeed;
    }

    if(enemyTrack[0][10] == 1)
    {
        enemyTrack[2][10]-=enemySpeed;
    }

    if(enemyTrack[0][11] == 1)
    {
        enemyTrack[2][11]-=enemySpeed;
    }

    if(enemyTrack[0][12] == 1)
    {
        enemyTrack[2][12]-=enemySpeed;
    }

    if(enemyTrack[0][13] == 1)
    {
        enemyTrack[2][13]-=enemySpeed;
    }

    if(enemyTrack[0][14] == 1)
    {
        enemyTrack[2][14]-=enemySpeed;
    }

    if(enemyTrack[0][15] == 1)
    {
        enemyTrack[2][15]-=enemySpeed;
    }

    if(enemyTrack[0][16] == 1)
    {
        enemyTrack[2][16]-=enemySpeed;
    }

    if(enemyTrack[0][17] == 1)
    {
        enemyTrack[2][17]-=enemySpeed;
    }



    //bullet part

    if(bullet[0].mode == 1)
    {
        bullet[0].bulletY += BULLET_SPEED;

    }

    if(bullet[1].mode == 1)
    {
        bullet[1].bulletY += BULLET_SPEED;

    }

    if(bullet[2].mode == 1)
    {
        bullet[2].bulletY += BULLET_SPEED;

    }

    if(bullet[3].mode == 1)
    {
        bullet[3].bulletY += BULLET_SPEED;

    }

    if(bullet[4].mode == 1)
    {
        bullet[4].bulletY += BULLET_SPEED;

    }

    if(bullet[5].mode == 1)
    {
        bullet[5].bulletY += BULLET_SPEED;

    }

    if(bullet[6].mode == 1)
    {
        bullet[6].bulletY += BULLET_SPEED;

    }

    if(bullet[7].mode == 1)
    {
        bullet[7].bulletY += BULLET_SPEED;

    }

    if(bullet[8].mode == 1)
    {
        bullet[8].bulletY += BULLET_SPEED;

    }

    if(bullet[9].mode == 1)
    {
        bullet[9].bulletY += BULLET_SPEED;

    }

    if(bullet[10].mode == 1)
    {
        bullet[10].bulletY += BULLET_SPEED;

    }

    if(bullet[11].mode == 1)
    {
        bullet[11].bulletY += BULLET_SPEED;

    }

    if(bullet[12].mode == 1)
    {
        bullet[12].bulletY += BULLET_SPEED;

    }

    if(bullet[13].mode == 1)
    {
        bullet[13].bulletY += BULLET_SPEED;

    }

    if(bullet[14].mode == 1)
    {
        bullet[14].bulletY += BULLET_SPEED;

    }

    if(bullet[15].mode == 1)
    {
        bullet[15].bulletY += BULLET_SPEED;

    }

    if(bullet[16].mode == 1)
    {
        bullet[16].bulletY += BULLET_SPEED;

    }

    if(bullet[17].mode == 1)
    {
        bullet[17].bulletY += BULLET_SPEED;

    }

    if(bullet[18].mode == 1)
    {
        bullet[18].bulletY += BULLET_SPEED;

    }

    if(bullet[19].mode == 1)
    {
        bullet[19].bulletY += BULLET_SPEED;

    }

    if(bullet[20].mode == 1)
    {
        bullet[20].bulletY += BULLET_SPEED;

    }

    if(bullet[21].mode == 1)
    {
        bullet[21].bulletY += BULLET_SPEED;

    }

    if(bullet[22].mode == 1)
    {
        bullet[22].bulletY += BULLET_SPEED;

    }

    if(bullet[23].mode == 1)
    {
        bullet[23].bulletY += BULLET_SPEED;

    }

    if(bullet[24].mode == 1)
    {
        bullet[24].bulletY += BULLET_SPEED;

    }


    //item part---------------

    if(items[0].mode == 1)
    {

        items[0].itemX -= ITEM_SPEED;
    }

    if(items[1].mode == 1)
    {

        items[1].itemX -= ITEM_SPEED ;
    }

    if(items[2].mode == 1)
    {

        items[2].itemX -= ITEM_SPEED ;
    }



//this part is simply to check condition of health...





}


void createItem(void)
{
    int i, j, itemY;


    if(items[0].maxupgrade == 1 && items[1].maxupgrade == 1 && items[2].maxupgrade == 1  )
        return;

    itemY = rand() % 400;

    itemY += 200;

    i = rand() % 3;

    while(1)
    {
        if(i > 2)
            i = 0;

        if(items[i].maxupgrade == 0)
        {
            initializeItem(i,itemY);
            break;
        }

        i++;


    }


    return;

}

void initializeItem(int itemIndex, int item_Y)
{

    items[itemIndex].itemX = SCREEN_LEN;
    items[itemIndex].itemY = item_Y;
    items[itemIndex].mode = 1;


    return;


}


void resetItem(int itemIndex)
{

    items[itemIndex].itemX = SCREEN_LEN+500;
    items[itemIndex].itemY = 0;
    items[itemIndex].mode = 0;

    return;
}


void initializeGame (void)
{

    iResumeTimer(explosionIndexTimerValue );
    iResumeTimer(bulletCollisionDetectorValue );
    iResumeTimer( increaseLevelValue);
    iResumeTimer( movementValue);
    iResumeTimer( createItemValue);
    iResumeTimer(spawnTimerValue1);



}


void freezeGame(void)
{



    iPauseTimer(explosionIndexTimerValue );
    iPauseTimer(bulletCollisionDetectorValue );
    iPauseTimer( increaseLevelValue);
    iPauseTimer( movementValue);
    iPauseTimer( createItemValue);
    iPauseTimer(spawnTimerValue1);
    iPauseTimer(spawnTimerValue2);
    iPauseTimer(spawnTimerValue3);
    iPauseTimer(shiftBgValue);

}


void resumeGame(void)
{


    iResumeTimer(explosionIndexTimerValue );
    iResumeTimer(bulletCollisionDetectorValue );
    iResumeTimer( increaseLevelValue);
    iResumeTimer( movementValue);
    iResumeTimer( createItemValue);
      iResumeTimer(shiftBgValue);

      if(spawnState == 1)
      {
          iResumeTimer(spawnTimerValue1);
        //  printf("spawn timer 1 was resumed\n");
      }

      if( spawnState == 2)
      {
          iResumeTimer(spawnTimerValue2);
                    //printf("spawn timer 2 was resumed\n");

      }

        if( spawnState == 3)
      {
          iResumeTimer(spawnTimerValue3);
                              //printf("spawn timer 3 was resumed\n");

      }




}

void highscoreRead (void)
{


    int i, j;



    FILE *fp;

    fp = fopen("highscore.txt", "r");


    if(fp == NULL)
    {
        printf("ERROR: Was unable to read highscores\n");
        highscoreFlag = -1;
        return ;
    }

    for(i = 0;    fscanf(fp," %s %d", &highscores[i].name,&highscores[i].score) != EOF  && i < 5; i++);


  scoresRead = i;




  for(i = 0; i < scoresRead; i++)
  {
      for(j = 0; j < scoresRead - 1; j++)
      {

          if(highscores[j].score < highscores[j+1].score)
          {
              struct highscoreStruct temp = highscores[j];

               highscores[j] = highscores[j+1];

               highscores[j+1] = temp;

          }

      }
  }

 highscoreFlag = 1;


    for(j = 0; j < scoresRead; j++)
    {

       sprintf(highscores[j].highscorePrint , "%d", highscores[j].score );
    }







fclose(fp);



}


void highscoreUpdate(void)
{
   int i, j, maxPlayers;
 FILE *fp;

   highscoreRead();

   if(highscoreFlag != 1)
   {
               printf("ERROR: Was unable to update highscores\n");

       return;
   }

   if(highscoreFlag == 1)
   {

       strcpy(highscores[scoresRead].name, player.name);

       highscores[scoresRead].score = player.score;
      sprintf( highscores[scoresRead].highscorePrint , "%d" , player.score );
       scoresRead++;





         for(i = 0; i < scoresRead; i++)
  {
      for(j = 0; j < scoresRead - 1; j++)
      {

          if(highscores[j].score < highscores[j+1].score)
          {
              struct highscoreStruct temp = highscores[j];

               highscores[j] = highscores[j+1];

               highscores[j+1] = temp;

          }

      }
  }


  if(scoresRead == 6)
  {
      scoresRead = 5;

  }


  fp = fopen("highscore.txt", "w");

    if(fp == NULL)
    return;


  for(i = 0; i < scoresRead; i++)
  {
      fprintf(fp, "%s %d ",highscores[i].name , highscores[i].score);
  }






highscoreFlag = 0;
scoresRead = 0;
  fclose(fp);

   }

   return;



}




void resetGame(void)
{ int temp;

       iPauseTimer(explosionIndexTimerValue );
    iPauseTimer(bulletCollisionDetectorValue );
    iPauseTimer( increaseLevelValue);
    iPauseTimer( movementValue);
    iPauseTimer( createItemValue);
    iPauseTimer(spawnTimerValue1);
    iPauseTimer(spawnTimerValue2);
    iPauseTimer(spawnTimerValue3);

    score = 0;
    spawnState = 1;
    level = 1;
     highscoreFlag = 0;
     scoresRead = 0;
    streak = 1;
 health = 10;
     comboToggle = 0;
 comboDrawTimer = 0;
 shipx = 450 ;
  shipy = 80;
gunMode = 1;
shipSpeed = 15;

  for(temp = 0; temp < MAX_ENEMY; temp++)
  {
      enemyTrack[0][temp] = 0;
    enemyTrack[1][temp] = -100;
    enemyTrack[2][temp] = 800;
    enemyTrack[3][temp] = 0;
    enemyTrack[4][temp] = 0;
  }


  for(temp = 0; temp < MAX_ITEMS; temp++ )
  {

    items[temp].itemX = SCREEN_LEN+500;
    items[temp].itemY = 0;
    items[temp].mode = 0;
  }

  for(temp = 0; temp < MAX_BULLET; temp++)
  {

    bullet[temp].mode = 0;
    bullet[temp].bulletX = 2000;
    bullet[temp].bulletY = 2000;
  }


  for(temp = 0; temp < 10; temp++)
  {
      explosion[temp].explosionIndex = 0;
      explosion[temp].mode = 0;
      explosion[temp].explosionX = 0;
      explosion[temp].explosionY = 0;
  }



return ;


}





//End of Operational functions -----------------------------------------------------



//Draw Functions------------------------------------------------------------


void scoreDraw(void)
{
    iSetColor(255,255,255);

    sprintf(scorePrint,"%d",score);
    iText(940,780,scorePrint,GLUT_BITMAP_9_BY_15);

    iSetColor(0,0,0);

}

void healthDraw(void)
{

    if (health > 0)
        iShowBMP2(920,50,"heart.bmp",0);

    if (health > 1)
        iShowBMP2(935,50,"heart.bmp",0);

    if (health > 2)
        iShowBMP2(950,50,"heart.bmp",0);

    if (health > 3)
        iShowBMP2(965,50,"heart.bmp",0);

    if (health > 4)
        iShowBMP2(980,50,"heart.bmp",0);

    if (health > 5)
        iShowBMP2(920,30,"heart.bmp",0);

    if (health > 6)
        iShowBMP2(935,30,"heart.bmp",0);

    if (health > 7)
        iShowBMP2(950,30,"heart.bmp",0);

    if (health > 8)
        iShowBMP2(965,30,"heart.bmp",0);

    if (health > 9)
        iShowBMP2(980,30,"heart.bmp",0);




if(health == 0)
{

    gamestate = GAMEOVER;
    PlayGameOverMusic();

    player.score = score;


    resetGame();


}








    return;
}






void enemyDraw(void)
{
    if(enemyTrack[0][0] == 1)
    {
        iShowBMP2(enemyTrack[1][0],enemyTrack[2][0], enemySprite[enemyTrack[4][0]],0);



        if (enemyTrack[2][0] <= enemyTrack[3][0])
        {

            resetEnemy(0);

        }
        if (enemyTrack[2][0] <= 50)
        {
            health -= 1;
            createExplosion(enemyTrack[1][0],enemyTrack[2][0]);//must be done before reset.
            streak = 1;

            resetEnemy(0);
        }

    }


    if(enemyTrack[0][1] == 1)
    {
        iShowBMP2(enemyTrack[1][1],enemyTrack[2][1],enemySprite[enemyTrack[4][1]],0);



        if (enemyTrack[2][1] <= enemyTrack[3][1])
        {

            resetEnemy(1);

        }
        if (enemyTrack[2][1] <= 50)
        {
            health -= 1;
             streak = 1;

            createExplosion(enemyTrack[1][1],enemyTrack[2][1]);  //must be done before reset.

            resetEnemy(1);
        }

    }


    if(enemyTrack[0][2] == 1)
    {
        iShowBMP2(enemyTrack[1][2],enemyTrack[2][2],enemySprite[enemyTrack[4][2]],0);



        if (enemyTrack[2][2] <= enemyTrack[3][2])
        {

            resetEnemy(2);

        }
        if (enemyTrack[2][2] <= 50)
        {
            health -= 1;
             streak = 1;

            createExplosion(enemyTrack[1][2],enemyTrack[2][2]);  //must be done before reset.

            resetEnemy(2);
        }

    }

    if(enemyTrack[0][3] == 1)
    {
        iShowBMP2(enemyTrack[1][3],enemyTrack[2][3],enemySprite[enemyTrack[4][3]],0);



        if (enemyTrack[2][3] <= enemyTrack[3][3])
        {

            resetEnemy(3);

        }
        if (enemyTrack[2][3] <= 50)
        {
            health -= 1;
             streak = 1;

            createExplosion(enemyTrack[1][3],enemyTrack[2][3]);  //must be done before reset.

            resetEnemy(3);
        }

    }


    if(enemyTrack[0][4] == 1)
    {
        iShowBMP2(enemyTrack[1][4],enemyTrack[2][4],enemySprite[enemyTrack[4][4]],0);



        if (enemyTrack[2][4] <= enemyTrack[3][4])
        {

            resetEnemy(4);

        }
        if (enemyTrack[2][4] <= 50)
        {
            health -= 1;
             streak = 1;
            createExplosion(enemyTrack[1][4],enemyTrack[2][4]);  //must be done before reset.

            resetEnemy(4);
        }

    }


    if(enemyTrack[0][5] == 1)
    {
        iShowBMP2(enemyTrack[1][5],enemyTrack[2][5],enemySprite[enemyTrack[4][5]],0);



        if (enemyTrack[2][5] <= enemyTrack[3][5])
        {

            resetEnemy(5);

        }
        if (enemyTrack[2][5] <= 50)
        {
            health -= 1;
             streak = 1;
            createExplosion(enemyTrack[1][5],enemyTrack[2][5]);  //must be done before reset.

            resetEnemy(5);
        }

    }


    if(enemyTrack[0][6] == 1)
    {
        iShowBMP2(enemyTrack[1][6],enemyTrack[2][6],enemySprite[enemyTrack[4][6]],0);



        if (enemyTrack[2][6] <= enemyTrack[3][6])
        {

            resetEnemy(6);

        }
        if (enemyTrack[2][6] <= 50)
        {
            health -= 1;
             streak = 1;
            createExplosion(enemyTrack[1][6],enemyTrack[2][6]);  //must be done before reset.

            resetEnemy(6);
        }

    }


    if(enemyTrack[0][7] == 1)
    {
        iShowBMP2(enemyTrack[1][7],enemyTrack[2][7],enemySprite[enemyTrack[4][7]],0);



        if (enemyTrack[2][7] <= enemyTrack[3][7])
        {

            resetEnemy(7);

        }
        if (enemyTrack[2][7] <= 50)
        {
            health -= 1;
             streak = 1;
            createExplosion(enemyTrack[1][7],enemyTrack[2][7]);  //must be done before reset.
            resetEnemy(7);
        }

    }


    if(enemyTrack[0][8] == 1)
    {
        iShowBMP2(enemyTrack[1][8],enemyTrack[2][8],enemySprite[enemyTrack[4][8]],0);



        if (enemyTrack[2][8] <= enemyTrack[3][8])
        {

            resetEnemy(8);

        }
        if (enemyTrack[2][8] <= 50)
        {
            health -= 1;
             streak = 1;
            createExplosion(enemyTrack[1][8],enemyTrack[2][8]);  //must be done before reset.
            resetEnemy(8);
        }

    }


    if(enemyTrack[0][9] == 1)
    {
        iShowBMP2(enemyTrack[1][9],enemyTrack[2][9],enemySprite[enemyTrack[4][9]],0);



        if (enemyTrack[2][9] <= enemyTrack[3][9])
        {

            resetEnemy(9);

        }
        if (enemyTrack[2][9] <= 50)
        {
            health -= 1;
             streak = 1;
            createExplosion(enemyTrack[1][9],enemyTrack[2][9]);  //must be done before reset.
            resetEnemy(9);
        }

    }

    if(enemyTrack[0][10] == 1)
    {
        iShowBMP2(enemyTrack[1][10],enemyTrack[2][10],enemySprite[enemyTrack[4][10]],0);



        if (enemyTrack[2][10] <= enemyTrack[3][10])
        {

            resetEnemy(10);

        }
        if (enemyTrack[2][10] <= 50)
        {
            health -= 1;
             streak = 1;
            createExplosion(enemyTrack[1][10],enemyTrack[2][10]);  //must be done before reset.
            resetEnemy(10);
        }

    }

    if(enemyTrack[0][11] == 1)
    {
        iShowBMP2(enemyTrack[1][11],enemyTrack[2][11],enemySprite[enemyTrack[4][11]],0);



        if (enemyTrack[2][11] <= enemyTrack[3][11])
        {

            resetEnemy(11);

        }
        if (enemyTrack[2][11] <= 50)
        {
            health -= 1;
             streak = 1;
            createExplosion(enemyTrack[1][11],enemyTrack[2][11]);  //must be done before reset
            resetEnemy(11);
        }

    }

    if(enemyTrack[0][12] == 1)
    {
        iShowBMP2(enemyTrack[1][12],enemyTrack[2][12],enemySprite[enemyTrack[4][12]],0);



        if (enemyTrack[2][12] <= enemyTrack[3][12])
        {

            resetEnemy(12);

        }
        if (enemyTrack[2][12] <= 50)
        {
            health -= 1;
             streak = 1;
            createExplosion(enemyTrack[1][12],enemyTrack[2][12]);  //must be done before reset
            resetEnemy(12);
        }

    }

    if(enemyTrack[0][13] == 1)
    {
        iShowBMP2(enemyTrack[1][13],enemyTrack[2][13],enemySprite[enemyTrack[4][13]],0);



        if (enemyTrack[2][13] <= enemyTrack[3][13])
        {

            resetEnemy(13);

        }
        if (enemyTrack[2][13] <= 50)
        {
            health -= 1;
             streak = 1;
            createExplosion(enemyTrack[1][13],enemyTrack[2][13]);  //must be done before reset
            resetEnemy(13);
        }

    }

    if(enemyTrack[0][14] == 1)
    {
        iShowBMP2(enemyTrack[1][14],enemyTrack[2][14],enemySprite[enemyTrack[4][14]],0);



        if (enemyTrack[2][14] <= enemyTrack[3][14])
        {

            resetEnemy(14);

        }
        if (enemyTrack[2][14] <= 50)
        {
            health -= 1;
             streak = 1;
            createExplosion(enemyTrack[1][14],enemyTrack[2][14]);  //must be done before reset
            resetEnemy(14);
        }

    }

    if(enemyTrack[0][15] == 1)
    {
        iShowBMP2(enemyTrack[1][15],enemyTrack[2][15],enemySprite[enemyTrack[4][15]],0);



        if (enemyTrack[2][15] <= enemyTrack[3][15])
        {

            resetEnemy(15);

        }
        if (enemyTrack[2][15] <= 50)
        {
            health -= 1;
             streak = 1;
            createExplosion(enemyTrack[1][15],enemyTrack[2][15]);  //must be done before reset
            resetEnemy(15);
        }

    }

    if(enemyTrack[0][16] == 1)
    {
        iShowBMP2(enemyTrack[1][16],enemyTrack[2][16],enemySprite[enemyTrack[4][16]],0);



        if (enemyTrack[2][16] <= enemyTrack[3][16])
        {

            resetEnemy(16);

        }
        if (enemyTrack[2][16] <= 50)
        {
            health -= 1;
             streak = 1;
            createExplosion(enemyTrack[1][16],enemyTrack[2][16]);  //must be done before reset
            resetEnemy(16);
        }

    }

    if(enemyTrack[0][17] == 1)
    {
        iShowBMP2(enemyTrack[1][17],enemyTrack[2][17],enemySprite[enemyTrack[4][17]],0);



        if (enemyTrack[2][17] <= enemyTrack[3][17])
        {

            resetEnemy(17);

        }
        if (enemyTrack[2][17] <= 50)
        {
            health -= 1;
             streak = 1;
            createExplosion(enemyTrack[1][17],enemyTrack[2][17]);  //must be done before reset
            resetEnemy(17);
        }

    }


}


void explosionDraw(void)
{
    if (explosion[0].mode == 1)
    {
        iShowBMP2(explosion[0].explosionX, explosion[0].explosionY, explosionSprite[explosion[0].explosionIndex], 0);


    }

    if (explosion[1].mode == 1)
    {
        iShowBMP2(explosion[1].explosionX, explosion[1].explosionY, explosionSprite[explosion[1].explosionIndex], 0);


    }
    if (explosion[2].mode == 1)
    {
        iShowBMP2(explosion[2].explosionX, explosion[2].explosionY, explosionSprite[explosion[2].explosionIndex], 0);


    }
    if (explosion[3].mode == 1)
    {
        iShowBMP2(explosion[3].explosionX, explosion[3].explosionY, explosionSprite[explosion[3].explosionIndex], 0);


    }
    if (explosion[4].mode == 1)
    {
        iShowBMP2(explosion[4].explosionX, explosion[4].explosionY, explosionSprite[explosion[4].explosionIndex], 0);


    }
    if (explosion[5].mode == 1)
    {
        iShowBMP2(explosion[5].explosionX, explosion[5].explosionY, explosionSprite[explosion[5].explosionIndex], 0);


    }
    if (explosion[6].mode == 1)
    {
        iShowBMP2(explosion[6].explosionX, explosion[6].explosionY, explosionSprite[explosion[6].explosionIndex], 0);


    }
    if (explosion[7].mode == 1)
    {
        iShowBMP2(explosion[7].explosionX, explosion[7].explosionY, explosionSprite[explosion[7].explosionIndex], 0);


    }
    if (explosion[8].mode == 1)
    {
        iShowBMP2(explosion[8].explosionX, explosion[8].explosionY, explosionSprite[explosion[8].explosionIndex], 0);


    }
    if (explosion[9].mode == 1)
    {
        iShowBMP2(explosion[9].explosionX, explosion[9].explosionY, explosionSprite[explosion[9].explosionIndex], 0);


    }


}

void bgDraw(void)
{
    for(int i=0; i<20; i++)
    {
        iShowBMP(bg[i].bgX,bg[i].bgY,bgImage[i]);

    }
}


void bulletDraw(void)
{

    if(bullet[0].mode == 1)
    {

        iShowBMP2(bullet[0].bulletX,bullet[0].bulletY, "bulletlaser.bmp", 0);



        if (bullet[0].bulletY > SCREEN_WIDTH)
        {
            resetBullet(0);
        }


    }

    if(bullet[1].mode == 1)
    {

        iShowBMP2(bullet[1].bulletX,bullet[1].bulletY, "bulletlaser.bmp", 0);


        if (bullet[1].bulletY > SCREEN_WIDTH)
        {
            resetBullet(1);
        }


    }

    if(bullet[2].mode == 1)
    {

        iShowBMP2(bullet[2].bulletX,bullet[2].bulletY, "bulletlaser.bmp", 0);


        if (bullet[2].bulletY > SCREEN_WIDTH)
        {
            resetBullet(2);
        }
    }

    if(bullet[3].mode == 1)
    {

        iShowBMP2(bullet[3].bulletX,bullet[3].bulletY, "bulletlaser.bmp", 0);


        if (bullet[3].bulletY > SCREEN_WIDTH)
        {
            resetBullet(3);
        }
    }

    if(bullet[4].mode == 1)
    {

        iShowBMP2(bullet[4].bulletX,bullet[4].bulletY, "bulletlaser.bmp", 0);


        if (bullet[4].bulletY > SCREEN_WIDTH)
        {
            resetBullet(4);
        }
    }

    if(bullet[5].mode == 1)
    {

        iShowBMP2(bullet[5].bulletX,bullet[5].bulletY, "bulletlaser.bmp", 0);


        if (bullet[5].bulletY > SCREEN_WIDTH)
        {
            resetBullet(5);
        }
    }

    if(bullet[6].mode == 1)
    {

        iShowBMP2(bullet[6].bulletX,bullet[6].bulletY, "bulletlaser.bmp", 0);


        if (bullet[6].bulletY > SCREEN_WIDTH)
        {
            resetBullet(6);
        }
    }

    if(bullet[7].mode == 1)
    {

        iShowBMP2(bullet[7].bulletX,bullet[7].bulletY, "bulletlaser.bmp", 0);


        if (bullet[7].bulletY > SCREEN_WIDTH)
        {
            resetBullet(7);
        }
    }

    if(bullet[8].mode == 1)
    {

        iShowBMP2(bullet[8].bulletX,bullet[8].bulletY, "bulletlaser.bmp", 0);


        if (bullet[8].bulletY > SCREEN_WIDTH)
        {
            resetBullet(8);
        }
    }

    if(bullet[9].mode == 1)
    {

        iShowBMP2(bullet[9].bulletX,bullet[9].bulletY, "bulletlaser.bmp", 0);


        if (bullet[9].bulletY > SCREEN_WIDTH)
        {
            resetBullet(9);
        }
    }

    if(bullet[10].mode == 1)
    {

        iShowBMP2(bullet[10].bulletX,bullet[10].bulletY, "bulletlaser.bmp", 0);


        if (bullet[10].bulletY > SCREEN_WIDTH)
        {
            resetBullet(10);
        }
    }

    if(bullet[11].mode == 1)
    {

        iShowBMP2(bullet[11].bulletX,bullet[11].bulletY, "bulletlaser.bmp", 0);


        if (bullet[11].bulletY > SCREEN_WIDTH)
        {
            resetBullet(11);
        }
    }

    if(bullet[12].mode == 1)
    {

        iShowBMP2(bullet[12].bulletX,bullet[12].bulletY, "bulletlaser.bmp", 0);


        if (bullet[12].bulletY > SCREEN_WIDTH)
        {
            resetBullet(12);
        }
    }

    if(bullet[13].mode == 1)
    {

        iShowBMP2(bullet[13].bulletX,bullet[13].bulletY, "bulletlaser.bmp", 0);


        if (bullet[13].bulletY > SCREEN_WIDTH)
        {
            resetBullet(13);
        }
    }

    if(bullet[13].mode == 1)
    {

        iShowBMP2(bullet[13].bulletX,bullet[13].bulletY, "bulletlaser.bmp", 0);


        if (bullet[13].bulletY > SCREEN_WIDTH)
        {
            resetBullet(13);
        }
    }

    if(bullet[14].mode == 1)
    {

        iShowBMP2(bullet[14].bulletX,bullet[14].bulletY, "bulletlaser.bmp", 0);


        if (bullet[14].bulletY > SCREEN_WIDTH)
        {
            resetBullet(14);
        }
    }

    if(bullet[15].mode == 1)
    {

        iShowBMP2(bullet[15].bulletX,bullet[15].bulletY, "bulletlaser.bmp", 0);


        if (bullet[15].bulletY > SCREEN_WIDTH)
        {
            resetBullet(15);
        }
    }

    if(bullet[16].mode == 1)
    {

        iShowBMP2(bullet[16].bulletX,bullet[16].bulletY, "bulletlaser.bmp", 0);


        if (bullet[16].bulletY > SCREEN_WIDTH)
        {
            resetBullet(16);
        }
    }

    if(bullet[17].mode == 1)
    {

        iShowBMP2(bullet[17].bulletX,bullet[17].bulletY, "bulletlaser.bmp", 0);


        if (bullet[17].bulletY > SCREEN_WIDTH)
        {
            resetBullet(17);
        }
    }

    if(bullet[18].mode == 1)
    {

        iShowBMP2(bullet[18].bulletX,bullet[18].bulletY, "bulletlaser.bmp", 0);


        if (bullet[18].bulletY > SCREEN_WIDTH)
        {
            resetBullet(18);
        }
    }

    if(bullet[19].mode == 1)
    {

        iShowBMP2(bullet[19].bulletX,bullet[19].bulletY, "bulletlaser.bmp", 0);


        if (bullet[19].bulletY > SCREEN_WIDTH)
        {
            resetBullet(19);
        }
    }

    if(bullet[20].mode == 1)
    {

        iShowBMP2(bullet[20].bulletX,bullet[20].bulletY, "bulletlaser.bmp", 0);


        if (bullet[20].bulletY > SCREEN_WIDTH)
        {
            resetBullet(20);
        }
    }

    if(bullet[21].mode == 1)
    {

        iShowBMP2(bullet[21].bulletX,bullet[21].bulletY, "bulletlaser.bmp", 0);


        if (bullet[21].bulletY > SCREEN_WIDTH)
        {
            resetBullet(21);
        }
    }



    if(bullet[22].mode == 1)
    {

        iShowBMP2(bullet[22].bulletX,bullet[22].bulletY, "bulletlaser.bmp", 0);


        if (bullet[22].bulletY > SCREEN_WIDTH)
        {
            resetBullet(22);
        }
    }

    if(bullet[23].mode == 1)
    {

        iShowBMP2(bullet[23].bulletX,bullet[23].bulletY, "bulletlaser.bmp", 0);


        if (bullet[23].bulletY > SCREEN_WIDTH)
        {
            resetBullet(23);
        }
    }

    if(bullet[24].mode == 1)
    {

        iShowBMP2(bullet[24].bulletX,bullet[24].bulletY, "bulletlaser.bmp", 0);


        if (bullet[24].bulletY > SCREEN_WIDTH)
        {
            resetBullet(24);
        }
    }





}

void levelDraw()
{
    iSetColor(255, 255, 255);
    if(showLevel == 1)
    {
        levelDrawTimer++;
        sprintf(levelPrint, "LEVEL %d",level);


        iText(480,450,levelPrint,GLUT_BITMAP_HELVETICA_18);




    }

    if(levelDrawTimer > 100)
    {
        showLevel = 0;
        levelDrawTimer = 0;
    }

    iSetColor(0, 0, 0);

}


void itemDraw(void)
{
    if(items[0].mode == 1)
    {
        iShowBMP2(items[0].itemX,items[0].itemY, itemSprite[0], 0);



        if(items[0].itemX < 0)
        {
            resetItem(0);
        }



    }

    if(items[1].mode == 1)
    {
        iShowBMP2(items[1].itemX,items[1].itemY, itemSprite[1], 0);



        if(items[1].itemX < 0)
        {
            resetItem(1);
        }



    }

    if(items[2].mode == 1)
    {
        iShowBMP2(items[2].itemX,items[2].itemY, itemSprite[2], 0);



        if(items[2].itemX < 0)
        {
            resetItem(2);
        }



    }



}


void menuDraw()
{

    iSetColor(255, 255, 255);

    iShowBMP2(0,0,"menu.bmp",0);







}

void instructionDraw()
{
iShowBMP2(0,0,"instructions.bmp",0);
}
void creditsDraw(){

iShowBMP2(0,0,"credits.bmp",0);


}
void pauseDraw (void)
{
     iSetColor(255, 255, 255);

     iText(440, 500, "RESUME" , GLUT_BITMAP_TIMES_ROMAN_24);

      iText(460, 400, "QUIT" , GLUT_BITMAP_TIMES_ROMAN_24);







}

void comboDraw (void)
{
 int temp;



     iSetColor(255, 255, 255);



     if(comboToggle == 1)
     {
         temp = streak / 10;


         comboDrawTimer = 50;

         sprintf(comboPrint, "%d0 X COMBO!",temp);

         comboToggle = 0;




     }

        if(comboDrawTimer > 0)
         {



         iText(450,500, comboPrint, GLUT_BITMAP_HELVETICA_18);


        }



      comboDrawTimer--;



}

void highscoreDraw()

{

     iSetColor(255, 255, 255);

    iText(420, 700, "H I G H   S C O R E S",GLUT_BITMAP_TIMES_ROMAN_24);
    iText(950,30, "Back", GLUT_BITMAP_HELVETICA_18);



    if(highscoreFlag == 0)
    {
        highscoreRead();
    }


    if(highscoreFlag == 1)
    {
        iText(300, 580, "Name", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(700, 580, "Score", GLUT_BITMAP_TIMES_ROMAN_24);

        if(0 < scoresRead)
        {
            //iText(300, 500, "1) " ,GLUT_BITMAP_HELVETICA_18);
            iText(300,500,highscores[0].name, GLUT_BITMAP_HELVETICA_18);
            iText(700,500,highscores[0].highscorePrint, GLUT_BITMAP_HELVETICA_18);

        }

       if(1 < scoresRead)
        {
            //iText(300, 420, "2) " ,GLUT_BITMAP_HELVETICA_18);
            iText(300,420,highscores[1].name, GLUT_BITMAP_HELVETICA_18);
            iText(700,420,highscores[1].highscorePrint, GLUT_BITMAP_HELVETICA_18);

        }

         if(2 < scoresRead)
        {
            //iText(300, 340, "3) " ,GLUT_BITMAP_HELVETICA_18);
            iText(300,340,highscores[2].name, GLUT_BITMAP_HELVETICA_18);
            iText(700,340,highscores[2].highscorePrint, GLUT_BITMAP_HELVETICA_18);

        }

         if(3 < scoresRead)
        {
            //iText(300, 260, "4) " ,GLUT_BITMAP_HELVETICA_18);
            iText(300,260,highscores[3].name, GLUT_BITMAP_HELVETICA_18);
            iText(700,260,highscores[3].highscorePrint, GLUT_BITMAP_HELVETICA_18);

        }

        if(4 < scoresRead)
        {
            //iText(300, 180, "5) " ,GLUT_BITMAP_HELVETICA_18);
            iText(300,180,highscores[4].name, GLUT_BITMAP_HELVETICA_18);
            iText(700,180,highscores[4].highscorePrint, GLUT_BITMAP_HELVETICA_18);

        }





    }

}


void gameoverDraw (void)
{

     iSetColor(255, 255, 255);

    // iText(400, 700, "G A M E        O V E R",GLUT_BITMAP_TIMES_ROMAN_24 );

       iShowBMP2(0,0,"gameover.bmp",0);


    // iText(420, 550, "Enter Your Name", GLUT_BITMAP_TIMES_ROMAN_24);


    iText(260, 405, nameStack , GLUT_BITMAP_TIMES_ROMAN_24);

     iFilledRectangle(250, 400, 530, 3);







}
void introDraw(){

static int i=0;
iShowBMP2(0,0,introImage[i],0);
i++;
if(i>=29)i=10;
iText(350,250,"Press Left Click or Enter to Continue");

}




//end of Draw Functions

//end of user created functions.



void iDraw()
{
    iClear();



    bgDraw();

    if(gamestate==INTRO){
        introDraw();

    }

    if(gamestate == MENU)
    {

        menuDraw();

    }


    if (gamestate == INSTRUCTION)
    {

        instructionDraw();
    }


    if(gamestate == PAUSE)
    {

        pauseDraw();
    }


   if(gamestate==CREDITS){

    creditsDraw();

   }

   if(gamestate == HIGHSCORE)
   {

       highscoreDraw();
   }

   if(gamestate == GAMEOVER)
   {

       gameoverDraw();
   }


    if(gamestate == GAME)
    {


        iShowBMP2(0, 0, "mothership2.bmp",0);
        iSetColor(20, 200, 0);
        iShowBMP2(shipx, shipy, "ship3.bmp",0);
        iSetColor(255, 255, 255);
        enemyDraw();
        healthDraw();
        scoreDraw();
        bulletDraw();
        itemDraw();
        levelDraw();
        comboDraw();
        explosionDraw();

    }

   // printf("gamestate is %d",gamestate);



}


void iMouseMove(int mx, int my)
{

}


void iMouse(int button, int state, int mx, int my)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        if(gamestate==INTRO)gamestate=MENU;

    }




    if(gamestate == MENU)
    {



        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {

            if( (mx >= 470 && mx <= 534) && (my >= 490 && my <= 505) )
            {

                gamestate = GAME;
                initializeGame();
            }

             if ( (mx >= 410 && mx <= 610) && (my >= 416 && my <= 432))
            {
                gamestate = INSTRUCTION;

            }

            if ( (mx >= 441 && mx <= 558) && (my >= 279 && my <= 298))
            {

               gamestate=CREDITS;
            }



            if ( (mx >= 470 && mx <= 528) && (my >= 209 && my <= 225))
            {
               exit(EXIT_SUCCESS);
            }

             if ( (mx >= 410 && mx <= 590) && (my >= 349 && my <= 370))
            {

               gamestate= HIGHSCORE;
            }





        }

    }

    if (gamestate == CREDITS)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {

            if( (mx >= 889 && mx <= 954) && (my >= 124 && my <= 153) )
            {
                gamestate = MENU;

            }

        }
    }


    if (gamestate == INSTRUCTION)
    {
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {

            if( (mx >= 893 && mx <= 966) && (my >= 148 && my <= 179) )
            {
                gamestate = MENU;

            }


        }
    }

      if (gamestate == HIGHSCORE)

    {

        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {

            if( (mx >= 940 && mx <= 990) && (my >= 30 && my <= 45) )
            {
                gamestate = MENU;

            }

        }
    }





    if(gamestate == PAUSE)
    {

         if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {

            if( (mx >= 440 && mx <= 540) && (my >= 495 && my <= 520) )
            {
                resumeGame();
                gamestate = GAME;

            }


            if ( (mx >= 460 && mx <= 520) && (my >= 397 && my <= 420))
            {
                exit(EXIT_SUCCESS);
            }

           // printf("%d %d \n",mx , my);



        }




    }





    if (gamestate == GAME)

    {


        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if(gunMode == 1)
            {
                createBullet(shipx + BULLETX_ADJ ,shipy + BULLETY_ADJ);
            }

            if(gunMode == 2)
            {
                createBullet(shipx + BULLETX_ADJ+10 ,shipy + BULLETY_ADJ);
                createBullet(shipx + BULLETX_ADJ-10 ,shipy + BULLETY_ADJ);
            }

            if(gunMode == 3)
            {
                createBullet(shipx + BULLETX_ADJ-15 ,shipy + BULLETY_ADJ);
                createBullet(shipx + BULLETX_ADJ+15 ,shipy + BULLETY_ADJ);
                createBullet(shipx + BULLETX_ADJ ,shipy + BULLETY_ADJ);
            }

            if(gunMode > 3)
            {
                createBullet(shipx + BULLETX_ADJ-15 ,shipy + BULLETY_ADJ);
                createBullet(shipx + BULLETX_ADJ+15 ,shipy + BULLETY_ADJ);
                createBullet(shipx + BULLETX_ADJ ,shipy + BULLETY_ADJ);
            }

        }

       /* if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
        {
            createBullet(shipx + BULLETX_ADJ-15 ,shipy + BULLETY_ADJ);
            createBullet(shipx + BULLETX_ADJ+15 ,shipy + BULLETY_ADJ);
            createBullet(shipx + BULLETX_ADJ ,shipy + BULLETY_ADJ);
        }
        */


    }



}


void iKeyboard(unsigned char key)
{
    if(gamestate==INTRO && key=='\r'){gamestate=MENU;}

    if (key == 'm' && gamestate != GAMEOVER)
    {
        if (playMusic)
        {
            playMusic = false;
            PlaySound(0,0,0 );
        }
        else if (!playMusic)
        {
            playMusic = true;
            PlaySound("bgmusic.wav",NULL, SND_LOOP | SND_ASYNC );
        }

    }


   /* if(key == 'v' && gamestate != GAMEOVER)  //debug prints
    {
        printf("%d is streak, %d is comboToggle, %d is combomultiplier\n",streak, comboToggle,comboMultiplier);
    }
*/

    if (gamestate == GAME)

    {



        if (key == 'w' && shipy < (SCREEN_WIDTH - 100))
        {
            shipy += shipSpeed;
        }

        if (key == 's' && shipy > 60)
        {
            shipy -= shipSpeed;
        }
        if (key == 'a' && shipx > 25)
        {
            shipx -= shipSpeed;
        }
        if (key == 'd' && shipx < SCREEN_LEN  - 100)
        {
            shipx += shipSpeed;
        }


        if(key == 'p')
        {
            freezeGame();
            gamestate = PAUSE;

        }



    }

    if(gamestate == PAUSE)
    {

         if(key == 'r')
        {
            resumeGame();
            gamestate = GAME;

        }
    }


    if(gamestate == GAMEOVER)
    {
        int i, j;


        if(key == '\r')
        {

            PlayGameMusic();
            strcpy(player.name, nameStack);

            for( i = 0; i < nameLen; i++ )
            {
                nameStack[i] = 0;
            }
            nameLen = 0;

            highscoreUpdate();

            gamestate = HIGHSCORE;

        }


       else if(key == '\b')
       {

			if(nameLen>0)
			{
				nameLen--;
				nameStack[nameLen]=0;
			}

       }


       else if(nameLen < 45 && key != ' ')
       {
           nameStack[nameLen] = key;
           nameLen++;
       }
    }


}




void iSpecialKeyboard(unsigned char key)
{

    if (gamestate == GAME)

    {


        if (key == GLUT_KEY_UP && shipy < (SCREEN_WIDTH - 100))
        {
            shipy += shipSpeed;
        }

        if (key == GLUT_KEY_DOWN && shipy > 60)
        {
            shipy -= shipSpeed;
        }
        if (key == GLUT_KEY_LEFT && shipx > 25)
        {
            shipx -= shipSpeed;
        }
        if (key == GLUT_KEY_RIGHT && shipx < SCREEN_LEN - 100)
        {
            shipx += shipSpeed;
        }

    }


}


int main()
{



    setBg();
    shiftBgValue =   iSetTimer(bgShiftSpeed,shiftBg);

    if (playMusic)
    {
        PlaySound("bgmusic.wav",NULL, SND_LOOP | SND_ASYNC );
    }


    srand((unsigned) time (NULL));
    spawnTimerValue1 = iSetTimer(2000,enemyTimer);
    spawnTimerValue2 = iSetTimer(1500, enemyTimer);
    spawnTimerValue3 = iSetTimer(1000, enemyTimer);






    explosionIndexTimerValue = iSetTimer(140,explosionIndexTimer);
    bulletCollisionDetectorValue = iSetTimer(10, bulletCollisionDetector);//actually all collision detection is done here. Ship, bullet, item.
    increaseLevelValue = iSetTimer(30000, increaseLevel);
    movementValue = iSetTimer(30, movement);
    createItemValue = iSetTimer(17000, createItem);




    iPauseTimer(explosionIndexTimerValue );
    iPauseTimer(bulletCollisionDetectorValue );
    iPauseTimer( increaseLevelValue);
    iPauseTimer( movementValue);
    iPauseTimer( createItemValue);
    iPauseTimer(spawnTimerValue1);
    iPauseTimer(spawnTimerValue2);
    iPauseTimer(spawnTimerValue3);

    iInitialize(SCREEN_LEN, SCREEN_WIDTH, "NEW ORBIT.exe");
    return 0;
}
