//
//  tetris.h
//  
//
//  Created by Yves BAZIN on 30/11/17.
//

#ifndef tetris2_h
#define tetris2_h





#define DISP_RIGHT   0
#define DISP_UP  1
#include "tetris3.h"
void initTetrisScoketControl();
void tetrisWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);

int displayNextPiecePos=DISP_UP;
bool gamePaused=false;
//int hauteur=25;
//int largeur=18;
int score=0;
//bool authdisplay=false;

CRGB *backgroundBlocks;     //8 x 16 display + 4 x 8 blocks above for blocks to spawn in
CRGB *displayScreen;
CRGB nextBlockImage[12*4]; //je prends les deux premieres lignes du block
//CRGB TdisplayScreen [160];
CRGB *tertisScreen;

bool stopfall=false;
//int TETRIS_HEIGHT=25;
//int TETRIS_WIDTH=12;
CRGB shadow[40*2*2]; //pour mettre le shadow de la piece
int TETRIS_X=3;
int TETRIS_Y=3;
int blockType ;                   //7 different block types
int nextBlockType; //to Display the next piece
int state;                        //4 possible rotation states
bool isInitiated=false;
bool isDisplayNextPiece=false;
bool isDisplayScore=false;
bool displayShadow=true;
int tetrisWebSocketPort=85;
//long int fallinterval=1000000; // 1 seconde
volatile int interruptCounter;
int totalInterruptCounter;

//hw_timer_t * timer = NULL;
//portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;
/*
const int activeBlocks [28][4][4] = {
    {{0,0,1,0},    //     blockType + 7(state)
        {0,1,1,0},    // 0 =    0      + 7(0)
        {0,1,0,0},
        {0,0,0,0}}  ,
    
    {{0,2,0,0},    // 1 =    1      + 7(0)
        {0,2,2,0},
        {0,2,0,0},
        {0,0,0,0}} ,
    
    {{0,3,0,0},    // 2 =    2      + 7(0)
        {0,3,3,0},
        {0,0,3,0},
        {0,0,0,0}} ,
    
    {{0,0,0,0},    // 3 =    3      + 7(0)
        {0,4,4,0},
        {0,4,4,0},
        {0,0,0,0}} ,
    
    {{0,5,0,0},    // 4 =    4      + 7(0)
        {0,5,0,0},
        {0,5,5,0},
        {0,0,0,0}} ,
    
    {{0,6,6,0},    // 5 =    5      + 7(0)
        {0,6,0,0},
        {0,6,0,0},
        {0,0,0,0}} ,
    
    {{0,0,7,0},    // 6 =    6      + 7(0)
        {0,0,7,0},
        {0,0,7,0},
        {0,0,7,0}} ,
    
    {{0,0,0,0},  // 7 =    0      + 7(1)
        {1,1,0,0},
        {0,1,1,0},
        {0,0,0,0}}  ,
    
    {{0,0,0,0},    // 8 =    1      + 7(1)
        {2,2,2,0},
        {0,2,0,0},
        {0,0,0,0}} ,
    
    {{0,0,0,0},    // 9 =    2      + 7(1)
        {0,3,3,0},
        {3,3,0,0},
        {0,0,0,0}} ,
    
    {{0,0,0,0},    // 10 =    3      + 7(1)
        {0,4,4,0},
        {0,4,4,0},
        {0,0,0,0}} ,
    
    {{0,0,0,0},    // 11 =    4      + 7(1)
        {5,5,5,0},
        {5,0,0,0},
        {0,0,0,0}} ,
    
    {{0,0,0,0},    // 12 =    5      + 7(1)
        {6,6,6,0},
        {0,0,6,0},
        {0,0,0,0}} ,
    
    {{0,0,0,0},    // 13 =    6      + 7(1)
        {0,0,0,0},
        {7,7,7,7},
        {0,0,0,0}} ,
    
    {{0,1,0,0},    // 14 =    0      + 7(2)
        {1,1,0,0},
        {1,0,0,0},
        {0,0,0,0}}  ,
    
    {{0,2,0,0},    // 15 =    1      + 7(2)
        {2,2,0,0},
        {0,2,0,0},
        {0,0,0,0}} ,
    
    {{3,0,0,0},    // 16 =    2      + 7(2)
        {3,3,0,0},
        {0,3,0,0},
        {0,0,0,0}} ,
    
    {{0,0,0,0},    // 17 =    3      + 7(2)
        {0,4,4,0},
        {0,4,4,0},
        {0,0,0,0}} ,
    
    {{5,5,0,0},    // 18 =    4      + 7(2)
        {0,5,0,0},
        {0,5,0,0},
        {0,0,0,0}} ,
    
    {{0,6,0,0},    // 19 =    5      + 7(2)
        {0,6,0,0},
        {6,6,0,0},
        {0,0,0,0}} ,
    
    {{0,7,0,0},    // 20 =    6      + 7(2)
        {0,7,0,0},
        {0,7,0,0},
        {0,7,0,0}} ,
    
    {{1,1,0,0},    // 21 =    0      + 7(3)
        {0,1,1,0},
        {0,0,0,0},
        {0,0,0,0}}  ,
    
    {{0,2,0,0},    // 22 =    1      + 7(3)
        {2,2,2,0},
        {0,0,0,0},
        {0,0,0,0}} ,
    
    {{0,3,3,0},    // 23 =    2      + 7(3)
        {3,3,0,0},
        {0,0,0,0},
        {0,0,0,0}} ,
    
    {{0,0,0,0},    // 24 =    3      + 7(3)
        {0,4,4,0},
        {0,4,4,0},
        {0,0,0,0}} ,
    
    {{0,0,5,0},    // 25 =    4      + 7(3)
        {5,5,5,0},
        {0,0,0,0},
        {0,0,0,0}} ,
    
    {{6,0,0,0},    // 26 =    5      + 7(3)
        {6,6,6,0},
        {0,0,0,0},
        {0,0,0,0}} ,
    
    {{0,0,0,0},    // 27 =    6      + 7(3)
        {7,7,7,7},
        {0,0,0,0},
        {0,0,0,0}}
};

CRGB paletblock[10]={CRGB::Black,CRGB::Red,CRGB::Green,CRGB::Blue,CRGB::Yellow,CRGB::Purple,CRGB::Cyan,CRGB::White} ;
CRGB paletblock2[10]={bgColor,CRGB::Red,CRGB::Green,CRGB::Blue,CRGB::Yellow,CRGB::Purple,CRGB::Cyan,CRGB::White} ;
 */
int blockColumn;             //the x value of the left most row in the 4x4 active block placeholder
int blockRow;                //the y value of the bottom column in the 4x4 active block placeholder

int rowToBeDeleted;
bool inGame = false;
bool justLost = false;
int brightness = 8;
//long fallRate;
//long dixs=80000*5;

WebSocketsServer tetrisWebSocket = WebSocketsServer(tetrisWebSocketPort); //creating the entry for socket


void  combineArrays()  //updates the displayScreen array by combining the current positions of the backgroundBlocks and the activeBlocks
{
    //first make an exact copy of the backgroundBlocks
    // Serial.println("on combine");
    for(byte y = 0; y < TETRIS_HEIGHT; y++)
        for(byte x = 0; x < TETRIS_WIDTH; x++)
            displayScreen[x+TETRIS_WIDTH*y] = backgroundBlocks[x+TETRIS_WIDTH*y];
    
    //then add the non zero elements of the activeBlocks
    for(int i=0;i<4*TETRIS_WIDTH;i++)
    {
        shadow[i]=bgColor;
    }
    for(int y = 0; y < 4; y++)
        for(int x = 0; x < 4; x++)
        {
            if(activeBlocks[blockType + (7 * state)][y][x] > 0)
            {
                //   Serial.print("e:");
                //Serial.println(activeBlocks[blockType + (7 * state)][x][y]);
                displayScreen[x + blockColumn+TETRIS_WIDTH*(y + blockRow)] = paletblock[ activeBlocks[blockType + (7 * state)][y][x] ];
                shadow[(x + blockColumn)*2]=paletblock[ activeBlocks[blockType + (7 * state)][y][x] ];
                shadow[(x + blockColumn)*2+1]=paletblock[ activeBlocks[blockType + (7 * state)][y][x] ];
                shadow[(x + blockColumn)*2+2*TETRIS_WIDTH]=paletblock[ activeBlocks[blockType + (7 * state)][y][x] ];
                shadow[(x + blockColumn)*2+1+2*TETRIS_WIDTH]=paletblock[ activeBlocks[blockType + (7 * state)][y][x] ];
            }
            
        }
}


