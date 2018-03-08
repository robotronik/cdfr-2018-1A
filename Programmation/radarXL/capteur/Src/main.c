/*!!!!!WARNING : ALIMENTATION!!!!!
~> Nucleo : 5V ?(ordi)
-> Servo : 7.40V / 500mA ?
*/


/**
  ******************************************************************************
  * File Name          : main.c
  * Date               : 01/03/2018 16:55:48
  * Description        : Main program body
  ******************************************************************************
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* USER CODE BEGIN Includes */
#include <string.h>
#include "X-NUCLEO-53L0A1.h"
#include "vl53l0x_api.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include "xl_320.h"

/**
 * @defgroup Configuration Static configuration
 * @{
 */
#define HAVE_ALARM_DEMO 0

/** Time the initial 53L0 message is shown at power up */
#define WelcomeTime 660

/** Time the initial 53L0 message is shown at power up */
#define ModeChangeDispTime  500

/**
 * Time considered as  a "long push" on push button
 */
#define PressBPSwicthTime   1000

/** @}  */ /* config group */

#ifndef MIN
#   define MIN(a,b) ((a) < (b) ? (a) : (b))
#endif

#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define USART1_DIR_Pin GPIO_PIN_9
#define USART1_DIR_GPIO_Port GPIOC


#ifndef ARRAY_SIZE
#   define ARRAY_SIZE(x) (sizeof((x))/sizeof((x)[0]))
#endif

/**
 * @defgroup ErrCode Errors code shown on display
 * @{
 */
#define ERR_DETECT             -1
#define ERR_DEMO_RANGE_ONE     1
#define ERR_DEMO_RANGE_MULTI   2


/** }@} */ /* defgroup ErrCode */


/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

const char TxtRangeValue[]  = "rng";
const char TxtBarGraph[]    = "bar";
#if HAVE_ALARM_DEMO
const char TxtAlarm[]       = "Alr";
#endif


typedef enum {
	LONG_RANGE 		= 0, /*!< Long range mode */
	HIGH_SPEED 		= 1, /*!< High speed mode */
	HIGH_ACCURACY	= 2, /*!< High accuracy mode */
} RangingConfig_e;
char *RangingConfigTxt[3] = {"LR", "HS", "HA"};

typedef enum {
	RANGE_VALUE 	= 0, /*!< Range displayed in cm */
	BAR_GRAPH 		= 1, /*!< Range displayed as a bar graph : one bar per sensor */
} DemoMode_e;
char *DemoModeTxt[2] = {"rng", "bar"};

/**
 * Global ranging struct
 */
VL53L0X_RangingMeasurementData_t RangingMeasurementData;


/** leaky factor for filtered range
 *
 * r(n) = averaged_r(n-1)*leaky +r(n)(1-leaky)
 *
 * */
int LeakyFactorFix8 = (int)( 0.6 *256);
/** How many device detect set by @a DetectSensors()*/
int nDevPresent=0;
/** bit is index in VL53L0XDevs that is not necessary the dev id of the BSP */
int nDevMask;


VL53L0X_Dev_t VL53L0XDevs[]={
        {.Id=XNUCLEO53L0A1_DEV_LEFT, .DevLetter='l', .I2cHandle=&XNUCLEO53L0A1_hi2c, .I2cDevAddr=0x52},
        {.Id=XNUCLEO53L0A1_DEV_CENTER, .DevLetter='c', .I2cHandle=&XNUCLEO53L0A1_hi2c, .I2cDevAddr=0x52},
        {.Id=XNUCLEO53L0A1_DEV_RIGHT, .DevLetter='r', .I2cHandle=&XNUCLEO53L0A1_hi2c, .I2cDevAddr=0x52},
};

/** range low (and high) in @a RangeToLetter()
 *
 * used for displaying  multiple sensor as bar graph
 */
int RangeLow=100;

/** range medium in @a RangeToLetter()
 *
 * used for displaying  multiple sensor as bar graph
 */
int RangeMedium=300;

/** Timer
 *
 * Used to get time stamp for UART logging
 */
TIM_HandleTypeDef htim5;

/* TIM5 init function */
void MX_TIM5_Init(void)
{

  TIM_MasterConfigTypeDef sMasterConfig;
  TIM_OC_InitTypeDef sConfigOC;

  htim5.Instance = TIM5;
  htim5.Init.Prescaler = 83;
  htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim5.Init.Period = 0xFFFFFFFF;
  htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_OC_Init(&htim5);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig);

  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_OC_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1);

}

void TimeStamp_Init(){
    MX_TIM5_Init();
}

void TimeStamp_Reset(){
    HAL_TIM_Base_Start(&htim5);
    htim5.Instance->CNT=0;
}

uint32_t TimeStamp_Get(){
    return htim5.Instance->CNT;
}

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
static void MX_GPIO_Init(void);
static void SystemClock_Config(void);
static void MX_I2C1_Init(void);
static void MX_TIM3_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
void ResetAndDetectSensor(int SetDisplay);

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */

#define debug_printf    trace_printf
char WelcomeMsg[]="Hi I am Ranging VL53L0X mcu " MCU_NAME "\n";

#if HAVE_ALARM_DEMO
volatile int IntrCount;
volatile int LastIntrPin;
volatile int LastIntrId;
volatile int IntrCounts[3];
#endif

