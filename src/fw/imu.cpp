#include "fw/imu.h"
#include "fw/logger.h"
#include <map>

static std::map<uint8_t, float> LSB_GYRO_MAP
{
    {MPU6050_IMU::MPU6050_GYRO_FS_250,  131},
    {MPU6050_IMU::MPU6050_GYRO_FS_500,  65.5},
    {MPU6050_IMU::MPU6050_GYRO_FS_1000, 32.8},
    {MPU6050_IMU::MPU6050_GYRO_FS_2000, 16.4}
};

static std::map<uint8_t, float> LSB_ACCEL_MAP
{
    {MPU6050_IMU::MPU6050_ACCEL_FS_2,  16384},
    {MPU6050_IMU::MPU6050_ACCEL_FS_4,  8192},
    {MPU6050_IMU::MPU6050_ACCEL_FS_8,  4096},
    {MPU6050_IMU::MPU6050_ACCEL_FS_16, 2048}
};

IMU::IMU(uint16_t scl, uint16_t sda) 
: scl_(scl)
, sda_(sda)
, mpu6050_()
, imuMotion_({0, 0, 0, 0, 0, 0})
, imuMotionOffset_({0, 0, 0, 0, 0, 0})
, fsGyroRange_(0)
, fsAccelRange_(0)
, inited_(false)
{}

IMU::~IMU()
{
    inited_ = false;
}

ErrorCode IMU::init()
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

    fsGyroRange_ = mpu6050_.getFullScaleGyroRange();
    fsAccelRange_ = mpu6050_.getFullScaleAccelRange();
    
    inited_ = true;

    LOG_INFO("IMU: init ok");
    return CODE_OK;
}

bool IMU::checkInit()
{
    if (!inited_) {
        LOG_ERROR("IMU: Please init first");
    }
    return inited_;
}

ErrorCode IMU::update()
{
    if (!checkInit()) return CODE_ERROR_INIT_CHECK;

    mpu6050_.getMotion6(&imuMotion_.ax, &imuMotion_.ay, &imuMotion_.az, &imuMotion_.gx, &imuMotion_.gy, &imuMotion_.gz);
    LOG_TRACE(
        "IMU: update data, ax:%.3fg ay:%.3fg az:%.3fg gx:%.3fdeg/s gy:%.3fdeg/s gz:%.3fdeg/s", 
        getAccelX(), getAccelY(), getAccelZ(), getGyroX(), getGyroY(), getGyroZ()
    );

    return CODE_OK;
}

// 自动校准
void IMU::calibrate()
{
    LOG_TRACE("IMU: calibrating ...");
    // 600 readings
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

float IMU::getValue(int16_t value, bool isAccel)
{
    if (isAccel) {
        return value / LSB_ACCEL_MAP[fsAccelRange_];
    } else {
        return value / LSB_GYRO_MAP[fsGyroRange_];
    }
}