    //
//  ledTable.h
//  
//
//  Created by Yves BAZIN on 25/11/17.
//

#ifndef ledTable_h
#define ledTable_h


//#include <ArduinoJson.h>

#include <mem.h>
extern "C" {
#include "user_interface.h"
}
// How many leds in your strip?




#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
//#include <ESP8266WiFiMulti.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <FS.h>
//#include <EEPROM.h>

#define FASTLED_ESP8266_RAW_PIN_ORDER
#define FASTLED_ESP8266_NODEMCU_PIN_ORDER
#define FASTLED_ESP8266_D1_PIN_ORDER
#define FASTLED_ALLOW_INTERRUPTS 0
#include "FastLED.h"
FASTLED_USING_NAMESPACE

#include "math.h"

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806 define both DATA_PIN and CLOCK_PIN

//#define DATA_PIN 3
//#define CLOCK_PIN 13 //needed if we go for ws2801


#define DATA_PIN      D7     // for Huzzah: Pins w/o special function:  #4, #5, #12, #13, #14; // #16 does not work :(
#define DATA_PIN2     D6
#define LED_TYPE      NEOPIXEL
#define COLOR_ORDER   RGB

//Define table orientation this is where the pixel 0 is
#define DOWN_RIGHT   0 //natural mode no transpostion to be made
#define DOWN_LEFT    1 //We turn 90° clock wise
#define UP_LEFT      2
#define UP_RIGHT     3
#define DOWN_RIGHT_INV   4 //natural mode no transpostion to be made
#define DOWN_LEFT_INV    5 //We turn 90° clock wise
#define UP_LEFT_INV      6
#define UP_RIGHT_INV     7
#define DEFAULT_BRIGHTNESS 128

void scrollScreenDown();

int tableBrightness;
int anim = 9	;
char mess[]="SOON 60x50 STAY TUNED FOR MORE FUN";
MDNSResponder mdns;