#define BSP_BP_PORT GPIOC
#define BSP_BP_PIN  GPIO_PIN_13

int BSP_GetPushButton(void){
    GPIO_PinState state ;
    state = HAL_GPIO_ReadPin(BSP_BP_PORT, BSP_BP_PIN);
    return state;
}

/**
 * When button is already pressed it waits for user to release it.
 * if button remains pressed for a given time it returns true.
 * This is used to detect mode switch by long press on blue Push Button
 *
 * As soon as time is elapsed -rb- is displayed to let user know the mode
 * switch is taken into account
 *
 * @return True if button remains pressed more than specified time
 */
int PusbButton_WaitUnPress(void){
    uint32_t TimeStarted;
    TimeStarted = HAL_GetTick();
    while( !BSP_GetPushButton() ){ ; /* debounce */
        if(HAL_GetTick()- TimeStarted> PressBPSwicthTime){
            XNUCLEO53L0A1_SetDisplayString (" rb ");
        }
    }
    return  HAL_GetTick() - TimeStarted>PressBPSwicthTime;

}

#if HAVE_ALARM_DEMO
/**
 * Interrupt handler called each time an interrupt is produced by the ranging sensor (in ALARM mode)
 * @param err
 */
void VL53L0A1_EXTI_Callback(int DevNo, int GPIO_Pin){
    IntrCount++;
    LastIntrPin=GPIO_Pin;
    LastIntrId=DevNo;

    if( DevNo< ARRAY_SIZE(IntrCounts)  ){
        IntrCounts[DevNo]++;
    }
}
#endif


/**
 * Handle Error
 *
 * Set err on display and loop forever
 * @param err Error case code
 */
void HandleError(int err){
    char msg[16];
    sprintf(msg,"Er%d", err);
    XNUCLEO53L0A1_SetDisplayString(msg);
    while(1){};
}

/**
 * Reset all sensor then do presence detection
 *
 * All present devices are data initiated and assigned to their final I2C address
 * @return
 */
int DetectSensors(int SetDisplay) {
    int i;
    uint16_t Id;
    int status;
    int FinalAddress;

    char PresentMsg[5]="    ";
    /* Reset all */
    nDevPresent = 0;
    for (i = 0; i < 3; i++)
        status = XNUCLEO53L0A1_ResetId(i, 0);

    /* detect all sensors (even on-board)*/
    for (i = 0; i < 3; i++) {
        VL53L0X_Dev_t *pDev;
        pDev = &VL53L0XDevs[i];
        pDev->I2cDevAddr = 0x52;
        pDev->Present = 0;
        status = XNUCLEO53L0A1_ResetId( pDev->Id, 1);
        HAL_Delay(2);
        FinalAddress=0x52+(i+1)*2;

        do {
        	/* Set I2C standard mode (400 KHz) before doing the first register access */
        	if (status == VL53L0X_ERROR_NONE)
        		status = VL53L0X_WrByte(pDev, 0x88, 0x00);

        	/* Try to read one register using default 0x52 address */
            status = VL53L0X_RdWord(pDev, VL53L0X_REG_IDENTIFICATION_MODEL_ID, &Id);
            if (status) {
                debug_printf("#%d Read id fail\n", i);
                break;
            }
            if (Id == 0xEEAA) {
				/* Sensor is found => Change its I2C address to final one */
                status = VL53L0X_SetDeviceAddress(pDev,FinalAddress);
                if (status != 0) {
                    debug_printf("#i VL53L0X_SetDeviceAddress fail\n", i);
                    break;
                }
                pDev->I2cDevAddr = FinalAddress;
                /* Check all is OK with the new I2C address and initialize the sensor */
                status = VL53L0X_RdWord(pDev, VL53L0X_REG_IDENTIFICATION_MODEL_ID, &Id);
                if (status != 0) {
					debug_printf("#i VL53L0X_RdWord fail\n", i);
					break;
				}

                status = VL53L0X_DataInit(pDev);
                if( status == 0 ){
                    pDev->Present = 1;
                }
                else{
                    debug_printf("VL53L0X_DataInit %d fail\n", i);
                    break;
                }
                trace_printf("VL53L0X %d Present and initiated to final 0x%x\n", pDev->Id, pDev->I2cDevAddr);
                nDevPresent++;
                nDevMask |= 1 << i;
                pDev->Present = 1;
            }
            else {
                debug_printf("#%d unknown ID %x\n", i, Id);
                status = 1;
            }
        } while (0);
        /* if fail r can't use for any reason then put the  device back to reset */
        if (status) {
            XNUCLEO53L0A1_ResetId(i, 0);
        }
    }
    /* Display detected sensor(s) */
    if( SetDisplay ){
        for(i=0; i<3; i++){
            if( VL53L0XDevs[i].Present ){
                PresentMsg[i+1]=VL53L0XDevs[i].DevLetter;
            }
        }
        PresentMsg[0]=' ';
        XNUCLEO53L0A1_SetDisplayString(PresentMsg);
        HAL_Delay(1000);
    }

    return nDevPresent;
}

/**
 *  Setup all detected sensors for single shot mode and setup ranging configuration
 */
