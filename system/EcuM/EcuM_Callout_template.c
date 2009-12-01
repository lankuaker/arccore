/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core ------------------------------*/








// This file is just examples of implementation for the stubs needed by
// the EcuM. Every Autocore application should use an own version of this
// file to implement the setup and tear down of the system.

#include "EcuM.h"
#include "Det.h"
#if defined(USE_MCU)
#include "Mcu.h"
#endif
#if defined(USE_GPT)
#include "Gpt.h"
#endif
#if defined(USE_CAN)
#include "Can.h"
#endif
#if defined(USE_CANIF)
#include "CanIf.h"
#endif
#if defined(USE_PDUR)
#include "PduR.h"
#endif
#if defined(USE_COM)
#include "Com.h"
#endif
#if defined(USE_PWM)
#include "Pwm.h"
#endif

void EcuM_AL_DriverInitZero()
{
	Det_Init();
    Det_Start();
}

EcuM_ConfigType* EcuM_DeterminePbConfiguration()
{
	return &EcuMConfig;
}

void EcuM_AL_DriverInitOne(const EcuM_ConfigType *ConfigPtr)
{
#if defined(USE_MCU)
	Mcu_Init(ConfigPtr->McuConfig);

	// Set up default clock (Mcu_InitClock requires initRun==1)
	Mcu_InitClock( ConfigPtr->McuConfig->McuDefaultClockSettings );

	// Wait for PLL to sync.
	while (Mcu_GetPllStatus() != MCU_PLL_LOCKED)
	  ;
#endif

#if defined(USE_PORT)
	// Setup Port
	Port_Init(ConfigPtr->PortConfig);
#endif


#if defined(USE_GPT)
	// Setup the GPT
	Gpt_Init(ConfigPtr->GptConfig);
#endif

	// Setup watchdog
	// TODO

#if defined(USE_DMA)
	// Setup DMA
	Dma_Init(ConfigPtr->DmaConfig);
#endif

#if defined(USE_ADC)
	// Setup ADC
	Adc_Init(ConfigPtr->AdcConfig);
#endif

	// Setup ICU
	// TODO

	// Setup PWM
#if defined(USE_PWM)
	// Setup PWM
	Pwm_Init(ConfigPtr->PwmConfig);
#endif
}

void EcuM_AL_DriverInitTwo(const EcuM_ConfigType* ConfigPtr)
{
#if defined(USE_SPI)
	// Setup SPI
	Spi_Init(ConfigPtr->SpiConfig);
#endif

#if defined(USE_EEP)
	// Setup EEP
	Eep_Init(ConfigPtr->EEpConfig);
#endif

#if defined(USE_FLS)
	// Setup Flash
	FlashInit(ConfigPtr->FlashConfig);
#endif

	// Setup NVRAM Manaager
	// TODO

	// Setup CAN tranceiver
	// TODO

#if defined(USE_CAN)
	// Setup Can driver
	Can_Init(ConfigPtr->CanConfig);
#endif

#if defined(USE_CANIF)
	// Setup CanIf
	CanIf_Init(ConfigPtr->CanIfConfig);
#endif

	// Setup LIN
	// TODO

#if defined(USE_PDUR)
	// Setup PDU Router
	PduR_Init(ConfigPtr->PduRConfig);
#endif

#if defined(USE_COM)
	// Setup COM layer
	Com_Init(ConfigPtr->ComConfig);
#endif

}

void EcuM_AL_DriverInitThree(const EcuM_ConfigType ConfigPtr)
{
#if defined(USE_CANIF)
	// Startup the CAN interface; due to the missing COM manager
	CanIf_InitController(CANIF_CHANNEL_0, CANIF_CHANNEL_0_CONFIG_0);
	CanIf_SetControllerMode(CANIF_CHANNEL_0, CANIF_CS_STARTED);
#endif
}