byte font1[][7]=
{
    
    //32->47
    {B00000,  B00000, B00000, B00000, B00000, B00000, B00000  },{B01000,  B01000, B01000, B01000, B01000, B00000, B01000  },  {B01010,  B01010, B01010, B00000, B00000, B00000, B00000  },  {B01010,  B01010, B11111, B01010, B11111, B01010, B01010  },  {B00100,  B01111, B10100, B01110, B00101, B11110, B00100  },  {B11000,  B11001, B00010, B00100, B01000, B10011, B00011  },  {B01000,  B10100, B10100, B01000, B10101, B10010, B01101  },  {B01100,  B00100, B01000, B00000, B00000, B00000, B00000  },  {B00010,  B00100, B01000, B01000, B01000, B00100, B00010  },  {B01000,  B00100, B00010, B00010, B00010, B00100, B01000  },  {B10101,  B01110, B00100, B01110, B10101, B00000, B00000  },  {B00100,  B00100, B00100, B11111, B00100, B00100, B00100  },  {B00000,  B00000, B00000, B00000, B11000, B01000, B10000  },  {B00000,  B00000, B00000, B11100, B00000, B00000, B00000  },  {B00000,  B00000, B00000, B00000, B00000, B01100, B01100  },  {B00000,  B00001, B00010, B00100, B01000, B10000, B00000  },
    
    //48->57
    {B01110,  B10001, B10011, B10101, B11001, B10001, B01110  },  {B00100,  B01100, B00100, B00100, B00100, B00100, B01110  },  {B01110,  B10001, B00001, B00010, B00100, B01000, B11111  },  {B11111,  B00010, B00100, B00010, B00001, B10001, B01110  },  {B00010,  B00110, B01010, B10010, B11111, B00010, B00010  },  {B11111,  B10000, B11110, B00001, B00001, B10001, B01110  },  {B00110,  B01000, B10000, B11110, B10001, B10001, B01110  },  {B11111,  B00001, B00010, B00100, B01000, B10000, B10000  },  {B01110,  B10001, B10001, B01110, B10001, B10001, B01110  },  {B01110,  B10001, B10001, B01111, B00001, B00010, B01100  },
    
    //58->64
    {B00000,  B01100, B01100, B00000, B01100, B01100, B00000  },  {B00000,  B01100, B01100, B00000, B01100, B00100, B01000  },  {B00010,  B00100, B01000, B10000, B01000, B00100, B00010  },  {B00000,  B00000, B11111, B00000, B11111, B00000, B00000  },  {B10000,  B01000, B00100, B00010, B00100, B01000, B10000  },  {B01110,  B10001, B00001, B00010, B00100, B00000, B00100  },  {B01110,  B10001, B10011, B10100, B10101, B10001, B01110  },
    
    //65->90
    {B01110,  B10001, B10001, B11111, B10001, B10001, B10001  },  {B11110,  B10001, B10001, B11110, B10001, B10001, B11110  },  {B01110,  B10001, B10000, B10000, B10000, B10001, B01110  },  {B11110,  B10001, B10001, B10001, B10001, B10001, B11110  },  {B11111,  B10000, B10000, B11110, B10000, B10000, B11111  },  {B11111,  B10000, B10000, B11110, B10000, B10000, B10000  },  {B01110,  B10001, B10000, B10111, B10001, B10001, B01110  },  {B10001,  B10001, B10001, B11111, B10001, B10001, B10001  },  {B01110,  B00100, B00100, B00100, B00100, B00100, B01110  },  {B00111,  B00010, B00010, B00010, B00010, B10010, B01100  },  {B10001,  B10010, B10100, B11000, B10100, B10010, B10001  },  {B10000,  B10000, B10000, B10000, B10000, B10000, B11111  },  {B10001,  B11011, B10101, B10101, B10001, B10001, B10001  },  {B10001,  B10001, B11001, B10101, B10011, B10001, B10001  },  {B01110,  B10001, B10001, B10001, B10001, B10001, B01110  },  {B11110,  B10001, B10001, B11110, B10000, B10000, B10000  },  {B01110,  B10001, B10001, B10001, B10101, B10010, B01101  },  {B11110,  B10001, B10001, B11110, B10100, B10010, B10001  },  {B01111,  B10000, B10000, B01110, B00001, B00001, B11110  },  {B11111,  B00100, B00100, B00100, B00100, B00100, B00100  },  {B10001,  B10001, B10001, B10001, B10001, B10001, B01110  },  {B10001,  B10001, B10001, B10001, B10001, B01010, B00100  },  {B10001,  B10001, B10001, B10001, B10101, B10101, B01010  },  {B10001,  B10001, B01010, B00100, B01010, B10001, B10001  },  {B10001,  B10001, B10001, B01010, B00100, B00100, B00100  },  {B11111,  B00001, B00010, B00100, B01000, B10000, B11111  },
    
    //91->96
    {B01110,  B01000, B01000, B01000, B01000, B01000, B01110  },  {B10001,  B01010, B11111, B00100, B11111, B00100, B00100  },  {B01110,  B00010, B00010, B00010, B00010, B00010, B01110  },  {B00100,  B01010, B10001, B00000, B00000, B00000, B00000  },  {B00000,  B00000, B00000, B00000, B00000, B00000, B11111  },  {B01000,  B00100, B00010, B00000, B00000, B00000, B00000  },
    
    //97->122
    {B00000,  B00000, B01110, B00001, B01111, B10001, B01111  },  {B10000,  B10000, B10110, B11001, B10001, B10001, B11110  },  {B00000,  B00000, B01110, B10000, B10000, B10001, B01110  },  {B00001,  B00001, B01101, B10011, B10001, B10001, B01111  },  {B00000,  B00000, B01110, B10001, B11111, B10000, B01110  },  {B00110,  B01001, B01000, B11100, B01000, B01000, B01000  },  {B00000,  B01111, B10001, B10001, B01111, B00001, B01110  },  {B10000,  B10000, B10110, B11001, B10001, B10001, B10001  },  {B00100,  B00000, B01100, B00100, B00100, B00100, B01110  },  {B00010,  B00000, B00110, B00010, B00010, B10010, B01100  },  {B10000,  B10000, B10010, B10100, B11000, B10100, B10010  },  {B01100,  B00100, B00100, B00100, B00100, B00100, B01110  },  {B00000,  B00000, B11010, B10101, B10101, B10001, B10001  },  {B00000,  B00000, B10110, B11001, B10001, B10001, B10001  },  {B00000,  B00000, B01110, B10001, B10001, B10001, B01110  },  {B00000,  B00000, B11110, B10001, B11110, B10000, B10000  },  {B00000,  B00000, B01110, B10001, B01111, B00001, B00001  },  {B00000,  B00000, B10110, B11001, B10000, B10000, B10000  },  {B00000,  B00000, B01110, B10000, B01110, B00001, B11110  },  {B01000,  B01000, B11100, B01000, B01000, B01001, B00110  },  {B00000,  B00000, B10001, B10001, B10001, B10011, B01101  },  {B00000,  B00000, B10001, B10001, B10001, B01010, B00100  },  {B00000,  B00000, B10001, B10001, B10001, B10101, B01010  },  {B00000,  B00000, B10001, B01010, B00100, B01010, B10001  },  {B00000,  B00000, B10001, B10001, B01111, B00001, B01110  },  {B00000,  B00000, B11111, B00010, B00100, B01000, B11111  },
    
    
};

