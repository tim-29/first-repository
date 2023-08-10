/**************************************************************************************************
  Filename:       User_CC2541.c
  Revised:        $Date: 2019��12��27��13.44.37 $
  Revision:       $Revision: 01 $

  Description:    �Զ��幦��c�ļ�
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


uint32  User_PassCode = 0;      //�����


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
 * @brief   IO����Ϊ���
 *
 * @param   GPIO -ѡ�ж˿�
 *
 * @param   Pin -ѡ������
 *
 * @return  none
 */
void GPIO_Output(uint8 GPIO,uint8 PPin)
{
  /*
  P0SEL &= 0xFE;  //�� P00 Ϊ��ͨIO��   11111110
  P0DIR |= 0x01;  //�� P00 ����Ϊ���   00000001
  */

  if(GPIO == 0)
  {
    P0SEL &= ~PPin; //�� P0x Ϊ��ͨIO��
    P0DIR |= PPin;  //�� P0x ����Ϊ���
  }
  else if(GPIO == 1)
  {
    P1SEL &= ~PPin; //�� P1x Ϊ��ͨIO��
    P1DIR |= PPin;  //�� P1x ����Ϊ���
  }
  else if(GPIO == 2)
  {
    P2SEL &= ~PPin; //�� P2x Ϊ��ͨIO��
    P2DIR |= PPin;  //�� P2x ����Ϊ���
  }
}
/*********************************************************************
 * @fn      GPIO_SetLow
 *
 * @brief   IO���Ϊ��
 *
 * @param   GPIO -ѡ�ж˿�
 *
 * @param   Pin -ѡ������
 *
 * @return  none
 */
void GPIO_SetLow(uint8 GPIO,uint8 PPin)
{
  if(GPIO == 0)
  {
    P0 &= ~PPin; //�� P0x ����͵�ƽ
  }
  else if(GPIO == 1)
  {
    P1 &= ~PPin; //�� P1x ����͵�ƽ
  }
  else if(GPIO == 2)
  {
    P2 &= ~PPin; //�� P2x ����͵�ƽ
  }
}
/*********************************************************************
 * @fn      GPIO_SetHig
 *
 * @brief   IO���Ϊ��
 *
 * @param   GPIO -ѡ�ж˿�
 *
 * @param   Pin -ѡ������
 *
 * @return  none
 */
void GPIO_SetHig(uint8 GPIO,uint8 PPin)
{
  if(GPIO == 0)
  {
    P0 |= PPin; //�� P0x ����ߵ�ƽ
  }
  else if(GPIO == 1)
  {
    P1 |= PPin; //�� P1x ����ߵ�ƽ
  }
  else if(GPIO == 2)
  {
    P2 |= PPin; //�� P2x ����ߵ�ƽ
  }
}

/*********************************************************************
 * @fn      GPIO_SetUser
 *
 * @brief   IO����Զ���
 *
 * @param   GPIO -ѡ�ж˿�
 *
 * @param   Pin -ѡ������
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
    
    P0 = Sta0; //�� P0x ���
  }
  else if(GPIO == 1)
  {
    Sta0 = P1;
    
    Sta0 = ((~PPin) & Sta0);
    
    Sta0 = (Sta | Sta0);
    
    P1 = Sta0; //�� P1x ���
  }
  else if(GPIO == 2)
  {
    Sta0 = P2;
    
    Sta0 = ((~PPin) & Sta0);
    
    Sta0 = (Sta | Sta0);
    
    P2 = Sta0; //�� P2x ���
  }
}

/*********************************************************************
 * @fn      MAC_Matching
 *
 * @brief   ƥ��MAC��ַ�Ƿ�������Χ
 *
 * @param   ownAddress -MAC���λ��
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
  //��Ч��Χ��Max��Min��24λ��ͬ����1��
  if(DatX3 == 0)
  {
    //����MAC��24λ�Ƿ�ƥ����Ч��Χ
    if(DatX1 == MAC_Min_H)
    {
      //����MAC��24λ�Ƿ�ƥ����Ч��Χ
      if(( MAC_Min_L <= DatX2) && (DatX2 <= MAC_Max_L))
      {
        //ƥ��
        DatX4 = 1;
      }
      else
      {
        //��ƥ��
      }
    }
    else
    {
      
    }
  }
  //��Ч��Χ��Max��Min��24λ���1����2��
  else if(DatX3 == 1)
  {
    if(DatX1 == MAC_Max_H)
    {
      if(DatX2 <= MAC_Max_L)
      {
        //ƥ��
        DatX4 = 1;
      }
      else
      {
        //��ƥ��
      }
    }
    else if(DatX1 == MAC_Min_H)
    {
      if(DatX2 >= MAC_Min_L)
      {
        //ƥ��
        DatX4 = 1;
      }
      else
      {
        //��ƥ��
      }
    }
    else
    {
      //��ƥ��
    }
  }
  //��Ч��Χ��Max��Min��24λ������1����3��
  else if(DatX3 > 1)
  {
    if(DatX1 == MAC_Max_H)
    {
      if(DatX2 <= MAC_Max_L)
      {
        //ƥ��
        DatX4 = 1;
      }
      else
      {
        //��ƥ��
      }
    }
    else if(DatX1 == MAC_Min_H)
    {
      if(DatX2 >= MAC_Min_L)
      {
        //ƥ��
        DatX4 = 1;
      }
      else
      {
        //��ƥ��
      }
    }
    else if((MAC_Min_H < DatX1) && (DatX1 < MAC_Max_H))
    {
      //ƥ��
      DatX4 = 1;
    }
    else
    {
      //��ƥ��
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
 * @brief   ��ȡ��һMAC��ַ
 *
 * @param   PriMAC1 -��ȡ����MAC�ĵ�ַ
 *
 * @return  none
 */
void Get_PriMAC( uint8 *PriMAC1 )
{
  PriMAC1[0] = *( unsigned char* )( 0x780E );     // ֱ��ָ��ָ������
  PriMAC1[1] = *( unsigned char* )( 0x780F );
  PriMAC1[2] = *( unsigned char* )( 0x7810 );
  PriMAC1[3] = XREG( 0x7811 );                    // define ����ֱ�Ӷ�������
  PriMAC1[4] = XREG( 0x7812 );
  PriMAC1[5] = XREG( 0x7813 );

  //HalLcdWriteString( bdAddr2Str( PriMAC ),  HAL_LCD_LINE_2 );
  //NPI_PrintString( bdAddr2Str( PriMAC ) );
  //NPI_PrintString( "\r\n" );
}
/*********************************************************************
 * @fn      Get_UserPassCode
 *
 * @brief   ��ȡ�����
 *
 * @param   dst -��Ҫ���м����MAC�Ĵ洢��ַ
 *
 * @return  �����
 */
uint32 Get_UserPassCode(uint8 *dst)
{
  uint32 DatX0 = (uint32)dst[0]+((uint32)dst[3]<<8)+((uint32)dst[4]<<16);
  uint32 DatX1 = (uint32)dst[1]+((uint32)dst[2]<<8)+((uint32)dst[5]<<16);

  uint32 User_PassCode = ((DatX0^DatX1)+8517)%1000000;

  return User_PassCode;
}


