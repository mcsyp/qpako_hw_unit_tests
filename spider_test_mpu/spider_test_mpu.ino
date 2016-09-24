#include "pin.h"
#include "math.h"


#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"


#define M_PI 3.1415926f


MPU6050 mpu;
#if (I2CDEV_IMPLEMENTATION==I2CDEV_SOFTWARE)
void soft_i2c_delay(void) {
	delayMicroseconds(5);
}
void soft_i2c_sda_mode(uint8_t value) {
	if (value) {
		pinMode(SOFT_I2C_SDA, OUTPUT);
	}
	else {
		pinMode(SOFT_I2C_SDA, INPUT);
	}
}
void soft_i2c_sda_write(uint8_t value) {
	digitalWrite(SOFT_I2C_SDA, value);
}
uint8_t soft_i2c_sda_read(void) {
	return digitalRead(SOFT_I2C_SDA);
}
void soft_i2c_scl_write(uint8_t value) {
	digitalWrite(SOFT_I2C_SCL, value);
}

#endif

bool g_dmpReady = false;
int g_packetSize = 0;
uint16_t g_fifoCount=0;     // count of all bytes currently in FIFO
uint8_t g_fifoBuffer[64]; // FIFO storage buffer
Quaternion g_q;
VectorFloat g_gravity;
float g_ypr[3];
float g_heading;
float g_lastHeading=0;
bool g_mpuInterrupt = false;
void dmpDataReady()
{
	g_mpuInterrupt = true;
}

void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Hello world!");
  
  //init the dmp6050
#if I2CDEV_IMPLEMENTATION == I2CDEV_SOFTWARE
  pinMode(SOFT_I2C_SDA, OUTPUT);
  pinMode(SOFT_I2C_SCL, OUTPUT);
  soft_i2c_init();
#endif
  do{
	  mpu.initialize();
	  // load and configure the DMP
	  Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

	  Serial.println(F("Initializing DMP..."));
	  if (mpu.dmpInitialize()) {
			g_dmpReady = false;
			break;
	  }
	  g_dmpReady = true;
	  
	  // supply your own gyro offsets here, scaled for min sensitivit
	  mpu.setXGyroOffset(220);
	  mpu.setYGyroOffset(76);
	  mpu.setZGyroOffset(-85);
	  mpu.setZAccelOffset(1788); // 1688 factory default for my test chip
	  //mpu.setRate(9);//50hz
	  if (g_dmpReady) {
		  // turn on the DMP, now that it's ready
		  Serial.println(F("Enabling DMP..."));
		  mpu.setDMPEnabled(true);

		  attachInterrupt(MPU6050_INT_RDY, dmpDataReady, RISING);
		  mpu.getIntStatus();
  
		  // set our DMP Ready flag so the main loop() function knows it's okay to use it
		  Serial.println(F("DMP ready! Waiting for first interrupt..."));
		 
		  // get expected DMP packet size for later comparison
		  g_packetSize = mpu.dmpGetFIFOPacketSize();
		}
  }while(0);
}

void schedule_dmp() {
	//while (!g_mpuInterrupt && g_fifoCount < g_packetSize) {
	//}
	// reset interrupt flag and get INT_STATUS byte
	g_mpuInterrupt = false;
    uint8_t mpuIntStatus = mpu.getIntStatus();

	// get current FIFO count
	g_fifoCount = mpu.getFIFOCount();

	// check for overflow (this should never happen unless our code is too inefficient)
	if ((mpuIntStatus & 0x10) || g_fifoCount == 1024) {
		// reset so we can continue cleanly
		mpu.resetFIFO();
		//Serial.println(F("FIFO overflow!"));

		// otherwise, check for DMP data ready interrupt (this should happen frequently)
	}
	else if (mpuIntStatus & 0x02) {
		
		// wait for correct available data length, should be a VERY short wait
		while (g_fifoCount < g_packetSize) g_fifoCount = mpu.getFIFOCount();

		// read a packet from FIFO
		mpu.getFIFOBytes(g_fifoBuffer, g_packetSize);

		// track FIFO count here in case there is > 1 packet available
		// (this lets us immediately read more without waiting for an interrupt)
		g_fifoCount -= g_packetSize;


		// display Euler angles in degrees
		mpu.dmpGetQuaternion(&g_q, g_fifoBuffer);
		mpu.dmpGetGravity(&g_gravity, &g_q);
		mpu.dmpGetYawPitchRoll(g_ypr, &g_q, &g_gravity);
		g_heading = g_ypr[0] * 180 / M_PI;
    Serial.print("heading:");Serial.println(g_heading);
	}
}

void loop() {
	schedule_dmp();
}








