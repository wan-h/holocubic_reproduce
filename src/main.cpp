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

void setup() {
  // put your setup code here, to run once:
  resource.init();
  resource.printInfo();

  led.init();
  led.setBrightness(0.2);
  led.setRGB(0, 0, 0, 127);

  display.init();
  display.setBackLight(0.5);

  sdCard.init();

  imuAction.init();
}

void loop() {
  // put your main code here, to run repeatedly:
  ActionInfo actionInfo;
  imuAction.getAction(&actionInfo);
}
