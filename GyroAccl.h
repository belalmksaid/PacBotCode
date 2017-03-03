#ifndef GYROACCL
#define GYROACCL

#include "Arduino.h"

#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
    #include "Wire.h"
#endif

class GyroAccl {
public:
	GyroAccl() {

	}

	void update(unsigned long timestamp) {
		if (!dmpReady) return;
 		while (fifoCount < packetSize) {
 			break;
  		}
  		mpuInterrupt = false;
 		mpuIntStatus = mpu.getIntStatus();
 		fifoCount = mpu.getFIFOCount();
 		if ((mpuIntStatus & 0x10) || fifoCount == 1024)
  		{
	    	mpu.resetFIFO();
 	   		Serial.println(F("FIFO overflow!"));
  		}
  		else if (mpuIntStatus & 0x02)
  		{
    		while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();
   			mpu.getFIFOBytes(fifoBuffer, packetSize);
  			fifoCount -= packetSize;
 			mpu.dmpGetQuaternion(&q, fifoBuffer);
    		mpu.dmpGetGyro(gyro, fifoBuffer);
    		mpu.dmpGetEuler(euler, &q);
    		dt = gyro[0];
    		orientation = euler[0];
  		} 
	}

	void init() {
		Wire.begin();
		TWBR = 24;
		mpu.initialize();
    	devStatus = mpu.dmpInitialize();
 	    mpu.setXGyroOffset(220);
	    mpu.setYGyroOffset(76);
	    mpu.setZGyroOffset(-85);
	    mpu.setZAccelOffset(1788);
    	if (devStatus == 0) {
    	    mpu.setDMPEnabled(true);
        	mpuIntStatus = mpu.getIntStatus();
        	dmpReady = true;
       		packetSize = mpu.dmpGetFIFOPacketSize();
    	} else {
        	Serial.print(F("DMP Initialization failed (code "));
        	Serial.print(devStatus);
        	Serial.println(F(")"));
    	}
	}

	double getChange() {
		return dt - dtdrift;
	}

	void reset() {
		dt = 0;
	}

	void dmpDataReady()
	{
	  mpuInterrupt = true;
	}

	void setDrift() {
		dtdrift = (dt + dtdrift) / 2.0;
	}

private:

	double dt = 0.0;
	double dtdrift = 0.0;
	double orientation = 0.0;

	MPU6050 mpu;            // AD0 low = 0x68

	// MPU control/status vars
	bool dmpReady = false;  // set true if DMP init was successful
	uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
	uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
	uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
	uint16_t fifoCount;     // count of all bytes currently in FIFO
	uint8_t fifoBuffer[64]; // FIFO storage buffer

	// orientation/motion vars
	Quaternion q;           // [w, x, y, z]         quaternion container
	VectorFloat gravity;    // [x, y, z]            gravity vector
	int16_t gyro[3];        // [x, y, z]            gyro vector
	float euler[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

	volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
	byte buf_tmp=0;
	uint8_t i2cData[14];




};

#endif
