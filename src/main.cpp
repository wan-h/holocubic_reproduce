#include <Arduino.h>
#include <esp32-hal-timer.h>
#include "fw/logger.h"
#include "fw/imu.h"
#include "fw/display.h"
#include "fw/resource.h"
#include "fw/sdCard.h"
#include "fw/led.h"
#include "fw/wifi.h"
#include "sys/imuAction.h"
#include "sys/appController.h"
#include "app/astronaut/astronaut.h"
#include "app/circle/circle.h"
#include "conf.h"

Resource resource(LOG_BAUD, LEVEL_INFO);
IMU imu(IMU_SCL, IMU_SDA);
Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_BL_PIN);
SDCard sdCard(SD_SCK, SD_MISO, SD_MOSI, SD_SS);
Led led(LED_PIN, LED_NUM);
WifiStation wifiStation(WIFI_SSID, WIFI_PASSWD);
ImuAction imuAction(&imu, ACTION_CHECK_INTERVAL);
AppController appControler;

void setup() {
  // put your setup code here, to run once:
  resource.init();
  resource.printInfo();

  led.init();
  led.setBrightness(LED_BRIGHTNESS);
  led.setRGB(0, 255, 0, 0);

  display.init();
  display.setBackLight(DISPLAY_BACKLIGHT);

  // sdCard.init();
  wifiStation.init();

  imuAction.init();

  appControler.init();
  appControler.install(astronautAppDesc);
  appControler.install(circleAppDesc);
}

void loop() {
  // put your main code here, to run repeatedly:
  ActionInfo actionInfo;
  imuAction.getAction(&actionInfo);
  appControler.process(&actionInfo);

  led.update(LED_INTERVAL);
  display.update();

  // String resp;
  // String req = "GET /";
  // ErrorCode ret = wifiStation.request("www.baidu.com", 80, req, resp);
}
