//
//  tetris.h
//  
//
//  Created by Yves BAZIN on 30/11/17.
//

#ifndef tetris3_h
#define tetris3_h





#define DISP_RIGHT   0
#define DISP_UP  1


/*
void initTetrisScoketControl();
void tetrisWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
void newGame();*/
int nbTetrisPlayer=1;
void speedUpFalling();
int displayNextPiecePos1=DISP_UP;

//int hauteur=25;//
int largeur=18;

bool authdisplay=false;

int score1=0;
CRGB *backgroundBlocks1;     //8 x 16 display + 4 x 8 blocks above for blocks to spawn in
CRGB *displayScreen1;
CRGB nextBlockImage1[12*4]; //je prends les deux premieres lignes du block
//CRGB TdisplayScreen1 [160];
CRGB *tertisScreen1;


//bool stopfall=false;
int TETRIS_HEIGHT=25;
int TETRIS_WIDTH=12;
CRGB shadow1[40*2*2]; //pour mettre le shadow1 de la piece
int TETRIS_X1=63;
int TETRIS_Y1=3;

int blockType1 ;                   //7 different block types
int nextblockType1; //to Display the next piece
int state1;                        //4 possible rotation state1s


bool displayshadow1=true;

/*
int blockType11 ;                   //7 different block types
int nextblockType11; //to Display the next piece
int state11;                        //4 possible rotation state1s

*/
/*
bool isInitiated=false;


int tetrisWebSocketPort=85;
long int fallinterval=1000000; // 1 seconde
volatile int interruptCounter;
int totalInterruptCounter;
*/
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

long int fallinterval=1000000;
bool isDisplayNextPiece1=false;
bool isDisplayscore1=false;

