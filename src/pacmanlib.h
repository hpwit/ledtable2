//
//  pacmanlib.h
//  
//
//  Created by Yves BAZIN on 18/03/18.
//

#ifndef pacmanlib_h
#define pacmanlib_h

#define PACMAN_WIDTH 28
#define PACMAN_HEIGHT 31
#include "barpc.h"
//unsigned char pacboardfull[123];

void initPacmanSocketControl();
void pacmanWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
bool initPacman();
void newPacman();
void executePacmanSocketControl();

void newFoodPosition();
void displayarray();
//void IRAM_ATTR movePacman();
void  movePacman();
//void IRAM_ATTR moveGhosts();
void displayPacman();
int PacmanWebSocketPort=90;
bool inPacman=false;
bool PacmanInitiated=false;
//int pacmanInterval;
int followupPath=0;
int gohstInterval;
int pacmanScore;
int directionpac=0;
int pacmanFace=0;
bool resetpossible=true;
bool incalcul=false;
bool updatepossible=true;
uint32_t pacmanInterval=3000;
byte facestuff=0;
WebSocketsServer PacmanWebSocket = WebSocketsServer(PacmanWebSocketPort);

void calculpacboard();

struct node{
    byte x,y;
    long cost;
    long pathlength;
    byte px,py;
    byte pax,pay;
    node *path;
    int followupPath;
    int shortpathlength;
};
struct directionst{
    int vx,vy;
};

directionst blinkyDirection;
node openList[100];
node closedList[100];
//node shortpath[300];
node shortpathBlinky[70];
node shortpathClyde[70];
node shortpathPinky[70];
//node shortpath[300];
//node shortpath[300];
int shortpathlength=0;
int openListSize=0;
int closedListSize=0;
 node pacmanPosition,Blinky,Pinky,Inky,Clyde,targetPacmanPosition,targetBlinky;
 directionst pacmanDirection;
bool isPacmanMoving=false;

int decalDisplay=0;
bool isFreeTile(struct node n);
long calculCost(struct node  n);
int offsetDisplayBoard;
 void ghostDirection(struct node n);
volatile int value=0;
struct directionst finalDirection={0,0};
volatile int finvx,finvy;
//hw_timer_t * timerPacman = NULL;
//hw_timer_t * timerGhost = NULL;
//portMUX_TYPE timerPacmanMux = portMUX_INITIALIZER_UNLOCKED;
volatile int Blinkypx;
//int finvy,finvx;
void addInOpenList(node n);
void addInClosedList(node n);
bool isInOpenList(node n);
bool isInClosedList(node n);
void emptyClosedList();
void emptyOpenList();


void emptyOpenList()
{
    resetpossible=false;
    while(incalcul){}
    openListSize=0;
    resetpossible=true;
}


void emptyClosedList()
{
    resetpossible=false;
    while(incalcul){}
    closedListSize=0;
    resetpossible=true;
}
void addInOpenList(node n)
{
    openList[openListSize]=n;
    openListSize++;
}

void addInClosedList(node n)
{
    closedList[closedListSize]=n;
    closedListSize++;
}

bool isInOpenList(node n)
{
   
    for(int i=0;i<openListSize;i++)
    {
        node p=openList[i];
        if (n.x==p.x and n.y==p.y)
            return true;
    }
    return false;
}


bool isInShortPath(node target,node n)
{
    
    for(int i=0;i<target.followupPath+1;i++)
    {
        node p=target.path[i];
        if (n.x==p.x and n.y==p.y)
            return true;
    }
    return false;
}

