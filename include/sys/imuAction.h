#ifndef _IMU_ACTION_H_
#define _IMU_ACTION_H_

#include "fw/errorCode.h"
#include "fw/imu.h"

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
    ACTION_TYPE actionType = ACTION_NONE;
    bool isAvailable = false;
}ActionInfo;


class ImuAction 
{
public:
    ImuAction(IMU* imu);
    ~ImuAction();
    ErrorCode init();
    ErrorCode getAction(ActionInfo* actionInfo);
private:
    IMU* imu_;
    bool inited_;
};

#endif