const int activeBlocks [28][4][4] = {
    {{0,0,1,0},    //     blockType1 + 7(state1)
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

int blockColumn1;             //the x value of the left most row in the 4x4 active block placeholder
int blockRow1;                //the y value of the bottom column in the 4x4 active block placeholder


int rowToBeDeleted1;
/*bool inGame = false;
bool justLost = false;
int brightness = 8;*/
long fallRate;
long dixs=80000*5;

//WebSocketsServer tetrisWebSocket = WebSocketsServer(tetrisWebSocketPort); //creating the entry for socket


void  combineArrays1()  //updates the displayScreen1 array by combining the current positions of the backgroundBlocks1 and the activeBlocks
{
    //first make an exact copy of the backgroundBlocks1
    // Serial.println("on combine");
    for(byte y = 0; y < TETRIS_HEIGHT; y++)
        for(byte x = 0; x < TETRIS_WIDTH; x++)
            displayScreen1[x+TETRIS_WIDTH*y] = backgroundBlocks1[x+TETRIS_WIDTH*y];
    
    //then add the non zero elements of the activeBlocks
    for(int i=0;i<4*TETRIS_WIDTH;i++)
    {
        shadow1[i]=bgColor;
    }
    for(int y = 0; y < 4; y++)
        for(int x = 0; x < 4; x++)
        {
            if(activeBlocks[blockType1 + (7 * state1)][y][x] > 0)
            {
                //   Serial.print("e:");
                //Serial.println(activeBlocks[blockType1 + (7 * state1)][x][y]);
                displayScreen1[x + blockColumn1+TETRIS_WIDTH*(y + blockRow1)] = paletblock[ activeBlocks[blockType1 + (7 * state1)][y][x] ];
                shadow1[(x + blockColumn1)*2]=paletblock[ activeBlocks[blockType1 + (7 * state1)][y][x] ];
                shadow1[(x + blockColumn1)*2+1]=paletblock[ activeBlocks[blockType1 + (7 * state1)][y][x] ];
                shadow1[(x + blockColumn1)*2+2*TETRIS_WIDTH]=paletblock[ activeBlocks[blockType1 + (7 * state1)][y][x] ];
                shadow1[(x + blockColumn1)*2+1+2*TETRIS_WIDTH]=paletblock[ activeBlocks[blockType1 + (7 * state1)][y][x] ];
            }
            
        }
}


void displayArray1()  // cycles through each pixel in displayScreen1 and outputs corresponding colour
{
    while(authdisplay){Serial.println("loop tetirs3");};
    
    authdisplay=false;
    //displaypic(displayScreen1,TETRIS_X1,TETRIS_Y1,TETRIS_HEIGHT,TETRIS_WIDTH);
    if(isDisplayNextPiece1)
    {
        int x=0;
        int y=0;
        switch (displayNextPiecePos1) {
            case DISP_UP:
                 x=2;
                y=(TETRIS_HEIGHT+1+TETRIS_Y1);
                break;
            case DISP_RIGHT:
                x=TETRIS_X1+2*TETRIS_WIDTH+2;
                y=TETRIS_Y1+2*TETRIS_HEIGHT-8;
                break;
            default:
                break;
        }
        displayPicNew(nextBlockImage1,x,y,6,8); //on ecrit la next piece
    }
    if(isDisplayscore1)
    {
        char chi[2];
        sprintf(chi, "%d", score1);
        //Serial.println(chi);
        //Serial.println(sizeof(chi)/sizeof(char));
        if(score1<10)
        {
            chi[1]=chi[0];
            chi[0]=0x0030;
            
        }
        char but[4];
        my_itoa(score1,but,10,3);
        afficheMessage2(but, TETRIS_X1+2*TETRIS_WIDTH+2,3);
       // afficheLettre((int)(chi[0])-32,TETRIS_X1+2*TETRIS_WIDTH+1,2);
        //afficheLettre((int)(chi[1])-32,TETRIS_X1+2*TETRIS_WIDTH+6, 2);
    }
    
    //on transpose les case de displayScreen1 un peu crade mais efficace
    
    for(int y=0;y<TETRIS_HEIGHT;y++)
        for(int x=0;x<TETRIS_WIDTH;x++)
        {
           // tertisScreen1[2*y*2*TETRIS_WIDTH+2*x]=displayScreen1[x+y*TETRIS_WIDTH];
           // tertisScreen1[(2*y+1)*2*TETRIS_WIDTH+2*x+1]=displayScreen1[x+y*TETRIS_WIDTH];
            tertisScreen1[2*y*2*TETRIS_WIDTH+2*x]=displayScreen1[x+y*TETRIS_WIDTH];
            tertisScreen1[2*y*2*TETRIS_WIDTH+2*x+1]=displayScreen1[x+y*TETRIS_WIDTH];
            tertisScreen1[(2*y+1)*2*TETRIS_WIDTH+2*x]=displayScreen1[x+y*TETRIS_WIDTH];
            tertisScreen1[(2*y+1)*2*TETRIS_WIDTH+2*x+1]=displayScreen1[x+y*TETRIS_WIDTH];
        }
   // fill(CRGB(10,10,10));
    displayPicNew(tertisScreen1,TETRIS_X1,TETRIS_Y1,2*TETRIS_HEIGHT,2*TETRIS_WIDTH);
    if(displayshadow1)
        displayPicNew(shadow1,TETRIS_X1,TETRIS_Y1-3,2,2*TETRIS_WIDTH);
    //authdisplay=true;
}



void updateDisplay1() // this function is called by a timer interupt every 10 milliseconds
{
    //Serial.println("on affiche");
    combineArrays1();
    
    
    
    
    // adds the latest position of the active block to the displayScreen1 Array
    //Serial.println("on display");
    displayArray1();
    //replaceled();
      // FastLEDshowESP32();
    //FastLED.show();// outputs the displayScreen1 Array
}


void resetArrays1()  // resets arrays to all zeros
{
    for(byte y = 0; y < TETRIS_HEIGHT; y++)
        for(byte x = 0; x < TETRIS_WIDTH; x++)
        {
            displayScreen1[x+TETRIS_WIDTH*y] = CRGB(0,0,0);
            backgroundBlocks1[x+TETRIS_WIDTH*y] =
            tertisScreen1[2*y*2*TETRIS_WIDTH+2*x]=CRGB(0,0,0);
            tertisScreen1[2*y*2*TETRIS_WIDTH+2*x+1]=CRGB(0,0,0);
            tertisScreen1[(2*y+1)*2*TETRIS_WIDTH+2*x]=CRGB(0,0,0);
           tertisScreen1[(2*y+1)*2*TETRIS_WIDTH+2*x+1]=CRGB(0,0,0);
            
          
        }   }


void fillNextBlock1(int blockType1)
{
    for(int y = 0; y < 3; y++)
        for(int x = 0; x < 4; x++)
        {
                nextBlockImage1[2*x +8*2*y] = paletblock2[ activeBlocks[blockType1 + (7 * 3)][y][x] ];
            nextBlockImage1[2*x +1+8*2*y] = paletblock2[ activeBlocks[blockType1 + (7 * 3)][y][x] ];
            nextBlockImage1[2*x +8*(2*y+1)] = paletblock2[ activeBlocks[blockType1 + (7 * 3)][y][x] ];
            nextBlockImage1[2*x+1 +8*(2*y+1)] = paletblock2[ activeBlocks[blockType1 + (7 * 3)][y][x] ];
        }
}

void newBlock1() //
{
    blockColumn1 = 2;
    blockRow1 = TETRIS_HEIGHT-3;
    blockType1=nextblockType1;
    nextblockType1 = random(7);// blockType1 is a random between 0 and 6 inclusive
    //Serial.println(blockType1);
    fillNextBlock1(nextblockType1);
    state1 = 3;     // reset state1 back to spawn block state1
}


bool canBeMoved1(int newCol, int newRow)  // return true if the there is empty pixels for the block to move in to
{
    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            if(activeBlocks[blockType1 + (7 * state1)][y][x] > 0)   // finds the positions of the non-blank blocks in the 4x4 matrix
            {
                int boardX = x + newCol;                            // calculates the corresponding x position on the display board
                int boardY = y + newRow;                            // calculates the corresponding y position on the display board
                //Serial.println(boardY);
                if(boardX < 0 ||  boardX > TETRIS_WIDTH-1 || boardY < 0)         // if the pixel is outside the boundaries of the board
                    return false;
                if(backgroundBlocks1[boardX+TETRIS_WIDTH*boardY] > CRGB(0,0,0))            // if the pixel is already full
                    return false;
            }
        }
    }
    return true;
}