void displayArray()  // cycles through each pixel in displayScreen and outputs corresponding colour
{
    while(authdisplay){Serial.println("loop display");}
    
    authdisplay=false;
    //displaypic(displayScreen,TETRIS_X,TETRIS_Y,TETRIS_HEIGHT,TETRIS_WIDTH);
    if(isDisplayNextPiece)
    {
        int x=0;
        int y=0;
        switch (displayNextPiecePos) {
            case DISP_UP:
                 x=2;
                y=(TETRIS_HEIGHT+1+TETRIS_Y);
                break;
            case DISP_RIGHT:
                x=TETRIS_X+2*TETRIS_WIDTH+2;
                y=TETRIS_Y+2*TETRIS_HEIGHT-8;
                break;
            default:
                break;
        }
        displayPicNew(nextBlockImage,x,y,6,8); //on ecrit la next piece
    }
    if(isDisplayScore)
    {
        char chi[2];
        sprintf(chi, "%d", score);
        //Serial.println(chi);
        //Serial.println(sizeof(chi)/sizeof(char));
        if(score<10)
        {
            chi[1]=chi[0];
            chi[0]=0x0030;
            
        }
        char but[4];
        my_itoa(score,but,10,3);
        afficheMessage2(but, TETRIS_X+2*TETRIS_WIDTH+2,3);
       // afficheLettre((int)(chi[0])-32,TETRIS_X+2*TETRIS_WIDTH+1,2);
        //afficheLettre((int)(chi[1])-32,TETRIS_X+2*TETRIS_WIDTH+6, 2);
    }
    
    //on transpose les case de displayScreen un peu crade mais efficace
    
    for(int y=0;y<TETRIS_HEIGHT;y++)
        for(int x=0;x<TETRIS_WIDTH;x++)
        {
           // tertisScreen[2*y*2*TETRIS_WIDTH+2*x]=displayScreen[x+y*TETRIS_WIDTH];
           // tertisScreen[(2*y+1)*2*TETRIS_WIDTH+2*x+1]=displayScreen[x+y*TETRIS_WIDTH];
            tertisScreen[2*y*2*TETRIS_WIDTH+2*x]=displayScreen[x+y*TETRIS_WIDTH];
            tertisScreen[2*y*2*TETRIS_WIDTH+2*x+1]=displayScreen[x+y*TETRIS_WIDTH];
            tertisScreen[(2*y+1)*2*TETRIS_WIDTH+2*x]=displayScreen[x+y*TETRIS_WIDTH];
            tertisScreen[(2*y+1)*2*TETRIS_WIDTH+2*x+1]=displayScreen[x+y*TETRIS_WIDTH];
        }
   // fill(CRGB(10,10,10));
    displayPicNew(tertisScreen,TETRIS_X,TETRIS_Y,2*TETRIS_HEIGHT,2*TETRIS_WIDTH);
    if(displayShadow)
        displayPicNew(shadow,TETRIS_X,TETRIS_Y-3,2,2*TETRIS_WIDTH);
    authdisplay=true;
}

void updateDisplay() // this function is called by a timer interupt every 10 milliseconds
{
    //Serial.println("on affiche");
    combineArrays();
    
    
    
    
    // adds the latest position of the active block to the displayScreen Array
    //Serial.println("on display");
    displayArray();
    replaceled();
      // FastLEDshowESP32();
    //FastLED.show();// outputs the displayScreen Array
}


void resetArrays()  // resets arrays to all zeros
{
    for(byte y = 0; y < TETRIS_HEIGHT; y++)
        for(byte x = 0; x < TETRIS_WIDTH; x++)
        {
            displayScreen[x+TETRIS_WIDTH*y] = CRGB(0,0,0);
            backgroundBlocks[x+TETRIS_WIDTH*y] =
            tertisScreen[2*y*2*TETRIS_WIDTH+2*x]=CRGB(0,0,0);
            tertisScreen[2*y*2*TETRIS_WIDTH+2*x+1]=CRGB(0,0,0);
            tertisScreen[(2*y+1)*2*TETRIS_WIDTH+2*x]=CRGB(0,0,0);
           tertisScreen[(2*y+1)*2*TETRIS_WIDTH+2*x+1]=CRGB(0,0,0);
        }   }


