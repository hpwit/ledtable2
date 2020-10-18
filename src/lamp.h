//
//  lamp.h
//  
//
//  Created by Yves BAZIN on 7/01/18.
//

#ifndef lamp_h
#define lamp_h

void initlampScoketControl();
void lampWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length);
bool initlamp();
void newlamp();
void executelampSocketControl();

int lampWebSocketPort=83;
bool lampInitiated=false;
bool inlamp=false;

WebSocketsServer lampWebSocket = WebSocketsServer(lampWebSocketPort);

void initlampScoketControl()
{
    lampWebSocket.begin();
    lampWebSocket.onEvent(lampWebSocketEvent);
}

void executelampSocketControl()
{
    lampWebSocket.loop();
    
}




bool initlamp()
{
    if(isTable)
    {
        server.serveStatic("/lamp.html", SPIFFS, "/lamp.html");
         server.serveStatic("/main.js", SPIFFS, "/main.js");
         server.serveStatic("/screen.css", SPIFFS, "/screen.css");
        server.serveStatic("/test_b_check.jpg", SPIFFS, "/test_b_check.jpg");
        //on ajoute le lien vers tetris
        initlampScoketControl();
        lampInitiated=true;
        Serial.println("patint cree");
        return true;
        
    }
    else{
        Serial.println("No table existing create the table first");
        lampInitiated=false;
        return false;
    }
}




void newlamp()
{
    
    Serial.println("voici lamp");// clears the red display matrix
    if(!lampInitiated)
    {
        Serial.println("on cree la base fait");
        initlamp();
        
    }
    inlamp=true;
    //anim=23;
     fill_solid(leds, NUM_LEDS, CRGB(8,8,8));
   // FastLED.show();
    
}

bool changecolor=false;
void lampWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
    // noInterrupts();
    // Serial.printf("webSocketEvent(%d, %d, ...)\r\n", num, type);
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\r\n", num);
            break;
        case WStype_CONNECTED:
        {
            IPAddress ip = lampWebSocket.remoteIP(num);
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
            
            char str[20];
            int h,s,v,b;
            sscanf ((const char *)payload,"%s  %d %d %d %d",str,&h,&s,&v,&b);
            if (strcmp("hsv", (const char *)str) == 0)  {
                fill_solid(leds, NUM_LEDS, CHSV(h,s,v));
                replaceled();
                changecolor=true;
                //FastLED.show();
                setTableBrightness(b);
                 //FastLED.setBrightness(b);
                //FastLED.show();
                // Serial.println("on va a droite");
                
            }
            
            
            if (strcmp("new", (const char *)payload) == 0)  {
                //fill(CRGB(8,8,8));
                
                newlamp();
            }
            if (strcmp("stop", (const char *)payload) == 0)  {
                fill_solid(leds, NUM_LEDS,bgColor);
                inlamp=false;
                FastLED.setBrightness(64);
               // anim=0;
                
                
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
    
    // interrupts();
}


#endif /* lamp_h */