bool isInClosedList(node n)
{
    
    for(int i=0;i<closedListSize;i++)
    {
        node p=closedList[i];
        if (n.x==p.x and n.y==p.y)
            return true;
    }
    return false;
}
/*
int boardpiece[16*15]=
{
    1,2,9,9,
    1,2,9,9,
    1,2,9,9,
    1,2,9,9,
    
    9,9,2,1,
    9,9,2,1,
    9,9,2,1,
    9,9,2,1,
 
    9,9,9,9,
    9,9,9,9,
    9,9,9,2,
    9,9,2,1,
   
    9,9,2,1,
    9,9,9,2,
    9,9,9,9,
    9,9,9,9,
   
    1,2,9,9,
    1,2,9,9,
    1,1,2,2,
    1,1,1,1,
    
    1,1,1,1,
    1,1,2,2,
    1,2,9,9,
    1,2,9,9,

    9,9,9,9,
    9,3,3,9,
    9,3,3,9,
    9,9,9,9,
    
    1,1,1,1,
    2,2,2,2,
    9,9,9,9,
    9,9,9,9,
  
    9,9,9,9,
    9,9,9,9,
    2,2,2,2,
    1,1,1,1,
   
    9,9,9,9,
    9,9,9,9,
    2,9,9,9,
    1,2,9,9,
    
    1,2,9,9,
    2,9,9,9,
    9,9,9,9,
    9,9,9,9,
    
    9,9,2,1,
    9,9,2,1,
    2,2,1,1,
    1,1,1,1,
    
    1,1,1,1,
    2,2,1,1,
    9,9,2,1,
    9,9,2,1,

    9,3,3,9,
    3,3,3,3,
    3,3,3,3,
    9,3,3,9,
    
    9,9,9,9,
    9,9,9,9,
    9,9,9,9,
    9,9,9,9,
    
};*/

//CRGB boardpieceRGB[16*14];

int pacboard[28*31]
{
     6, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8,13,
     1,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 2,
     1,15, 3, 9, 9, 9, 9, 9, 9, 9, 9,10,15, 3,10,15, 3, 9, 9, 9, 9, 9, 9, 9, 9,10,15, 2,
     1,15, 4, 8, 8, 8, 8,13, 6, 8, 8,11,15, 2, 1,15, 4, 8, 8,13, 6, 8, 8, 8, 8,11,15, 2,
     1,15,15,15,15,15,15, 2, 1,15,15,15,15, 2, 1,15,15,15,15, 2, 1,15,15,15,15,15,15, 2,
     5, 9,10,15, 3,10,15, 2, 1,15, 3, 9, 9,12, 5, 9, 9,10,15, 2, 1,15, 3,10,15, 3, 9,12,
    
     6, 8,11,15, 2, 1,15, 4,11,15, 4, 8, 8, 8, 8, 8, 8,11,15, 4,11,15, 2, 1,15, 4, 8,13,
     1,15,15,15, 2, 1,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 2, 1,15,15,15, 2,
     1,15, 3, 9,12, 1,15, 3, 9, 9, 9,10,15, 3,10,15, 3, 9, 9, 9,10,15, 2, 5, 9,10,15, 2,
     1,15, 4, 8, 8,11,15, 4, 8, 8, 8,11,15, 2, 1,15, 4, 8, 8, 8,11,15, 4, 8, 8,11,15, 2,
     1,15,15,15,15,15,15,15,15,15,15,15,15, 2, 1,15,15,15,15,15,15,15,15,15,15,15,15, 2,
     5, 9, 9, 9, 9,10,15, 3,10,15, 3, 9, 9,12, 5, 9, 9,10,15, 3,10,15, 3, 9, 9, 9, 9,12,
    
    
    15,15,15,15,15, 1,15, 2, 1,15, 4, 8, 8, 8, 8, 8, 8,11,15, 2, 1,15, 2,15,15,15,15,15,
    15,15,15,15,15, 1,15, 2, 1,15,15,15,15,15,15,15,15,15,15, 2, 1,15, 2,15,15,15,15,15,
    15,15,15,15,15, 1,15, 2, 1,15, 3, 9, 9, 9, 9, 9, 9,10,15, 2, 1,15, 2,15,15,15,15,15,
     8, 8, 8, 8, 8,11,15, 4,11,15, 2,15,15,15,15,15,15, 1,15, 4,11,15, 4, 8, 8, 8, 8, 8,
    15,15,15,15,15,15,15,15,15,15, 2,15,15,15,15,15,15, 1,15,15,15,15,15,15,15,15,15,15,
     9, 9, 9, 9, 9,10,15, 3,10,15, 2,15,15,15,15,15,15, 1,15, 3,10,15, 3, 9, 9, 9, 9, 9,
    
    15,15,15,15,15, 1,15, 2, 1,15, 4, 8, 8, 8, 8, 8, 8,11,15, 2, 1,15, 2,15,15,15,15,15,
    15,15,15,15,15, 1,15, 2, 1,15,15,15,15,15,15,15,15,15,15, 2, 1,15, 2,15,15,15,15,15,
    15,15,15,15,15, 1,15, 2, 5, 9, 9,10,15, 3,10,15, 3, 9, 9,12, 1,15, 2,15,15,15,15,15,
     6, 8, 8, 8, 8,11,15, 2, 6, 8, 8,11,15, 2, 1,15, 4, 8, 8,13, 1,15, 4, 8, 8, 8, 8,13,
     1,15,15,15,15,15,15, 2, 1,15,15,15,15, 2, 1,15,15,15,15, 2, 1,15,15,15,15,15,15, 2,
     1,15, 3, 9, 9,10,15, 2, 1,15, 3, 9, 9,12, 5, 9, 9,10,15, 2, 1,15, 3, 9, 9,10,15, 2,
    
     1,15, 4, 8, 8,11,15, 4,11,15, 4, 8, 8, 8, 8, 8, 8,11,15, 4, 11,15,4, 8, 8,11,15, 2,
     1,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15, 2,
     1,15, 3, 9, 9,10,15, 3, 9, 9, 9,10,15, 3,10,15, 3, 9, 9, 9,10,15, 3, 9, 9,10,15, 2,
     1,15, 2,15,15, 1,15, 2,15,15,15, 1,15, 2, 1,15, 2,15,15,15, 1,15, 2,15,15, 1,15, 2,
     1,15, 4, 8, 8,11,15, 4, 8, 8, 8,11,15, 2, 1,15, 4, 8, 8, 8,11,15, 4, 8, 8,11,15, 2,
     1,15,15,15,15,15,15,15,15,15,15,15,15, 2, 1,15,15,15,15,15,15,15,15,15,15,15,15, 2,
     5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,12, 5, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,12
    
    
    
};

