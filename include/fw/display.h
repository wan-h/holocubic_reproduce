#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include "lvgl.h"
#include <TFT_eSPI.h>
#include "fw/errorCode.h"

class Display {
public:
    Display(uint16_t width, uint16_t height, uint8_t brightnessPin);
    ~Display();
    ErrorCode init();
    ErrorCode setBackLight(float duty);
    ErrorCode update();
private:
    bool chechInit();
private:
    uint16_t width_;
    uint16_t height_;
    uint8_t brightnessPin_;
    float brightness_;
    lv_disp_draw_buf_t drawBuf_;
    lv_color_t* buf_;
    lv_disp_drv_t dispDrv_;
    bool inited_;
};

#endif