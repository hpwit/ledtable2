//
//  meteo.h
//  
//
//  Created by Yves BAZIN on 19/12/17.
//

#ifndef meteo_h
#define meteo_h
 #include <ArduinoJson.h>
void getmeteo();

void getMeteo()
{
    int nbretry=3;
    String json = "";
    char  *host="api.openweathermap.org";
    Serial.println("connecting to ");
    Serial.println(host);
    
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    // while(nbretry >1 and !((const char *)json.charAt(1)=="}") )
    //{
    // String json = "";
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }
    
    // We now create a URI for the request
    String url = "/data/2.5/weather?zip=1000,be&units=metric&appid=cee2dece9fdd919d420d4f5972ec3f1e";
    
    Serial.print("Requesting URL: ");
    Serial.println(url);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    
    // This will send the request to the server
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }
    
    
    // delay(20);
    
    // Read all the lines of the reply from server and print them to Serial
    Serial.println("Respond:");
    
    String str="";
    boolean httpBody = false;
   /* while (client.available()) {
        String line = client.readStringUntil('\r');
        str="line:charat0";  //+":"+line.charAt(1);
        //Serial.println(str);
        //Serial.println(line.charAt(1));
        // Serial.println(line.charAt(0));
        //Serial.println(line);
        // Serial.println("end line");
        if (!httpBody and (line.charAt(1) == '{')) {
            httpBody = true;
        }
        if (httpBody) {
            // Serial.print("line:");
            // Serial.println(line);
            json += line;
            //Serial.print("json:");
            // Serial.println(json);
        }
    }*/
    //  nbretry--;
    //}
    
    const size_t capacity = JSON_OBJECT_SIZE(3) + JSON_ARRAY_SIZE(2) + 600;
    DynamicJsonBuffer jsonBuffer(capacity);
    char status[32] = {0};
    client.readBytesUntil('\r', status, sizeof(status));
    if (strcmp(status, "HTTP/1.1 200 OK") != 0) {
        Serial.print(F("Unexpected response: "));
        Serial.println(status);
        return;
    }
    //Serial.println("Got data json:");
    //Serial.println(json);
    char endOfHeaders[] = "\r\n\r\n";
    if (!client.find(endOfHeaders)) {
        Serial.println(F("Invalid response"));
        return;
    }
    JsonObject &root = jsonBuffer.parseObject(client);
    if (!root.success()) {
        Serial.println(F("Parsing failed!"));
        return;
    }
    //char* data[80];
     String data = root["name"];
    String tp= root["main"]["temp"];
    const char* we = root["weather"][0]["main"];
    int temp=tp.toInt();
    //String ville=(String)data[0]+(String)data[1]+(String)data[2]+(String)data[3 ]+(String)data[4 ];
    //data.toUpperCase();
    if (data.length()>0)
    {
        fill(bgColor);
        Color=CRGB::Red;
        afficheMessage(&data[0],0,14);
        afficheMessage(&data[1],6,14);
        afficheMessage(&data[2],12,14);
        afficheMessage(&data[3],18,14);
        afficheMessage(&data[4],24,14);
        afficheMessage((char*)we,0,7);
        char chi[2];
        sprintf(chi, "%d", temp);
        //Serial.println(chi);
        //Serial.println(sizeof(chi)/sizeof(char));
        if(temp<10)
        {
            chi[1]=chi[0];
            chi[0]=0x0030;
            
        }
        
        afficheLettre((int)(chi[0])-32,12,0);
        afficheLettre((int)(chi[1])-32,18, 0);
        //afficheMessage(String(temp), 12,0);
        afficheMessage("C",24,0);
         FastLED.show();
        delay(3000);
    }
    //k2=0;
    Serial.println(data);
   // Serial.println(ville);
    Serial.println(String(temp));
    //Serial.println("closing connection");
    
}

#endif /* meteo_h */