CRGB palepac[5]={CRGB::Black,CRGB::Blue,CRGB(255,0,255),CRGB::Yellow};

CRGB *boardpacman;


void displayPacman()
{
    //on va calculer l'offset du board
    decalDisplay=pacmanPosition.py-LED_WIDTH/2;
    if(decalDisplay<0)
    {
        
    }
    else
        decalDisplay=0;
    displayBitmapFromProgmem(pacboardfull,1,decalDisplay,31*4,112);
    displaygifdir(pacmancalc,pacmanPosition.px+1,pacmanPosition.py-decalDisplay,8,8,pacmanFace,directionpac);
    displayPicNew(ghostpc,Blinky.px+1,Blinky.py-decalDisplay,8,9);
    replaceled();
    
    
}

bool isFreeTile(struct node n)
{
    if(pacboard[n.x+n.y*PACMAN_WIDTH]==15)
        return true;
    else
        return false;
}
void addvoisins(node n)
{
    
}

node getParent(node n)
{
    node r;
    r.x=0;
    r.y=0;
    for(int i=0;i<closedListSize;i++)
    {
        node p=closedList[i];
        if (n.pax==p.x and n.pay==p.y)
            return p;
    }
    return  r;
}

int getNode(node n)
{
    node r;
    r.x=0;
    r.y=0;
    for(int i=0;i<openListSize;i++)
    {
        node p=openList[i];
        if (n.x==p.x and n.y==p.y)
            return i;
    }
    return  0;
}


node newMinimumNode()
{
    long score=9999999999;
    int minnode=0;
    for(int i=0;i<openListSize;i++)
    {
         node p=openList[i];
        if(score>p.cost+p.pathlength)
        {
            minnode=i;
            score=p.cost+p.pathlength;
        }
        
    }
   // Serial.printf("found in %d\n",minnode);
    return openList[minnode];
}