bool canMoveDown1()   // row - 1
{
   if(blockRow1-1<0)
       Serial.println(blockRow1);
    
    if(canBeMoved1(blockColumn1, blockRow1 -1))
        return true;
    else
        return false;
}

bool canMoveLeft1()
{
    if(canBeMoved1(blockColumn1 - 1, blockRow1)) // column -1
        return true;
    else
        return false;
}

bool canMoveRight1()
{
    if(canBeMoved1(blockColumn1 + 1, blockRow1)) // column + 1
        return true;
    else
        return false;
}

bool canBeRotated1(int newstate1)
{
    for(int y = 0; y < 4; y++)
    {
        for(int x = 0; x < 4; x++)
        {
            if(activeBlocks[blockType1 + (7 * newstate1)][y][x] > 0) // finds the positions of the non-blank blocks in the 4x4 matrix
            {
                int boardX = x + blockColumn1;                        // calculates the corresponding x position on the display board
                int boardY = y + blockRow1;                           // calculates the corresponding y position on the display board
                if(boardX < 0 ||  boardX > TETRIS_WIDTH || boardY < 0)          // if the pixel is outside the boundaries of the board
                    return false;
                
                if(backgroundBlocks1[boardX+TETRIS_WIDTH*boardY] > CRGB(0,0,0))             // if the pixel is already full
                    return false;
            }
        }
    }
    return true;
}

bool canRotateLeft1()
{
    int nextstate1;
    if(state1 == 0)      // state1 to the left of 0 is 3
        nextstate1 = 3;
    else
        nextstate1 = state1 - 1;
    
    if(canBeRotated1(nextstate1))
        return true;
    else
        return false;
}