void fillNextBlock(int blockType)
{
    for(int y = 0; y < 3; y++)
        for(int x = 0; x < 4; x++)
        {
                nextBlockImage[2*x +8*2*y] = paletblock2[ activeBlocks[blockType + (7 * 3)][y][x] ];
            nextBlockImage[2*x +1+8*2*y] = paletblock2[ activeBlocks[blockType + (7 * 3)][y][x] ];
            nextBlockImage[2*x +8*(2*y+1)] = paletblock2[ activeBlocks[blockType + (7 * 3)][y][x] ];
            nextBlockImage[2*x+1 +8*(2*y+1)] = paletblock2[ activeBlocks[blockType + (7 * 3)][y][x] ];
        }
}

void newBlock() //
{
    blockColumn = 2;
    blockRow = TETRIS_HEIGHT-3;
    blockType=nextBlockType;
    nextBlockType = random(7);// blocktype is a random between 0 and 6 inclusive
    //Serial.println(blockType);
    fillNextBlock(nextBlockType);
    state = 3;     // reset state back to spawn block state
}


bool canBeMoved(int newCol, int newRow)  // return true if the there is empty pixels for the block to move in to
{
    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            if(activeBlocks[blockType + (7 * state)][y][x] > 0)   // finds the positions of the non-blank blocks in the 4x4 matrix
            {
                int boardX = x + newCol;                            // calculates the corresponding x position on the display board
                int boardY = y + newRow;                            // calculates the corresponding y position on the display board
                //Serial.println(boardY);
                if(boardX < 0 ||  boardX > TETRIS_WIDTH-1 || boardY < 0)         // if the pixel is outside the boundaries of the board
                    return false;
                if(backgroundBlocks[boardX+TETRIS_WIDTH*boardY] > CRGB(0,0,0))            // if the pixel is already full
                    return false;
            }
        }
    }
    return true;
}

bool canMoveDown()   // row - 1
{
   if(blockRow-1<0)
       Serial.println(blockRow);
    
    if(canBeMoved(blockColumn, blockRow -1))
        return true;
    else
        return false;
}

bool canMoveLeft()
{
    if(canBeMoved(blockColumn - 1, blockRow)) // column -1
        return true;
    else
        return false;
}

bool canMoveRight()
{
    if(canBeMoved(blockColumn + 1, blockRow)) // column + 1
        return true;
    else
        return false;
}

bool canBeRotated(int newState)
{
    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            if(activeBlocks[blockType + (7 * newState)][y][x] > 0) // finds the positions of the non-blank blocks in the 4x4 matrix
            {
                int boardX = x + blockColumn;                        // calculates the corresponding x position on the display board
                int boardY = y + blockRow;                           // calculates the corresponding y position on the display board
                if(boardX < 0 ||  boardX > TETRIS_WIDTH || boardY < 0)          // if the pixel is outside the boundaries of the board
                    return false;
                
                if(backgroundBlocks[boardX+TETRIS_WIDTH*boardY] > CRGB(0,0,0))             // if the pixel is already full
                    return false;
            }
        }
    }
    return true;
}

bool canRotateLeft()
{
    int nextState;
    if(state == 0)      // state to the left of 0 is 3
        nextState = 3;
    else
        nextState = state - 1;
    
    if(canBeRotated(nextState))
        return true;
    else
        return false;
}

bool canRotateRight()
{
    int nextState;
    if(state == 3)      // state to the right of 3 is 0
        nextState = 0;
    else
        nextState = state + 1;
    
    if(canBeRotated(nextState))
        return true;
    else
        return false;
}

void moveActiveBlocksToBackground()
{
    combineArrays(); //updated the display array
    
    for(byte y = 0; y < TETRIS_HEIGHT; y++)
        for(byte x = 0; x < TETRIS_WIDTH; x++)
            backgroundBlocks[x+TETRIS_WIDTH*y] = displayScreen[x+TETRIS_WIDTH*y];    // copy the displayScreen to the backgroundBlocks
}

