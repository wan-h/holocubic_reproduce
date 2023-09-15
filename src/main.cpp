#include <Arduino.h>
#include "fw/logger.h"
#include "fw/imu.h"
#include "fw/display.h"
#include "conf.h"

Logger logger(LOG_BAUD, LEVEL_TRACE);
IMU imu(IMU_SCL, IMU_SDA);
Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT);

void setup() {
  // put your setup code here, to run once:
  logger.init();
  imu.init();
  display.init();
  LOG_INFO("Main: Setup success");
}

uint32_t cnt = 0;
void loop() {
  // put your main code here, to run repeatedly:
  imu.update();
  delay(30);
}
