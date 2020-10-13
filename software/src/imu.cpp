/**
 * @file IMU.cpp
 * @author Daniel Stumpp (dcs98@pitt.edu)
 * @brief 
 * @version 0.1
 * @date 2020-09-21
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include "IMU.hpp"

/* Set the delay between fresh samples */
    #define BNO055_SAMPLERATE_DELAY_MS (100)

    // Check I2C device address and correct line below (by default address is 0x29 or 0x28)
    //                                   id, address
    Adafruit_BNO055 bno = Adafruit_BNO055(-1, 0x28);

bool IMU::init()
{
    Serial.println("Initializing IMU...");

    Serial.begin(115200);
        /* Initialise the sensor */
    if(!bno.begin())
    {
        /* There was a problem detecting the BNO055 ... check your connections */
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        while(1);
    }
    
    bno.setExtCrystalUse(true);

    return true;
}

bool IMU::read(Data *data)
{
    
    Serial.println("Reading IMU data...");

    /* Get the four calibration values (0..3) */
    /* Any sensor data reporting 0 should be ignored, */
    /* 3 means 'fully calibrated" */
    uint8_t system, gyro, accel, mag;
    system = gyro = accel = mag = 0;
    bno.getCalibration(&system, &gyro, &accel, &mag);

    /* Get a new sensor event (EULER) */
    sensors_event_t event;
    bno.getEvent(&event);
    if ((system && gyro && mag && accel) >= 0){

        /* Get a magnetization vector */
        imu::Vector<3> magnet = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

        /* Get a angular acceleration vector */
        imu::Vector<3> omega = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);

        /* Get Quat Data */
        imu::Quaternion quat = bno.getQuat();

        /* Display the current temperature */
        int8_t temp = bno.getTemp();

    
        data->imuData.eulerX = event.orientation.x;
        data->imuData.eulerY = event.orientation.y;
        data->imuData.eulerZ = event.orientation.z;
        data->imuData.quatA = quat.w();
        data->imuData.quatB = quat.x();
        data->imuData.quatC = quat.y();
        data->imuData.quatD = quat.z();
        data->imuData.omegaX = omega.x();
        data->imuData.omegaY = omega.y();
        data->imuData.omegaZ = omega.z();
        data->imuData.magX = magnet.x();  
        data->imuData.magY = magnet.y();
        data->imuData.magZ = magnet.z();
        data->imuData.temp = temp;

        Serial.print("Current Temperature: ");
        Serial.print(data->imuData.temp);
        Serial.println(" C");
        Serial.println("");

        /* Display the floating point data */
        Serial.println("Euler Vectors");
        Serial.print("X: ");
        Serial.print(data->imuData.eulerX);
        Serial.print("\tY: ");
        Serial.print(data->imuData.eulerY);
        Serial.print("\tZ: ");
        Serial.println(data->imuData.eulerZ);
        Serial.println("");

    /* Display the floating point data */
        Serial.println("Quaternion Vectors");
        Serial.print("A: ");
        Serial.print(data->imuData.quatA);
        Serial.print("\tB: ");
        Serial.print(data->imuData.quatB);
        Serial.print("\tC: ");
        Serial.print(data->imuData.quatC);
        Serial.print("\tD: ");
        Serial.println(data->imuData.quatD);
        Serial.println("");

        /* Display the floating point data */
        Serial.println("Angular Acceleration Vectors");
        Serial.print("w(X): ");
        Serial.print(data->imuData.omegaX);
        Serial.print("\tw(Y): ");
        Serial.print(data->imuData.omegaY);
        Serial.print("\tw(Z): ");
        Serial.println(data->imuData.omegaZ);
        Serial.println("");

        /* Display the floating point data */
        Serial.println("Magnetization Vectors");
        Serial.print("X: ");
        Serial.print(data->imuData.magX);
        Serial.print("\tY: ");
        Serial.print(data->imuData.magY);
        Serial.print("\tZ: ");
        Serial.println(data->imuData.magZ);
        Serial.println("");
        
    }

    
    return true;
}

bool IMU::enable()
{
    return true;
}

bool IMU::disable()
{
    return true;
}