void SetupSingleShot(RangingConfig_e rangingConfig){
    int i;
    int status;
    uint8_t VhvSettings;
    uint8_t PhaseCal;
    uint32_t refSpadCount;
	uint8_t isApertureSpads;
	FixPoint1616_t signalLimit = (FixPoint1616_t)(0.25*65536);
	FixPoint1616_t sigmaLimit = (FixPoint1616_t)(18*65536);
	uint32_t timingBudget = 33000;
	uint8_t preRangeVcselPeriod = 14;
	uint8_t finalRangeVcselPeriod = 10;

    for( i=0; i<3; i++){
        if( VL53L0XDevs[i].Present){
            status=VL53L0X_StaticInit(&VL53L0XDevs[i]);
            if( status ){
                debug_printf("VL53L0X_StaticInit %d failed\n",i);
            }

            status = VL53L0X_PerformRefCalibration(&VL53L0XDevs[i], &VhvSettings, &PhaseCal);
			if( status ){
			   debug_printf("VL53L0X_PerformRefCalibration failed\n");
			}

			status = VL53L0X_PerformRefSpadManagement(&VL53L0XDevs[i], &refSpadCount, &isApertureSpads);
			if( status ){
			   debug_printf("VL53L0X_PerformRefSpadManagement failed\n");
			}

            status = VL53L0X_SetDeviceMode(&VL53L0XDevs[i], VL53L0X_DEVICEMODE_SINGLE_RANGING); // Setup in single ranging mode
            if( status ){
               debug_printf("VL53L0X_SetDeviceMode failed\n");
            }

            status = VL53L0X_SetLimitCheckEnable(&VL53L0XDevs[i], VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, 1); // Enable Sigma limit
			if( status ){
			   debug_printf("VL53L0X_SetLimitCheckEnable failed\n");
			}

			status = VL53L0X_SetLimitCheckEnable(&VL53L0XDevs[i], VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, 1); // Enable Signa limit
			if( status ){
			   debug_printf("VL53L0X_SetLimitCheckEnable failed\n");
			}
			/* Ranging configuration */
            switch(rangingConfig) {
            case LONG_RANGE:
            	signalLimit = (FixPoint1616_t)(0.1*65536);
            	sigmaLimit = (FixPoint1616_t)(60*65536);
            	timingBudget = 33000; //33ms
            	preRangeVcselPeriod = 18;
            	finalRangeVcselPeriod = 14;
            	break;
            case HIGH_ACCURACY:
				signalLimit = (FixPoint1616_t)(0.25*65536); //the return signal rate limit in MCPS
				sigmaLimit = (FixPoint1616_t)(18*65536);
				timingBudget = 200000; //200ms
				preRangeVcselPeriod = 14; //laser pulse periods
				finalRangeVcselPeriod = 10;
				break;
            case HIGH_SPEED:
				signalLimit = (FixPoint1616_t)(0.25*65536);
				sigmaLimit = (FixPoint1616_t)(32*65536);
				timingBudget = 20000; //20ms
				preRangeVcselPeriod = 14;
				finalRangeVcselPeriod = 10;
				break;
            default:
            	debug_printf("Not Supported");
            }

            status = VL53L0X_SetLimitCheckValue(&VL53L0XDevs[i],  VL53L0X_CHECKENABLE_SIGNAL_RATE_FINAL_RANGE, signalLimit);
			if( status ){
			   debug_printf("VL53L0X_SetLimitCheckValue failed\n");
			}

			status = VL53L0X_SetLimitCheckValue(&VL53L0XDevs[i],  VL53L0X_CHECKENABLE_SIGMA_FINAL_RANGE, sigmaLimit);
			if( status ){
			   debug_printf("VL53L0X_SetLimitCheckValue failed\n");
			}

            status = VL53L0X_SetMeasurementTimingBudgetMicroSeconds(&VL53L0XDevs[i],  timingBudget);
            if( status ){
               debug_printf("VL53L0X_SetMeasurementTimingBudgetMicroSeconds failed\n");
            }

            status = VL53L0X_SetVcselPulsePeriod(&VL53L0XDevs[i],  VL53L0X_VCSEL_PERIOD_PRE_RANGE, preRangeVcselPeriod);
			if( status ){
			   debug_printf("VL53L0X_SetVcselPulsePeriod failed\n");
			}

            status = VL53L0X_SetVcselPulsePeriod(&VL53L0XDevs[i],  VL53L0X_VCSEL_PERIOD_FINAL_RANGE, finalRangeVcselPeriod);
			if( status ){
			   debug_printf("VL53L0X_SetVcselPulsePeriod failed\n");
			}

			status = VL53L0X_PerformRefCalibration(&VL53L0XDevs[i], &VhvSettings, &PhaseCal);
			if( status ){
			   debug_printf("VL53L0X_PerformRefCalibration failed\n");
			}

            VL53L0XDevs[i].LeakyFirst=1;
        }
    }
}

char RangeToLetter(VL53L0X_Dev_t *pDev, VL53L0X_RangingMeasurementData_t *pRange){
    char c;
    if( pRange->RangeStatus == 0 ){
        if( pDev->LeakyRange < RangeLow ){
            c='_';
        }
        else if( pDev->LeakyRange < RangeMedium ){
                c='=';
        }
        else {
            c = '~';
        }

    }
    else{
        c='-';
    }
    return c;
}