bool rowIsFull()                // goes through all 16 rows and checks if they are full
{
    for(byte y = 0; y < TETRIS_HEIGHT; y++)
    {
        bool isfull=true;
        for(byte x=0;x<TETRIS_WIDTH;x++)
        {
            if( backgroundBlocks[TETRIS_WIDTH*y+x] ==CRGB(0,0,0)  )
                isfull= false;
        }
        if(isfull)
        {
            Serial.println("on efface la ligne");
            rowToBeDeleted = y;      // the row is returned as a global variable
            return true;
        }
    }
    return false;
}

void deleteRow()
{
    score++;
    
    if(rowToBeDeleted==TETRIS_HEIGHT-1)
    {
        for(byte x = 0; x < TETRIS_WIDTH; x++)
            backgroundBlocks[x+TETRIS_WIDTH*(TETRIS_HEIGHT-1)] = CRGB(0,0,0);
    }
    else
    {
       // Serial.print("On efface ligne:");
       // Serial.println(rowToBeDeleted);
        for(byte y = rowToBeDeleted; y < TETRIS_HEIGHT-1; y++)
            for(byte x = 0; x < TETRIS_WIDTH; x++)
                backgroundBlocks[x+TETRIS_WIDTH*y] = backgroundBlocks[x+TETRIS_WIDTH*(y + 1)];  // replaces row with row above

    }
    
}

/*
void speedUpFalling()
{
    //timerStop(timer1);
    timerAlarmDisable(timer);
    
    if(fallinterval > 50000)   // to stop fallRate decreasing to zero
        fallinterval -= 50000;   // blocks falling speeds up by 50000 nanoseconds every full row made
    timerAlarmWrite(timer, fallinterval, true);
    timerAlarmEnable(timer);
    
}
*/
void deleteFullRows()
{
    for(int i = 0; i < 4; i++) // checking 4 times if there are full rows to be deleted
    {
        if(rowIsFull())
        {
            deleteRow();
            speedUpFalling();
        }
    }
}

bool spaceForNewBlock()  // returns true if there is space for the new block to be spawned at the top of the matrix
{
    if(canBeMoved(2, TETRIS_HEIGHT-3))
        return true;
    else
        return false;
}


void fillScreenT()       // fills pixels one at a time with green at the end of the game one at a time starting from the top
{
    for(int y = 0; y <TETRIS_HEIGHT; y++)
    {
        for(int x = 0; x < TETRIS_WIDTH; x++)
        {
            displayScreen[x+TETRIS_WIDTH*y] = CRGB(0,100,0);    // turns the pixel green

        }
        displayArray();
        FastLED.show();// outputs the pixel change to the screen
        FastLED.delay(30);
    }
}


void IRAM_ATTR fall()               // this function is called by a timer interupt every fallRate nanoseconds
{
    if(stopfall)
    {
        Serial.println('on a stop fall');
        return;
    }
    Serial.println("on fal");
   // portENTER_CRITICAL_ISR(&timerMux);
    ////no//interrupts();
    if(nbTetrisPlayer>1)
    {
        if(canMoveDown1())
            blockRow1--;
        else   //block cant move
        {
            moveActiveBlocksToBackground1();      // adds the activeBlocks to the background display
            deleteFullRows1();                    // deletes any full rows caused by now stationary block
            newBlock1();
            if(spaceFornewBlock1())
            {// checks can a new block spawn
     
            }
            else  // new block cant spawn so game over
            {
                
               // timer0_detachInterrupt();            // timer1_detachInterrupt();// stops timer1 interupt
                
                    char mess[]="TU AS PERDU";
                    afficheMessage2(mess,63,20);
                    inGame = false;
                    justLost = true;
                
                //delay(3000);
                //newGame();
                return;
            }
        }
    }
    
    
    if(canMoveDown())
        blockRow--;
    else   //block cant move
    {
        moveActiveBlocksToBackground();      // adds the activeBlocks to the background display
        deleteFullRows();                    // deletes any full rows caused by now stationary block
        newBlock();
        if(spaceForNewBlock())
        {// checks can a new block spawn
            
        }
        else  // new block cant spawn so game over
        {
            
            // timer0_detachInterrupt();            // timer1_detachInterrupt();// stops timer1 interupt
            
            char mess[]="TU AS PERDU";
            afficheMessage2(mess,3,20);
            inGame = false;
            justLost = true;
            
            //delay(3000);
            //newGame();
            return;
        }
    }
    //portEXIT_CRITICAL_ISR(&timerMux);
    updateDisplay1();
    updateDisplay();
    long    next=ESP.getCycleCount() +  fallRate*dixs;
    //timer0_write(next);
    
    ////interrupts();
    //yield();
}