uint8_t  gamma8[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,8,8,8,9,9,9,10,10,10,11,11,11,12,12,13,13,14,14,14,15,15,16,16,17,17,18,18,19,19,20,21,21,22,22,23,23,24,25,25,26,27,27,28,29,29,30,31,31,32,33,34,34,35,36,37,37,38,39,40,41,42,42,43,44,45,46,47,48,49,50,51,52,52,53,54,55,56,57,59,60,61,62,63,64,65,66,67,68,69,71,72,73,74,75,77,78,79,80,82,83,84,85,87,88,89,91,92,93,95,96,98,99,100,102,103,105,106,108,109,111,112,114,115,117,119,120,122,123,125,127,128,130,132,133,135,137,138,140,142,144,145,147,149,151,153,155,156,158,160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,190,192,194,197,199,201,203,205,207,210,212,214,216,219,221,223,226,228,230,233,235,237,240,242,245,247,250,252,255,
    
};
uint8_t  gammar[] = {
    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,2,2,2,2,2,2,2,3,3,3,3,3,4,4,4,4,5,5,5,5,6,6,6,6,7,7,7,8,8,8,9,9,9,10,10,10,11,11,11,12,12,13,13,14,14,14,15,15,16,16,17,17,18,18,19,19,20,21,21,22,22,23,23,24,25,25,26,27,27,28,29,29,30,31,31,32,33,34,34,35,36,37,37,38,39,40,41,42,42,43,44,45,46,47,48,49,50,51,52,52,53,54,55,56,57,59,60,61,62,63,64,65,66,67,68,69,71,72,73,74,75,77,78,79,80,82,83,84,85,87,88,89,91,92,93,95,96,98,99,100,102,103,105,106,108,109,111,112,114,115,117,119,120,122,123,125,127,128,130,132,133,135,137,138,140,142,144,145,147,149,151,153,155,156,158,160,162,164,166,168,170,172,174,176,178,180,182,184,186,188,190,192,194,197,199,201,203,205,207,210,212,214,216,219,221,223,226,228,230,233,235,237,240,242,245,247,250,252,255,
    
};

CRGB lettrefont1[35];

CRGB *leds;//[600];
CRGB *Tpic;//[600];

CRGB solidColor = CRGB(5, 5, 5);
CRGB bgColor = CRGB(5, 5, 5);
CRGB Color = CRGB :: Blue;
CRGB Color2 = CRGB :: Green;
bool isTable=false;
int tableOrientation=DOWN_RIGHT; //we put the first pixel down and right

int LED_WIDTH=30;
int LED_HEIGHT=14;
int NUM_LEDS;

ESP8266WebServer server(80);


float gammaCorrection=2.3;


void calculateGammaTable()
{
    Serial.print("bri");
    Serial.println(tableBrightness);
    Serial.println((float)tableBrightness/255);
    float correctGamma=powf((float)tableBrightness/255,1/gammaCorrection);
    Serial.print("gamma correction:");
    Serial.println(correctGamma);
    correctGamma=1;
    for (int i=0;i<256;i++)
    {
 
        float newValue=255*powf((float)i/255,correctGamma*gammaCorrection);
        //Serial.println(newValue);
        gamma8[i]=(int)newValue;
        //Serial.println(gamma8[i]);
        newValue=255*powf((float)i/255,correctGamma*(gammaCorrection+0.2));
        gammar[i]=(int)newValue;
        //Serial.println(gamma8[i]);
    }
}

void setTableBrightness(int b)
{
   
   FastLED.setBrightness(b);
    tableBrightness=b;
    calculateGammaTable();
}
//CREATTION DES LEDS (on prend la longueur des strips w et le nombre de strip h)

/*void PixelOn(byte x,byte y,CRGB Color)
{
    int offset=0;
    if (x<0 or y<0 or x>=LED_WIDTH or y>=LED_HEIGHT)
        return ;
    if(y%2==0)
        offset=x+y*LED_WIDTH;
    else
        offset=2 * LED_WIDTH * ((int)floor(y / 2) + 1) - 1 - x;
    
    leds[offset]=Color;
     
}*/


void PixelOn(uint16_t x,uint16_t y,CRGB Color)
{
    //int offset=0;
    if (x<0 or y<0 or x>=LED_WIDTH or y>=LED_HEIGHT)
        return ;
    if(y%2==0)
        leds[x+y*LED_WIDTH]=Color;
    else
    {
        //int offset2=2 * LED_WIDTH * ((int)floor(y /2)  + 1) - 1 - x;
        leds[(LED_WIDTH<<1) * ((y >>1)  + 1) - 1 - x]=Color;
        // leds[LED_WIDTH*y+(LED_WIDTH<<1)-1-x]=Color;
        
    }
    
    // leds[ (y%2==0) ? x+y*LED_WIDTH : (LED_WIDTH<<1) * ((y >>1)  + 1) - 1 - x]=Color;
    //leds[offset]=Color;
    
}
void putOrientation(CRGB *pic,int h,int w,int x0,int y0)
{
    //CRGB * Tpic = (CRGB*)calloc(h*w,sizeof(CRGB));
    if(!Tpic)
    {
        Serial.println("pas possible");
        return ;//NULL;
    }
    switch(tableOrientation){
            
        case DOWN_RIGHT: //on ne fait rien
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( ((x+x0)+LED_WIDTH*(y+y0)) <NUM_LEDS && x+x0 >=0 && y+y0>=0 && x+x0<LED_WIDTH && y+y0 <LED_HEIGHT)
                        Tpic[x+x0+LED_WIDTH*(y+y0)]=pic[w*y+x];
                }
            }
            
            break;
            
        case DOWN_LEFT:
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( LED_WIDTH*(LED_HEIGHT-1-x-x0)+y+y0 <NUM_LEDS && LED_HEIGHT-1-x-x0 >=0 && y+y0>=0 && LED_HEIGHT-1-x-x0<LED_HEIGHT && y+y0 <LED_WIDTH)
                    Tpic[LED_WIDTH*(LED_HEIGHT-1-x-x0)+y+y0]=pic[w*y+x];
                }
            }
            break;
            
            
        case UP_RIGHT:
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( (LED_WIDTH*((x+x0))+LED_WIDTH-1-(y+y0)) <NUM_LEDS  && (x+x0) >=0 && LED_WIDTH-1-(y+y0)>=0 && (x+x0)<LED_HEIGHT && LED_WIDTH-1-(y+y0) <LED_WIDTH  )
                    Tpic[LED_WIDTH*((x+x0))+LED_WIDTH-1-(y+y0)]=pic[w*y+x];
                }
            }
            break;
            
        case UP_LEFT:
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( LED_WIDTH-1-(x+x0)+LED_WIDTH*(LED_HEIGHT-1-(y+y0)) <NUM_LEDS  && LED_WIDTH-1-(x+x0)>=0 && LED_WIDTH*(LED_HEIGHT-1-(y+y0))>=0 && (LED_HEIGHT-1-(y+y0))<LED_HEIGHT && LED_WIDTH-1-(x+x0) <LED_WIDTH )
                        Tpic[LED_WIDTH-1-(x+x0)+LED_WIDTH*(LED_HEIGHT-1-(y+y0))]=pic[w*y+x];
                }
            }
            break;
            
