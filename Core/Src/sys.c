#include "sys.h"


//THUMB指令不支持汇编内联
//采用如下方法实现执行汇编指令WFI  
void WFI_SET(void)
{
    __ASM volatile("WFI");
}
//关闭所有中断
void INTX_DISABLE(void)
{
    __ASM volatile("CPSID I");
}
//开启所有中断
void INTX_ENABLE(void)
{
    __ASM volatile("CPSIE I");
}
//设置栈顶地址
//addr:栈顶地址
void MSR_MSP(u32 addr)
{
    __ASM volatile("MSR MSP, r0"); 			//set Main Stack value
    __ASM volatile("BX r14");
}

/**************************************************************************
Function: Set JTAG mode
Input   : mode:JTAG, swd mode settings；00，all enable；01，enable SWD；10，Full shutdown
Output  : none
函数功能：设置JTAG模式
入口参数：mode:jtag,swd模式设置;00,全使能;01,使能SWD;10,全关闭;	
返回  值：无
**************************************************************************/
//#define JTAG_SWD_DISABLE   0X02
//#define SWD_ENABLE         0X01
//#define JTAG_SWD_ENABLE    0X00	
void JTAG_Set(u8 mode)
{
	u32 temp;
	temp=mode;
	temp<<=25;
	RCC->APB2ENR|=1<<0;     //开启辅助时钟	   
	AFIO->MAPR&=0XF8FFFFFF; //清除MAPR的[26:24]
	AFIO->MAPR|=temp;       //设置jtag模式
} 
