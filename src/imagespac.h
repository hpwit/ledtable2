//
//  imagespac.h
//  
//
//  Created by Yves BAZIN on 20/02/18.
//

#ifndef imagespac_h
#define imagespac_h
//Define table orientation this is where the pixel 0 is
#define DOWN_RIGHT   0 //natural mode no transpostion to be made
#define DOWN_LEFT    1 //We turn 90° clock wise
#define UP_LEFT      2
#define UP_RIGHT     3
#define DOWN_RIGHT_INV   4 //natural mode no transpostion to be made
#define DOWN_LEFT_INV    5 //We turn 90° clock wise
#define UP_LEFT_INV      6
#define UP_RIGHT_INV     7
//i hvae decided to have 4 pictures for this gif

int pacmab[100]={
    9,1,1,1,9,
    1,1,1,1,1,
    1,1,1,1,1,
    1,1,1,1,1,
    9,1,1,1,9,
    
    9,1,1,1,9,
    1,1,1,1,1,
    9,9,1,1,1,
    1,1,1,1,1,
    9,1,1,1,9,
    
    9,1,1,1,9,
    9,9,1,1,1,
    9,9,9,1,1,
    9,9,1,1,1,
    9,1,1,1,9,
    
    
    9,1,1,1,9,
    1,1,1,1,1,
    9,9,1,1,1,
    1,1,1,1,1,
    9,1,1,1,9,
    
};


//the actula image
CRGB pacmancalc[100];




