/**************************************************************************************************
  Filename:       USER_CC2541.h
  Revised:        $Date: 2019年12月27日13.46.49 $
  Revision:       $Revision: 01 $

  Description:    自定义功能h文件
**************************************************************************************************/

#ifndef USER_CC2541_H
#define USER_CC2541_H

#include "ioCC2541.h"
#include "hal_types.h"
#include "User_Lyx.h"
#include "osal_snv.h"

#ifdef __cplusplus
extern "C"
{
#endif

/********************************************************************/


  
extern uint32  User_PassCode;     //配对码


/********************************************************************/
#define Pin(x)   (1<<x)
#define GP0       0
#define GP1       1
#define GP2       2

void GPIO_Output(uint8 GPIO,uint8 Pin);
void GPIO_SetLow(uint8 GPIO,uint8 PPin);
void GPIO_SetHig(uint8 GPIO,uint8 PPin);
void GPIO_SetUser(uint8 GPIO,uint8 PPin,uint8 Sta);
uint8 MAC_Matching( uint8 *ownAddress);
uint32 Get_UserPassCode(uint8 *dst);


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif /* USER_CC2541_H */
