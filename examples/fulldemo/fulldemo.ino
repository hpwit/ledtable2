
 #include "ledTable.h"
#include "images.h"
#include "yves_image.h"
#include "mariomap.h"
#include "tetris.h"
#include "gameoflife.h"
#include "paint.h"
#include "meteo.h"
#include "vivi.h" 
#include "dateheure.h"

#include "graphicfunction.h"
#include "lamp.h"
int k = 0;
long timeNow = 0;
float maxi=0;
float mini=9999;
int r=0;
int dire=0;
int pas=45;
bool switchanim = false;
bool firsttime = true;
long time1;
 // WiFiServer telnetServer(23);
//WiFiClient telnetserverClient;
void setup() {
  //system_update_cpu_freq(SYS_CPU_160MHZ);
  //Serial.begin(115200);
  //delay(100);
  //Serial.setDebugOutput(true);
  Color = CRGB::Red;

  calculghosts(bgColor) ;
  calculfraise(bgColor);
  calculpic(cerise, palec, bgColor, 14, 14, cerisecalc);
  calculpic(mario, palm, bgColor, 14, 17, mariocalc);
  calculpic(mario, pall, bgColor, 14, 17, luigicalc);

  if (initTable(30, 20)) //size of your led grid (wide*height)
  {

    fill(bgColor);


    FastLED.show();

    tableOrientation = DOWN_RIGHT_INV;

    //TETRIS_HEIGHT=25;
    //TETRIS_WIDTH=12;
    inGame = false;
    initTetris();
    initPaint();
    initlamp();

    //used if i want ta change table orientation )
    runTable();

  }
 // telnetServer.begin();
  //telnetServer.setNoDelay(true);
}