/*void IRAM_ATTR fall()               // this function is called by a timer interupt every fallRate nanoseconds
{
    Serial.println("on fal");
}
*/






bool initTetris()
{
    if(true)
    {
        if(tableOrientation%2==0)
        {
            displayNextPiecePos=DISP_RIGHT;
            displayNextPiecePos1=DISP_RIGHT;
            isDisplayScore=true;
            isDisplayNextPiece=true;
            isDisplayscore1=true;
            isDisplayNextPiece1=true;
            TETRIS_WIDTH=15;
            TETRIS_HEIGHT=22;
        }
        else
        {
            displayNextPiecePos=DISP_UP;
            isDisplayScore=false;
            isDisplayNextPiece=true;
            TETRIS_WIDTH=15;
            TETRIS_HEIGHT=22;
        }
        backgroundBlocks =(CRGB*)malloc(TETRIS_WIDTH*TETRIS_HEIGHT*sizeof(CRGB)) ;
        displayScreen =(CRGB*)malloc(TETRIS_WIDTH*TETRIS_HEIGHT*sizeof(CRGB)) ;
        tertisScreen=(CRGB*)malloc(4*TETRIS_WIDTH*TETRIS_HEIGHT*sizeof(CRGB)) ;
        backgroundBlocks1 =(CRGB*)malloc(TETRIS_WIDTH*TETRIS_HEIGHT*sizeof(CRGB)) ;
        displayScreen1 =(CRGB*)malloc(TETRIS_WIDTH*TETRIS_HEIGHT*sizeof(CRGB)) ;
        tertisScreen1=(CRGB*)malloc(4*TETRIS_WIDTH*TETRIS_HEIGHT*sizeof(CRGB)) ;
         resetArrays();
        resetArrays1();
        if(!backgroundBlocks && !displayScreen)
        {
            Serial.println("Unable to create the screens");
            isInitiated=false;
            return false;
        }
        Serial.println("Tetris créé");
        isInitiated=true;
        server.serveStatic("/tetris.html", SPIFFS, "/tetris.html"); //on ajoute le lien vers tetris
        server.serveStatic("/tetris2.html", SPIFFS, "/tetris2.html"); //on ajoute le lien vers tetris
        server.serveStatic("/left.gif", SPIFFS, "/left.gif");
        server.serveStatic("/right.gif", SPIFFS, "/right.gif");
        server.serveStatic("/left-turn.gif", SPIFFS, "/left-turn.gif");
        server.serveStatic("/right_turn.gif", SPIFFS, "/right_turn.gif");
        server.serveStatic("/images.css", SPIFFS, "/images.css");
        initTetrisScoketControl();
        return true;
    }
    else{
        Serial.println("No table existing create the table first");
        isInitiated=false;
        return false;
    }
    
    

    
}


void initTetrisScoketControl()
{
    tetrisWebSocket.begin();
    tetrisWebSocket.onEvent(tetrisWebSocketEvent);
}

void executeTetrisSocketControl()
{
    tetrisWebSocket.loop();
    
}

void endGame()
{
    timerAlarmDisable(timer);
}


void newGame()
{
    fill(CRGB(10,10,10));
    bgColor=CRGB(10,10,10);
    inGame = true;
    justLost = false;
    score=0;
    fallRate=200;
    fallinterval=1000000;
    isInitiated=true;
    authdisplay=false;
    Serial.println("voici tetris");// clears the red display matrix
    if(!isInitiated)
    {
        Serial.println("on cree la base fait");
        initTetris();
        
    }
    if(isInitiated)
    {
        inGame = true;
        justLost = false;
        resetArrays();
        resetArrays1();
        randomSeed(ESP.getCycleCount());
        nextBlockType = random(7); //on initie le next block type
        newBlock();
        nextblockType1 = random(7); //on initie le next block type
        newBlock1();
        
        updateDisplay1();
        updateDisplay();
        fallRate = 200;
        ////no//interrupts();
         Serial.println("voici tetris2");
        timer = timerBegin(0, 80, true);
        timerAttachInterrupt(timer, &fall, true);
        timerAlarmWrite(timer, fallinterval, true);
        timerAlarmEnable(timer);
         Serial.println("voici tetris3");
       // timer0_isr_init();
        //timer0_attachInterrupt(fall);
        long  next=ESP.getCycleCount() + fallRate*dixs;
        //timer0_write(next);
        ////interrupts();
    }
    else
    {
        Serial.println("Tetris creation impossible");
    }
}



void tetrisWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
    authdisplay=false;
    stopfall=true;
     timerStop(timer);
    //authdisplay=false;
    ////no//interrupts();
    // Serial.printf("webSocketEvent(%d, %d, ...)\r\n", num, type);
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\r\n", num);
            break;
        case WStype_CONNECTED:
        {
            IPAddress ip = tetrisWebSocket.remoteIP(num);
            //       Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\r\n", num, ip[0], ip[1], ip[2], ip[3], payload);
            // Send the current LED status
        }
            break;
        case WStype_TEXT:
            Serial.printf("[%u] get Text: %s\r\n", num, payload);
            /*    if (strcmp("up", (const char *)payload) == 0)  {
             //writeLED(true);
             Serial.println("on go up");
             YO = (YO + 1) % LED_HEIGHT;
             fill_solid(leds, NUM_LEDS, bgColor);
             }
             else  if (strcmp("down", (const char *)payload) == 0)  {
             Serial.println("on go down");
             YO = (YO -1) % LED_HEIGHT;
             fill_solid(leds, NUM_LEDS, bgColor);
             }
             */
            if (strcmp("right", (const char *)payload) == 0)  {
                
                // Serial.println("on va a droite");
                if(canMoveRight())
                {
                    //no//interrupts();
                    blockColumn++;
                    updateDisplay1();
                    updateDisplay();
                    int next=ESP.getCycleCount()+fallRate*dixs;
                   // timer0_write(next);
                    //interrupts();
                }
            }
            
            if (strcmp("left", (const char *)payload) == 0)  {
                
                //Serial.println("on va a droite");
                if(canMoveLeft())
                {
                    //no//interrupts();
                    blockColumn--;
                    updateDisplay1();
                    updateDisplay();
                    int next=ESP.getCycleCount()+fallRate*dixs;
                    //timer0_write(next);
                    //interrupts();
                }
            }
            if (strcmp("new", (const char *)payload) == 0)  {
                fill(bgColor);
                newGame();
            }
            if (strcmp("2player", (const char *)payload) == 0)  {
                nbTetrisPlayer=2;
                fill(bgColor);
                newGame();
            }
            
            if (strcmp("hold", (const char *)payload) == 0)  {
                afficheMessage2("PAUSE",20,20);
                gamePaused=true;
                FastLEDshowESP32();
                stopfall=true;
            }
            if (strcmp("go", (const char *)payload) == 0)  {
                fill(bgColor);
                gamePaused=false;
                updateDisplay1();
                updateDisplay();
                FastLEDshowESP32();
                stopfall=false;
            }
            if (strcmp("1player", (const char *)payload) == 0)  {
                nbTetrisPlayer=1;
                fill(bgColor);
                newGame();
            }
            
            if (strcmp("turnr", (const char *)payload) == 0)  {
                
                if(canRotateRight())
                {
                    //no//interrupts();
                    if(state == 3)
                        state = 0;  // state to the right of 3 is 0
                    else
                        state++;
                    
                    updateDisplay1();
                    updateDisplay();
                    int next=ESP.getCycleCount()+fallRate*dixs;
                    //timer0_write(next);
                    //interrupts();
                }
                
            }
            
            
            if (strcmp("descend", (const char *)payload) == 0)  {
                Serial.println("on va desc");
               
                 Serial.println("on a topper timer");
                authdisplay=false;
                stopfall=true;
                while(canMoveDown())
                {
                    blockRow--;
                    Serial.println("on loop");
                    updateDisplay1();
                    updateDisplay();
                    authdisplay=false;
                    FastLEDshowESP32();
                    delay(10);

                }
                
                 //Serial.println("on a passer timer");
                authdisplay=false;
                stopfall=false;
               /* timer = timerBegin(0, 80, true);
                timerAttachInterrupt(timer, &fall, true);
                timerAlarmWrite(timer, 700000, true);
                timerAlarmEnable(timer);*/
                
                int next=ESP.getCycleCount()+fallRate*dixs;
               // timer0_write(next);
                //interrupts();
            }
            
            
            if (strcmp("turnl", (const char *)payload) == 0)  {
                
                if(canRotateLeft())
                {
                    //no//interrupts();
                    if(state == 0)
                        state = 3;  // state to the right of 3 is 0
                    else
                        state--;
                    
                    updateDisplay();
                    int next=ESP.getCycleCount()+fallRate*dixs;
                 //   timer0_write(next);
                    //interrupts();
                }
                
            }
            
            
            
            
            
            
            
            
            if (strcmp("right1", (const char *)payload) == 0)  {
                
                // Serial.println("on va a droite");
                if(canMoveRight1())
                {
                    //no//interrupts();
                    blockColumn1++;
                    updateDisplay1();
                    updateDisplay();
                    int next=ESP.getCycleCount()+fallRate*dixs;
                    // timer0_write(next);
                    //interrupts();
                }
            }
            
            if (strcmp("left1", (const char *)payload) == 0)  {
                
                //Serial.println("on va a droite");
                if(canMoveLeft1())
                {
                    //no//interrupts();
                    blockColumn1--;
                    updateDisplay1();
                    updateDisplay();
                    int next=ESP.getCycleCount()+fallRate*dixs;
                    //timer0_write(next);
                    //interrupts();
                }
            }
            if (strcmp("new", (const char *)payload) == 0)  {
                fill(bgColor);
                newGame();
            }
            
            if (strcmp("turnr1", (const char *)payload) == 0)  {
                
                if(canRotateRight1())
                {
                    //no//interrupts();
                    if(state1 == 3)
                        state1 = 0;  // state to the right of 3 is 0
                    else
                        state1++;
                    
                    updateDisplay1();
                    updateDisplay();
                    int next=ESP.getCycleCount()+fallRate*dixs;
                    //timer0_write(next);
                    //interrupts();
                }
                
            }
            
            
            if (strcmp("descend1", (const char *)payload) == 0)  {
                Serial.println("on va desc");
                
                Serial.println("on a topper timer");
                authdisplay=false;
                stopfall=true;
                while(canMoveDown1())
                {
                    blockRow1--;
                    Serial.println("on loop");
                    updateDisplay1();
                    updateDisplay();
                    authdisplay=false;
                    FastLEDshowESP32();
                    delay(10);
                    
                }
                
                //Serial.println("on a passer timer");
                authdisplay=false;
                stopfall=false;
                /* timer = timerBegin(0, 80, true);
                 timerAttachInterrupt(timer, &fall, true);
                 timerAlarmWrite(timer, 700000, true);
                 timerAlarmEnable(timer);*/
                
                int next=ESP.getCycleCount()+fallRate*dixs;
                // timer0_write(next);
                //interrupts();
            }
            
            
            if (strcmp("turnl1", (const char *)payload) == 0)  {
                
                if(canRotateLeft1())
                {
                    //no//interrupts();
                    if(state1 == 0)
                        state1 = 3;  // state to the right of 3 is 0
                    else
                        state1--;
                    
                    updateDisplay1();
                    updateDisplay();
                    int next=ESP.getCycleCount()+fallRate*dixs;
                    //   timer0_write(next);
                    //interrupts();
                }
                
            }
            
            
            
            
            
            
            
            
            else {
                // Serial.println("Unknown command");
            }
            // send data to all connected clients
            //webSocket.broadcastTXT(payload, length);
            break;
        case WStype_BIN:
            Serial.printf("[%u] get binary length: %u\r\n", num, length);
            //hexdump(payload, length);
            
            // echo data back to browser
            // webSocket.sendBIN(num, payload, length);
            break;
        default:
            Serial.printf("Invalid WStype [%d]\r\n", type);
            break;
    }
    if(!gamePaused)
        stopfall=false;
    else
        stopfall=true;
    authdisplay=true;
    timerStart(timer);
    //interrupts();
}





#endif /* tetris2_h */