/* Store new ranging data into the device structure, apply leaky integrator if needed */
void Sensor_SetNewRange(VL53L0X_Dev_t *pDev, VL53L0X_RangingMeasurementData_t *pRange){
    if( pRange->RangeStatus == 0 ){
        if( pDev->LeakyFirst ){
            pDev->LeakyFirst = 0;
            pDev->LeakyRange = pRange->RangeMilliMeter;
        }
        else{
            pDev->LeakyRange = (pDev->LeakyRange*LeakyFactorFix8 + (256-LeakyFactorFix8)*pRange->RangeMilliMeter)>>8;
        }
    }
    else{
        pDev->LeakyFirst = 1;
    }
}

void blink_led(int valeur, int* compteur){     /////modification de la led
    if (*compteur == 6){                       /////modification toutes les 6 mesures correctes du capteur (valeur limite ?)
        HAL_TIM_Base_Stop_IT(&htim3);
        htim3.Instance->ARR = 2*valeur-1+20;   /////modification de la periode du capteur (voir wiki stm32 pour plus de details) selon une droite
        HAL_TIM_Base_Start_IT(&htim3);
        htim3.Instance->CNT = 0;               /////remise a zero du timer de la led
        *compteur = 0;                         /////remise a zero du compteur
    }
}

#define Maxi_char_transmit 10  /////////
#define Delay 1000  /////////
#define Delay2 10//////

/////transmit modifie a retoucher

/*void transmit(int* i, char* bufferDistance, char* bufferAngle, int distance, int angle){  /////transmission vers pc
    char dataDistance[10];                                /////variable stockage de la valeur du capteur
    char dataAngle[10];
    char ligne[2];                                /////variable stockage du separateur \n
    int len;                                      /////variable longueur du buffer
    if (*i<Maxi_char_transmit-1){                 /////ajout valeur, dans data
        sprintf(dataDistance, "%d,",distance);
        sprintf(dataAngle, "%d,",angle);
    }
    else if (*i==Maxi_char_transmit-1){           /////ajout valeur dans data -> pour cloturer la sequence
        sprintf(dataDistance, "%d",distance);
        sprintf(dataAngle, "%d",angle);
    }
    strcat(bufferDistance,dataDistance);                          /////ajout valeur au buffer
    strcat(bufferAngle, dataAngle);
    if (*i==Maxi_char_transmit-1){
        len=strlen(bufferDistance);                       /////longueur du buffer
        HAL_UART_Transmit(&huart2, (uint8_t*)(strcat(bufferDistance,";")), len, 1000); /////transmission du buffer
        HAL_UART_Transmit(&huart2, (uint8_t*)(bufferAngle), len, 1000);
        sprintf(ligne, "\n");                                     /////ajout \n a ligne
        HAL_UART_Transmit(&huart2, (uint8_t*)ligne, 1, 1000);     /////transmission pour cloturer la ligne
        (*i)=-1;                                                  /////remise a zero du compteur
        sprintf(bufferDistance, "");                                      /////remise a zero du buffer
        sprintf(bufferAngle, "");
        HAL_Delay(Delay);         //////necessaire pour le graphique
    }
}*/

void Variation2Angle_maison(XL servo, int* ptr_angle){ ///test fonctionne
		uint16_t position;
		char dataAngle[10];
		int len;
		if(*ptr_angle<1000 && *ptr_angle>=0){
				XL_Set_Goal_Position(&servo, *ptr_angle, 1);
				*ptr_angle+=5;
		} else {
				*ptr_angle=50;
				XL_Set_Goal_Position(&servo, *ptr_angle, 1);
		}
		//XL_Set_Goal_Position(&servo, *ptr_angle, 1);   /////test fonctionne Db=115200
		/*HAL_Delay(1000);
		XL_Get_Current_Position(&servo, &position);
		sprintf(dataAngle, "%d,",position);
		len=strlen(dataAngle);
		HAL_UART_Transmit(&huart2, (uint8_t*)(dataAngle), len, 1000);*/
}

void Variation3Angle_maison(XL servo, int* ptr_angle, char* buffer, int* i){ ///test fonctionne
		uint16_t position;
		char dataAngle[10];
		char ligne[2];
		int len;
		if(*ptr_angle<1000 && *ptr_angle>=0){
				XL_Set_Goal_Position(&servo, *ptr_angle, 1);
				*ptr_angle+=5;
		} else {
				*ptr_angle=50;
				XL_Set_Goal_Position(&servo, *ptr_angle, 1);
		}
		XL_Set_Goal_Position(&servo, *ptr_angle, 1);
		/*HAL_Delay(1000);
		XL_Get_Current_Position(&servo, &position);   /////test fonctionne Db=115200
		sprintf(dataAngle, "%d,",position);
		len=strlen(dataAngle);
		HAL_UART_Transmit(&huart2, (uint8_t*)(dataAngle), len, 1000); */
		HAL_Delay(Delay2);
		XL_Get_Current_Position(&servo, &position);
		HAL_Delay(Delay2);
    if (*i<Maxi_char_transmit-1){                 /////ajout valeur, dans data
        sprintf(dataAngle, "%d,",position);
				/*len=strlen(dataAngle);
				HAL_UART_Transmit(&huart2, (uint8_t*)(dataAngle), len, 1000);*/
    }  else if (*i==Maxi_char_transmit-1){           /////ajout valeur dans data -> pour cloturer la sequence
        sprintf(dataAngle, "%d",position);
				/*len=strlen(dataAngle);
				HAL_UART_Transmit(&huart2, (uint8_t*)(dataAngle), len, 1000);*/
    }
    strcat(buffer,dataAngle);                          /////ajout valeur au buffer
    if (*i==Maxi_char_transmit-1){
        len=strlen(buffer);                       /////longueur du buffer
        HAL_UART_Transmit(&huart2, (uint8_t*)(buffer), len, 1000); /////transmission du buffer
        sprintf(ligne, "\n");                                     /////ajout \n a ligne
        HAL_UART_Transmit(&huart2, (uint8_t*)ligne, 1, 1000);     /////transmission pour cloturer la ligne
        (*i)=-1;                                                  /////remise a zero du compteur
        sprintf(buffer, "");                                      /////remise a zero du buffer
        HAL_Delay(Delay);         //////necessaire pour le graphique
    }
}