//on inverse la lecture des pixels au niveau des X on lit de gauche a droite
        case DOWN_RIGHT_INV: //on ne fait rien
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( LED_WIDTH-1-x-x0+LED_WIDTH*(y+y0) <NUM_LEDS && LED_WIDTH-1-x-x0 >=0 && y+y0>=0 && LED_WIDTH-1-x-x0<LED_WIDTH && y+y0 <LED_HEIGHT)
                        Tpic[LED_WIDTH-1-x-x0+LED_WIDTH*(y+y0)]=pic[w*y+x];
                }
            }
            
            break;
            
        case DOWN_LEFT_INV:
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( LED_WIDTH*(x+x0)+y+y0 <NUM_LEDS && x+x0 >=0 && y+y0>=0 && x+x0<LED_HEIGHT && y+y0 <LED_WIDTH)
                        Tpic[LED_WIDTH*(x+x0)+y+y0]=pic[w*y+x];
                }
            }
            break;
            
            
        case UP_RIGHT_INV:
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( (LED_WIDTH*((x+x0))+(y+y0)) <NUM_LEDS  && (x+x0) >=0 && (y+y0)>=0 && (x+x0)<LED_HEIGHT && (y+y0) <LED_WIDTH  )
                        Tpic[LED_WIDTH*((x+x0))+(y+y0)]=pic[w*y+x];
                }
            }
            break;
            
        case UP_LEFT_INV:
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( (x+x0)+LED_WIDTH*(LED_HEIGHT-1-(y+y0)) <NUM_LEDS  && (x+x0)>=0 && LED_WIDTH*(LED_HEIGHT-1-(y+y0))>=0 && (LED_HEIGHT-1-(y+y0))<LED_HEIGHT && (x+x0) <LED_WIDTH )
                        Tpic[(x+x0)+LED_WIDTH*(LED_HEIGHT-1-(y+y0))]=pic[w*y+x];
                }
            }
            break;
            
            
            
    }
     //return Tpic;
    
}




