#include "fw/display.h"
#include "fw/logger.h"

static TFT_eSPI tft;

static void my_print(lv_log_level_t level, const char* file, uint32_t line, const char* fun, const char* dsc)
{
    switch (level)
    {
    case LV_LOG_LEVEL_TRACE:
        LOG_TRACE(dsc);
        break;
    case LV_LOG_LEVEL_USER:
        LOG_DEBUG(dsc);
        break;
    case LV_LOG_LEVEL_INFO:
        LOG_INFO(dsc);
        break;
    case LV_LOG_LEVEL_WARN:
        LOG_WARNING(dsc);
        break;
    case LV_LOG_LEVEL_ERROR:
        LOG_ERROR(dsc);
        break;
    default:
        break;
    }
    Serial.flush();
} 

static void my_disp_flush(lv_disp_drv_t* disp, const lv_area_t* area, lv_color_t* color_p)
{
	uint32_t w = (area->x2 - area->x1 + 1);
	uint32_t h = (area->y2 - area->y1 + 1);

	tft.startWrite();
    tft.setAddrWindow(area->x1, area->y1, w, h);
	tft.pushColors(&color_p->full, w * h, true);
	tft.endWrite();

	lv_disp_flush_ready(disp);
}

Display::Display(uint16_t width, uint16_t height, uint8_t brightnessPin)
: width_(width)
, height_(height)
, brightnessPin_(brightnessPin)
, brightness_(0.5)
, buf_(nullptr)
, inited_(false)
{}

Display::~Display()
{
    if(buf_) {
        free(buf_);
        buf_ = nullptr;
    }
    inited_ = false;
}

#define LCD_BL_PWM_CHANNEL 0
#define LCD_BL_PWM_FREQ 5000

ErrorCode Display::init()
{
    // 背光
    ledcSetup(LCD_BL_PWM_CHANNEL, LCD_BL_PWM_FREQ, 8);
	ledcAttachPin(brightnessPin_, LCD_BL_PWM_CHANNEL);
    // lvgl初始化
    lv_init();
#if LV_USE_LOG
    lv_log_register_print_cb(my_print)
#endif
    // 分配显示buffer, 显示尺寸的 1/10
    uint32_t bufferSize = width_ * height_ / 10;
    buf_ = (lv_color_t*)(malloc(sizeof(lv_color_t) * bufferSize));
    lv_disp_draw_buf_init(&drawBuf_, buf_, nullptr, bufferSize);

    // 配置显示驱动
    tft.begin();
    // tft.setRotation(3);
    lv_disp_drv_init(&dispDrv_);
    dispDrv_.flush_cb = my_disp_flush;    /*Set your driver function*/
    dispDrv_.draw_buf = &drawBuf_;        /*Assign the buffer to the display*/
    dispDrv_.hor_res = width_;   /*Set the horizontal resolution of the display*/
    dispDrv_.ver_res = height_;   /*Set the vertical resolution of the display*/
    lv_disp_drv_register(&dispDrv_);      /*Finally register the driver*/
    
    inited_ = true;
    LOG_INFO("Display: init ok");
    return ERROR_CODE_OK;
}

ErrorCode Display::setBackLight(float duty)
{
    duty = constrain(duty, 0, 1);
	brightness_ = 1 - duty;
	ledcWrite(LCD_BL_PWM_CHANNEL, (int)(brightness_ * 255));
    return ERROR_CODE_OK;
}