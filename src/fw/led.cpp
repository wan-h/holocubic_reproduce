#include "fw/led.h"
#include "fw/logger.h"

Led::Led(uint8_t ledPin, uint32_t ledNum, float brightness)
: ledPin_(ledPin)
, ledNum_(ledNum)
, brightness_(constrain(brightness, 0, 1))
, colorBuffers_(nullptr)
, inited_(false)
{}

Led::~Led()
{
    if (colorBuffers_) {
        free(colorBuffers_);
        colorBuffers_ = nullptr;
    }
    inited_ = false;
}

#define LED_PIN 27

ErrorCode Led::init()
{
    uint32_t bufferSize = sizeof(CRGB) * ledNum_;
    colorBuffers_ = (CRGB*)malloc(bufferSize);
    memset(colorBuffers_, 0, bufferSize);

    // GRB是控制器的输出顺序，由具体的LED型号决定
    FastLED.addLeds<WS2812, LED_PIN, GRB>(colorBuffers_, ledNum_);
    FastLED.setBrightness((uint8_t)(255 * brightness_));
    
    inited_ = true;
    LOG_INFO("Led: init ok");
    return ERROR_CODE_OK;
}

bool Led::checkInit()
{
    if (!inited_) {
        LOG_ERROR("Led: Please init first");
    }
    return inited_;
}

ErrorCode Led::setBrightness(float duty)
{
    if (!checkInit()) return ERROR_CODE_INIT;

    duty = constrain(duty, 0, 1);
	FastLED.setBrightness((uint8_t)(255 * duty));
	FastLED.show();
    LOG_TRACE("Led: set brightness %f", duty);
	return ERROR_CODE_OK;
}

ErrorCode Led::setRGB(uint32_t id, uint8_t r, uint8_t g, uint8_t b)
{
    if (id >= ledNum_) {
        LOG_ERROR("Led: id should < %d", ledNum_);
        return ERROR_CODE_ERROR;
    }
    colorBuffers_[id] = CRGB(r, g, b);
	FastLED.show();
    LOG_TRACE("Led: set led[%d] to R[%d] G[%d] B[%d]", id, r, g, b);
    return ERROR_CODE_OK;
}