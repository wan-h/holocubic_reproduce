#ifndef _APP_CONTROLLER_H_
#define _APP_CONTROLLER_H_

#include "fw/errorCode.h"
#include "sys/imuAction.h"
#include "lvgl.h"
#include <vector>

typedef struct AppDesc {
    std::string name;
    lv_img_dsc_t* icon;
    ErrorCode (*appInit) (AppController* appController);
    ErrorCode (*appProcess) (AppController* appController, ActionInfo* actionInfo);
} AppDesc;

typedef struct MenuInfo {
    uint16_t appId_;
    bool appRunning_;
    lv_obj_t* appMenu;
} MenuInfo;

class AppController 
{
public:
    AppController();
    ~AppController();
    ErrorCode init();
    ErrorCode install(AppDesc appDesc);
    ErrorCode process(ActionInfo* actionInfo);
public:
    void exitApp();
private:
    bool checkInit();
    void showAppIcon(lv_scr_load_anim_t anim_type);
private:
    bool inited_;
    std::vector<AppDesc> appDescs_;
    MenuInfo menuInfo_;
};

#endif