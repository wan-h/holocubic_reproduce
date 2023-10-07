#include <Arduino.h>
#include <esp32-hal-timer.h>
#include "fw/logger.h"
#include "fw/imu.h"
#include "fw/display.h"
#include "fw/resource.h"
#include "fw/sdCard.h"
#include "fw/led.h"
#include "sys/imuAction.h"
#include "sys/appController.h"
#include "app/astronaut/astronaut.h"
#include "conf.h"

Resource resource(LOG_BAUD, LEVEL_DEBUG);
IMU imu(IMU_SCL, IMU_SDA);
Display display(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_BL_PIN);
SDCard sdCard(SD_SCK, SD_MISO, SD_MOSI, SD_SS);
Led led(LED_PIN, LED_NUM);
ImuAction imuAction(&imu, ACTION_CHECK_INTERVAL);
AppController appControler;

// void test() {
//   // 设置背景颜色
//   lv_obj_set_style_bg_color(lv_scr_act(), lv_color_hex(0x000000), LV_PART_MAIN);
//   // 分区
//   lv_obj_t * content = lv_obj_create(lv_scr_act());
//   lv_obj_set_style_bg_color(content, lv_color_hex(0x000000), LV_PART_MAIN);
//   lv_obj_set_size(content, 240, 240);
//   lv_obj_align(content, LV_ALIGN_CENTER, 0, 0);
//   lv_obj_set_flex_flow(content, LV_FLEX_FLOW_COLUMN);
//   lv_obj_set_flex_align(content, LV_FLEX_ALIGN_SPACE_EVENLY , LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

//   // 无边框
//   static lv_style_t style;
//   lv_style_init(&style);
//   lv_style_set_border_side(&style, LV_BORDER_SIDE_NONE);
//   lv_obj_add_style(content, &style, LV_PART_MAIN); 

//   // gif图
//   LV_IMG_DECLARE(astronaut);
//   lv_obj_t * img;
//   img = lv_gif_create(content);
//   lv_gif_set_src(img, &astronaut);

//   // 文字显示
//   lv_obj_t * label;
//   label = lv_label_create(content);
//   lv_label_set_text(label, "HOME");
//   lv_obj_set_style_text_color(content, lv_color_hex(0xffffff), LV_PART_MAIN);
//   lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
// }

void setup() {
  // put your setup code here, to run once:
  resource.init();
  resource.printInfo();

  led.init();
  led.setBrightness(LED_BRIGHTNESS);
  led.setRGB(0, 255, 0, 0);

  display.init();
  display.setBackLight(DISPLAY_BACKLIGHT);

  sdCard.init();

  imuAction.init();

  appControler.init();
  appControler.install(astronautAppDesc);

  // test();
}

void loop() {
  // put your main code here, to run repeatedly:
  ActionInfo actionInfo;
  imuAction.getAction(&actionInfo);
  appControler.process(&actionInfo);

  led.update(LED_INTERVAL);
  display.update();
}
