#ifndef _IMU_H_
#define _IMU_H_

#include <MPU6050.h>

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
    void init();
    void update();
    int16_t getAccelX() { return imuMotion_.ax; };
    int16_t getAccelY() { return imuMotion_.ay; };
    int16_t getAccelZ() { return imuMotion_.az; };
    int16_t getGyroX()  { return imuMotion_.gx; };
    int16_t getGyroY()  { return imuMotion_.gy; };
    int16_t getGyroZ()  { return imuMotion_.gz; };
private:
    void calibrate();
private:
    uint16_t scl_;
    uint16_t sda_;
    MPU6050 mpu6050_;
    ImuMotion imuMotion_;
    ImuMotionOffset imuMotionOffset_;
    bool inited_;
};


#endif // !_IMU_H_