void calculpath(node *start, node target)
{
    resetpossible=false; //do not touch the gohjst
    emptyClosedList();
    emptyOpenList();
    node n;
    n.x=start->x;
    n.y=start->y;
    n.pax=0;
    n.pay=0;
    n.pathlength=0;
   // addInOpenList(n);
    addInClosedList(n);
    while(!isInClosedList(target))
    {
        //on ajoute les voisins
        //Serial.printf("ici %d %d\n",n.x,n.y);
        
        node n1;
        n1.x=n.x+1;
        n1.y=n.y;
        n1.pax=n.x;
        n1.pay=n.y;
       // Serial.println("right %d\n",pacboard[n1.x+1+n1.y*PACMAN_WIDTH]);
        if(!isInClosedList(n1) and  pacboard[n1.x+n1.y*PACMAN_WIDTH]==15 )
        {
            //Serial.println("add right");
            n1.cost=calculCost(n1);  //distance from pacman
            n1.pathlength=getParent(n1).pathlength+1;
            
            if(isInOpenList(n1))
            {
               // Serial.println("on remplace");
                int g=getNode(n1);
                if(openList[g].cost+openList[g].pathlength>n1.cost+n1.pathlength)
                    openList[g]=n1;
            }
            else
                addInOpenList(n1);
        }
   
        n1.x=n.x-1;
        n1.y=n.y;
        n1.pax=n.x;
        n1.pay=n.y;
        //Serial.println("right %d\n",pacboard[n1.x+1+n1.y*PACMAN_WIDTH]);
        if(!isInClosedList(n1) and  pacboard[n1.x+n1.y*PACMAN_WIDTH]==15)
        {
            //Serial.println("add left");
            n1.cost=calculCost(n1);  //distance from pacman
            n1.pathlength=getParent(n1).pathlength+1;
            
            if(isInOpenList(n1))
            {
                //Serial.println("on remplace");
                int g=getNode(n1);
                if(openList[g].cost+openList[g].pathlength>n1.cost+n1.pathlength)
                    openList[g]=n1;
            }
            else
                addInOpenList(n1);
        }
        
        n1.x=n.x;
        n1.y=n.y-1;
        n1.pax=n.x;
        n1.pay=n.y;
        if(!isInClosedList(n1) and  pacboard[n1.x+n1.y*PACMAN_WIDTH]==15)
        {
          // Serial.println("add down");
            n1.cost=calculCost(n1);  //distance from pacman
            n1.pathlength=getParent(n1).pathlength+1;
            
            if(isInOpenList(n1))
            {
               // Serial.println("on remplace");
                int g=getNode(n1);
                if(openList[g].cost+openList[g].pathlength>n1.cost+n1.pathlength)
                    openList[g]=n1;
            }
            else
                addInOpenList(n1);
        }

        n1.x=n.x;
        n1.y=n.y+1;
        n1.pax=n.x;
        n1.pay=n.y;
        if(!isInClosedList(n1) and  pacboard[n1.x+n1.y*PACMAN_WIDTH]==15)
        {
            //Serial.println("add up");
            n1.cost=calculCost(n1);  //distance from pacman
            n1.pathlength=getParent(n1).pathlength+1;
            
            if(isInOpenList(n1))
            {
              //  Serial.println("on remplace");
                int g=getNode(n1);
                if(openList[g].cost+openList[g].pathlength>n1.cost+n1.pathlength)
                    openList[g]=n1;
            }
            else
                addInOpenList(n1);
        }
        
    
        n=newMinimumNode();
        //Serial.printf("minium node %d %d out of %d\n",n.x,n.y,openListSize);
        node k;
        k.x=255;
        k.y=255;
        k.cost=9999999999;
        k.pathlength=999999999999;
       // Serial.printf("node %d\n",getNode(n));
        openList[getNode(n)]=k;
        addInClosedList(n);
        
    }
    node p;
    int i=0;
    start->shortpathlength=0;
    while(n.x!=start->x or n.y!=start->y)
    {
        start->path[start->shortpathlength]=n;
        n=getParent(n);
        start->shortpathlength++;
    }
    
    
    //Serial.printf("done %d\n",start->shortpathlength);
    start->followupPath=start->shortpathlength-1;
    //displayarray();
    resetpossible=true;
}