void putOrientationInv(CRGB *pic,int h,int w,int x0,int y0)
{
    //CRGB * Tpic = (CRGB*)calloc(h*w,sizeof(CRGB));
    if(!Tpic)
    {
        Serial.println("pas possible");
        return ;//NULL;
    }
    switch(tableOrientation){
            
        case DOWN_RIGHT: //on ne fait rien
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( ((x+x0)+LED_WIDTH*(y+y0)) <NUM_LEDS && x+x0 >=0 && y+y0>=0 && x+x0<LED_WIDTH && y+y0 <LED_HEIGHT)
                        Tpic[x+x0+LED_WIDTH*(y+y0)]=pic[w*y+w-1-x];
                }
            }
            
            break;
            
        case DOWN_LEFT:
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( LED_WIDTH*(LED_HEIGHT-1-x-x0)+y+y0 <NUM_LEDS && LED_HEIGHT-1-x-x0 >=0 && y+y0>=0 && LED_HEIGHT-1-x-x0<LED_HEIGHT && y+y0 <LED_WIDTH)
                        Tpic[LED_WIDTH*(LED_HEIGHT-1-x-x0)+y+y0]=pic[w*y+w-1-x];
                }
            }
            break;
            
            
        case UP_RIGHT:
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( (LED_WIDTH*((x+x0))+LED_WIDTH-1-(y+y0)) <NUM_LEDS  && (x+x0) >=0 && LED_WIDTH-1-(y+y0)>=0 && (x+x0)<LED_HEIGHT && LED_WIDTH-1-(y+y0) <LED_WIDTH  )
                        Tpic[LED_WIDTH*((x+x0))+LED_WIDTH-1-(y+y0)]=pic[w*y+w-1-x];
                }
            }
            break;
            
        case UP_LEFT:
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( LED_WIDTH-1-(x+x0)+LED_WIDTH*(LED_HEIGHT-1-(y+y0)) <NUM_LEDS  && LED_WIDTH-1-(x+x0)>=0 && LED_WIDTH*(LED_HEIGHT-1-(y+y0))>=0 && (LED_HEIGHT-1-(y+y0))<LED_HEIGHT && LED_WIDTH-1-(x+x0) <LED_WIDTH )
                        Tpic[LED_WIDTH-1-(x+x0)+LED_WIDTH*(LED_HEIGHT-1-(y+y0))]=pic[w*y+w-1-x];
                }
            }
            break;
            
            //on inverse la lecture des pixels au niveau des X on lit de gauche a droite
        case DOWN_RIGHT_INV: //on ne fait rien
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( LED_WIDTH-1-x-x0+LED_WIDTH*(y+y0) <NUM_LEDS && LED_WIDTH-1-x-x0 >=0 && y+y0>=0 && LED_WIDTH-1-x-x0<LED_WIDTH && y+y0 <LED_HEIGHT)
                        Tpic[LED_WIDTH-1-x-x0+LED_WIDTH*(y+y0)]=pic[w*y+w-1-x];
                }
            }
            
            break;
            
        case DOWN_LEFT_INV:
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( LED_WIDTH*(x+x0)+y+y0 <NUM_LEDS && x+x0 >=0 && y+y0>=0 && x+x0<LED_HEIGHT && y+y0 <LED_WIDTH)
                        Tpic[LED_WIDTH*(x+x0)+y+y0]=pic[w*y+w-1-x];
                }
            }
            break;
            
            
        case UP_RIGHT_INV:
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( (LED_WIDTH*((x+x0))+(y+y0)) <NUM_LEDS  && (x+x0) >=0 && (y+y0)>=0 && (x+x0)<LED_HEIGHT && (y+y0) <LED_WIDTH  )
                        Tpic[LED_WIDTH*((x+x0))+(y+y0)]=pic[w*y+w-1-x];
                }
            }
            break;
            
        case UP_LEFT_INV:
            for(int y=0;y<h;y++)
            {
                for (int x=0;x<w;x++)
                {
                    if( (x+x0)+LED_WIDTH*(LED_HEIGHT-1-(y+y0)) <NUM_LEDS  && (x+x0)>=0 && LED_WIDTH*(LED_HEIGHT-1-(y+y0))>=0 && (LED_HEIGHT-1-(y+y0))<LED_HEIGHT && (x+x0) <LED_WIDTH )
                        Tpic[(x+x0)+LED_WIDTH*(LED_HEIGHT-1-(y+y0))]=pic[w*y+w-1-x];
                }
            }
            break;
            
            
            
    }
    //return Tpic;
    
}




void displayTpic()
{
    for (int y=0;y<LED_HEIGHT;y++)
    {
        if(y%2==0)
            memcpy(&leds[LED_WIDTH * y], &Tpic[y *LED_WIDTH ],LED_WIDTH * sizeof(CRGB));
        else
            for (int x = 0; x < LED_WIDTH; x++)
            {
                    leds[2 * LED_WIDTH * ((int)floor(y / 2) + 1) - 1 - x] = Tpic[LED_WIDTH * y  + x  ];
            }

    }
}

void displaypic( CRGB *pica, int x0, int y0, int h, int w)
{
    putOrientation(pica,h,w,x0,y0);
    if(Tpic)
    {
       int hmin=LED_HEIGHT;
       int  wmin=LED_WIDTH;
        x0=0;
        y0=0;
        for (int y = y0; y < hmin + y0; y++)
        {
            if (y >= 0) {
                if (y % 2 == 0)
                {
                    if (x0 < 0)
                    {
                        int nh = wmin + x0;
                        if (nh > 0)
                            memcpy(&leds[LED_WIDTH * y], &Tpic[(y - y0) *wmin - x0], nh * sizeof(CRGB));
                    }
                    else
                        memcpy(&leds[LED_WIDTH * y + x0], &Tpic[(y - y0)*wmin], wmin * sizeof(CRGB));
                }
                else
                {
                    for (int x = x0; x < wmin + x0; x++)
                    {
                        if (x >= 0)
                            leds[2 * LED_WIDTH * ((int)floor(y / 2) + 1) - 1 - x] = Tpic[wmin * (y - y0) + x - x0 ];
                    }
                }
            }
        }
       
    }
}


void displayPicInv( CRGB *pica, int x0, int y0, int h, int w)
{
    putOrientationInv(pica,h,w,x0,y0);
    if(Tpic)
    {
        int hmin=LED_HEIGHT;
        int  wmin=LED_WIDTH;
        x0=0;
        y0=0;
        for (int y = y0; y < hmin + y0; y++)
        {
            if (y >= 0) {
                if (y % 2 == 0)
                {
                    if (x0 < 0)
                    {
                        int nh = wmin + x0;
                        if (nh > 0)
                            memcpy(&leds[LED_WIDTH * y], &Tpic[(y - y0) *wmin - x0], nh * sizeof(CRGB));
                    }
                    else
                        memcpy(&leds[LED_WIDTH * y + x0], &Tpic[(y - y0)*wmin], wmin * sizeof(CRGB));
                }
                else
                {
                    for (int x = x0; x < wmin + x0; x++)
                    {
                        if (x >= 0)
                            leds[2 * LED_WIDTH * ((int)floor(y / 2) + 1) - 1 - x] = Tpic[wmin * (y - y0) + x - x0 ];
                    }
                }
            }
        }
        
    }
    
}



