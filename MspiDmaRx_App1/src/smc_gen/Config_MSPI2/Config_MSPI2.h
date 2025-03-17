/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws.
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2018, 2024 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name        : Config_MSPI2.h
* Component Version: 1.3.1
* Device(s)        : R7F702301BEBBA
* Description      : This file implements device driver for Config_MSPI2.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_mspi.h"

#ifndef CFG_Config_MSPI2_H
#define CFG_Config_MSPI2_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _MSPI2_FRAME_LENGTH                                      (0x0010U) /* MSPI frame length */
#define _MSPI2_HARDWARE_TRIGGER_DISABLE                          (0x00000000UL) /* MSPI hardware trigger disable */
#define _MSPI2_SETUP_TIME                                        (0x0001U) /* MSPI setup time */
#define _MSPI2_HOLD_TIME                                         (0x0001U) /* MSPI hold time */
#define _MSPI2_IDLE_TIME                                         (0x0001U) /* MSPI idle time */
#define _MSPI2_INTER_DATA_TIME                                   (0x0000U) /* MSPI inter time */
#define _MSPI2_FRAME_COUNT                                       (0x0008U) /* MSPI frame count */
#define _MSPI2_RAMSTART_ADDRESS                                  (0x0000U) /* MSPI RAM start address */
#define _MSPI2_CLOCK_FREQUENCY_DIVISION                          (0x0001U) /* MSPI2 clock frequency division */

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_Config_MSPI2_Create(void);
void R_Config_MSPI2_Start(void);
void R_Config_MSPI2_Stop(void);
MD_STATUS R_Config_MSPI2_Receive(uint16_t* const rx_buf);
void R_Config_MSPI2_Software_Trigger(void);
void R_Config_MSPI2_Create_UserInit(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