void ghostDirection( struct node n)
{
    long costmoin=999999;
    struct node voisin;
    struct directionst fin;
   // int finvx,finvy;
    value=0;
    finvx=0;
    finvy=0;
      //we get the cell around it
    //above
    
    incalcul=true;
    
    
 
    if( pacboard[n.x+(n.y+1)*PACMAN_WIDTH]==15 ) //on peut se déplacer sur la cellule
    {
        voisin.x=n.x;
        voisin.y=n.y+1;
        if(!isInClosedList(voisin))
            if(costmoin>=calculCost(voisin))
            {
                //voisin.x=n.x;
                //voisin.y=n.y;
             //  finalDirection.vx=0;
               //finalDirection.vy=1;
                finvx=0;
                finvy=1;
                value=1;
                costmoin=calculCost(voisin);
                
            }
    }
 
    if( pacboard[n.x+(n.y-1)*PACMAN_WIDTH]==15 ) //on peut se déplacer sur la cellule
    {
        voisin.x=n.x;
        voisin.y=n.y-1;
        if(!isInClosedList(voisin))
            if(costmoin>=calculCost(voisin))
            {
                finvx=0;
                finvy=-1;
                value=2;
                costmoin=calculCost(voisin);
            }
        
    }

   
    
    
    byte newx=0;
    if (n.x==27)
        newx=0;
    else
        newx=n.x+1;
    if( pacboard[newx+n.y*PACMAN_WIDTH]==15 ) //on peut se déplacer sur la cellule
    {
        
        voisin.x=newx;
        
        voisin.y=n.y;
        if(!isInClosedList(voisin))
            if(costmoin>=calculCost(voisin))
            {
                finvx=1;
                finvy=0;
                value=3;
                 costmoin=calculCost(voisin);
                
            }
       
    }
    byte newx2=0;
    if (n.x==0)
        newx2=27;
    else
        newx2=n.x-1;
    if( pacboard[newx2+n.y*PACMAN_WIDTH]==15 ) //on peut se déplacer sur la cellule
    {
        
        voisin.x=newx2;
        
        voisin.y=n.y;
        if(!isInClosedList(voisin))
            if(costmoin>=calculCost(voisin))
            {
                finvx=-1;
                finvy=0;
                value=4;
                 costmoin=calculCost(voisin);
            }
       
    }
    //return value;
    //finalDirection.vx=finvx;
    //finalDirection.vy=finvy;
     incalcul=false;
    switch(value)
    {
        case 1:
            voisin.x=n.x;
            voisin.y=n.y+1;
            addInClosedList(voisin);
        break;

        case 2:
            voisin.x=n.x;
            voisin.y=n.y-1;
            addInClosedList(voisin);
            break;

        case 3:
            voisin.x=newx;
            voisin.y=n.y;
            addInClosedList(voisin);
            break;
            
        case 4:
            voisin.x=newx2;
            voisin.y=n.y;
            addInClosedList(voisin);
            break;
            
            
    }
   
    
}

long calculCost(struct node n)
{
    return  abs(targetPacmanPosition.x-n.x)+abs(targetPacmanPosition.y-n.y); //(targetPacmanPosition.x-n.x)*(targetPacmanPosition.x-n.x)+(targetPacmanPosition.y-n.y)*(targetPacmanPosition.y-n.y);
}


/*
void calculpacboard()
{
   
    boardpacman =(CRGB*)malloc(28*31*3*16) ;
    CRGB bitmapRGB[16] ;
    fill(CRGB::Black);
     calculpic(boardpiece, palepac, CRGB(0,0,0),15,16,boardpieceRGB);
    //int offx=2;
     Serial.println("Debut du map mario");
    for (long i=0;i<31;i++)
    {
        for (int j=0;j<28;j++)
        {
            //displaygif(boardpieceRGB,4*j,4*i,4,4,pacboard[j+i*28]-1);
            
 
            memcpy ( bitmapRGB, boardpieceRGB+(16*(pacboard[j+i*28]-1)), 16*sizeof(CRGB) );
            for(int l=0;l<4;l++)
            {
                for(int k=0;k<4;k++)
                {
                    boardpacman[4*j+k+(4*i+l)*28*4]=bitmapRGB[k+4*l];
                }
            }
            
        }
    }
    for(long j=0;j<31*4;j++)
    {
        for(long i=0;i<28*4;i++)
        {
            Serial.printf("%d,%d,%d, ",boardpacman[i+j*28*4].r,boardpacman[i+j*28*4].g,boardpacman[i+j*28*4].b);
        }
        Serial.println();
    }
 Serial.println("fin du map mario");
    //free(bitmapRGB);
    free(boardpacman);
     //memcpy ( boardpacman, leds, 28*26*3 *16);
}


 */


         
         
 
