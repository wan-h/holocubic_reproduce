#ifndef _LED_H_
#define _LED_H_

#include "FastLED.h"
#include "fw/errorCode.h"

class Led
{
public:
    Led(uint8_t ledPin, uint32_t ledNum, float brightness = 0.5);
    ~Led();
    ErrorCode init();
    ErrorCode setBrightness(float duty);
    ErrorCode setRGB(uint32_t id, uint8_t r, uint8_t g, uint8_t b);
    ErrorCode update(uint16_t interval);
private:
    bool checkInit();
private:
    CRGB* colorBuffers_;
    uint8_t ledPin_;
    uint32_t ledNum_;
    float brightness_;
    bool inited_;
};

#endif // !_LED_H_

