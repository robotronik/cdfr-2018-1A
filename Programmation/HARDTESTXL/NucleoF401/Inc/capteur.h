#ifndef CAPTEUR_H
#define CAPTEUR_H

#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "xl_320.h"
#include "stm32f4xx_hal.h"
#include "servo.h"
#include "vl53l0x_api.h"
#include "X-NUCLEO-53L0A1.h"

#define ERR_DETECT             -1
#define ERR_DEMO_RANGE_ONE     1
#define ERR_DEMO_RANGE_MULTI   2
#define MAXI_CHAR_TRANSMIT 50
#define debug_printf    trace_printf

typedef enum {
	LONG_RANGE 		= 0, /*!< Long range mode */
	HIGH_SPEED 		= 1, /*!< High speed mode */
	HIGH_ACCURACY	= 2, /*!< High accuracy mode */
} RangingConfig_e;

extern VL53L0X_Dev_t VL53L0XDevs[];
extern TIM_HandleTypeDef htim3;
extern VL53L0X_RangingMeasurementData_t RangingMeasurementData;

extern int LeakyFactorFix8;
extern int nDevPresent;
extern int nDevMask;
extern int RangeLow;
extern int RangeMedium;

void RangeDemo(int UseSensorsMask, RangingConfig_e rangingConfig, XL* servo);

/* Store new ranging data into the device structure, apply leaky integrator if needed */
void Sensor_SetNewRange(VL53L0X_Dev_t *pDev, VL53L0X_RangingMeasurementData_t *pRange);

char RangeToLetter(VL53L0X_Dev_t *pDev, VL53L0X_RangingMeasurementData_t *pRange);

/**
 *  Setup all detected sensors for single shot mode and setup ranging configuration
 */
void SetupSingleShot(RangingConfig_e rangingConfig);

/**
 * Reset all sensor then do presence detection
 *
 * All present devices are data initiated and assigned to their final I2C address
 * @return
 */
int DetectSensors(int SetDisplay);

/**
 * Handle Error
 *
 * Set err on display and loop forever
 * @param err Error case code
 */
void HandleError(int err);

void ResetAndDetectSensor(int SetDisplay);

#endif
