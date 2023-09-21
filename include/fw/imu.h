#ifndef _IMU_H_
#define _IMU_H_

#include <MPU6050.h>
#include "fw/errorCode.h"

typedef struct ImuMotion
{
    int16_t ax;
    int16_t ay;
    int16_t az;
    int16_t gx;
    int16_t gy;
    int16_t gz;
}ImuMotion;

typedef struct ImuMotionOffset
{
    int16_t ax;
    int16_t ay;
    int16_t az;
    int16_t gx;
    int16_t gy;
    int16_t gz;
}ImuMotionOffset;


class IMU {
public:
    IMU(uint16_t scl, uint16_t sda);
    ~IMU();
    ErrorCode init();
    ErrorCode update();
    float getAccelX() { return getValue(imuMotion_.ax, true); };
    float getAccelY() { return getValue(imuMotion_.ay, true); };
    float getAccelZ() { return getValue(imuMotion_.az, true); };
    float getGyroX()  { return getValue(imuMotion_.gx, false); };
    float getGyroY()  { return getValue(imuMotion_.gy, false); };
    float getGyroZ()  { return getValue(imuMotion_.gz, false); };
private:
    bool checkInit();
    void calibrate();
    float getValue(int16_t value, bool isAccel);
private:
    uint16_t scl_;
    uint16_t sda_;
    MPU6050 mpu6050_;
    ImuMotion imuMotion_;
    ImuMotionOffset imuMotionOffset_;
    uint8_t fsGyroRange_;
    uint8_t fsAccelRange_;
    bool inited_;
};


#endif // !_IMU_H_