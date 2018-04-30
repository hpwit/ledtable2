//
//  gameoflife.h
//  
//
//  Created by Yves BAZIN on 10/12/17.
//

#ifndef gameoflife_h
#define gameoflife_h



byte stayalivewhenalive[9] ={0,0,1,1,0,0,0,0,0};
byte bornwhendead [9]={0,0,0,1,0,0,0,0,0};


byte countNeighbours(byte x,byte y);
byte isPixelOn(byte x,byte y);
byte newStatus(byte x,byte y);

bool ongoing=false;


byte isPixelOn(byte x,byte y)
{
    int offset=0;
    if (x<0 or y<0 or x>=LED_WIDTH or y>=LED_HEIGHT)
        return 0;
    if(y%2==0)
        offset=x+y*LED_WIDTH;
    else
        offset=2 * LED_WIDTH * ((int)floor(y / 2) + 1) - 1 - x;
    if(leds[offset]!=bgColor)
        return 1;
    else
        return 0;
}


byte countNeighbours(byte x,byte y)
{
    //byte nb=0;
    return isPixelOn(x-1,y)+isPixelOn(x+1,y)+isPixelOn(x-1,y-1)+isPixelOn(x,y-1)+isPixelOn(x+1,y-1)+isPixelOn(x-1,y+1)+isPixelOn(x,y+1)+isPixelOn(x+1,y+1);

}

byte newStatus(byte x,byte y)
{
    byte nb=countNeighbours(x,y);
    if(isPixelOn(x,y))
        return stayalivewhenalive[nb];
    else
        return bornwhendead[nb];
}

void gameOflife()
{
   long time1=ESP.getCycleCount();
   if(ongoing)
   {
    for(byte i=0;i<LED_WIDTH;i++)
        for(byte j=0;j<LED_HEIGHT;j++)
        {
            if(newStatus(i,j))
                Tpic[i+j*LED_WIDTH]=CRGB::Red;
            else
                Tpic[i+j*LED_WIDTH]=bgColor;
        }
   }
    else
    {
        fill(bgColor);
       /* for (int y=0;y<LED_HEIGHT;y++)
            Tpic[15+y*LED_WIDTH]=CRGB::Red;*/
        for(int l=0 ;l<LED_WIDTH*LED_HEIGHT;l++)
            if(random(20)%2==0)
                Tpic[l]=CRGB::Red;
        ongoing=true;
    }
    
    displayTpic();
    long time3=ESP.getCycleCount();
    //delay(100);
    //FastLED.show();
    long time2=ESP.getCycleCount();
    Serial.print((float)160000000/(time2-time1));
    Serial.println(" FPS game of life");
    Serial.print((float)160000000/(time3-time1));
    Serial.println(" FPS cacule life");
    Serial.print((float)160000000/(time2-time3));
    Serial.println(" FPS show");
    delay(50);
}







#endif /* gameoflife_h */