void displayBitmap(unsigned char *pic,int x0,int y0,int h,int w)
{
  //frame size
    int max_wide=0;
    int wide=w+x0;
    int offsety;
    int offsetx;
    int newx=0;
    int newy=0;
    if(wide<=0)
        return; // l'image ne peut etre affichée
    if(tableOrientation%2==0)
        max_wide=LED_WIDTH;
    else
        max_wide=LED_HEIGHT;
    
    if (x0>=max_wide) //on est en dehors du cadre
        return;
    if(x0>=0)
    {
        newx=x0;
        offsetx=0;
        if(w+x0<max_wide)
            wide=w;
        else
            wide=max_wide-x0;
    }
    else
    {
        newx=0;
        offsetx=-x0;
        if(w+x0<max_wide)
            wide=w+x0;
        else
            wide=max_wide;
    }
    
    
    
    
    int max_height=0;
    int height=h+y0;
    if(height<=0)
        return; // l'image ne peut etre affichée
    if(tableOrientation%2==0)
        max_height=LED_HEIGHT;
    else
        max_height=LED_WIDTH;
    
    if (y0>=max_height) //on est en dehors du cadre
        return;
    if(y0>=0)
    {
        newy=y0;
        offsety=0;
        if(h+y0<max_height)
            height=h;
        else
            height=max_height-y0;
    }
    else
    {
        newy=0;
        offsety=-y0;
        if(h+y0<max_height)
            height=h+y0;
        else
            height=max_height;
    }
    
    
    
    int r;
    int g;
    int b;
    // Serial.println("r1");
    CRGB *bitmapRGB =(CRGB*)os_malloc(wide*height*sizeof(CRGB)) ;
    if(bitmapRGB==NULL)
    {
        Serial.println("immossibnle de créer l'image");
        Serial.println(wide);
        Serial.println(height);
        Serial.println(x0);
        Serial.println(y0);
        return;
    }
    //Serial.println("image cree");
    for(int y=0;y<height;y++){
        for(int x=0;x<wide;x++){
          
            r=gammar[(int)pic[3*((y+offsety)*w+x+offsetx)]];
            g=gamma8[ (int)pic[3*((y+offsety)*w+x+offsetx)+1]];
            b= gamma8[(int)pic[3*((y+offsety)*w+x+offsetx)+2]];
           bitmapRGB[x+y*wide]=CRGB(r,g,b); //I have a program that switches directly from
        }
    }
    displaypic(bitmapRGB,newx,newy,height,wide);
    os_free(bitmapRGB);
    
    
    
}


void displayBitmap_old(unsigned char *pic,int x0,int y0,int h,int w )
{
    //
    //Serial.println("r1");
    int r;
    int g;
    int b;
   // Serial.println("r1");
    CRGB *bitmapRGB =(CRGB*)os_malloc(h*w*sizeof(CRGB)) ;
  if(bitmapRGB==NULL)
    {
        Serial.println("immossibnle de créer l'image");

        return;
    }
    Serial.println("image cree");
    for(int y=0;y<h;y++){
        for(int x=0;x<w;x++){
             //int wmin = (w > maxx) ? maxx : w;
            r=gamma8[(int)pic[3*(y*w+x)]];//<0 )     ? (256+(int)pic[3*(y*w+x)]):(int)pic[3*(y*w+x)];
           // Serial.println("r");
            g= gamma8[(int)pic[3*(y*w+x)+1]];//<0 ) ? (256+(int)pic[3*(y*w+x)+1]):(int)pic[3*(y*w+x)+1];
            b= gamma8[(int)pic[3*(y*w+x)+2]];//<0 ) ? (256+(int)pic[3*(y*w+x)+2]):(int)pic[3*(y*w+x)+2];
                // Serial.print(r);Serial.print(";");Serial.print(g);Serial.print(";");Serial.print(b);Serial.println("");
           // bitmapRGB[x+y*w]=CRGB(pic[3*(y*w+x)+2],pic[3*(y*w+x)+1],pic[3*(y*w+x)]);
            //Serial.println("ecrire");
            bitmapRGB[x+y*w]=CRGB(r,g,b);
        }
    }
    displaypic(bitmapRGB,x0,y0,h,w);
    os_free(bitmapRGB);

}