bool canRotateRight1()
{
    int nextstate1;
    if(state1 == 3)      // state1 to the right of 3 is 0
        nextstate1 = 0;
    else
        nextstate1 = state1 + 1;
    
    if(canBeRotated1(nextstate1))
        return true;
    else
        return false;
}

void moveActiveBlocksToBackground1()
{
    combineArrays1(); //updated the display array
    
    for(byte y = 0; y < TETRIS_HEIGHT; y++)
        for(byte x = 0; x < TETRIS_WIDTH; x++)
            backgroundBlocks1[x+TETRIS_WIDTH*y] = displayScreen1[x+TETRIS_WIDTH*y];    // copy the displayScreen1 to the backgroundBlocks1
}

bool rowIsFull1()                // goes through all 16 rows and checks if they are full
{
    for(byte y = 0; y < TETRIS_HEIGHT; y++)
    {
        bool isfull=true;
        for(byte x=0;x<TETRIS_WIDTH;x++)
        {
            if( backgroundBlocks1[TETRIS_WIDTH*y+x] ==CRGB(0,0,0)  )
                isfull= false;
        }
        if(isfull)
        {
            Serial.println("on efface la ligne");
            rowToBeDeleted1 = y;      // the row is returned as a global variable
            return true;
        }
    }
    return false;
}

void deleteRow1()
{
    score1++;
    
    if(rowToBeDeleted1==TETRIS_HEIGHT-1)
    {
        for(byte x = 0; x < TETRIS_WIDTH; x++)
            backgroundBlocks1[x+TETRIS_WIDTH*(TETRIS_HEIGHT-1)] = CRGB(0,0,0);
    }
    else
    {
       // Serial.print("On efface ligne:");
       // Serial.println(rowToBeDeleted1);
        for(byte y = rowToBeDeleted1; y < TETRIS_HEIGHT-1; y++)
            for(byte x = 0; x < TETRIS_WIDTH; x++)
                backgroundBlocks1[x+TETRIS_WIDTH*y] = backgroundBlocks1[x+TETRIS_WIDTH*(y + 1)];  // replaces row with row above

    }
    
}



void deleteFullRows1()
{
    for(int i = 0; i < 4; i++) // checking 4 times if there are full rows to be deleted
    {
        if(rowIsFull1())
        {
            deleteRow1();
            speedUpFalling();
        }
    }
}

bool spaceFornewBlock1()  // returns true if there is space for the new block to be spawned at the top of the matrix
{
    if(canBeMoved1(2, TETRIS_HEIGHT-3))
        return true;
    else
        return false;
}




void speedUpFalling()
{
    //timerStop(timer1);
    timerAlarmDisable(timer);
    
    if(fallinterval > 50000)   // to stop fallRate decreasing to zero
        fallinterval -= 50000;   // blocks falling speeds up by 50000 nanoseconds every full row made
    timerAlarmWrite(timer, fallinterval, true);
    timerAlarmEnable(timer);
    
}
 /*
void fillScreenT()       // fills pixels one at a time with green at the end of the game one at a time starting from the top
{
    for(int y = 0; y <TETRIS_HEIGHT; y++)
    {
        for(int x = 0; x < TETRIS_WIDTH; x++)
        {
            displayScreen1[x+TETRIS_WIDTH*y] = CRGB(0,100,0);    // turns the pixel green

        }
        displayArray1();
        FastLED.show();// outputs the pixel change to the screen
        FastLED.delay(30);
    }
}


void IRAM_ATTR fall()               // this function is called by a timer interupt every fallRate nanoseconds
{
    if(stopfall)
        return;
    Serial.println("on fal");
   // portENTER_CRITICAL_ISR(&timerMux);
    ////no//interrupts();
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
            authdisplay=true;
            char mess[]="TU AS PERDU";
            afficheMessage2(mess,3,20);
            inGame = false;
            justLost = true;
            
            delay(3000);
            authdisplay=false;
            newGame();
            return;
        }
    }
    //portEXIT_CRITICAL_ISR(&timerMux);
    updateDisplay();
    long    next=ESP.getCycleCount() +  fallRate*dixs;
    //timer0_write(next);
    
    ////interrupts();
    //yield();
}

*/
/*void IRAM_ATTR fall()               // this function is called by a timer interupt every fallRate nanoseconds
{
    Serial.println("on fal");
}
*/