/**
 * Implement the ranging demo with all modes managed through the blue button (short and long press)
 * This function implements a while loop until the blue button is pressed
 * @param UseSensorsMask Mask of any sensors to use if not only one present
 * @param rangingConfig Ranging configuration to be used (same for all sensors)
 */

/*void VariationAngle(XL * servo, int* ptr_compteurAngle){ /////fonction de raph bugge
    *ptr_compteurAngle=60;
    XL_Set_Goal_Position(servo, *ptr_compteurAngle, 1);
    if(*compteurAngle<621 && *compteurAngle>=0){
        XL_Set_Goal_Position(servo, *compteurAngle, 1);
        *compteurAngle++;
    }
    else if(*compteurAngle == 620){
        *compteurAngle --;
        XL_Set_Goal_Position(servo, *compteurAngle, 1);
    }
    else{
        XL_Set_Goal_Position(servo, *compteurAngle, 1);
        *compteurAngle--;
    }
}*/

int RangeDemo(int UseSensorsMask, RangingConfig_e rangingConfig, XL servo){
    int over=0;
    int status;
    char StrDisplay[5];
    char c;
    int i;
    int nSensorToUse;
    int SingleSensorNo=0;
    int distance;     ///creation variable distance
    /*unsigned int angle;        ///creation variable angle*/ //necessaire ?
    int compteur_blink = 0;                ///creation compteur
    int* ptr_compteur_blink = NULL;   ///creation pointeur sur compteur
    ptr_compteur_blink = &compteur_blink;
    int compteur_d = 0;                 ///creation compteur
    int* ptr_compteur = NULL;   ///creation pointeur sur compteur
    ptr_compteur = &compteur_d;
    char buffer[Maxi_char_transmit*4]; /////creation du buffer
    char buffer1[Maxi_char_transmit*5];
    int len;
    sprintf(buffer, "");               /////mise a zero du buffer
    sprintf(buffer1, "");
		int angle=10;              ////creation
	  int* ptr_angle = &angle;

    /* Setup all sensors in Single Shot mode */
    SetupSingleShot(rangingConfig);


    /* Which sensor to use ? */
    for(i=0, nSensorToUse=0; i<3; i++){
        if(( UseSensorsMask& (1<<i) ) && VL53L0XDevs[i].Present ){
            nSensorToUse++;
            if( nSensorToUse==1 )
                SingleSensorNo=i;
        }
    }
    if( nSensorToUse == 0 ){
        return -1;
    }

    /* Start ranging until blue button is pressed */
    do{
				//Variation2Angle_maison(servo, ptr_angle); ////fait bouger le servo
        if( nSensorToUse >1 ){
        	/* Multiple devices */
            strcpy(StrDisplay, "    ");
            for( i=0; i<3; i++){
                if( ! VL53L0XDevs[i].Present  || (UseSensorsMask & (1<<i))==0 )
                    continue;
                /* Call All-In-One blocking API function */
                status = VL53L0X_PerformSingleRangingMeasurement(&VL53L0XDevs[i],&RangingMeasurementData);
                if( status ){
                    HandleError(ERR_DEMO_RANGE_MULTI);
                }
                /* Push data logging to UART */
                trace_printf("%d,%u,%d,%d,%d\n", VL53L0XDevs[i].Id, TimeStamp_Get(), RangingMeasurementData.RangeStatus, RangingMeasurementData.RangeMilliMeter, RangingMeasurementData.SignalRateRtnMegaCps);
                /* Store new ranging distance */
                Sensor_SetNewRange(&VL53L0XDevs[i],&RangingMeasurementData);
                /* Translate distance in bar graph (multiple device) */
                c = RangeToLetter(&VL53L0XDevs[i],&RangingMeasurementData);
                StrDisplay[i+1]=c;
            }
        }
        else{
            /* only one sensor */
        	/* Call All-In-One blocking API function */
            status = VL53L0X_PerformSingleRangingMeasurement(&VL53L0XDevs[SingleSensorNo],&RangingMeasurementData);
            if( status ==0 ){
            	/* Push data logging to UART */
            	trace_printf("%d,%u,%d,%d,%d\n", VL53L0XDevs[SingleSensorNo].Id, TimeStamp_Get(), RangingMeasurementData.RangeStatus, RangingMeasurementData.RangeMilliMeter, RangingMeasurementData.SignalRateRtnMegaCps);
            	Sensor_SetNewRange(&VL53L0XDevs[SingleSensorNo],&RangingMeasurementData);
                /* Display distance in cm */
            	if( RangingMeasurementData.RangeStatus == 0 ){  /////boucle de mesures correctes
                    *ptr_compteur_blink+=1;                      /////incrementation du compteur
                    sprintf(StrDisplay, "%3dc",(int)VL53L0XDevs[SingleSensorNo].LeakyRange/10);  /////affichage sur le capteur
                    distance = (int)VL53L0XDevs[SingleSensorNo].LeakyRange/10;   /////distance lue par le capteur en cm
                    //XL_Get_Current_Position(servo, &angle); necessaire ?
                    blink_led(distance, ptr_compteur_blink);         /////fonction blink_led
										Variation3Angle_maison(servo, ptr_angle, buffer1, ptr_compteur);
                    //transmit(compteur2, buffer, buffer1, distance, angle);        /////fonction transmit vers pc modifie donc buggee
                    *ptr_compteur+=1;                              /////incrementation du compteur


//////bloc structure (je me comprends)
/*
                    //unsigned int angle;
                    //char dataAngle[10];
                    //XL_Set_Goal_Position(servo, 60, 1);
                    //sprintf(dataAngle, "%d,",angle);
                    //len=strlen(dataAngle);
                    //HAL_UART_Transmit(&huart2, (uint8_t*)(dataAngle), len, 1000);*/
                }
                else{                                           /////boucle de mesures incorrectes
                    sprintf(StrDisplay, "----");
                    StrDisplay[0]=VL53L0XDevs[SingleSensorNo].DevLetter;
                    //HAL_TIM_Base_Stop_IT(&htim3);             /////version courante : memoire de la frequence de la led
                    //htim3.Instance->ARR=2000;
                    //HAL_TIM_Base_Start_IT(&htim3);
                }
            }
            else{
                HandleError(ERR_DEMO_RANGE_ONE);
            }
        }
        XNUCLEO53L0A1_SetDisplayString(StrDisplay);
        /* Check blue button */
        if( !BSP_GetPushButton() ){
            over=1;
            break;
        }
    }while( !over);
    /* Wait button to be un-pressed to decide if it is a short or long press */
    status=PusbButton_WaitUnPress();
    htim3.Instance->CNT=0;       /////remise a zero du timer de la led
    return status;
}