void displayBitmapFromProgmem(const unsigned char *pic,int x0,int y0,int h,int w )
{

    int max_wide=0;
    int wide=w+x0;
    int offsety;
    int offsetx;
    int newx=0;
    int newy=0;
    if(wide<=0)
        return; // l'image ne peut etre affichée
    if(tableOrientation%2==0)
        max_wide=LED_WIDTH;
    else
        max_wide=LED_HEIGHT;
    
    if (x0>=max_wide) //on est en dehors du cadre
        return;
    if(x0>=0)
    {
        newx=x0;
        offsetx=0;
        if(w+x0<max_wide)
            wide=w;
        else
            wide=max_wide-x0;
    }
    else
    {
        newx=0;
        offsetx=-x0;
        if(w+x0<max_wide)
            wide=w+x0;
        else
            wide=max_wide;
    }
    
    
    
    
    int max_height=0;
    int height=h+y0;
    if(height<=0)
        return; // l'image ne peut etre affichée
    if(tableOrientation%2==0)
        max_height=LED_HEIGHT;
    else
        max_height=LED_WIDTH;
    
    if (y0>=max_height) //on est en dehors du cadre
        return;
    if(y0>=0)
    {
        newy=y0;
        offsety=0;
        if(h+y0<max_height)
            height=h;
        else
            height=max_height-y0;
    }
    else
    {
        newy=0;
        offsety=-y0;
        if(h+y0<max_height)
            height=h+y0;
        else
            height=max_height;
    }
    
    
    int r;
    int g;
    int b;

    CRGB *bitmapRGB =(CRGB*)os_malloc(wide*height*sizeof(CRGB)) ;
    if(bitmapRGB==NULL)
    {
        Serial.println("immossibnle de créer l'image");
        return;
    }

    for(int y=0;y<height;y++){
        for(int x=0;x<wide;x++){
            
             r= gammar[(int)pgm_read_byte(pic+ 3*((y+offsety)*w+x+offsetx))];
            g= gamma8[(int)pgm_read_byte(pic+3*((y+offsety)*w+x+offsetx)+1)];
            b= gamma8[(int)pgm_read_byte(pic+3*((y+offsety)*w+x+offsetx)+2)];
            bitmapRGB[x+y*wide]=CRGB(r,g,b); //I have a program that switches directly from
        }
    }
    displaypic(bitmapRGB,newx,newy,height,wide);
    os_free(bitmapRGB);
    
}

void fill(CRGB color)
{
     fill_solid(leds, NUM_LEDS, color);
    fill_solid(Tpic, NUM_LEDS, color);
}


void afficheLettre(int let,int x0,int y0)
{
    
    int taille=5;
    int hauteur=7;
    
    for(int x=x0;x<taille+x0;x++)
    {
        for (int y=y0;y<hauteur+y0;y++)
        {
            if ( ( (1 << (x0-x+taille-1)) &   font1[let][hauteur-1 - y + y0] ) > 0 )
            {
                lettrefont1[(x-x0)+(y-y0)*5]=CRGB(Color);
            }
            else
            {
                lettrefont1[(x-x0)+(y-y0)*5]=CRGB(bgColor);
            }
        }
    }
    
    displaypic(lettrefont1,x0,y0,7,5);
    
}


void afficheMessage(char *mess,int x,int y)
{
    if (!mess)
        return;
    int taille=strlen(mess);
    //Serial.println(mess);
    //Serial.println(taille);
    
    for (int i=0;i<taille;i++)
    {
       if(x+i*6 > -6 and x+i*6 <LED_WIDTH)
        afficheLettre(mess[i]-32, x+i*6,y);
        
        if (x+i*6> LED_WIDTH)
            return;
    }
    
}

void afficheMessageInv(char *mess,int x,int y)
{
    if (!mess)
        return;
    int taille=strlen(mess);
    Serial.println(mess);
    Serial.println(taille);
    
    for (int i=0;i<taille;i++)
    {
        afficheLettre(mess[i]-32, x-i*6,y);
    }
    
}

void initServer()
{
    server.serveStatic("/", SPIFFS, "/index.html");
    server.serveStatic("/index.html", SPIFFS, "/index.html");
    server.serveStatic("/jquery.js", SPIFFS, "/jquery.js");
    
    server.serveStatic("/farbtastic.js", SPIFFS, "/farbtastic.js");
    
    server.serveStatic("/farbtastic.css", SPIFFS, "/farbtastic.css");
    
    server.serveStatic("/marker.png", SPIFFS, "/marker.png");
    
    server.serveStatic("/mask.png", SPIFFS, "/mask.png");
    
    server.serveStatic("/wheel.png", SPIFFS, "/wheel.png");
    
    server.on("/changetext", HTTP_GET, []() {
        //fill_solid(leds, NUM_LEDS, solidColor);
        //FastLED.show();
        
        String g = server.arg("v");
        Serial.println(g);
        //strcopy(g);
        //mess = g;
       // k2 = 0;
        //Serial.println(mess);
        int lens = g.length();
        g.toCharArray(mess, lens);
        //Serial.println(lens);
        //fill_solid(leds, NUM_LEDS, bgColor);
       // FastLED.show();
        server.send(200, "text/html", "done");
        // i=0;
    });
    server.on("/up", HTTP_GET, []() {
        //fill_solid(leds, NUM_LEDS, solidColor);
        //FastLED.show();
        
        //String g = server.arg("v");
              tableOrientation=(tableOrientation+1)%8;
        server.send(200, "text/html", "done");
        // i=0;
    });
    server.on("/down", HTTP_GET, []() {
        //fill_solid(leds, NUM_LEDS, solidColor);
        //FastLED.show();
        
        //String g = server.arg("v");
        tableOrientation=abs((tableOrientation-1))%8;
        server.send(200, "text/html", "done");
        // i=0;
    });
}


