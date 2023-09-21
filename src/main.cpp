#include <Arduino.h>
#include <esp32-hal-timer.h>
#include "fw/logger.h"
#include "fw/imu.h"
#include "fw/display.h"
#include "fw/resource.h"
#include "fw/sdCard.h"
#include "fw/led.h"
#include "sys/imuAction.h"
#include "conf.h"

Resource resource;
Logger logger(LOG_BAUD, LEVEL_TRACE);
IMU imu(IMU_SCL, IMU_SDA);
Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_BL_PIN);
SDCard sdCard(SD_SCK, SD_MISO, SD_MOSI, SD_SS);
Led led(LED_PIN, LED_NUM);
ImuAction imuAction(&imu);

static bool updated = false;
static TimerHandle_t xTimerAction = nullptr;
void actionCheckHandle(TimerHandle_t xTimer)
{
    // 标志需要检测动作
    updated = true;
}

void createActionTimer() 
{
  xTimerAction = xTimerCreate(
    "Action Timer",                  /*任务名字*/
    IMU_INTERVAL / portTICK_RATE_MS, /*设置时钟周期:100ms*/
    pdTRUE,                          /*pdTRUE周期调用,pdFALSE:单次调用*/
    (void *)0,                       /*计时器优先级*/
    actionCheckHandle
  );

  xTimerStart(xTimerAction, 0);
}

void lv_example_style_2(void)
{
    static lv_style_t style;
    lv_style_init(&style);
    lv_style_set_radius(&style, 5);

    /*Make a gradient*/
    lv_style_set_bg_opa(&style, LV_OPA_COVER);
    static lv_grad_dsc_t grad;
    grad.dir = LV_GRAD_DIR_VER;
    grad.stops_count = 2;
    grad.stops[0].color = lv_palette_lighten(LV_PALETTE_GREY, 1);
    grad.stops[1].color = lv_palette_main(LV_PALETTE_BLUE);

    /*Shift the gradient to the bottom*/
    grad.stops[0].frac  = 128;
    grad.stops[1].frac  = 192;

    lv_style_set_bg_grad(&style, &grad);

    /*Create an object with the new style*/
    lv_obj_t * obj = lv_obj_create(lv_scr_act());
    lv_obj_add_style(obj, &style, 0);
    lv_obj_center(obj);
}

void setup() {
  // put your setup code here, to run once:
  logger.init();

  resource.init();
  resource.printInfo();

  led.init();
  led.setBrightness(0.2);
  led.setRGB(0, 0, 0, 127);

  display.init();
  display.setBackLight(0.5);

  sdCard.init();

  imuAction.init();

  createActionTimer();
}

void loop() {
  // put your main code here, to run repeatedly:
  ActionInfo actionInfo;
  
  if (updated) {
    imuAction.getAction(&actionInfo);
    updated = false;
  }
}