void initPacmanSocketControl()
 {
     PacmanWebSocket.begin();
     PacmanWebSocket.onEvent(pacmanWebSocketEvent);
 }
    
    void executePacmanSocketControl()
 {
     PacmanWebSocket.loop();
     
 }
        
            
            
            
bool initPacman()
{
 if(isTable)
 {
     server.serveStatic("/Pacman.html", SPIFFS, "/Pacman.html"); //on ajoute le lien vers
     //server.serveStatic("/image.css", SPIFFS, "/image.css"); //on ajoute le lien vers
     initPacmanSocketControl();
     PacmanInitiated=true;
     Serial.println("Pacman cree");
     return true;
     
 }
 else{
     Serial.println("No table existing create the table first");
     PacmanInitiated=false;
     return false;
 }
}
        
            
            
void newPacman()
 {
     
     Serial.println("voici Pacman");// clears the red display matrix
     if(!PacmanInitiated)
     {
         Serial.println("on cree la base fait");
         initPacman();
         
     }
     
     //on reset le tableau des Pacmans

     decalDisplay=0; //on repmace l'affichage en bas;
     pacmanPosition.x=5;
     pacmanPosition.y=1;
     pacmanPosition.px=pacmanPosition.x*4-2;
     pacmanPosition.py=pacmanPosition.y*4-2;
     
     pacmanDirection.vx=0;
     pacmanDirection.vy=0;
     //finvx=0;
    // finvy=0;
     
     targetPacmanPosition.x=pacmanPosition.x;
     targetPacmanPosition.px=pacmanPosition.px;
     targetPacmanPosition.py=pacmanPosition.py;
     targetPacmanPosition.y=pacmanPosition.y;
     
    // targetPacmanPosition
     Blinky.x=26;
     Blinky.y=29;
     Blinky.px=(Blinky.x*4-2);
     Blinky.py=(Blinky.y*4-2);
     Blinky.path=shortpathBlinky;
     blinkyDirection.vx=0;
     blinkyDirection.vy=0;
     Clyde.x=1;
     Clyde.y=29;
     Clyde.px=(Clyde.x*4-2);
     Clyde.py=(Clyde.y*4-2);
     Clyde.path=shortpathClyde;

     Pinky.x=13;
     Pinky.y=29;
     Pinky.px=(Pinky.x*4-2);
     Pinky.py=(Pinky.y*4-2);
     Pinky.path=shortpathPinky;
     isPacmanMoving=false;

     inPacman=true;
     //fill(CRGB(0,0,0));
     pacmanInterval=90000;
     gohstInterval=320000;
     //timerPacman = timerBegin(0, 80, true);
     //timerAttachInterrupt(timerPacman, &movePacman, true);
     //timerAlarmWrite(timerPacman, pacmanInterval, true);
     //timerAlarmEnable(timerPacman);
     //timerGhost = timerBegin(1, 80, true);
     //timerAttachInterrupt(timerGhost, &moveGhosts, true);
    // timerAlarmWrite(timerGhost, gohstInterval, true);
     //timerAlarmEnable(timerGhost);
     pacmanScore=0;
     randomSeed(ESP.getCycleCount()); //create a new seed
     //FastLED.show();
     
 }
    
            
            
            
void pacmanWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    //timerStop(timerGhost);
    //timerStop(timerPacman);
    switch(type) {
        case WStype_DISCONNECTED:
            // USE_SERIAL.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED:
        {
            IPAddress ip = PacmanWebSocket.remoteIP(num);
            Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
            
            // send message to client
            PacmanWebSocket.sendTXT(num, "Connected");
        }
            break;
        case WStype_TEXT:
            // USE_SERIAL.printf("[%u] get Text: %sdd\n", num, payload);
            if (strcmp("UP", (const char *)payload) == 0)  {
                
                //if(pacy<LED_HEIGHT/2-5)
                // pacy++;
                //Serial.println("UP");
                struct node d;
                d.x=pacmanPosition.x;
                d.y=pacmanPosition.y+1;
                if(isFreeTile(d))
                {
                    pacmanDirection.vx=0;
                    pacmanDirection.vy=+1;
                    targetPacmanPosition.y=pacmanPosition.y+1;
                    directionpac=2;
                    emptyClosedList();
                    calculpath(&Blinky,targetPacmanPosition);
                   // calculpath(&Clyde,targetPacmanPosition);
                    //calculpath(&Pinky,targetPacmanPosition);
                    //calculpath(Blinky,targetPacmanPosition);
                }
               // movePacman();
                
                
            }
            if (strcmp("DOWN", (const char *)payload) == 0)  {
                //             if(pacy>0)
                //pacy--;
                // Serial.println("on va a droite");
                //Serial.println("DOWN");
                struct node d;
                d.x=pacmanPosition.x;
                d.y=pacmanPosition.y-1;
                if(isFreeTile(d))
                {
                    pacmanDirection.vx=0;
                    pacmanDirection.vy=-1;
                    targetPacmanPosition.y=pacmanPosition.y-1;
                    directionpac=4;
                    emptyClosedList();
                    calculpath(&Blinky,targetPacmanPosition);
                   // calculpath(&Clyde,targetPacmanPosition);
                   // calculpath(&Pinky,targetPacmanPosition);
                    //calculpath(Blinky,targetPacmanPosition);
                }
               /// movePacman();
                
            }
            if (strcmp("RIGHT", (const char *)payload) == 0)  {
                //if(pacx<LED_WIDTH-5)
                // pacx++;
                
                struct node d;
                d.x=pacmanPosition.x+1;
                d.y=pacmanPosition.y;
                if(isFreeTile(d))
                {
                    //Serial.println("on va a droite");
                    pacmanDirection.vx=1;
                    pacmanDirection.vy=0;
                  //  if(pacmanPosition=PACMAN_WIDTH-1)
                   //     targetPacmanPosition.x=0;
                   // else
                        targetPacmanPosition.x=pacmanPosition.x+1;
                    directionpac=1;
                    emptyClosedList();
                    calculpath(&Blinky,targetPacmanPosition);
                   // calculpath(&Clyde,targetPacmanPosition);
                   // calculpath(&Pinky,targetPacmanPosition);
                    //calculpath(Blinky,targetPacmanPosition);
                }
                //movePacman();
            }
            if (strcmp("LEFT", (const char *)payload) == 0)  {
                
                // Serial.println("on va a droite");
                //if(pacx>0)
                // pacx--;
                
                struct node d;
                d.x=pacmanPosition.x-1;
                d.y=pacmanPosition.y;
                if(isFreeTile(d))
                {
                   // Serial.println("LEFT");
                    pacmanDirection.vx=-1;
                    pacmanDirection.vy=0;
                    targetPacmanPosition.x=pacmanPosition.x-1;
                    directionpac=3;
                    emptyClosedList();
                    calculpath(&Blinky,targetPacmanPosition);
                   // calculpath(&Clyde,targetPacmanPosition);
                   // calculpath(&Pinky,targetPacmanPosition);
                    //calculpath(Blinky,targetPacmanPosition);
                }
              //  movePacman();
            }
            // send message to client
            // webSocket.sendTXT(num, "message here");
            
            // send data to all connected clients
            // webSocket.broadcastTXT("message here");
            break;
        case WStype_BIN:
            Serial.printf("[%u] get binary length: %u\n", num, length);
            // hexdump(payload, length);
            
            // send message to client
            // webSocket.sendBIN(num, payload, length);
            break;
    }
   // timerStart(timerGhost);
    //timerStart(timerPacman);
}
 

 //void IRAM_ATTR movePacman()
