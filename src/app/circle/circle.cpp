#include "app/circle/circle.h"
#include "conf.h"

#define CIRCLE_APP_NAME "circle"

static lv_obj_t* appScr = nullptr;

ErrorCode circleInit(AppController* appController)
{
    return CODE_OK;
}

ErrorCode circleProcess(AppController* appController, ActionInfo* actionInfo)
{
    switch (actionInfo->actionType)
    {
    case ACTION_HOME:
        lv_obj_clean(appScr);
        appScr = nullptr;
        appController->exitApp();
        return CODE_OK;
    default:
        break;
    }

    // 页面展示
    lv_obj_t* act_obj = lv_scr_act();
    if (act_obj == appScr) {
        return CODE_OK;
    }
    // 清空页面
    lv_obj_clean(act_obj);
    // 页面设置
    appScr = lv_obj_create(nullptr);
    lv_obj_set_style_bg_color(appScr, lv_color_hex(0x000000), LV_PART_MAIN);
    lv_obj_set_size(appScr, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    lv_obj_align(appScr, LV_ALIGN_CENTER, 0, 0);
    // gif图展示
    LV_IMG_DECLARE(circle_app_gif);
    lv_obj_t* gif;
    gif = lv_gif_create(appScr);
    lv_gif_set_src(gif, &circle_app_gif);
    lv_obj_center(gif);
    // 加载页面
    lv_scr_load(appScr);

    return CODE_OK;
}

AppDesc circleAppDesc = {
    CIRCLE_APP_NAME,
    &circle_app_icon,
    circleInit,
    circleProcess
};