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

Resource resource(LOG_BAUD, LEVEL_DEBUG);
IMU imu(IMU_SCL, IMU_SDA);
Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_BL_PIN);
SDCard sdCard(SD_SCK, SD_MISO, SD_MOSI, SD_SS);
Led led(LED_PIN, LED_NUM);
ImuAction imuAction(&imu, ACTION_CHECK_INTERVAL);

void test() {
  LV_IMG_DECLARE(astronaut);
  lv_obj_t * img;

  img = lv_gif_create(lv_scr_act());
  lv_gif_set_src(img, &astronaut);
  lv_obj_align(img, LV_ALIGN_LEFT_MID, 20, 0);
}

void setup() {
  // put your setup code here, to run once:
  resource.init();
  resource.printInfo();

  led.init();
  led.setBrightness(0.2);
  led.setRGB(0, 255, 0, 0);

  display.init();
  display.setBackLight(0.5);

  sdCard.init();

  imuAction.init();

  test();
}

void loop() {
  // put your main code here, to run repeatedly:
  ActionInfo actionInfo;
  imuAction.getAction(&actionInfo);
  led.update(20);
}