CRGB  ghost[14][14] = {
    {0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0},
    {1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 3, 3, 1, 1, 1, 1, 3, 3, 1, 1},
    {1, 1, 1, 3, 3, 2, 2, 1, 1, 3, 3, 2, 2, 1},
    {0, 1, 1, 3, 3, 2, 2, 1, 1, 3, 3, 2, 2, 1},
    {0, 1, 1, 3, 3, 3, 3, 1, 1, 3, 3, 3, 3, 1},
    {0, 1, 1, 1, 3, 3, 1, 1, 1, 1, 3, 3, 1, 0},
    {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
    {0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0},
    {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0}
};
CRGB ghostred[296];
CRGB ghostyellow[296];
CRGB ghostgreen[296];
CRGB ghostPurple[296];
CRGB ghostCyan[296];


CRGB fraise[11][10] = {
    {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
    {0, 0, 0, 1, 2, 1, 1, 0, 0, 0},
    {0, 0, 1, 1, 1, 1, 2, 1, 0, 0},
    {0, 1, 2, 1, 2, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 1, 1, 2, 1, 0},
    {1, 1, 2, 1, 2, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 1, 1, 2, 1, 2, 1},
    {1, 2, 1, 2, 1, 3, 1, 1, 1, 1},
    {0, 1, 1, 1, 3, 3, 3, 1, 2, 0},
    {0, 0, 3, 3, 3, 2, 3, 3, 3, 0},
    {0, 0, 0, 0, 0, 2, 0, 0, 0, 0}
};


int YO = 0;

int cerise[196] = {
    100, 100, 100, 0, 0, 0, 0, 100, 100, 100, 100, 100, 100, 100,
    100, 100, 0, 1, 1, 1, 1, 0, 100, 100, 100, 100, 100, 100,
    100, 0, 1, 1, 2, 2, 1, 1, 0, 0, 0, 0, 100, 100,
    100, 0, 1, 1, 1, 1, 2, 1, 0, 1, 1, 1, 0, 100,
    100, 0, 1, 1, 1, 1, 1, 1, 0, 2, 2, 1, 1, 0,
    100, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 2, 1, 0,
    100, 100, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0,
    100, 100, 100, 0, 0, 3, 0, 1, 1, 1, 1, 1, 1, 0,
    100, 100, 100, 0, 3, 0, 100, 0, 1, 1, 1, 1, 0, 100,
    100, 100, 0, 3, 0, 0, 0, 3, 0, 0, 0, 0, 100, 100,
    100, 0, 0, 3, 0, 3, 3, 0, 100, 100, 100, 100, 100, 100,
    0, 3, 3, 3, 3, 0, 0, 100, 100, 100, 100, 100, 100, 100,
    0, 3, 3, 0, 0, 100, 100, 100, 100, 100, 100, 100, 100, 100,
    100, 0, 0, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100
};

int mario[238]={
    100,3,3,100,100,100,100,100,100,100,100,100,100,100,100,100,100,
    100,3,3,3,2,2,2,2,2,2,100,100,100,100,100,100,100,
    100,100,3,3,2,2,2,2,2,2,2,2,2,2,3,3,100,
    100,100,100,100,2,2,2,2,4,2,2,2,2,2,3,3,100,
    100,5,5,1,1,1,1,2,2,2,2,4,2,2,3,3,100,
    5,5,1,1,1,1,1,2,1,1,1,2,100,100,3,3,100,
    5,5,1,1,1,1,2,1,1,1,2,1,1,100,100,3,100,
    100,100,100,100,100,5,5,5,5,5,5,5,1,1,100,100,100,
    100,100,100,3,3,5,5,5,5,6,6,6,6,1,100,100,100,
    100,100,100,3,5,3,3,5,5,5,6,5,5,5,1,100,100,
    100,100,100,3,5,3,5,5,5,6,5,5,5,1,1,100,100,
    100,100,100,100,3,3,3,5,5,6,5,100,1,1,1,100,100,
    100,100,100,100,1,1,1,1,1,1,1,1,1,5,5,100,100,
    100,100,100,100,100,1,1,1,1,1,100,100,5,5,5,100,100
};

CRGB fraiseCalc[110];

//this allow to associate a color to the value hence with the same template I can change mario pants color
CRGB palec[4] = {CRGB::Black, CRGB::Red, CRGB::White, CRGB::Green};
CRGB palpacman[2]={CRGB::Black,CRGB::Yellow};

CRGB palm[7]={CRGB:: Red,CRGB::Red, CRGB::Blue,CRGB(98,65,7),CRGB::Yellow,CRGB(238,151,64),CRGB::Black};


// this function replace the 1,2,3 by the color you want to use in your palette
void calculpic(int *pic, CRGB *palette, CRGB color, int h, int w,CRGB *result)
{
    Serial.println("on est là");
    int to = h * w;
    // static CRGB result[296];
    for (int m = 0; m < h; m++)
    {
        for (int y = 0; y < w; y++)
        {
            
            result[m * w + y] = palette[pic[m * w + y]];
            //Serial.print(palette[pic[m * w + y]]);
            //Serial.printf(":%d\n", pic[m * w + y]);
            
            
            if (pic[m * w + y] == 100)
            {
                result[m * w + y] = color;
                
            }
            if (pic[m * w + y] == 9)
            {
                result[m * w + y] = color;
                
            }
            
        }
    }
    // return result;
    
}



void calculghosts(CRGB color)
{
    for (int m = 0; m < 14; m++)
    {
        for (int y = 0; y < 14; y++)
        {
            if (ghost[m][y] == (CRGB)1)
            {
                ghostred[m * 14 + y] = CRGB :: Red;
                ghostyellow[m * 14 + y] = CRGB :: Yellow;
                ghostgreen[m * 14 + y] = CRGB :: Green;
                ghostPurple[m * 14 + y] = CRGB :: Purple;
                ghostCyan[m * 14 + y] = CRGB(64, 222, 255);
            }
            if (ghost[m][y] == (CRGB)2)
            {
                ghostred[m * 14 + y] = CRGB :: Blue;
                ghostyellow[m * 14 + y] = CRGB :: Blue;
                ghostgreen[m * 14 + y] = CRGB :: Blue;
                ghostPurple[m * 14 + y] = CRGB :: Blue;
                ghostCyan[m * 14 + y] = CRGB :: Blue;
            }
            
            if (ghost[m][y] == (CRGB)3)
            {
                ghostred[m * 14 + y] = CRGB :: White;
                ghostyellow[m * 14 + y] = CRGB :: White;
                ghostgreen[m * 14 + y] = CRGB :: White;
                ghostPurple[m * 14 + y] = CRGB :: White;
                ghostCyan[m * 14 + y] = CRGB :: White;
            }
            if (ghost[m][y] == (CRGB)0)
            {
                ghostred[m * 14 + y] = color;
                ghostyellow[m * 14 + y] = color;
                ghostgreen[m * 14 + y] = color;
                ghostPurple[m * 14 + y] = color;
                ghostCyan[m * 14 + y] = color;
            }
            
        }
    }
}




CRGB cerisecalc[196];

CRGB mariocalc[238];
void calculfraise(CRGB color)
{
    for (int m = 0; m < 11; m++)
    {
        for (int y = 0; y < 10; y++)
        {
            if (fraise[m][y] == (CRGB)1)
            {
                fraiseCalc[m * 10 + y] = CRGB :: Red;
                
            }
            if (fraise[m][y] == (CRGB)2)
            {
                fraiseCalc[m * 10 + y] = CRGB :: White;
                
            }
            
            if (fraise[m][y] == (CRGB)3)
            {
                fraiseCalc[m * 10 + y] = CRGB :: Green;
                
            }
            if (fraise[m][y] == (CRGB)0)
            {
                fraiseCalc[m * 10 + y] = color;
                
            }
            
        }
    }
}






//then you need to display the pic


void displaygif( CRGB *pica, long int x0, long int y0, long int h, long int w,int pic)
{
    
    CRGB *bitmapRGB =(CRGB*)malloc(w*h*sizeof(CRGB)) ;
    if(bitmapRGB==NULL)
    {
        Serial.println("immossibnle de créer l'image");
        return;
    }
    
    memcpy ( bitmapRGB, pica+(h*w*pic), h*w*sizeof(CRGB) );
    displaypic( bitmapRGB, x0, y0,  h,  w);
    
    free(bitmapRGB);
}








//here the fonction i have created by it's really based on you mapping which is not classical because led 0 of strip 1 is not vertically alinged with led 0 of strip 2 ..



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
                            //leds[2 * LED_WIDTH * ((int)floor(y / 2) + 1) - 1 - x] = Tpic[wmin * (y - y0) + x - x0 ];
                            leds[(LED_WIDTH <<1)* ( (y>>1) + 1) - (1 + x)] = Tpic[wmin * (y - y0) + x - x0 ];
                    }
                }
            }
        }
        
    }
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