void  movePacman()
{
     if(facestuff==0)
     {
         targetBlinky=Blinky.path[Blinky.followupPath];
         blinkyDirection.vx=targetBlinky.x-Blinky.x;
         blinkyDirection.vy=targetBlinky.y-Blinky.y;
         Blinky.followupPath--;
     }
     if(pacmanDirection.vx!=0) //we move horizionatally
     {
         if((pacmanPosition.px+2)%4>0)
         {
             pacmanPosition.px+=pacmanDirection.vx;
         }
         else
         {
             if(pacmanPosition.x!=targetPacmanPosition.x)
                 pacmanPosition.px+=pacmanDirection.vx;
             else
                 pacmanDirection.vx=0;
         }
 
 
     }
     if(pacmanDirection.vy!=0)
     {
         if((pacmanPosition.py+2)%4>0)
         {
             pacmanPosition.py+=pacmanDirection.vy;
         }
         else
         {
             if(pacmanPosition.y!=targetPacmanPosition.y)
                 pacmanPosition.py+=pacmanDirection.vy;
             else
                 pacmanDirection.vy=0;
         }
     
     }
     
     
     if(blinkyDirection.vx!=0) //we move horizionatally
     {
         if((Blinky.px+2)%4>0)
         {
             Blinky.px+=blinkyDirection.vx;
         }
         else
         {
             if(Blinky.x!=targetBlinky.x)
                 Blinky.px+=blinkyDirection.vx;
             else
                 blinkyDirection.vx=0;
         }
         
         
     }
     if(blinkyDirection.vy!=0)
     {
         if((Blinky.py+2)%4>0)
         {
             Blinky.py+=blinkyDirection.vy;
         }
         else
         {
             if(Blinky.y!=targetBlinky.y)
                 Blinky.py+=blinkyDirection.vy;
             else
                 blinkyDirection.vy=0;
         }
         
     }
     
     pacmanFace=(pacmanFace+1)%4;
     pacmanPosition.x=(pacmanPosition.px+2)/4;
     pacmanPosition.y=(pacmanPosition.py+2)/4;
     Blinky.x=(Blinky.px+2)/4;
     Blinky.y=(Blinky.py+2)/4;
    // displayarray();
    // Serial.printf("%d %d \n",pacmanPosition.x,pacmanPosition.y);
     facestuff=(facestuff+1)%4;
     displayPacman();
     //displayarray();
     
 }
 

/*
void deplacefantomes()
{
    //int val=0;
    ghostDirection(Blinky);
    switch(value)
    {
        case 1:
             Blinky.py+=1;
            break;
        case 2:
            Blinky.py-=1;
            break;
        case 3:
            Blinky.px+=1;
            break;
        case 4:
            Blinky.px-=1;
            break;
    }
    Blinky.x=(Blinky.px-2)/4;
    Blinky.y=(Blinky.py-2)/4;
}
*/

void displayarray()
{
    for (int j=PACMAN_HEIGHT-1;j>=0;j--)
    {
        for(int i=0;i<PACMAN_WIDTH;i++)
        {
            String e;
            e=" ";
            if(pacboard[i+j*PACMAN_WIDTH]!=15)
                e="X";
            node p;
            p.x=i;
            p.y=j;
            if(isInShortPath(Blinky,p))
                e="*";
            if(isInShortPath(Clyde,p))
                e="^";
            if(isInShortPath(Pinky,p))
                e="!";
            if(i==Pinky.x and j==Pinky.y)
                e="P";
            if(i==Clyde.x and j==Clyde.y)
                e="C";
            if(i==Blinky.x and j==Blinky.y)
                e="B";
            if(i==targetPacmanPosition.x   and j==targetPacmanPosition.y)
                e="P";
            Serial.print(e);

        }
        Serial.println();
    }
}
/*
 void IRAM_ATTR moveGhosts()
 {
     
    if(Blinky.x==pacmanPosition.x and Blinky.y==pacmanPosition.y)
        Serial.println("TROUVE");
    else{
        return;
        while(!resetpossible){}
    
     Blinky.px+=finvx;
     Blinky.py+=finvy;
     Blinky.x=(Blinky.px+2)/4;
     Blinky.y=(Blinky.py+2)/4;
    // Blinky.x+=finvx;
        node f=Blinky.path[Blinky.followupPath];
        Blinky.x=f.x;
        Blinky.y=f.y;
        Blinky.followupPath--;

         f=Clyde.path[Clyde.followupPath];
        Clyde.x=f.x;
        Clyde.y=f.y;
        Clyde.followupPath--;
        
        f=Pinky.path[Pinky.followupPath];
        Pinky.x=f.x;
        Pinky.y=f.y;
        Pinky.followupPath--;
        
        
    // Blinky.y+=finvy;
     //Serial.printf("%d %d %d %d %d\n",Blinky.x,Blinky.y,Blinky.px,Blinky.py,closedListSize);
     //displayarray();`
        displayPacman();
    }
    
 
 }
*/

#endif /* pacmanlib_h */
