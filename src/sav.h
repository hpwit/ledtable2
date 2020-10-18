//
//  sav.h
//  
//
//  Created by Yves BAZIN on 11/03/18.
//

#ifndef sav_h
#define sav_h

WebSocketsServer tetrisWebSocket = WebSocketsServer(81);


void tetrisWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length)
{
    // noInterrupts();
    // Serial.printf("webSocketEvent(%d, %d, ...)\r\n", num, type);
    switch(type) {
        case WStype_DISCONNECTED:
            Serial.printf("[%u] Disconnected!\r\n", num);
            break;
        case WStype_CONNECTED:
        {
            // IPAddress ip = tetrisWebSocket.remoteIP(num);
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
                
            }
            
            if (strcmp("left", (const char *)payload) == 0)  {
                
                //Serial.println("on va a droite");
                
            }
            if (strcmp("new", (const char *)payload) == 0)  {
                // fill(bgColor);
                //newGame();
            }
            
            if (strcmp("turnr", (const char *)payload) == 0)  {
                
                
            }
            
            
            if (strcmp("descend", (const char *)payload) == 0)  {
                
                
            }
            
            
            if (strcmp("turnl", (const char *)payload) == 0)  {
                
                
                
            }
            
            
            else {
                // Serial.println("Unknown command");
            }
            // send data to all connected clients
            //webSocket.broadcastTXT(payload, length);
            break;
        case WStype_BIN:
            Serial.printf("[%u] get binary length: %u\r\n", num, length);
            // hexdump(payload, length);
            
            // echo data back to browser
            // webSocket.sendBIN(num, payload, length);
            break;
        default:
            Serial.printf("Invalid WStype [%d]\r\n", type);
            break;
    }
    
    //interrupts();
}



#endif /* sav_h */
