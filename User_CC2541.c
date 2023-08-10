/**************************************************************************************************
  Filename:       User_CC2541.c
  Revised:        $Date: 2019年12月27日13.44.37 $
  Revision:       $Revision: 01 $

  Description:    自定义功能c文件
**************************************************************************************************/

/*********************************************************************
 * INCLUDES
 */

/********************************************************************/

#include "User_CC2541.h"

/********************************************************************/

/********************************************************************/

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * CONSTANTS
 */

/*********************************************************************
 * TYPEDEFS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */

uint8   Flag_UARTx_MsgDeb = 1;  //


uint32  User_PassCode = 0;      //配对码


/*********************************************************************
 * EXTERNAL VARIABLES
 */

/*********************************************************************
 * EXTERNAL FUNCTIONS
 */

/*********************************************************************
 * LOCAL VARIABLES
 */

/*********************************************************************
 * LOCAL FUNCTIONS
 */

/*********************************************************************
 * PROFILE CALLBACKS
 */

/*********************************************************************
 * PUBLIC FUNCTIONS
 */

/*********************************************************************
 * @fn      GPIO_Output
 *
 * @brief   IO配置为输出
 *
 * @param   GPIO -选中端口
 *
 * @param   Pin -选中引脚
 *
 * @return  none
 */
void GPIO_Output(uint8 GPIO,uint8 PPin)
{
  /*
  P0SEL &= 0xFE;  //让 P00 为普通IO口   11111110
  P0DIR |= 0x01;  //把 P00 设置为输出   00000001
  */

  if(GPIO == 0)
  {
    P0SEL &= ~PPin; //让 P0x 为普通IO口
    P0DIR |= PPin;  //把 P0x 设置为输出
  }
  else if(GPIO == 1)
  {
    P1SEL &= ~PPin; //让 P1x 为普通IO口
    P1DIR |= PPin;  //把 P1x 设置为输出
  }
  else if(GPIO == 2)
  {
    P2SEL &= ~PPin; //让 P2x 为普通IO口
    P2DIR |= PPin;  //把 P2x 设置为输出
  }
}
/*********************************************************************
 * @fn      GPIO_SetLow
 *
 * @brief   IO输出为低
 *
 * @param   GPIO -选中端口
 *
 * @param   Pin -选中引脚
 *
 * @return  none
 */
void GPIO_SetLow(uint8 GPIO,uint8 PPin)
{
  if(GPIO == 0)
  {
    P0 &= ~PPin; //让 P0x 输出低电平
  }
  else if(GPIO == 1)
  {
    P1 &= ~PPin; //让 P1x 输出低电平
  }
  else if(GPIO == 2)
  {
    P2 &= ~PPin; //让 P2x 输出低电平
  }
}
/*********************************************************************
 * @fn      GPIO_SetHig
 *
 * @brief   IO输出为高
 *
 * @param   GPIO -选中端口
 *
 * @param   Pin -选中引脚
 *
 * @return  none
 */
void GPIO_SetHig(uint8 GPIO,uint8 PPin)
{
  if(GPIO == 0)
  {
    P0 |= PPin; //让 P0x 输出高电平
  }
  else if(GPIO == 1)
  {
    P1 |= PPin; //让 P1x 输出高电平
  }
  else if(GPIO == 2)
  {
    P2 |= PPin; //让 P2x 输出高电平
  }
}

/*********************************************************************
 * @fn      GPIO_SetUser
 *
 * @brief   IO输出自定义
 *
 * @param   GPIO -选中端口
 *
 * @param   Pin -选中引脚
 *
 * @return  none
 */
void GPIO_SetUser(uint8 GPIO,uint8 PPin,uint8 Sta)
{
  uint8 Sta0 = 0;
  
  if(GPIO == 0)
  {
    Sta0 = P0;
    
    Sta0 = ((~PPin) & Sta0);
    
    Sta0 = (Sta | Sta0);
    
    P0 = Sta0; //让 P0x 输出
  }
  else if(GPIO == 1)
  {
    Sta0 = P1;
    
    Sta0 = ((~PPin) & Sta0);
    
    Sta0 = (Sta | Sta0);
    
    P1 = Sta0; //让 P1x 输出
  }
  else if(GPIO == 2)
  {
    Sta0 = P2;
    
    Sta0 = ((~PPin) & Sta0);
    
    Sta0 = (Sta | Sta0);
    
    P2 = Sta0; //让 P2x 输出
  }
}

