#include "fw/imu.h"
#include "fw/logger.h"

IMU::IMU(uint16_t scl, uint16_t sda) 
: scl_(scl)
, sda_(sda)
, mpu6050_()
, imuMotion_({0, 0, 0, 0, 0, 0})
, imuMotionOffset_({0, 0, 0, 0, 0, 0})
, inited_(false)
{}

IMU::~IMU()
{}

void IMU::init()
{
    // TODO: I2C 统一封装
    Wire.begin(sda_, scl_);
    Wire.setClock(400000);
    while (!mpu6050_.testConnection())
    {
        LOG_WARNING("IMU: MPU6050 test connextion ...");
    }
    mpu6050_.initialize();
    calibrate();
    inited_ = true;
}

void IMU::update()
{
    if (!inited_) {
        LOG_ERROR("IMU: Please init first");
        return;
    }
    mpu6050_.getMotion6(&imuMotion_.ax, &imuMotion_.ay, &imuMotion_.az, &imuMotion_.gx, &imuMotion_.gy, &imuMotion_.gz);
    LOG_TRACE(
        "IMU: update data, ax:%d ay:%d az:%d gx:%d gy:%d gz:%d", 
        imuMotion_.ax, imuMotion_.ay, imuMotion_.az, imuMotion_.gx, imuMotion_.gy, imuMotion_.gz
    );
}

// 自动校准
void IMU::calibrate()
{
    LOG_TRACE("IMU: calibrating ...");
    // 6次循环自动校正
    mpu6050_.CalibrateAccel(6);
    mpu6050_.CalibrateGyro(6);
    imuMotionOffset_.ax = mpu6050_.getXAccelOffset();
    imuMotionOffset_.ay = mpu6050_.getYAccelOffset();
    imuMotionOffset_.az = mpu6050_.getZAccelOffset();
    imuMotionOffset_.gx = mpu6050_.getXGyroOffset();
    imuMotionOffset_.gy = mpu6050_.getYGyroOffset();
    imuMotionOffset_.gz = mpu6050_.getZGyroOffset();
    LOG_TRACE(
        "IMU: calibrate data, ax:%d ay:%d az:%d gx:%d gy:%d gz:%d", 
        imuMotionOffset_.ax, imuMotionOffset_.ay, imuMotionOffset_.az, imuMotionOffset_.gx, imuMotionOffset_.gy, imuMotionOffset_.gz
    );
}