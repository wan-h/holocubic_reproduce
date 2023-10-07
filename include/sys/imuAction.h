#ifndef _IMU_ACTION_H_
#define _IMU_ACTION_H_

#include "fw/errorCode.h"
#include "fw/imu.h"

#define HISTORY_ACTIONS_NUM 3

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
    ImuAction(IMU* imu, uint16_t interval);
    ~ImuAction();
    ErrorCode init();
    ErrorCode getAction(ActionInfo* actionInfo);
private:
    bool checkInit();
private:
    IMU* imu_;
    uint16_t interval_;
    ACTION_TYPE historyActions_[HISTORY_ACTIONS_NUM];
    bool inited_;
};

#endif