
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
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
#include "main.h"
#include "stm32f3xx_hal.h"
#include "dma.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "wwdg.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "motor.h"
#include "odometry.h"
#include "Robotronik_corp_pid.h"


#include "fsm_master.h"

#include "interpol.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

Odometry odometry;
volatile int sum_goal,diff_goal;
PID_DATA pid_sum;
PID_DATA pid_diff;

extern FSM_Instance *volatile fsm;
extern FSM_Position_Pts fsm_pos_pts;
extern FSM_Position_Pts fsm_pos_abs;
extern volatile int ENCODER_DIST;//distance between encoders
extern volatile int ENCODER_STEP_DIST;//distance for 1 encoder step/2
extern volatile int deltaL;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef* p_hwwdg){
  if(p_hwwdg == &hwwdg){

  }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_I2C1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  MX_TIM3_Init();
  MX_TIM15_Init();
  //MX_WWDG_Init();//TODO re-enable
  /* USER CODE BEGIN 2 */

  //================================================== besoin ?
  //                    UART
  //==================================================
  RP_Init_Interface(&P_interface, USART2, RP_UART_Transmit, HAL_GetTick);
  RP_INIT_UART_DMA(DMA1, LL_DMA_CHANNEL_6, USART2, P_interface);


  /**************************************************/ //a check
  /*            PID INIT                            */
  /**************************************************/
  int Te = 10;//in ms
  int prec_steps_l=0,prec_steps_r=0;
  float kc=0,speed_percent=0,vr=0,vl=0,wc=0,val_r,val_l;//for interpolation
  //PID Sum
  pid_sum = (PID_DATA) {.Te = 0.01,
				 .Kp = 0.01,
				 .Ki = 0.01,
				 .Kd = 0.0001};
  pid_init(&pid_sum);

  //PID Diff
  pid_diff = (PID_DATA) {.Te = 0.01,
				  .Kp = 0.01,
				  .Ki = 0.01,
				  .Kd = 0.0001};
  pid_init(&pid_diff);

  fsm_pos_pts.pid_speed_l=(PID_SPEED_DATA) {.Te = 0.01,
				 .Kp = 0.01,
				 .Ki = 0.01,
				 .Kd = 0.0001};
  fsm_pos_pts.pid_speed_r=(PID_SPEED_DATA) {.Te = 0.01,
				 .Kp = 0.01,
				 .Ki = 0.01,
				 .Kd = 0.0001};
  /**************************************************/
  /*            Odometry Start                      */
  /**************************************************/
  //Init odometry struct and start sampling
  init_odometry(&odometry, &htim2, &htim1, &htim15);

  /**************************************************/
  /*            Motors Init                         */
  /**************************************************/
  //Init variable used to reconfigure PWM
  TIM_OC_InitTypeDef sConfigOC;
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

  //PWM Start
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);//EN_2
  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);//EN_1

  //Direction init : forward
  HAL_GPIO_WritePin(DIR_R_GPIO_Port, DIR_R_Pin, 1);
  HAL_GPIO_WritePin(DIR_L_GPIO_Port, DIR_L_Pin, 0);

  //Enable : stop
  DRIVE_MOTOR_R(0);//encoder2 forward positive positive voltage
  DRIVE_MOTOR_L(0);//encoder1 forward positive positive voltage

  //Release the brakes
  HAL_GPIO_WritePin (NBRAKE_R_GPIO_Port, NBRAKE_R_Pin, GPIO_PIN_SET);
  HAL_GPIO_WritePin (NBRAKE_L_GPIO_Port, NBRAKE_L_Pin, GPIO_PIN_SET);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

// a changer pour la distance à parcourir
  sum_goal=10;
  diff_goal=10;

#if TEST_ENCODER != 0
  while (1) {
    int i;
    for(i = 0; i < 25500; i++){
      if(i == 0){
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
      }
      if(i%100 && i/100 == led_level){
	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
      }
    }
  }
#endif

  fsm= (FSM_Instance*)&fsm_pos_abs;
  fsm->run=FSM_Abs_End;
  float cor_sum, cor_diff;
  while (1)
  {
    //Watchdog refresh
    //HAL_WWDG_Refresh(&hwwdg);//TODO re-enable
    //FSM
    fsm->run(fsm);

    //Process PID
      cor_sum = pid(&pid_sum, sum_goal - 0.5 * (odometry.encoder_l.steps + odometry.encoder_r.steps));
      cor_diff = pid(&pid_diff, diff_goal - (odometry.encoder_r.steps - odometry.encoder_l.steps));

      val_r = cor_sum + cor_diff;
      val_l = cor_sum - cor_diff;

    //Motor control
    DRIVE_MOTOR_L(val_l);
    DRIVE_MOTOR_R(val_r);

    HAL_Delay(Te);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL16;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1|RCC_PERIPHCLK_TIM1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  PeriphClkInit.Tim1ClockSelection = RCC_TIM1CLK_HCLK;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
