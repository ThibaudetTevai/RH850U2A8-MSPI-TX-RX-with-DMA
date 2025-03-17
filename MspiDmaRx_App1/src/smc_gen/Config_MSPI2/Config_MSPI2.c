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
* File Name        : Config_MSPI2.c
* Component Version: 1.3.1
* Device(s)        : R7F702301BEBBA
* Description      : This file implements device driver for Config_MSPI2.
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
#include "Config_MSPI2.h"
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
extern volatile uint32_t g_cg_sync_read;
volatile uint32_t  g_mspi2_rx_num;                         /* mspi2 receive data number */
volatile uint32_t  g_mspi2_rx_total_num;                   /* mspi2 receive data total times */
volatile uint16_t * gp_mspi2_rx_address;                   /* mspi2 receive buffer address */
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_Config_MSPI2_Create
* Description  : This function initializes the Config_MSPI2 module.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_MSPI2_Create(void)
{
    /* Set MSPI2 control setting */
    MSPI2.CTL1.UINT32 = _MSPI_CLOCK_DEFAULT_LOW | _MSPI_CS_SIGNAL_RECOGNIZED | _MSPI_SLAVE_MODE | 
                        _MSPI_SAMPLE_STANDARD | _MSPI_MSPISOUT_ENABLE_LOW_END_HOLD | _MSPI_CS0_SIGNAL_ACTIVE_LOW | 
                        _MSPI_CS1_SIGNAL_ACTIVE_LOW | _MSPI_CS2_SIGNAL_ACTIVE_LOW | _MSPI_CS3_SIGNAL_ACTIVE_LOW | 
                        _MSPI_CS4_SIGNAL_ACTIVE_LOW | _MSPI_CS5_SIGNAL_ACTIVE_LOW | _MSPI_CS6_SIGNAL_ACTIVE_LOW | 
                        _MSPI_CS7_SIGNAL_ACTIVE_LOW;
    MSPI2.CTL2.UINT8 = _MSPI_CONSISTENCY_DISABLE | _MSPI_LOOPBACK_DISABLE;
    /* Enable MSPI2 operation */
    MSPI2.CTL0.UINT8 = _MSPI_FUNCTION_ENABLE;
    /* Set MSPI2 configuration setting */
    MSPI2.CFG00.UINT32 = _MSPI_TRANSMISSION_DISABLE | _MSPI_RECEPTION_ENABLE | _MSPI_DIRECT_MODE | 
                         _MSPI_CHANNEL_OPERATION_END | _MSPI_INTMSPITX_INTERRUPT_DISABLE | 
                         _MSPI_INTMSPIRX_INTERRUPT_ENABLE | _MSPI_INTMSPIFE_INTERRUPT_ENABLE | 
                         _MSPI_INTMSPIERR_INTERRUPT_ENABLE | _MSPI_CHANNEL_LOCK_OPERATION_DISABLE | 
                         _MSPI_CHANNEL_PRIORITY_LEVEL8;
    MSPI2.CFG01.UINT32 = _MSPI_SCK_PHASE_SHIFT_ODD_EDGES | _MSPI_COMMUNICATION_MSB | _MSPI_NO_CHECK | 
                         _MSPI_SPCK_IDLE_LOW | _MSPI_CS_IDLE_LEVEL_INACTIVE | _MSPI_SAFE_SPI_DISABLE | 
                         _MSPI_IDLE_TIME_NOT_INSERTED | _MSPI_HOLD_ACTIVE_LEVEL;
    MSPI2.CFG02.UINT16 = _MSPI2_FRAME_LENGTH;
    MSPI2.CFG03.UINT16 = _MSPI_CLOCK_FREQUENCY_DIVISION_1 | _MSPI2_CLOCK_FREQUENCY_DIVISION;
    MSPI2.CFG04.UINT32 = _MSPI_FIFO_SIZE_8 | _MSPI2_HARDWARE_TRIGGER_DISABLE;
    MSPI2.RASTAD0.UINT16 = _MSPI2_RAMSTART_ADDRESS;
    MSPI2.SEUP0.UINT16 = _MSPI2_SETUP_TIME;
    MSPI2.HOLD0.UINT16 = _MSPI2_HOLD_TIME;
    MSPI2.IDLE0.UINT16 = _MSPI2_IDLE_TIME;
    MSPI2.INDA0.UINT16 = _MSPI2_INTER_DATA_TIME;
    MSPI2.CFSET0.UINT16 = _MSPI2_FRAME_COUNT;
    MSPI2.SSEL0.UINT16 = _MSPI_DEACTIVATE_CS0 | _MSPI_DEACTIVATE_CS1 | _MSPI_DEACTIVATE_CS2 | _MSPI_DEACTIVATE_CS3 | 
                         _MSPI_DEACTIVATE_CS4 | _MSPI_DEACTIVATE_CS5 | _MSPI_DEACTIVATE_CS6 | _MSPI_DEACTIVATE_CS7;
    MSPITG.CTL2.UINT32 &= _MSPI_CHANNEL0_TRIGGER_SET_CLEAR;
    MSPITG.CTL2.UINT32 |= _MSPI_TRIGGER1_RX0_TRIGGER2_NONE;
    MSPITG.CTL2.UINT32 |= _MSPI_CHANNEL0_DMA_TRIGGER_ENABLE;
    MSPI2_INTF.MSPI2INTMSK1.UINT32 &= _MSPI_CHANNEL0_INTERRUPT_NOT_MASKED;
    MSPI2_INTF.MSPI2INTMSK3.UINT32 &= _MSPI_CHANNEL0_INTERRUPT_NOT_MASKED;
    MSPI2_INTF.MSPI2INTMSK2.UINT32 &= _MSPI_CHANNEL0_INTERRUPT_NOT_MASKED;
    /* Synchronization processing */
    g_cg_sync_read = MSPI2.CTL1.UINT32;
    __syncp();

    /* Set MSPI2SC pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(10U);
    PORT0.PCR10_11.UINT32 = (PORT0.PCR10_11.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR10_11.UINT32 |= _PCR_ALT_IN3;
    PORT0.PCR10_11.UINT32 |= _PCR_SET_PMC;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set MSPI2SI pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(10U);
    PORT0.PCR10_12.UINT32 = (PORT0.PCR10_12.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR10_12.UINT32 |= _PCR_ALT_IN3;
    PORT0.PCR10_12.UINT32 |= _PCR_SET_PMC;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    /* Set MSPI2SSI pin */
    PORT0.PKCPROT = _WRITE_PROTECT_ENABLE;
    PORT0.PWE = SETBIT(10U);
    PORT0.PCR10_9.UINT32 = (PORT0.PCR10_9.UINT32 & _PCR_DEFAULT_VALUE) | _PCR_SET_PM;
    PORT0.PCR10_9.UINT32 |= _PCR_ALT_IN3;
    PORT0.PCR10_9.UINT32 |= _PCR_SET_PMC;
    PORT0.PWE = _PORT_WRITE_PROTECT_DISABLE;
    PORT0.PKCPROT = _WRITE_PROTECT_DISABLE;

    R_Config_MSPI2_Create_UserInit();
}