#if HAVE_ALARM_DEMO
struct AlrmMode_t {
    const int VL53L0X_Mode;
    const char *Name;
    uint32_t ThreshLow;
    uint32_t ThreshHigh;
};

struct AlrmMode_t AlarmModes[]={
        { .VL53L0X_Mode = VL53L0X_GPIOFUNCTIONALITY_THRESHOLD_CROSSED_LOW , .Name="Lo" , .ThreshLow=300<<16 ,  .ThreshHigh=0<<16  },
        { .VL53L0X_Mode = VL53L0X_GPIOFUNCTIONALITY_THRESHOLD_CROSSED_HIGH, .Name= "hi", .ThreshLow=0<<16   ,  .ThreshHigh=300<<16},
        { .VL53L0X_Mode = VL53L0X_GPIOFUNCTIONALITY_THRESHOLD_CROSSED_OUT , .Name="out", .ThreshLow=300<<16 ,  .ThreshHigh=400<<16},
};

VL53L0X_Error WaitStopCompleted(VL53L0X_DEV Dev) {
    VL53L0X_Error Status = VL53L0X_ERROR_NONE;
    uint32_t StopCompleted=0;
    uint32_t LoopNb;

    // Wait until it finished
    // use timeout to avoid deadlock
    if (Status == VL53L0X_ERROR_NONE) {
        LoopNb = 0;
        do {
            Status = VL53L0X_GetStopCompletedStatus(Dev, &StopCompleted);
            if ((StopCompleted == 0x00) || Status != VL53L0X_ERROR_NONE) {
                break;
            }
            LoopNb = LoopNb + 1;
            VL53L0X_PollingDelay(Dev);
        } while (LoopNb < VL53L0X_DEFAULT_MAX_LOOP);

        if (LoopNb >= VL53L0X_DEFAULT_MAX_LOOP) {
            Status = VL53L0X_ERROR_TIME_OUT;
        }

    }

    return Status;
}


