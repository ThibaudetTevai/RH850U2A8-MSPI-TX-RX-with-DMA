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
* File Name        : Config_SDMAC01.h
* Component Version: 1.5.0
* Device(s)        : R7F702301BEBBA
* Description      : This file implements device driver for Config_SDMAC01.
***********************************************************************************************************************/

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_dma.h"

#ifndef CFG_Config_SDMAC01_H
#define CFG_Config_SDMAC01_H

/***********************************************************************************************************************
Macro definitions (Register bit)
***********************************************************************************************************************/

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define _DMAC01_SPID_Value                    (0x00001C00UL)
#define _DMAC01_SOURCE_ADDRESS                (0xFFD800D0UL)
#define _DMAC01_DESTINATION_ADDRESS           (0xFE400D00UL)
#define _DMAC01_TRANSFER_SIZE                 (0x00000010UL)
#define _DMAC01_UPPER_LIMIT_BUFFER            (0x00000080UL)
#define _DMAC01_TRANSFER_COUNT                (0x00010000UL)

/***********************************************************************************************************************
Typedef definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Global functions
***********************************************************************************************************************/
void R_Config_SDMAC01_Create(void);
void R_Config_SDMAC01_Start(void);
void R_Config_SDMAC01_Stop(void);
void R_Config_SDMAC01_Suspend(void);
void R_Config_SDMAC01_Resume(void);
void R_Config_SDMAC01_Callback_PE0_Address_Error(void);
void R_Config_SDMAC01_Create_UserInit(void);
/* Start user code for function. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
#endif
