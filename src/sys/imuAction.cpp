#include "sys/imuAction.h"

static bool updated = false;

ImuAction::ImuAction(IMU* imu, uint16_t interval)
: imu_(imu)
, interval_(interval)
, xTimerAction(nullptr)
, inited_(false)
{}

ImuAction::~ImuAction()
{
    inited_ = false;
}

ErrorCode ImuAction::init()
{
    // 设置定时器
    // xTimerAction = xTimerCreate("Action Check",
    //                             200 / portTICK_PERIOD_MS,
    //                             pdTRUE, (void *)0, actionCheckHandle);
}

ErrorCode ImuAction::getAction(ActionInfo* actionInfo)
{

}