void AlarmDemo(void){
    VL53L0X_Dev_t *pDev;
    uint8_t VhvSettings;
    uint8_t PhaseCal;
    uint32_t refSpadCount;
	uint8_t isApertureSpads;
	VL53L0X_RangingMeasurementData_t RangingMeasurementData;
    int status;
    int Over=0;
    int Mode=0;
    char StrDisplay[5]="----";

    /* Only center device is used */
    pDev=&VL53L0XDevs[1];


    /* configure BSP/MCU center sensor interrupt */
    VL53L0A1_EXTI_IOConfigure(XNUCLEO53L0A1_DEV_CENTER, 0, 0);
    XNUCLEO53L0A1_SetIntrStateId(1, XNUCLEO53L0A1_DEV_CENTER);

    /* Initialize the device in continuous ranging mode */
	VL53L0X_StaticInit(pDev);
	VL53L0X_PerformRefCalibration(pDev, &VhvSettings, &PhaseCal);
	VL53L0X_PerformRefSpadManagement(pDev, &refSpadCount, &isApertureSpads);
	VL53L0X_SetInterMeasurementPeriodMilliSeconds(pDev, 250);
	VL53L0X_SetDeviceMode(pDev, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING);

    do{
       /* set sensor interrupt mode */
       VL53L0X_StopMeasurement(pDev);           // it is safer to do this while sensor is stopped
       VL53L0X_SetInterruptThresholds(pDev, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING ,  AlarmModes[Mode].ThreshLow ,  AlarmModes[Mode].ThreshHigh);
       status = VL53L0X_SetGpioConfig(pDev, 0, VL53L0X_DEVICEMODE_CONTINUOUS_RANGING, AlarmModes[Mode].VL53L0X_Mode, VL53L0X_INTERRUPTPOLARITY_HIGH);
       status = VL53L0X_ClearInterruptMask(pDev, -1); // clear interrupt pending if any

       /* Start continuous ranging */
       VL53L0X_StartMeasurement(pDev);
       IntrCounts[1]=0;

       /* Check for interrupt */
       do{
           __WFI();
           /* Interrupt received */
           if( IntrCounts[1] !=0 ){
        	   /* Reset interrupt counter */
               IntrCounts[1]=0;
               /* Get ranging data and display distance*/
               VL53L0X_GetRangingMeasurementData(pDev, &RangingMeasurementData);
               sprintf(StrDisplay, "%3dc",(int)RangingMeasurementData.RangeMilliMeter/10);
               /* Clear interrupt */
               status = VL53L0X_ClearInterruptMask(pDev, -1);
               /* keep display for at least 100ms otherwise user may never see it on display*/
               XNUCLEO53L0A1_SetDisplayString(StrDisplay);
               HAL_Delay(100);
           }
           else{
        	   /* No interrupt received => Display alarm mode */
               XNUCLEO53L0A1_SetDisplayString(AlarmModes[Mode].Name);
           }
           /* Check blue button */
           if( !BSP_GetPushButton() ){
               break;
           }
       }while(1);
       /* Wait button to be released to decide if it is a short or long press */
       status=PusbButton_WaitUnPress();
       /* Long press => stop this demo */
       if( status )
           Over =1;
       /* Short press => change alarm mode */
       Mode=(Mode+1)%ARRAY_SIZE(AlarmModes);
    }while( !Over );

    /* Stop continuous ranging */
    VL53L0X_StopMeasurement(pDev);

    /* Ensure device is ready for other commands */
    WaitStopCompleted(pDev);

    /* Disable configuration of BSP/MCU center sensor interrupt */
    XNUCLEO53L0A1_SetIntrStateId(0, XNUCLEO53L0A1_DEV_CENTER);
    VL53L0A1_EXTI_IOUnconfigure(XNUCLEO53L0A1_DEV_CENTER);
}
#endif

void ResetAndDetectSensor(int SetDisplay){
    int nSensor;
    nSensor = DetectSensors(SetDisplay);
    /* at least one sensor and if one it must be the built-in one  */
    if( (nSensor <=0) ||  (nSensor ==1 && VL53L0XDevs[1].Present==0) ){
        HandleError(ERR_DETECT);
    }
}

//////XL maintenance
XL_Interface interface;

uint8_t XL_320_Send_HAL(uint8_t *data, uint16_t size, uint32_t timeout){
  HAL_StatusTypeDef status = HAL_UART_Transmit(&huart1, data, size, timeout);
  return (status==HAL_OK)?0:1;
}

void XL_320_Set_Direction_HAL(XL_Direction dir){
  HAL_GPIO_WritePin(USART1_DIR_GPIO_Port, USART1_DIR_Pin, (dir==XL_SEND)?GPIO_PIN_SET:GPIO_PIN_RESET);
}

uint8_t XL_320_Receive_HAL(uint8_t *buffer, uint16_t size, uint32_t timeout){
  HAL_StatusTypeDef status = HAL_UART_Receive(&huart1, buffer, size, timeout);
  return (status==HAL_OK)?0:1;
}