/*********************************************************************
 * @fn      MAC_Matching
 *
 * @brief   匹配MAC地址是否在允许范围
 *
 * @param   ownAddress -MAC存放位置
 *
 * @return  none
 */
uint8 MAC_Matching( uint8 *ownAddress)
{
#if (Flag_MAC_Matching)
  uint32 DatX1 = ownAddress[3] + ( ( uint32 )ownAddress[4]<<8 ) + ( ( uint32 )ownAddress[5]<<16 );
  uint32 DatX2 = ownAddress[0] + ( ( uint32 )ownAddress[1]<<8 ) + ( ( uint32 )ownAddress[2]<<16 );
  uint32 DatX3 = MAC_Max_H - MAC_Min_H;
  uint8  DatX4 = 0;
  //有效范围的Max和Min高24位相同，分1段
  if(DatX3 == 0)
  {
    //本机MAC高24位是否匹配有效范围
    if(DatX1 == MAC_Min_H)
    {
      //本机MAC低24位是否匹配有效范围
      if(( MAC_Min_L <= DatX2) && (DatX2 <= MAC_Max_L))
      {
        //匹配
        DatX4 = 1;
      }
      else
      {
        //不匹配
      }
    }
    else
    {
      
    }
  }
  //有效范围的Max和Min高24位相差1，分2段
  else if(DatX3 == 1)
  {
    if(DatX1 == MAC_Max_H)
    {
      if(DatX2 <= MAC_Max_L)
      {
        //匹配
        DatX4 = 1;
      }
      else
      {
        //不匹配
      }
    }
    else if(DatX1 == MAC_Min_H)
    {
      if(DatX2 >= MAC_Min_L)
      {
        //匹配
        DatX4 = 1;
      }
      else
      {
        //不匹配
      }
    }
    else
    {
      //不匹配
    }
  }
  //有效范围的Max和Min高24位相差大于1，分3段
  else if(DatX3 > 1)
  {
    if(DatX1 == MAC_Max_H)
    {
      if(DatX2 <= MAC_Max_L)
      {
        //匹配
        DatX4 = 1;
      }
      else
      {
        //不匹配
      }
    }
    else if(DatX1 == MAC_Min_H)
    {
      if(DatX2 >= MAC_Min_L)
      {
        //匹配
        DatX4 = 1;
      }
      else
      {
        //不匹配
      }
    }
    else if((MAC_Min_H < DatX1) && (DatX1 < MAC_Max_H))
    {
      //匹配
      DatX4 = 1;
    }
    else
    {
      //不匹配
    }
  }

  return DatX4;
#else
  return 1;
#endif
}
/*********************************************************************
 * @fn      Get_PriMAC
 *
 * @brief   读取第一MAC地址
 *
 * @param   PriMAC1 -读取后存放MAC的地址
 *
 * @return  none
 */
void Get_PriMAC( uint8 *PriMAC1 )
{
  PriMAC1[0] = *( unsigned char* )( 0x780E );     // 直接指向指针内容
  PriMAC1[1] = *( unsigned char* )( 0x780F );
  PriMAC1[2] = *( unsigned char* )( 0x7810 );
  PriMAC1[3] = XREG( 0x7811 );                    // define 函数直接读出数据
  PriMAC1[4] = XREG( 0x7812 );
  PriMAC1[5] = XREG( 0x7813 );

  //HalLcdWriteString( bdAddr2Str( PriMAC ),  HAL_LCD_LINE_2 );
  //NPI_PrintString( bdAddr2Str( PriMAC ) );
  //NPI_PrintString( "\r\n" );
}
/*********************************************************************
 * @fn      Get_UserPassCode
 *
 * @brief   获取配对码
 *
 * @param   dst -需要进行计算的MAC的存储地址
 *
 * @return  配对码
 */
uint32 Get_UserPassCode(uint8 *dst)
{
  uint32 DatX0 = (uint32)dst[0]+((uint32)dst[3]<<8)+((uint32)dst[4]<<16);
  uint32 DatX1 = (uint32)dst[1]+((uint32)dst[2]<<8)+((uint32)dst[5]<<16);

  uint32 User_PassCode = ((DatX0^DatX1)+8517)%1000000;

  return User_PassCode;
}