/***********************************************************************************************************************
* Function Name: r_Config_MSPI2_enable_interrupt
* Description  : This function enables interrupt operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_MSPI2_enable_interrupt(void)
{
    /* Clear MSPI2 interrupt request and enable operation */
    INTC2.EIC265.BIT.EIRF265 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC267.BIT.EIRF267 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC266.BIT.EIRF266 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC265.BIT.EIMK265 = _INT_PROCESSING_ENABLED;
    INTC2.EIC267.BIT.EIMK267 = _INT_PROCESSING_ENABLED;
    INTC2.EIC266.BIT.EIMK266 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: r_Config_MSPI2_disable_interrupt
* Description  : This function disables interrupt operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void r_Config_MSPI2_disable_interrupt(void)
{
    /* Disable MSPI2 interrupt operation and clear request */
    INTC2.EIC265.BIT.EIMK265 = _INT_PROCESSING_DISABLED;
    INTC2.EIC267.BIT.EIMK267 = _INT_PROCESSING_DISABLED;
    INTC2.EIC266.BIT.EIMK266 = _INT_PROCESSING_DISABLED;
    INTC2.EIC265.BIT.EIRF265 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC267.BIT.EIRF267 = _INT_REQUEST_NOT_OCCUR;
    INTC2.EIC266.BIT.EIRF266 = _INT_REQUEST_NOT_OCCUR;
}

/***********************************************************************************************************************
* Function Name: R_Config_MSPI2_Start
* Description  : This function starts the Config_MSPI2 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_MSPI2_Start(void)
{
    /* Clear MSPI20 interrupt request and enable operation */
    r_Config_MSPI2_enable_interrupt();
    /* Enable MSPI2 channel0 operation */
    MSPI2.CSTS0.UINT8 = _MSPI_CHANNEL_SET_ENABLE_FLAG;
}

/***********************************************************************************************************************
* Function Name: R_Config_MSPI2_Stop
* Description  : This function This function stops the MSPI2 module operation.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_MSPI2_Stop(void)
{
    /* Disable MSPI2 channel0 operation */
    MSPI2.CSTC0.UINT8 = _MSPI_CHANNEL_CLEAR_ENABLE_FLAG;
    /* Disable MSPI20 interrupt operation and clear request */
    r_Config_MSPI2_disable_interrupt();
    /* Synchronization processing */
    g_cg_sync_read = MSPI2.CTL0.UINT8;
    __syncp();
}

/***********************************************************************************************************************
* Function Name: R_Config_MSPI2_Receive
* Description  : This function receives MSPI2 data.
* Arguments    : rx_buf -
*                    receive buffer pointer
* Return Value : MD_STATUS -
*                    the status of receiving
***********************************************************************************************************************/
MD_STATUS R_Config_MSPI2_Receive(uint16_t* const rx_buf)
{
    /* Set receive setting */
    gp_mspi2_rx_address = rx_buf;
    g_mspi2_rx_total_num = _MSPI2_FRAME_COUNT;
    g_mspi2_rx_num = 0U;

    return MD_OK;
}

/***********************************************************************************************************************
* Function Name: R_Config_MSPI2_Software_Trigger
* Description  : This function sets software trigger.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_Config_MSPI2_Software_Trigger()
{
    MSPI2.CSTS0.UINT8 = _MSPI_CHANNEL_SET_ACTIVE_FLAG | _MSPI_CHANNEL_SET_ENABLE_FLAG;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
