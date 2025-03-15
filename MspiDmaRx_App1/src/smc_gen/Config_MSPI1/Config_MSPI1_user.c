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
* File Name        : Config_MSPI1_user.c
* Component Version: 1.3.1
* Device(s)        : R7F702301BEBBA
* Description      : This file implements device driver for Config_MSPI1.
***********************************************************************************************************************/
/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_userdefine.h"
#include "Config_MSPI1.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t  g_mspi1_rx_num;                        /* mspi1 receive data number */
extern volatile uint32_t  g_mspi1_rx_total_num;                  /* mspi1 receive data total times */
extern volatile uint16_t * gp_mspi1_rx_address;                  /* mspi1 receive buffer address */
void r_Config_MSPI1_callback_receiveend(void);
void r_Config_MSPI1_callback_error(uint32_t err_type);
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_MSPI1_Create_UserInit
* Description  : This function adds user code after initializing MSPI module
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_MSPI1_Create_UserInit(void)
{
    /* Start user code for user init. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_MSPI1_interrupt_receive
* Description  : This function is MSPI1 receive interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_Config_MSPI1_interrupt_receive(enable=false, channel=261, fpu=true, callt=false)
void r_Config_MSPI1_interrupt_receive(void)
{
    uint8_t err_type = 0U;
    uint32_t temp_intmsk = 0U;
    uint32_t temp = 0U;

    temp_intmsk = MSPI1_INTF.MSPI1INTMSK1.UINT32;
    MSPI1_INTF.MSPI1INTMSK1.UINT32 = _MSPI_ALL_CHANNELS_INTERRUPT_MASKED;
    if ((MSPI1_INTF.MSPI1INTF1.UINT32 & _MSPI_CHANNEL0_INTERRUPT_OCCURRED) != 0U)
    {
        MSPI1_INTF.MSPI1INTFC1.UINT32 = _MSPI_CHANNEL0_INTERRUPT_FLAG_CLEAR;
        err_type = (MSPI1.FRERST0.UINT8 & (_MSPI_CRC_ERROR_DETECTED | _MSPI_PARITY_ERROR_DETECTED));
        MSPI1.FRERSTC0.UINT8 |= (_MSPI_CONSISTENCY_ERROR_CLEAR | _MSPI_CRC_ERROR_CLEAR | _MSPI_PARITY_ERROR_CLEAR);
        if (err_type == 0U)
        {
            temp = g_mspi1_rx_total_num;
            if (g_mspi1_rx_num < temp)
            {
                *gp_mspi1_rx_address = MSPI1.RXDA00.UINT32;
                gp_mspi1_rx_address++;
                g_mspi1_rx_num++;
            }
            if (g_mspi1_rx_num >= temp)
            {
                r_Config_MSPI1_callback_receiveend();
            }
        }
    }
    MSPI1_INTF.MSPI1INTMSK1.UINT32 = temp_intmsk;
}

/***********************************************************************************************************************
* Function Name: r_Config_MSPI1_channel10_interrupt_receive
* Description  : This function is MSPI10 receive interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_Config_MSPI1_channel10_interrupt_receive(enable=false, channel=255, fpu=true, callt=false)
void r_Config_MSPI1_channel10_interrupt_receive(void)
{
    /* Start user code for r_Config_MSPI1_channel10_interrupt_receive. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_MSPI1_interrupt_error
* Description  : This function is MSPI1 error interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_Config_MSPI1_interrupt_error(enable=false, channel=263, fpu=true, callt=false)
void r_Config_MSPI1_interrupt_error(void)
{
    uint8_t err_type = 0U;
    uint32_t temp_intmsk = 0U;

    temp_intmsk = MSPI1_INTF.MSPI1INTMSK3.UINT32;
    MSPI1_INTF.MSPI1INTMSK3.UINT32 = _MSPI_ALL_CHANNELS_INTERRUPT_MASKED;
    if ((MSPI1_INTF.MSPI1INTF3.UINT32 & _MSPI_CHANNEL0_INTERRUPT_OCCURRED) != 0U)
    {
        MSPI1_INTF.MSPI1INTFC3.UINT32 = _MSPI_CHANNEL0_INTERRUPT_FLAG_CLEAR;
        err_type = (MSPI1.CEST0.UINT8 & (_MSPI_CHANNEL_CONSISTENCY_ERROR_DETECTED | _MSPI_CHANNEL_CRC_ERROR_DETECTED | 
                   _MSPI_CHANNEL_PARITY_ERROR_DETECTED | _MSPI_CHANNEL_OVER_READ_ERROR_DETECTED | 
                   _MSPI_CHANNEL_OVER_WRITE_ERROR_DETECTED | _MSPI_CHANNEL_OVER_RUN_ERROR_DETECTED));
        MSPI1.CESTC0.UINT8 |= (_MSPI_CHANNEL_CONSISTENCY_ERROR_CLEAR | _MSPI_CHANNEL_CRC_ERROR_CLEAR | 
                              _MSPI_CHANNEL_PARITY_ERROR_CLEAR | _MSPI_CHANNEL_OVER_READ_ERROR_CLEAR | 
                              _MSPI_CHANNEL_OVER_WRITE_ERROR_CLEAR | _MSPI_CHANNEL_OVER_RUN_ERROR_CLEAR);
        if (err_type != 0U)
        {
            r_Config_MSPI1_callback_error(err_type);
        }
    }
    MSPI1_INTF.MSPI1INTMSK3.UINT32 = temp_intmsk;
}

/***********************************************************************************************************************
* Function Name: r_Config_MSPI1_interrupt_frameend
* Description  : This function is MSPI1 frame end interrupt service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
#pragma interrupt r_Config_MSPI1_interrupt_frameend(enable=false, channel=262, fpu=true, callt=false)
void r_Config_MSPI1_interrupt_frameend(void)
{
    uint32_t temp_intmsk = 0U;

    temp_intmsk = MSPI1_INTF.MSPI1INTMSK2.UINT32;
    MSPI1_INTF.MSPI1INTMSK2.UINT32 = _MSPI_ALL_CHANNELS_INTERRUPT_MASKED;
    if ((MSPI1_INTF.MSPI1INTF2.UINT32 & _MSPI_CHANNEL0_INTERRUPT_OCCURRED) != 0U)
    {
        MSPI1_INTF.MSPI1INTFC2.UINT32 = _MSPI_CHANNEL0_INTERRUPT_FLAG_CLEAR;
        r_Config_MSPI1_callback_receiveend();
        /* Start user code for r_Config_MSPI1_interrupt_frameend. Do not edit comment generated here */
        /* End user code. Do not edit comment generated here */
    }
    MSPI1_INTF.MSPI1INTMSK2.UINT32 = temp_intmsk;
}

/***********************************************************************************************************************
* Function Name: r_Config_MSPI1_callback_receiveend
* Description  : This function is MSPI1 receiveend callback service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_MSPI1_callback_receiveend(void)
{
    /* Start user code for r_Config_MSPI1_callback_receiveend. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: r_Config_MSPI1_callback_error
* Description  : This function is MSPI1 error callback service routine
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_MSPI1_callback_error(uint32_t err_type)
{
    /* Start user code for r_Config_MSPI1_callback_error. Do not edit comment generated here */
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
