//
//  snake.h
//  
//
//  Created by Yves BAZIN on 1/05/18.
//

#ifndef snake_h
#define snake_h

void initSnakeSocketControl();
void snakeWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
bool initSnake();
void newSnake();
void executeSnakeSocketControl();
bool canMove();
void newFoodPosition();

void moveSnake();
void displaySnake();
int snakeWebSocketPort=86;
bool inSnake=false;
bool snakeInitiated=false;

WebSocketsServer snakeWebSocket = WebSocketsServer(snakeWebSocketPort);
const byte snakeWidth=60;
const byte snakeHeight=24;

//bool snaketiles[snakeWidth*snakeHeight]={false};
byte snake_x[100];
byte snake_y[100];
int totalSnakeLength=99;
byte snake_length=2;
int snakeInterval;
int snakeScore;
byte food_x;
byte food_y;

int vx=0;
int vy=0;
CRGB snakeColor=CRGB(30,30,0);

struct snakePosition{
    byte x,y;
};

snakePosition nextSnakePosition();
bool weEat();



bool weEat()
{
   struct snakePosition np=nextSnakePosition();
    if(np.x ==food_x and np.y==food_y)
    {
        memmove(&snake_x[1],&snake_x[0],totalSnakeLength);
        memmove(&snake_y[1],&snake_y[0],totalSnakeLength);
        snake_x[0]=food_x;
        snake_y[0]=food_y;
        snake_length++;
        //Serial.println("same as food");
        return true;
    }
    else
        return false;
}


bool canMove()
{
    struct snakePosition np=nextSnakePosition();
    //we touch the snake
    for(byte i=0;i<=totalSnakeLength;i++)
    {
        if(np.x==snake_x[i] and np.y==snake_y[i])
            return false;
    }
    //we touch the bordersake
    if(vx==1 and np.x==0)
        return false;
    if(vx==-1 and np.x==snakeWidth-1)
        return false;
    if(vy==1 and np.y==0)
        return false;
    if(vy==-1 and np.y==snakeHeight-1)
        return false;
    return true;
}

void newFoodPosition()
{
    bool cont=true;
    while(cont)
    {
        cont=false;
        food_x=random(snakeWidth);
        food_y=random(snakeHeight);
        for(byte i=0;i<=totalSnakeLength;i++)
        {
            if(food_y==snake_y[i] and food_x==snake_x[i])
                cont=true;
        }
    }
    
}

void moveSnake()
{
    if(!inSnake)
        return;
    struct snakePosition np=nextSnakePosition();
    if(weEat())
    {
       //Serial.println("same domm");
       if(snakeInterval>200) //on accelère la vitesse du snake
           snakeInterval-=100;
        snakeScore++;
       
       // FastLEDshowESP32();
       // delay(1000);
        newFoodPosition();
        displaySnake();
        return;
    }
    
    if(canMove())
    {
        memmove(&snake_x[1],&snake_x[0],totalSnakeLength);
        memmove(&snake_y[1],&snake_y[0],totalSnakeLength);
        snake_x[snake_length]=99;
        snake_y[snake_length]=99;
        snake_x[0]=np.x;
        snake_y[0]=np.y;
        displaySnake();
    }
    else
    {
        inSnake=false;
        char mes[]="PERDU";
        afficheMessage2(mes, 1,15);
        char but[4];
        my_itoa(snakeScore,but,10,3);
        afficheMessage2(but, 2,2);
        replaceled();
        FastLEDshowESP32();
        delay(2000);
        newSnake();
        
    }
    
}


void displaySnake()
{
   fill(CRGB(0,0,0));
    for(byte i=0;i<snake_length;i++)
         {
             
             byte x=snake_x[i];
             byte y=snake_y[i];
             if(x<99)
             {
                 PixelOn(2*x+1,2*y,snakeColor);
                 PixelOn(2*x+2,2*y,snakeColor);
                 PixelOn(2*x+2,2*y+1,snakeColor);
                 PixelOn(2*x+1,2*y+1,snakeColor);
                 //leds[2*y*LED_WIDTH+2*x]=snakeColor;
                 //leds[2*y*LED_WIDTH+2*x+1]=snakeColor;
                 //leds[(2*y+1)*LED_WIDTH+2*x]=snakeColor;
                 //leds[(2*y+1)*LED_WIDTH+2*x+1]=snakeColor;
             }
         }
        PixelOn(2*food_x+1,2*food_y,CRGB(0,255,0));
    PixelOn(2*food_x+1,2*food_y+1,CRGB(0,255,0));
    PixelOn(2*food_x+2,2*food_y,CRGB(0,255,0));
    PixelOn(2*food_x+2,2*food_y+1,CRGB(0,255,0));
        // leds[2*food_y*LED_WIDTH+2*food_x]=CRGB(0,255,0);
         //leds[2*food_y*LED_WIDTH+2*food_x+1]=CRGB(0,255,0);
        // leds[(2*food_y+1)*LED_WIDTH+2*food_x]=CRGB(0,255,0);
        // leds[(2*food_y+1)*LED_WIDTH+2*food_x+1]=CRGB(0,255,0);
    replaceled();
    FastLEDshowESP32();
}