bool initTable(int w,int h)
{
    
    system_update_cpu_freq(SYS_CPU_160MHZ);
    Serial.begin(115200);
    delay(100);
    Serial.setDebugOutput(true);
    
    uint32_t realSize = ESP.getFlashChipRealSize();
    uint32_t ideSize = ESP.getFlashChipSize();
    FlashMode_t ideMode = ESP.getFlashChipMode();
    
    Serial.printf("Flash real id:   %08X\n", ESP.getFlashChipId());
    Serial.printf("Flash real size: %u\n\n", realSize);
    
    Serial.printf("Flash ide  size: %u\n", ideSize);
    Serial.printf("Flash ide speed: %u\n", ESP.getFlashChipSpeed());
    Serial.printf("Flash ide mode:  %s\n", (ideMode == FM_QIO ? "QIO" : ideMode == FM_QOUT ? "QOUT" : ideMode == FM_DIO ? "DIO" : ideMode == FM_DOUT ? "DOUT" : "UNKNOWN"));
    
    if(ideSize != realSize) {
        Serial.println("Flash Chip configuration wrong!\n");
    } else {
        Serial.println("Flash Chip configuration ok.\n");
    }
    LED_WIDTH=w;
    LED_HEIGHT=h;
    NUM_LEDS=w*h;
   leds =(CRGB*)malloc(NUM_LEDS*sizeof(CRGB)) ;
    Tpic =(CRGB*)malloc(NUM_LEDS*sizeof(CRGB)) ;
    if(!leds )
    {
        Serial.println("Unable to create the screen");
        isTable=false;
        return false;
    }
    if(!Tpic)
    {
        Serial.println("Unable to create the screen tpic");
        isTable=false;
        return false;
    }
    Serial.println("Table crééssse");
    Serial.println(NUM_LEDS);
    Serial.println(LED_WIDTH);
    Serial.println(LED_HEIGHT);
    isTable=true;
   //FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS   )  ;
    FastLED.addLeds<WS2811_PORTA,2>(leds, 300);
    fill(CRGB(10, 10, 10));
    FastLED.show();
    //FastLED.setBrightness(DEFAULT_BRIGHTNESS);
    setTableBrightness(DEFAULT_BRIGHTNESS);
   // FastLED.setCorrection(TypicalSMD5050);
    int saveTable=tableOrientation;
    tableOrientation=DOWN_RIGHT_INV;
    CRGB savecol=Color;
    Color=CRGB(255,0,0);
    fill(CRGB(10, 10, 10));
    afficheMessage("INIT",5,5);
    FastLED.show();
    WiFi.mode(WIFI_STA);
    Serial.printf("Connecting to %s\n", "WiFi-2.4-E19C");
    Serial.printf("Connecting ");
    WiFi.begin("WiFi-2.4-E19C", "yvesyves");
    while (WiFi.status() != WL_CONNECTED) {
         delay(500);
         Serial.print(".");
     }
     
     Serial.print("Connected! Open http://");
     Serial.print(WiFi.localIP());
     Serial.println(" in your browser");
    ArduinoOTA.setHostname("ledtable");
    ArduinoOTA.onStart([]() {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
            type = "sketch";
        else // U_SPIFFS
            type = "filesystem";
        
        // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
        Serial.println("Start updating " + type);
    });
    ArduinoOTA.onEnd([]() {
        Serial.println("\nEnd");
    });
    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
        Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
    });
    ArduinoOTA.onError([](ota_error_t error) {
        Serial.printf("Error[%u]: ", error);
        if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
        else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
        else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
        else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
        else if (error == OTA_END_ERROR) Serial.println("End Failed");
        ESP.restart();
    });
    
    ArduinoOTA.begin();
    MDNS.addService("http","tcp",80);
    MDNS.addService("ws", "tcp", 81);
  // if(mdns.begin("ledtable",WiFi.localIP()))
   // Serial.println("MDNS has started");
     SPIFFS.begin();
     
     Dir dir = SPIFFS.openDir("/");
     while (dir.next()) {
         String fileName = dir.fileName();
         size_t fileSize = dir.fileSize();
         Serial.printf("FS File: %s, size: %s\n", fileName.c_str(), String(fileSize).c_str());
     }

     initServer();

    
    fill(CRGB(10, 10, 10));
    afficheMessage("DONE",5,5);
    FastLED.show();
    tableOrientation=saveTable;
    Color=savecol;
    delay(2000);
         return true;
}

void runTable()
 {
     if(isTable)
     {
         server.begin();
     }
 }
         
void handleTable()
 {
     server.handleClient();
      //ArduinoOTA.handle();
 }

#endif /* ledTable_h */

