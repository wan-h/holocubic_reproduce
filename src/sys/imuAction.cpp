#include "sys/imuAction.h"
#include "fw/logger.h"

static bool updated = false;
static TimerHandle_t xTimerAction = nullptr;
void actionCheckHandle(TimerHandle_t xTimer)
{
    // 标志需要检测动作
    updated = true;
}

ImuAction::ImuAction(IMU* imu, uint16_t interval)
: imu_(imu)
, interval_(interval)
, historyActions_({ACTION_NONE})
, inited_(false)
{}

ImuAction::~ImuAction()
{
    inited_ = false;
}

ErrorCode ImuAction::init()
{
    ErrorCode ret = imu_->init();
    if (ret != CODE_OK) {
        return ret;
    }

    xTimerAction = xTimerCreate(
        "Action Timer",
        interval_ / portTICK_RATE_MS,
        pdTRUE,
        (void *)0,
        actionCheckHandle
    );
    if (xTimerAction == nullptr) {
        LOG_ERROR("ImuAction: Create action timer failed");
        return CODE_ERROR;
    }

    if(xTimerStart(xTimerAction, 0) != pdPASS) {
        LOG_ERROR("ImuAction: Start action timer failed");
        return CODE_ERROR;
    }

    LOG_INFO("ImuAction: init ok");
    return CODE_OK;
}

ErrorCode ImuAction::getAction(ActionInfo* actionInfo)
{
    // 动作判断
    ErrorCode ret = imu_->update();
    if (ret != CODE_OK) return ret;

    if (updated) {
        if(imu_->getAccelY() <= -0.5) {
            actionInfo->actionType = ACTION_LEFT;
            LOG_DEBUG("ImuAction: getAction [ACTION_LEFT]");
        } else if (imu_->getAccelY() >= 0.5) {
            actionInfo->actionType = ACTION_RIGHT;
            LOG_DEBUG("ImuAction: getAction [ACTION_RIGHT]");
        } else if (imu_->getAccelX() <= -0.5) {
            actionInfo->actionType = ACTION_UP;
            LOG_DEBUG("ImuAction: getAction [ACTION_UP]");
        } else if (imu_->getAccelX() >= 0.5) {
            actionInfo->actionType = ACTION_DOWN;
            LOG_DEBUG("ImuAction: getAction [ACTION_DOWN]");
        } else if (imu_->getAccelZ() >= 1.5) {
            actionInfo->actionType = ACTION_HOME;
            LOG_DEBUG("ImuAction: getAction [ACTION_HOME]");
        } else {
            actionInfo->actionType = ACTION_NONE;
            LOG_DEBUG("ImuAction: getAction [ACTION_NONE]");
        }

        actionInfo->isAvailable = true;
        updated = false;
    } else {
        actionInfo->actionType = ACTION_NONE;
        actionInfo->isAvailable = false;
    }
    
    // 历史记录
    static uint8_t index = 0;
    if (index >= HISTORY_ACTIONS_NUM) {
        index = 0;
    }
    historyActions_[index] = actionInfo->actionType;
    index++;

    return CODE_OK;
}