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
    if (inited_) return CODE_OK;

    uint32_t bufferSize = sizeof(CRGB) * ledNum_;
    colorBuffers_ = (CRGB*)malloc(bufferSize);
    memset(colorBuffers_, 0, bufferSize);

    // TODO: 这里的LED_PIN只能用宏定义或则const, 因为这个模板参数值需要在编译时就确定
    // GRB是控制器的输出顺序，由具体的LED型号决定
    FastLED.addLeds<WS2812, LED_PIN, GRB>(colorBuffers_, ledNum_);
    FastLED.setBrightness((uint8_t)(255 * brightness_));
    
    inited_ = true;
    LOG_INFO("Led: init ok");
    return CODE_OK;
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
    if (!checkInit()) return CODE_ERROR_INIT_CHECK;

    duty = constrain(duty, 0, 1);
	FastLED.setBrightness((uint8_t)(255 * duty));
	FastLED.show();
    LOG_TRACE("Led: set brightness %f", duty);
	return CODE_OK;
}

ErrorCode Led::setRGB(uint32_t id, uint8_t r, uint8_t g, uint8_t b)
{
    if (!checkInit()) return CODE_ERROR_INIT_CHECK;

    if (id >= ledNum_) {
        LOG_ERROR("Led: id should < %d", ledNum_);
        return CODE_ERROR;
    }
    colorBuffers_[id] = CRGB(r, g, b);
	FastLED.show();
    LOG_TRACE("Led: set led[%d] to R[%d] G[%d] B[%d]", id, r, g, b);
    return CODE_OK;
}

ErrorCode Led::update(uint16_t interval)
{
    if (!checkInit()) return CODE_ERROR_INIT_CHECK;
    static long timePre = 0;
    long timeCur = millis();
    if ((timeCur - timePre) >= interval) {
        static uint8_t hue = 0;
        fill_rainbow(colorBuffers_, ledNum_, hue, 8);
        setBrightness(hue / 500 + 0.1);
        hue++;
        FastLED.show();
        timePre = timeCur;
    }

    return CODE_OK;
}