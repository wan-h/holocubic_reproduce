#include "sys/appController.h"
#include "fw/logger.h"
#include "conf.h"

AppController::AppController()
: menuInfo_({0})
, inited_(false)
{}

AppController::~AppController()
{
    inited_ = false;
    if (menuInfo_.appMenu != nullptr) {
        lv_obj_clean(menuInfo_.appMenu);
        menuInfo_.appMenu = nullptr;
    }
}

ErrorCode AppController::init()
{
    if (inited_) return CODE_OK;

    appDescs_.clear();
    // 初始化Info
    menuInfo_.appId_ = 0;
    menuInfo_.appRunning_ = false;
    menuInfo_.appMenu = nullptr;
    // 初始化菜单显示
    menuInfo_.appMenu = lv_obj_create(nullptr);
    lv_obj_set_style_bg_color(menuInfo_.appMenu, lv_color_hex(0x000000), LV_PART_MAIN); // 黑色背景
    lv_obj_set_size(menuInfo_.appMenu, DISPLAY_WIDTH, DISPLAY_HEIGHT);
    lv_obj_align(menuInfo_.appMenu, LV_ALIGN_CENTER, 0, 0);
    lv_scr_load(menuInfo_.appMenu);

    inited_ = true;
    LOG_INFO("AppController: init ok");
    return CODE_OK;
}

bool AppController::checkInit()
{
    if (!inited_) {
        LOG_ERROR("AppController: Please init first");
    }
    return inited_;
}

void AppController::showAppIcon(lv_scr_load_anim_t anim_type)
{
    // 清空当前页面
    lv_obj_clean(lv_scr_act());

    lv_obj_t* appIcon = lv_img_create(menuInfo_.appMenu);
    lv_img_set_src(appIcon, appDescs_[menuInfo_.appId_].icon);
    lv_obj_align(appIcon, LV_ALIGN_CENTER, 0, 0);

    lv_scr_load_anim(appIcon, anim_type, 300, 300, false);
}

void AppController::exitApp()
{
    menuInfo_.appRunning_ = false;
}

ErrorCode AppController::install(AppDesc appDesc)
{
    if (!checkInit()) return CODE_ERROR_INIT_CHECK;
    appDescs_.push_back(appDesc);
    LOG_INFO("AppController: Install %s success", appDesc.name.c_str());
    return CODE_OK;
}

ErrorCode AppController::process(ActionInfo* actionInfo)
{
    if (!checkInit()) return CODE_ERROR_INIT_CHECK;
    // app 运行中
    if (menuInfo_.appRunning_) {
        appDescs_[menuInfo_.appId_].appProcess(this, actionInfo);
    } else {
        // 切换app icon
        lv_scr_load_anim_t anim_type = LV_SCR_LOAD_ANIM_NONE;
        switch (actionInfo->actionType)
        {
        case ACTION_HOME:
            menuInfo_.appId_ = 0;
            anim_type = LV_SCR_LOAD_ANIM_MOVE_TOP;
            break;
        case ACTION_LEFT:
            menuInfo_.appId_ = menuInfo_.appId_ == 0 ? (appDescs_.size() - 1) : (menuInfo_.appId_ - 1);
            anim_type = LV_SCR_LOAD_ANIM_MOVE_LEFT;
            break;
        case ACTION_RIGHT:
            menuInfo_.appId_ = menuInfo_.appId_ == (appDescs_.size() - 1) ? 0 : (menuInfo_.appId_ + 1);
            anim_type = LV_SCR_LOAD_ANIM_MOVE_RIGHT;
            break;
        case ACTION_UP:
        case ACTION_DOWN:
            menuInfo_.appRunning_ = true;
            appDescs_[menuInfo_.appId_].appInit(this);
            break;
        default:
            break;
        }

        LOG_TRACE("AppController: Menu switch to %s", appDescs_[menuInfo_.appId_].name.c_str());
        
        if (!menuInfo_.appRunning_) {
            showAppIcon(anim_type);
        }
    }
    // 动作已响应
    actionInfo->actionType = ACTION_NONE;
    actionInfo->isAvailable = false;
}