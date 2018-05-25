#include "capteur.h"

void RangeDemo(int UseSensorsMask, RangingConfig_e rangingConfig, XL* servo){
    int over = 0;
    int status;
    char StrDisplay[5];
    char c;
    int i;
    int nSensorToUse;
    int SingleSensorNo = 0;
    int distance;     ///creation variable distance
    int compteur_blink = 0;                ///creation compteur
    int* ptr_compteur_blink = NULL;   ///creation pointeur sur compteur
    ptr_compteur_blink = &compteur_blink;
    int compteur = 0;                 ///creation compteur
    int* ptr_compteur = NULL;   ///creation pointeur sur compteur
    ptr_compteur = &compteur;
    char buffer_distance[MAXI_CHAR_TRANSMIT*15]; /////creation du buffer
    char buffer_angle[MAXI_CHAR_TRANSMIT*10];
    sprintf(buffer_distance, "");               /////mise a zero du buffer
    sprintf(buffer_angle, "");
	  int angle=0;              ////creation
	  int* ptr_angle = &angle;
    int sens = 1;
    char ligne[2];
    int len;
    int test = 0;
    int* ptr_test = &test;

    /* Test  */
    do {
      *ptr_compteur_blink+=1;                      /////incrementation du compteur
      *ptr_compteur+=1;
      //distance = (int)VL53L0XDevs[SingleSensorNo].LeakyRange/10;   /////distance lue par le capteur en cm
      //blink_led(distance, ptr_compteur_blink);         /////fonction blink_led
      angle_transmit(servo, ptr_angle, buffer_angle, ptr_compteur, &sens, ptr_test);
      //distance_transmit(distance, buffer_distance, ptr_compteur);
      HAL_Delay(100);
      if (*ptr_compteur == MAXI_CHAR_TRANSMIT) {
          strcat(buffer_distance,buffer_angle);
          len=strlen(buffer_distance);                       /////longueur du buffer
          HAL_UART_Transmit(&huart2, (uint8_t*)(buffer_distance), len, 1000); /////transmission du buffer
          sprintf(ligne, "\n");                                     /////ajout \n a ligne
          HAL_UART_Transmit(&huart2, (uint8_t*)ligne, 1, 1000);     /////transmission pour cloturer la ligne                                                  /////remise a zero du compteur
          sprintf(buffer_distance, "");
          sprintf(buffer_angle, "");
          *ptr_compteur=0;
          HAL_Delay(1000);         //////necessaire pour le graphique
      }
    }while( !over);

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
        return;
    }

    /* Start ranging until blue button is pressed */
    do{
        if( nSensorToUse >1 ){
        	/* Multiple devices */
            for( i=0; i<2; i++){
                if( ! VL53L0XDevs[i].Present  || (UseSensorsMask & (1<<i))==0 )
                    continue;
                /* Call All-In-One blocking API function */
                status = VL53L0X_PerformSingleRangingMeasurement(&VL53L0XDevs[i],&RangingMeasurementData);
                if( status ){
                    HandleError(ERR_DEMO_RANGE_MULTI);
                // } else {
                //   if( RangingMeasurementData.RangeStatus == 0 ){  /////boucle de mesures correctes
                //         *ptr_compteur_blink+=1;                      /////incrementation du compteur
                //         *ptr_compteur+=1;
                //         sprintf(StrDisplay, "%3dc",(int)VL53L0XDevs[i].LeakyRange/10);  /////affichage sur le capteur
                //         distance = (int)VL53L0XDevs[i].LeakyRange/10;   /////distance lue par le capteur en cm
                //         blink_led(distance, ptr_compteur_blink);         /////fonction blink_led
    					  //         angle_transmit(servo, ptr_angle, buffer_angle, ptr_compteur, &sens, ptr_test); // rajouter un angle au tof gauche
                //         distance_transmit(distance, buffer_distance, ptr_compteur);
                //         if (*ptr_compteur==MAXI_CHAR_TRANSMIT) {
                //             strcat(buffer_distance,buffer_angle);
                //             len=strlen(buffer_distance);                       /////longueur du buffer
                //             HAL_UART_Transmit(&huart2, (uint8_t*)(buffer_distance), len, 1000); /////transmission du buffer
                //             sprintf(ligne, "\n");                                     /////ajout \n a ligne
                //             HAL_UART_Transmit(&huart2, (uint8_t*)ligne, 1, 1000);     /////transmission pour cloturer la ligne                                                  /////remise a zero du compteur
                //             sprintf(buffer_distance, "");
                //             sprintf(buffer_angle, "");
                //             *ptr_compteur=0;
                //             HAL_Delay(1000);         //////necessaire pour le graphique
                //         }
                //     }
                }
            }
        }
        else{
            /* only one sensor */
        	/* Call All-In-One blocking API function */
            status = VL53L0X_PerformSingleRangingMeasurement(&VL53L0XDevs[SingleSensorNo],&RangingMeasurementData);
            if( status == 0 ){
            	Sensor_SetNewRange(&VL53L0XDevs[SingleSensorNo],&RangingMeasurementData);
                /* Display distance in cm */
            	if( RangingMeasurementData.RangeStatus == 0 ){  /////boucle de mesures correctes
                    *ptr_compteur_blink+=1;                      /////incrementation du compteur
                    *ptr_compteur+=1;
                    distance = (int)VL53L0XDevs[SingleSensorNo].LeakyRange/10;   /////distance lue par le capteur en cm
                    blink_led(distance, ptr_compteur_blink);         /////fonction blink_led
					          angle_transmit(servo, ptr_angle, buffer_angle, ptr_compteur, &sens, ptr_test);
                    distance_transmit(distance, buffer_distance, ptr_compteur);
                    if (*ptr_compteur == MAXI_CHAR_TRANSMIT) {
                        strcat(buffer_distance,buffer_angle);
                        len=strlen(buffer_distance);                       /////longueur du buffer
                        HAL_UART_Transmit(&huart2, (uint8_t*)(buffer_distance), len, 1000); /////transmission du buffer
                        sprintf(ligne, "\n");                                     /////ajout \n a ligne
                        HAL_UART_Transmit(&huart2, (uint8_t*)ligne, 1, 1000);     /////transmission pour cloturer la ligne                                                  /////remise a zero du compteur
                        sprintf(buffer_distance, "");
                        sprintf(buffer_angle, "");
                        *ptr_compteur=0;
                        HAL_Delay(1000);         //////necessaire pour le graphique
                    }
                }
                else{                                           /////boucle de mesures incorrectes
                    sprintf(StrDisplay, "----");
                    StrDisplay[0]=VL53L0XDevs[SingleSensorNo].DevLetter;
                    /* Action a faire si perte de distance */

                    /* Fin d'action a faire si perte de distance */
                }
            }
            else{
                HandleError(ERR_DEMO_RANGE_ONE);
            }
        }
        XNUCLEO53L0A1_SetDisplayString(StrDisplay);
    }while( !over);
    /* Wait button to be un-pressed*/
    htim3.Instance->CNT=0;       /////remise a zero du timer de la led
}

void HandleError(int err){
    char msg[16];
    sprintf(msg,"Er%d", err);
    XNUCLEO53L0A1_SetDisplayString(msg);
    while(1){};
}

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

void SetupSingleShot(RangingConfig_e rangingConfig){
    int i;
    int status;
    uint8_t VhvSettings;
    uint8_t PhaseCal;
    uint32_t refSpadCount;
	  uint8_t isApertureSpads;
	  FixPoint1616_t signalLimit = (FixPoint1616_t)(0.1*65536); //return signal rate limit in MCPS
	  FixPoint1616_t sigmaLimit = (FixPoint1616_t)(60*65536);
	  uint32_t timingBudget = 20000; //20ms
	  uint8_t preRangeVcselPeriod = 18; //laser pulse periods
	  uint8_t finalRangeVcselPeriod = 14;

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

void ResetAndDetectSensor(int SetDisplay){
    int nSensor;
    nSensor = DetectSensors(SetDisplay);
    /* at least one sensor and if one it must be the built-in one  */
    if( (nSensor <=0) ||  (nSensor ==1 && VL53L0XDevs[1].Present==0) ){
        HandleError(ERR_DETECT);
    }
}