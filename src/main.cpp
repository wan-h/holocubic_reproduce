#include <Arduino.h>
#include "fw/logger.h"
#include "fw/imu.h"

Logger logger(9600, LEVEL_TRACE);
IMU imu(33, 32);

void setup() {
  // put your setup code here, to run once:
  logger.init();
  imu.init();
  LOG_INFO("Setup success");
}

uint32_t cnt = 0;
void loop() {
  // put your main code here, to run repeatedly:
  LOG_INFO("Hello World! [%d]", cnt++);
  imu.update();
  delay(500);
}