/*


bool initTetris()
{
    if(true)
    {
        if(tableOrientation%2==0)
        {
            displayNextPiecePos1=DISP_RIGHT;
            isDisplayscore1=true;
            isDisplayNextPiece=true;
            TETRIS_WIDTH=15;
            TETRIS_HEIGHT=22;
        }
        else
        {
            displayNextPiecePos1=DISP_UP;
            isDisplayscore1=false;
            isDisplayNextPiece=true;
            TETRIS_WIDTH=15;
            TETRIS_HEIGHT=22;
        }
        backgroundBlocks1 =(CRGB*)malloc(TETRIS_WIDTH*TETRIS_HEIGHT*sizeof(CRGB)) ;
        displayScreen1 =(CRGB*)malloc(TETRIS_WIDTH*TETRIS_HEIGHT*sizeof(CRGB)) ;
        tertisScreen1=(CRGB*)malloc(4*TETRIS_WIDTH*TETRIS_HEIGHT*sizeof(CRGB)) ;
        
        resetArrays1();
        if(!backgroundBlocks1 && !displayScreen1)
        {
            Serial.println("Unable to create the screens");
            isInitiated=false;
            return false;
        }
        Serial.println("Tetris créé");
        isInitiated=true;
        server.serveStatic("/tetris.html", SPIFFS, "/tetris.html"); //on ajoute le lien vers tetris
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


void newGame()
{
    inGame = true;
    justLost = false;
    score1=0;
    fallRate=200;
    isInitiated=true;
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
        resetArrays1();
        randomSeed(ESP.getCycleCount());
        nextblockType1 = random(7); //on initie le next block type
        newBlock1();
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
     timerStop(timer);
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
               if (strcmp("up", (const char *)payload) == 0)  {
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
 
            if (strcmp("right", (const char *)payload) == 0)  {
                
                // Serial.println("on va a droite");
                if(canMoveRight1())
                {
                    //no//interrupts();
                    blockColumn1++;
                    updateDisplay();
                    int next=ESP.getCycleCount()+fallRate*dixs;
                   // timer0_write(next);
                    //interrupts();
                }
            }
            
            if (strcmp("left", (const char *)payload) == 0)  {
                
                //Serial.println("on va a droite");
                if(canMoveLeft1())
                {
                    //no//interrupts();
                    blockColumn1--;
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
            
            if (strcmp("turnr", (const char *)payload) == 0)  {
                
                if(canRotateRight1())
                {
                    //no//interrupts();
                    if(state1 == 3)
                        state1 = 0;  // state1 to the right of 3 is 0
                    else
                        state1++;
                    
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
                while(canMoveDown1())
                {
                    blockRow1--;
                    Serial.println("on loop");
                    updateDisplay();
                    authdisplay=false;
                    FastLEDshowESP32();
                    delay(10);

                }
                
                 //Serial.println("on a passer timer");
                authdisplay=false;
                stopfall=false;
               timer = timerBegin(0, 80, true);
                timerAttachInterrupt(timer, &fall, true);
                timerAlarmWrite(timer, 700000, true);
                timerAlarmEnable(timer);
                
                int next=ESP.getCycleCount()+fallRate*dixs;
               // timer0_write(next);
                //interrupts();
            }
            
            
            if (strcmp("turnl", (const char *)payload) == 0)  {
                
                if(canRotateLeft1())
                {
                    //no//interrupts();
                    if(state1 == 0)
                        state1 = 3;  // state1 to the right of 3 is 0
                    else
                        state1--;
                    
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
    timerStart(timer);
    //interrupts();
}


*/


#endif /* tetris3_h */
