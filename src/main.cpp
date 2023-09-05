#include <Arduino.h>
#include "logger.h"

Logger logger(9600, LEVEL_INFO);

void setup() {
  // put your setup code here, to run once:
  logger.init();
  LOG_INFO("Setup success");
}

uint32_t cnt = 0;
void loop() {
  // put your main code here, to run repeatedly:
  LOG_INFO("Hello World! [%d]", cnt++);
}