void XL_320_Delay_HAL(uint32_t t){
  HAL_Delay(t);
}
/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */
  int ExitWithLongPress;
  RangingConfig_e RangingConfig = LONG_RANGE;
  DemoMode_e DemoMode = RANGE_VALUE;
  int UseSensorsMask = 1<<XNUCLEO53L0A1_DEV_CENTER;
  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  SystemClock_Config();
  MX_I2C1_Init();
  MX_TIM3_Init();
  MX_USART2_UART_Init();
  MX_USART1_UART_Init();

  /* USER CODE BEGIN 2 */
  XNUCLEO53L0A1_Init();
  uart_printf(WelcomeMsg);
  XNUCLEO53L0A1_SetDisplayString("53L0");
  HAL_Delay(WelcomeTime);
  ResetAndDetectSensor(1);
  HAL_TIM_Base_Start_IT(&htim3); //£

  /* Set VL53L0X API trace level */
  VL53L0X_trace_config(NULL, TRACE_MODULE_NONE, TRACE_LEVEL_NONE, TRACE_FUNCTION_NONE); // No Trace
  //VL53L0X_trace_config(NULL,TRACE_MODULE_ALL, TRACE_LEVEL_ALL, TRACE_FUNCTION_ALL); // Full trace

  //////XL maintenance ----------------------
  interface.send = XL_320_Send_HAL;
  interface.set_direction = XL_320_Set_Direction_HAL;
  interface.receive = XL_320_Receive_HAL;
  interface.delay = XL_320_Delay_HAL;

  HAL_Delay(1000);

  XL broadcast = (XL) {.interface = &interface, .id = XL_BROADCAST};

  XL servo;
  uint16_t nb_servos = 0;
  /*int compteurAngle=100;      //compteur de variation d'angle*/

  XL_Discover(&interface, &servo, 1, &nb_servos);
  #if CONFIG==1
  XL_Configure_ID(&servo[0],3);
  #endif
  XL_Say_Hello(&servo);
  HAL_Delay(1000);
  XL_Power_On(&broadcast, XL_NOW);
  /* USER CODE END 2 */

  /* USER CODE BEGIN 3 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */
      /* Display demo mode */
      XNUCLEO53L0A1_SetDisplayString(DemoModeTxt[DemoMode]);
      HAL_Delay(ModeChangeDispTime);

      /* Display Ranging config */
	  XNUCLEO53L0A1_SetDisplayString(RangingConfigTxt[RangingConfig]);
	  HAL_Delay(ModeChangeDispTime);

	  /* Reset and Detect all sensors */
      ResetAndDetectSensor(0);

      /* Reset Timestamping */
      TimeStamp_Reset();

#if HAVE_ALARM_DEMO
      XNUCLEO53L0A1_SetDisplayString(TxtAlarm);
      HAL_Delay(ModeChangeDispTime);
      ResetAndDetectSensor(0);
      AlarmDemo();
#else

//////phase de tests simples

      /*XL_Set_Goal_Position(&servo, 60, 1); ///test position fonctionne
      uint16_t position;
      XL_Get_Current_Position(&servo, &position);
			position;*/

			/*void VariationAngle_maison(XL servo, int Angle){ ///test fonctionne
					uint16_t position;
					XL_Set_Goal_Position(&servo, Angle, 1);
					XL_Get_Current_Position(&servo, &position);
			}

			VariationAngle_maison(servo, compteurAngle);*/

      /* Start Ranging demo */
      ExitWithLongPress = RangeDemo(UseSensorsMask, RangingConfig, servo);

      /* Blue button has been pressed (long or short press) */
      if(ExitWithLongPress){
    	  /* Long press : change demo mode if multiple sensors present*/
    	  if( nDevPresent >1 ){
    		  /* If more than one sensor is present then toggle demo mode */
    		  DemoMode = (DemoMode == RANGE_VALUE) ? BAR_GRAPH : RANGE_VALUE;
    		  UseSensorsMask = (DemoMode == BAR_GRAPH) ? 0x7 : 1<<XNUCLEO53L0A1_DEV_CENTER;
    	  }
      } else {
    	  /* Short press : change ranging config */
    	  RangingConfig = (RangingConfig == LONG_RANGE) ? HIGH_SPEED : ((RangingConfig == HIGH_SPEED) ? HIGH_ACCURACY : LONG_RANGE);
      }
#endif
  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

  __PWR_CLK_ENABLE();

  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  HAL_RCC_OscConfig(&RCC_OscInitStruct);

  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
  HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);

}

/* I2C1 init function */
void MX_I2C1_Init(void)
{

  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLED;
  HAL_I2C_Init(&hi2c1);

}

/* TIM3 init function */
void MX_TIM3_Init(void)
{

  TIM_ClockConfigTypeDef sClockSourceConfig;
  TIM_MasterConfigTypeDef sMasterConfig;

  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 42000-1;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 1000-1;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  HAL_TIM_Base_Init(&htim3);

  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  HAL_TIM_ConfigClockSource(&htim3, &sClockSourceConfig);

  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig);

}

/* USART1 init function */
void MX_USART1_UART_Init(void)
{

  huart1.Instance = USART1;
  huart1.Init.BaudRate = 1000000;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart1);

}

/* USART2 init function */
void MX_USART2_UART_Init(void)
{

  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  HAL_UART_Init(&huart2);

}

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
        * Free pins are configured automatically as Analog (this feature is enabled through
        * the Code Generation settings)
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __GPIOC_CLK_ENABLE();
  __GPIOH_CLK_ENABLE();
  __GPIOA_CLK_ENABLE();
  __GPIOB_CLK_ENABLE();
  __GPIOD_CLK_ENABLE();

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PC0 PC1 PC2 PC3
                           PC4 PC5 PC6 PC7
                           PC8 PC10 PC11 PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(USART1_DIR_GPIO_Port, USART1_DIR_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA1 PA4 PA6
                           PA7 PA8 PA11 PA12
                           PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB12 PB13 PB14 PB15
                           PB4 PB5 PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : PC9 */
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PD2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim){ //£
  if(htim->Instance == htim3.Instance){
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);              /////changement d'etat de la led
  }
}

/* USER CODE END 4 */

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */

/**
  * @}
*/

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
