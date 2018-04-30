//
//  dateheure.h
//  
//
//  Created by Yves BAZIN on 2/01/18.
//

#ifndef dateheure_h
#define dateheure_h



void afficherTime();

const char* host = "129.6.15.28";

int ln = 0;
String TimeDate = "";


void afficherTime()
{
    WiFiClient client;
    const int httpPort = 13;
    
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }
    String line="";
    while(client.available())
    {
        line += client.readStringUntil('\r');
    }
    Serial.println(line);
   // sendStrXY(">Sending Header<", 1, 0);
    
    // This will send the request to the server
    client.print("DATE");
    
    delay(100);
    
    // Read all the lines of the reply from server and print them to Serial
    // expected line is like : Date: Thu, 01 Jan 2015 22:00:14 GMT
    char buffer[12];
    String dateTime = "";
    //sendStrXY(">  Listening...<", 2, 0);
    line="";
    while(client.available())
    {
        line += client.readStringUntil('\r');
    }
    Serial.print("line:");
    Serial.println(line);
        if (line!="")
        {
            
            Serial.print("icu");
            // date starts at pos 7
            TimeDate = line.substring(7);
            Serial.println(TimeDate);
            // time starts at pos 14
            TimeDate = line.substring(10, 15);
            Serial.println(TimeDate);
            TimeDate.toCharArray(buffer, 10);
            Serial.println(buffer);
            afficheMessage(buffer,0,3);
      //      sendStrXY("UTC Date/Time:", 4, 0);
       //     sendStrXY(buffer, 5, 0);
            TimeDate = line.substring(16, 24);
            TimeDate.toCharArray(buffer, 10);
            afficheMessage(buffer,0,10);
        //    sendStrXY(buffer, 6, 0);
            FastLED.show();
            delay(3000);
        }
    
}

#endif /* dateheure_h */