snakePosition nextSnakePosition()
{
    struct snakePosition sp;
    
    if(vx==1)
    {
        byte x=snake_x[0];
        if(x==(snakeWidth-1))
            x=0;
        else
            x=x+1;
        sp.x=x;
        sp.y=snake_y[0];
        return sp;
    }
    
    if(vx==-1)
    {
        byte x=snake_x[0];
        if(x==0)
            x=snakeWidth-1;
        else
            x=(byte)(int)(x-1);
        //Serial.printf("%d\n",x);
        sp.x=x;
        sp.y=snake_y[0];
        return sp;
    }

    if(vy==-1)
    {
        byte y=snake_y[0];
        if(y==0)
            y=snakeHeight-1;
        else
            y=y-1;
        sp.x=snake_x[0];
        sp.y=y;
        return sp;
    }
  
    if(vy==1)
    {
        byte y=snake_y[0];
        if(y==snakeHeight-1)
            y=0;
        else
            y=y+1;
        sp.x=snake_x[0];
        sp.y=y;
        return sp;
    }
    
    
}


void initSnakeSocketControl()
{
    snakeWebSocket.begin();
    snakeWebSocket.onEvent(snakeWebSocketEvent);
}

void executeSnakeSocketControl()
{
    snakeWebSocket.loop();
    
}




bool initSnake()
{
    if(isTable)
    {
        server.serveStatic("/snake.html", SPIFFS, "/snake.html"); //on ajoute le lien vers
        //server.serveStatic("/image.css", SPIFFS, "/image.css"); //on ajoute le lien vers
        initSnakeSocketControl();
        snakeInitiated=true;
        Serial.println("snake cree");
        return true;
        
    }
    else{
        Serial.println("No table existing create the table first");
        snakeInitiated=false;
        return false;
    }
}



void newSnake()
{
    
    Serial.println("voici snake");// clears the red display matrix
    if(!snakeInitiated)
    {
        Serial.println("on cree la base fait");
        initSnake();
        
    }
    
    //on reset le tableau des snakes
    for(byte i=0;i<=totalSnakeLength;i++)
    {
        snake_x[i]=99;
        snake_y[i]=99;
    }
    snake_length=4;
    snake_x[0]=10;
    snake_x[1]=10;
    snake_x[2]=10;
    snake_x[3]=10;
    snake_y[0]=3;
    snake_y[1]=4;
    snake_y[2]=5;
    snake_y[3]=6;
    newFoodPosition();
    vy=0;
    vx=1;
    inSnake=true;
    fill(CRGB(0,0,0));
    snakeInterval=3000;
    snakeScore=0;
    randomSeed(ESP.getCycleCount()); //create a new seed
    //FastLED.show();
    
}




void snakeWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
    
    switch(type) {
        case WStype_DISCONNECTED:
            // USE_SERIAL.printf("[%u] Disconnected!\n", num);
            break;
        case WStype_CONNECTED:
        {
            IPAddress ip = snakeWebSocket.remoteIP(num);
            USE_SERIAL.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
            
            // send message to client
              snakeWebSocket.sendTXT(num, "Connected");
        }
            break;
        case WStype_TEXT:
            // USE_SERIAL.printf("[%u] get Text: %sdd\n", num, payload);
            if (strcmp("UP", (const char *)payload) == 0)  {
                
                //if(pacy<LED_HEIGHT/2-5)
                // pacy++;
                Serial.println("UP");
                vx=0;
                if(vy==0)
                    vy=+1;
                moveSnake();
                
                
            }
            if (strcmp("DOWN", (const char *)payload) == 0)  {
                //             if(pacy>0)
                //pacy--;
                // Serial.println("on va a droite");
                 Serial.println("DOWN");
                vx=0;
                if(vy==0)
                    vy=-1;
                moveSnake();

            }
            if (strcmp("RIGHT", (const char *)payload) == 0)  {
                //if(pacx<LED_WIDTH-5)
                // pacx++;
                Serial.println("on va a droite");
                if(vx==0)
                    vx=1;
                vy=0;
                moveSnake();
            }
            if (strcmp("LEFT", (const char *)payload) == 0)  {
                
                // Serial.println("on va a droite");
                //if(pacx>0)
                // pacx--;
                 Serial.println("LEFT");
                if(vx==0)
                    vx=-1;
                vy=0;
                moveSnake();
            }
            // send message to client
            // webSocket.sendTXT(num, "message here");
            
            // send data to all connected clients
            // webSocket.broadcastTXT("message here");
            break;
        case WStype_BIN:
            USE_SERIAL.printf("[%u] get binary length: %u\n", num, length);
            // hexdump(payload, length);
            
            // send message to client
            // webSocket.sendBIN(num, payload, length);
            break;
    }
    
}


#endif /* snake_h */