//how to use
#define LED_WIDTH 30
#define LED_HEIGHT 20
int tableOrientation;
void setup()
{
tableOrientation=DOWN_RIGHT_INV; //by changing this value you virtually change the orientation of you matrix no

//first calculate the image based on the template and the color palette
calculghosts(solidColor); //here i could have used calculpic
calculfraise(solidColor); //same here
calculpic(cerise, palec, solidColor, 14, 14,cerisecalc);
calculpic(mario, palm, solidColor, 14, 17,mariocalc);
calculpic(pacmab, palpacman, solidColor, 5, 20,pacmancalc);
}

void loop()
{
    
    int f=110+30+180+40;
    fill(bgColor);
    for(int l=0 ;l<1;l++)
    {
        Y1=0;
        displaypic(cerisecalc, -k%f+ offset , Y1, 14, 14);
        displaypic(fraiseCalc, -k%f+ offset + 14 , Y1 + 2, 11, 10);
        displaypic(ghostred, -k%f + offset + 30, Y1, 14, 14);
        displaypic(ghostyellow, -k%f + offset +46, Y1, 14, 14);
        displaypic(ghostgreen, -k%f + offset + 62, Y1, 14, 14);
        displaypic(ghostPurple, -k%f + offset +78, Y1, 14, 14);
        displaypic(ghostCyan, -k%f + offset + 94, Y1, 14, 14);
        displaypic(mariocalc, -k%f + offset+110 , Y1, 14, 17);
        displaygif(pacmancalc,-k%f+offset+110+30,Y1+8,5,5,(k/7) %4);
       // afficheMessage(mess, -k%f+ offset + 110+40, YO + 7);
        displaygif(pacmancalc,-k%f+offset+110+30+170,Y1+8,5,5,(k/5) %4);
        displaygif(pacmancalc,-k%f+offset+110+30+180,Y1+8,5,5,(k/5) %4);
        
    }
k++
    Fastled.show();
}



#endif /* imagespac_h */
