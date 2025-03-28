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
* File Name        : r_cg_dma_common.c
* Version          : 1.0.131
* Device(s)        : R7F702301BEBBA
* Description      : None
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
/* Start user code for include. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
* Function Name: R_DMAC_Start_Error_Interrupt_PE0
* Description  : This function starts INTSDMACERR interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC_Start_Error_Interrupt_PE0(void)
{
    /* Clear address error interrupt (INTSDMACERR) request and enable operation */
    INTC1_PE0.EIC29.BIT.EIRF29 = _INT_REQUEST_NOT_OCCUR;
    INTC1_PE0.EIC29.BIT.EIMK29 = _INT_PROCESSING_ENABLED;
}

/***********************************************************************************************************************
* Function Name: R_DMAC_Stop_Error_Interrupt_PE0
* Description  : This function stops INTSDMACERR interrupt.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_DMAC_Stop_Error_Interrupt_PE0(void)
{
    /* Disable address error interrupt (INTSDMACERR) operation and clear request */
    INTC1_PE0.EIC29.BIT.EIMK29 = _INT_PROCESSING_DISABLED;
    INTC1_PE0.EIC29.BIT.EIRF29 = _INT_REQUEST_NOT_OCCUR;
}

/* Start user code for adding. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */
