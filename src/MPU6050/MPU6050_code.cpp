#include "MPU6050.h"

Adafruit_MPU6050 mpu;

void mpuBegin() {
    if (!mpu.begin()) {
        Serial.println("Failed to find MPU6050 chip");
        while (1) { delay(10); }
    }
    
    mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
    mpu.setGyroRange(MPU6050_RANGE_500_DEG);
    mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
}

mpuReading getMPU() {
    mpuReading reading;
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);

    reading.gyro.x = g.gyro.x; // Assign gyro data
    reading.gyro.y = g.gyro.y;
    reading.gyro.z = g.gyro.z;

    return reading;
}
