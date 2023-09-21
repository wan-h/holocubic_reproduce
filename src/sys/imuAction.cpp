#include "sys/imuAction.h"
#include "fw/logger.h"

ImuAction::ImuAction(IMU* imu)
: imu_(imu)
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

    LOG_INFO("ImuAction: init ok");
    return CODE_OK;
}

ErrorCode ImuAction::getAction(ActionInfo* actionInfo)
{
    // 动作判断
    ErrorCode ret = imu_->update();
    if (ret != CODE_OK) return ret;

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
    return CODE_OK;
}