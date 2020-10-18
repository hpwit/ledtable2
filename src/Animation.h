//
//  Animation.h
//  
//
//  Created by Yves BAZIN on 20/02/2019.
//

#ifndef Animation_h
#define Animation_h

#include "FastLED.h"
class Animation
{
    
public:
    
    
    
    
    Animation( CRGB *ext_leds,int start_led,int end_led)
    {
        this->ext_leds=ext_leds;
        this->start_led=start_led;
        this->end_led=end_led;
        this->num_leds=end_led-start_led+1;
        this->ledsa= (CRGB*)malloc((end_led-start_led+1)*sizeof(CRGB));
        memset(ledsa,0,num_leds*3);
            }
    
   virtual void animation(){};
    void loop()
    {
        animation();
        pushleds();
    }
    
    
protected:
    //void (*animation)();
    CRGB *ledsa;
    int num_leds;
    CRGB *ext_leds;
    int start_led;
    int end_led;
    
    void pushleds()
    {
        memcpy(ext_leds+start_led,ledsa,num_leds*3);
    }
    
};
#endif /* Animation_h */