void loop() {
 /* if (telnetServer.hasClient()) {
    if (!telnetserverClient || !telnetserverClient.connected()) {
      if (telnetserverClient) {
        telnetserverClient.stop();
        Serial.println("                                               Telnet Client Stop");
      }
      telnetserverClient = telnetServer.available();
      Serial.println("                                                   New Telnet client");
      telnetserverClient.flush();  // clear input buffer, else you get strange characters 
    }
  }*/
  /*while(telnetserverClient.available()) {  // get data from Client
    Serial.write(telnetserverClient.read());
  }*/
  handleTable();
   ArduinoOTA.handle();
  int offset = +30;;
  int YO = 0;
  if (isTable) {

    if (!inGame)
    {
      if (!inPaint)
      {

        if (justLost)
        {

          fill(CRGB(0, 255, 0));
          CRGB saveColor = Color;
          CRGB savebgColor = bgColor;
          bgColor = CRGB(0, 255, 0);
          Color = CRGB(255, 255, 255);
          afficheMessage("LOST", 0, 10);
          char str[6];
          sprintf(str, "%d L", score);
          //Serial.println(str);
          afficheMessage(str, 1, 1);
          FastLED.show();
          //interrupts();
          FastLED.delay((int)(3000 ));
          // interrupts();
          //delay(3000);
          Color = saveColor;
          bgColor = savebgColor;
          justLost = false;
          ongoing = false;
        }


        switch (anim) {

          case 0:
            {
              switchanim = false;
              if (firsttime)
              {
                fill(bgColor);
                Color = CRGB::Red;
                afficheMessage("SCROLL", 0, 3);
                FastLED.show();
                FastLED.delay((int)(1000 / 100));
                delay(1000);
                firsttime = false;
              }
              long time1=ESP.getCycleCount();
              fill(bgColor);
              displayPicInv(cerisecalc, -k + offset, YO, 14, 14);

              displayPicInv(fraiseCalc, -k + offset + 14 , YO + 2, 11, 10);
              displayPicInv(ghostred, -k + offset + 30, YO, 14, 14);
              displayPicInv(ghostyellow, -k + offset + 46, YO, 14, 14);
              displayPicInv(ghostgreen, -k + offset + 62, YO, 14, 14);
              displayPicInv(ghostPurple, -k + offset + 78, YO, 14, 14);
              displayPicInv(ghostCyan, -k + offset + 94, YO, 14, 14);
              displayPicInv(mariocalc, -k + offset + 110 , YO, 14, 17);
              displayPicInv(luigicalc, -k + offset + 127 , YO, 14, 17);
              displayBitmap(mickey, -k + offset + 127 + 17, YO, 30, 32);
              displayBitmap(champi, -k + offset + 127 + 17 + 35, YO + 3, 16, 16);
              displayBitmapFromProgmem(lapin,-k+offset+127+17+35+18,YO,30,23);
              Color = CRGB::Red;
              afficheMessage(mess, -k + offset + 127 + 17 + 35 + 18+26, YO + 7);
                long time3=ESP.getCycleCount();
             //delay(100);
               FastLED.show();
                                 long time2=ESP.getCycleCount();
  Serial.print((float)160000000/(time2-time1));
  Serial.println(" FPS scroll total");
   Serial.print((float)160000000/(time3-time1));
  Serial.println(" FPS cacule scroll");
    Serial.print((float)160000000/(time2-time3));
  Serial.println(" FPS show");
  //Serial.println((float)time2*1000/160000000);
              k++;
              if (k == offset + 127 + 17 + 35 + 20 + 26+(sizeof(mess)+14) * 5)
              {
                switchanim = true;
                ongoing = false;
                //k=0;
                fill(bgColor);

              }
            }
            break;

          case 1:
            {
              switchanim = false;
              if (firsttime)
              {
                afficheMessage("GAME", 0, 12);
                afficheMessage(" LIFE", 0, 3);
                FastLED.show();
                FastLED.delay((int)(1000 / 100));
                delay(1000);
                fill(CRGB(5, 5, 5));
                firsttime = false;
              }
              gameOflife();
              k = k + 1;
              if (k == 200)
              {
                // anim=2;
                switchanim = true;
                // k=0;


              }
            }
            break;

          case 26: {
              switchanim = false;
              if (firsttime)
              {
                fill(bgColor);

                afficheMessage("IMAGE", 0, 3);
                FastLED.show();
                FastLED.delay((int)(1000 / 100));
                delay(1000);
                firsttime = false;
              }
              k++;
                long time1=ESP.getCycleCount();
              int nb = 10;
              int d = 64;
              d = d - 30;
              int g = 84;
              fill(CRGB::Black);
              if ((int)(k / d) % 2 == 0)
                offset = -(k % d);
              else
                offset = -d + (k % d);
              // time1=millis();
              displayBitmapFromProgmem(yves, offset, -(int)(k / d) * g / nb , g, d + 30);
              //Serial.println((long)(1/(millis()-time1)));
              if (k >= d * nb) //o ermove 0
              {
                switchanim = true;
                k = 0;
                fill(bgColor);
                firsttime = true;

              }
              long time3=ESP.getCycleCount();
             //delay(100);
               FastLED.show();
                                 long time2=ESP.getCycleCount();
  Serial.print((float)160000000/(time2-time1));
  Serial.println(" FPS photo total");
   Serial.print((float)160000000/(time3-time1));
  Serial.println(" FPS cacule photo");
    Serial.print((float)160000000/(time2-time3));
  Serial.println(" FPS show");
  
            }

            break;

          case 2: {
              switchanim = false;
              fill(bgColor);
              afficheMessage("METEO", 0, 3);
              FastLED.show();
              FastLED.delay((int)(1000 / 100));
              delay(1000);
              getMeteo();
              switchanim = true;
              FastLED.show();
            }
            break;

          case 3:{
              switchanim = false;
              fill(bgColor);
              afficheMessage("TIME", 0, 3);
             FastLED.show();
              FastLED.delay((int)(1000 / 100));
              delay(1000);
           // afficheMessage("JE SUIS", 0, 3);

              afficherTime();
              switchanim = true;
              FastLED.show();
          }
          break;

          case 4:{
            switchanim = false;
             if (firsttime)
              {
                fill(bgColor);
                afficheMessage("RAINBOW", 0, 3);
                FastLED.show();
                FastLED.delay((int)(1000 / 100));
                delay(1000);
                fill(CRGB(5, 5, 5));
                firsttime = false;
              }
             
              for(int i = 0; i < 20;i++) {
                    for(int j = 0; j < 30; j++) {
                      leds[i*30 + j] = CHSV((32*i) + k+j,192,255);
                    }
                  }
               k = k + 10;
               FastLED.show();
              if (k > 2000)
              {
                // anim=2;
                switchanim = true;
                // k=0;


              }
          }
          break;

          case 5:{
                     switchanim = false;
             if (firsttime)
              {
                r=0;
                fill(bgColor);
                afficheMessage("LINES", 0, 3);
                FastLED.show();
                FastLED.delay((int)(1000 / 100));
                delay(1000);
                fill(CRGB(5, 5, 5));
                firsttime = false;
                k=0;
                
              }
              long time1=ESP.getCycleCount();
             if(dire>=0)
             {
                r=r+1;
                if(r>50)
                  dire=-1;
             }
              else
              {
                r=r-1;
                if(r<1)
                  dire=0;
              }
              //r=(r+(int)k/10)%20;
             fill(CRGB(5, 5, 5));
              dessinePoly(15,9, r,k*pi/360,4,CRGB::Red);
             int r1=r-5;
             dessinePoly(15,9, r1,k*1.5*pi/360,3,CRGB::Green);
  
              r1=r-10;
 
             dessinePoly(15,9, r1,-k*pi/360,5,CRGB::Yellow);
              r1=r-15;
             dessinePoly(15,9, r1,+k*2*pi/360,4,CRGB::Blue);
                     
              r1=r-20;      
             dessinePoly(15,9, r1,-k*1.5*pi/360,3,CRGB::Purple);
             r1=r-25;
             dessinePoly(15,9, r1,k*1.5*pi/360,4,CRGB::Green);
  
              r1=r-30;
 
             dessinePoly(15,9, r1,-k*pi/360,5,CRGB::Yellow);
              r1=r-35;
             dessinePoly(15,9, r1,+k*2*pi/360,3,CRGB::Red);
                     
              r1=r-40;      
             dessinePoly(15,9, r1,-k*1.5*pi/360,3,CRGB::Blue);
             
             k=k+15;
             //delay(100);
              long time3=ESP.getCycleCount();
             //delay(100);
               FastLED.show();
                                 long time2=ESP.getCycleCount();
  Serial.print((float)160000000/(time2-time1));
  Serial.println(" FPS line total");
   Serial.print((float)160000000/(time3-time1));
  Serial.println(" FPS cacule line");
    Serial.print((float)160000000/(time2-time3));
  Serial.println(" FPS show");
 /* if (telnetserverClient && telnetserverClient.connected()) {
    //telnetserverClient.printf("%f",(float)160000000/(time2-time1));
    char buf[12];
    sprintf( buf, "%.2f",(float)160000000/(time2-time1));
    telnetserverClient.write(buf,6);
  telnetserverClient.write(" FPS line total\n",17);
   //telnetserverClient.printf("%f",(float)160000000/(time3-time1));
   sprintf( buf, "%.2f",(float)160000000/(time3-time1));
    telnetserverClient.write(buf,6);
  telnetserverClient.write(" FPS cacule line\n",17);
   // telnetserverClient.printf("%.2f",(float)160000000/(time2-time3));
      sprintf( buf, "%.2f",(float)160000000/(time2-time3));
    telnetserverClient.write(buf,6);
  telnetserverClient.write(" FPS show\n\n",11);
   }*/
  //Serial.println((float)time2*1000/160000000);
              if (k > 5000)
              {
                // anim=2;
                switchanim = true;
                // k=0;


              }
             
          }
          break;



          case 6:{
                     switchanim = false;
             if (firsttime)
              {
                r=0;
                afficheMessage("CIRCLES", 0, 3);
                FastLED.show();
                FastLED.delay((int)(1000 / 100));
                delay(1000);
                fill(CRGB(5, 5, 5));
                firsttime = false;
                k=0;
                
              }
              long time1=ESP.getCycleCount();
             if(dire>=0)
             {
                r=r+1;
                if(r>40)
                  dire=-1;
             }
              else
              {
                r=r-1;
                if(r<-10)
                  dire=0;
              }
              //r=(r+(int)k/10)%20;
             fill(CRGB(5, 5, 5));
             
             BresenhamCircle(20,8,r-15,CRGB::Yellow);
             BresenhamCircle(10,8,r-10,CRGB:: Blue);
             BresenhamCircle(15,0,r-5,CRGB::Cyan);
             BresenhamCircle(15,10,r,CRGB::Purple);
             BresenhamCircle(15,20,r+5,CRGB::Red);
             BresenhamCircle(15,8,r+10,CRGB::Green);
             BresenhamCircle(15,8,r+15,CRGB::Yellow);
             BresenhamCircle(15,8,r-20,CRGB::Red);
             BresenhamCircle(22,12,r-25,CRGB::Cyan);
             BresenhamCircle(7,4,r-25,CRGB::Purple);
             BresenhamCircle(40,0,r+5,CRGB::Purple);
             //ligne(x1,y1,x2,y2);
             //BresenhamEntier(x1,y1,x2,y2);
             k=k+15;
             long time3=ESP.getCycleCount();
             //delay(100);
               FastLED.show();
                                 long time2=ESP.getCycleCount();
  Serial.print((float)160000000/(time2-time1));
  Serial.println(" FPS circle total");
   Serial.print((float)160000000/(time3-time1));
  Serial.println(" FPS cacule circle");
    Serial.print((float)160000000/(time2-time3));
  Serial.println(" FPS show");
  //Serial.println((float)time2*1000/160000000);
              if (k > 5000)
              {
                // anim=2;
                switchanim = true;
                // k=0;


              }
             
          }
          break;
          
          case 10:
          {
            switchanim = false;
             if (firsttime)
              {
                r=0;
                afficheMessage("CIR S", 0, 3);
                FastLED.show();
                FastLED.delay((int)(1000 / 100));
                delay(1000);
                fill(CRGB(5, 5, 5));
                firsttime = false;
                k=0;
                //drawCircle2(5,20,10,CRGB::Blue);
                BresenhamCircle(25,5,10,CRGB::Red);
                circle(5,15,10,CRGB::Yellow);
               // drawCircle3(25,20,10,CRGB::Purple);
                FastLED.show();
                delay(20000);
                switchanim = true;
              }
          }
    break;


            case 9:
          {
            fill(bgColor);
            switchanim = false;
             if (firsttime)
              {
                r=0;
                afficheMessage("MARIO", 0, 3);
                FastLED.show();
                FastLED.delay((int)(1000 / 100));
                delay(1000);
                fill(CRGB(5, 5, 5));
                firsttime = false;
                k=1;
                //drawCircle2(5,20,10,CRGB::Blue);
                //BresenhamCircle(25,5,10,CRGB::Red);
                //circle(5,15,10,CRGB::Yellow);
               // drawCircle3(25,20,10,CRGB::Purple);
                //FastLED.show();
                //delay(20000);
                //switchanim = true;
                dire=-1;
               // pas=0;
              }
              delay(8);
               displayBitmapFromProgmem(mariomap,-k+30,YO+r,40,703);
               displayBitmapFromProgmem(mariomap3,-k+30+703,YO+r,40,792);
                
            if(dire>=0)
             {
              
               // r=r+(k%pas/(pas-1));
                if(r>=0)
                  dire=-1;
             }
              else
              {
               // r=r-(k%pas/(pas-1));
                if(r<-14)
                  dire=1;
              }
              if(k%(pas-1)==0)
              {
                FastLED.show();
               for(int g=0;g<5;g++)
               {
                
                displayBitmapFromProgmem(mariomap,-k+30,YO+r,40,703);
                   displayBitmapFromProgmem(mariomap3,-k+30+703,YO+r,40,792);
               
               
               FastLED.show();
               k++;
                displayBitmapFromProgmem(mariomap,-k+30,YO+r,40,703);
                   displayBitmapFromProgmem(mariomap3,-k+30+703,YO+r,40,792);
                   FastLED.show();
               r+=dire;
               }
               r-=dire;
               
              // k++;
                //  displayBitmapFromProgmem(mariomap,-k+30,YO+r,40,703);
                 // displayBitmapFromProgmem(mariomap3,-k+30+703,YO+r,40,792);
               //FastLED.show();
              }
              //displayBitmapFromProgmem(mariomap2,-k+1+30+703+703,YO+r,40,519);
            //  displayBitmapFromProgmem(mariomap2,-k+1+30+703+703+519,YO+r,40,519);
              //FastLED.show()2

              
                
          /*  if(dire>=0)
             {
              
                r=r+(k%5/4);
                if(r>0)
                  dire=-1;
             }
              else
              {
                r=r-(k%5/4);
                if(r<-20)
                  dire=0;
              }
               displayBitmapFromProgmem(mariomap,-k+1+30,YO+r,40,703);
              displayBitmapFromProgmem(mariomap,-k+1+30+703,YO+r,40,703);
               displayBitmapFromProgmem(mariomap,-k+1+30+703+703,YO+r,40,703);
              FastLED.show();
              //delay(1);
              displayBitmapFromProgmem(mariomap,-k+30,YO+r,40,703);
              displayBitmapFromProgmem(mariomap,-k+30+703,YO+r,40,703);
               displayBitmapFromProgmem(mariomap,-k+30+703+703,YO+r,40,703);
              //delay(5);*/
               k++;
              if (k >= 1494)
              {
                switchanim = true;
                ongoing = false;
                //k=0;
                fill(bgColor);

              }
          }
    break;
          case 7:{
                     switchanim = false;
             if (firsttime)
              {
                r=0;
                afficheMessage("CIR 2", 0, 3);
                FastLED.show();
                FastLED.delay((int)(1000 / 100));
                delay(1000);
                fill(CRGB(5, 5, 5));
                firsttime = false;
                k=0;
                
              }
              long time1=ESP.getCycleCount();
             if(dire>=0)
             {
                r=r+1;
                if(r>40)
                  dire=-1;
             }
              else
              {
                r=r-1;
                if(r<-10)
                  dire=0;
              }
              //r=(r+(int)k/10)%20;
             fill(CRGB(5, 5, 5));
             circleFilled(15,8,r+15,CRGB::Yellow);
             circleFilled(23,8,r+10,CRGB::Green);
             circleFilled(15,20,r+5,CRGB::Red);
             circleFilled(15,10,r,CRGB::Purple);
             circleFilled(15,0,r-5,CRGB::Cyan);
             circleFilled(10,8,r-10,CRGB:: Blue);
             circleFilled(20,8,r-15,CRGB::Yellow);
             circleFilled(20,8,r-15,CRGB::Yellow);
             circleFilled(15,12,r-20,CRGB::Red);
             circleFilled(22,12,r-25,CRGB::Cyan);
             circleFilled(7,4,r-25,CRGB::Purple);
             //ligne(x1,y1,x2,y2);
             //BresenhamEntier(x1,y1,x2,y2);
             k=k+15;
             //delay(100);
    long time3=ESP.getCycleCount();
             //delay(100);
               FastLED.show();
                                 long time2=ESP.getCycleCount();
  Serial.print((float)160000000/(time2-time1));
  Serial.println(" FPS circle filled total");
   Serial.print((float)160000000/(time3-time1));
  Serial.println(" FPS cacule circle filled");
     Serial.print((float)(time3-time1)/160);
     if(maxi<(float)(time3-time1)/160)
      maxi=(float)(time3-time1)/160;
      if(mini>(float)(time3-time1)/160)
       mini=(float)(time3-time1)/160;
  Serial.println(" nano cacule circle filled");
    Serial.print((float)160000000/(time2-time3));
  Serial.println(" FPS show");
  //Serial.println((float)time2*1000/160000000);
              if (k > 5000)
              {
                Serial.printf("max:%f  min:%f\n",maxi,mini);
                // anim=2;
                switchanim = true;
                // k=0;


              }
             
          }
          break;      



        case 8:{
                     switchanim = false;
             if (firsttime)
              {
                r=0;
                maxi=0;
                mini=9999;
                afficheMessage("CIR R", 0, 3);
                FastLED.show();
                FastLED.delay((int)(1000 / 100));
                delay(1000);
                fill(CRGB(5, 5, 5));
                firsttime = false;
                k=0;
                
              }
             time1=ESP.getCycleCount();
            /* if(dire>=0)
             {
                r=r+1;
                if(r>40)
                  dire=-1;
             }
              else
              {
                r=r-1;
                if(r<-10)
                  dire=0;
              }
              //r=(r+(int)k/10)%20;
             fill(CRGB(5, 5, 5));*/
             for (int r=20;r>1;-r--)
              {
               BresenhamCircleFilled(15,8,r,CHSV((32*r) + k,192,255));
              }
             //ligne(x1,y1,x2,y2);
             //BresenhamEntier(x1,y1,x2,y2);
             k=k+20;
             //delay(100);
                        long time3=ESP.getCycleCount();
             //delay(100);
               FastLED.show();
                                 long time2=ESP.getCycleCount();
  Serial.print((float)160000000/(time2-time1));
  Serial.println(" FPS rainbow total");
   Serial.print((float)160000000/(time3-time1));
  Serial.println(" FPS cacule circle rainbow");
      Serial.print((float)(time3-time1)/160);
     if(maxi<(float)(time3-time1)/160)
      maxi=(float)(time3-time1)/160;
      if(mini>(float)(time3-time1)/160)
       mini=(float)(time3-time1)/160;
       Serial.println(" nano cacule circle rainbow");
    Serial.print((float)160000000/(time2-time3));
  Serial.println(" FPS show");
              if (k > 5000)
              {
                // anim=2;
                Serial.printf("max:%f  min:%f\n",maxi,mini);
                switchanim = true;
                // k=0;


              }
             
          }
          break;      

          
            case 23:{
            
          }
          break;
        }
        if (switchanim)
        {
          anim = (anim + 1) % 10;
          k = 0;
          firsttime = true;

        }
      //  FastLED.show();

        FastLED.delay((int)(1000 / 100));
        // gameOflife();

      }
    }
    executePaintSocketControl();
    executeTetrisSocketControl();
    executelampSocketControl();
  }
}

