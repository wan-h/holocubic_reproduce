#ifndef _IMU_ACTION_H_
#define _IMU_ACTION_H_

#include "fw/errorCode.h"
#include "fw/imu.h"
#include <esp32-hal-timer.h>

enum ACTION_TYPE {
    ACTION_NONE = 0,
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_UP,
    ACTION_DOWN,
    ACTION_HOME,
    ACTION_UNKNOWN
};

typedef struct ActionInfo
{
    ACTION_TYPE actionType;
    bool isAvailable;
};


class ImuAction 
{
public:
    ImuAction(IMU* imu, uint16_t interval);
    ~ImuAction();
    ErrorCode init();
    ErrorCode getAction(ActionInfo* actionInfo);
private:
    IMU* imu_;
    uint16_t interval_;
    TimerHandle_t xTimerAction;
    bool inited_;
};

#endif