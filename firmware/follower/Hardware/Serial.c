#include "Headfile.h"

uint8_t Serial_RxFlag;
char Serial_RxPacket[100];


void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate=115200 ;
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode=USART_Mode_Tx|USART_Mode_Rx;
	USART_InitStructure.USART_Parity=USART_Parity_No;
	USART_InitStructure.USART_StopBits=USART_StopBits_1;
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);   //开启RXBE标志位到NVIC的输出
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel=USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;
	NVIC_Init(&NVIC_InitStructure);


	USART_Cmd(USART1,ENABLE);
}

void Serial_SendByte(uint8_t Byte)
{
	USART_SendData(USART1,Byte);
	while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	
}

void Serial_SendArray(uint8_t *Array,uint16_t Length)
{
	uint16_t  i;
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint8_t i;
	Serial_SendByte('@');
	for(i=0;String[i]!='\0';i++)       //0
	{
		Serial_SendByte(String[i]);
	}
	Serial_SendByte('\r');
	Serial_SendByte('\n');
	
}
uint32_t Serial_Pow(uint32_t X,uint32_t Y)
{
	uint32_t Result=1;
	while(Y--)
	{
		Result*=X;
	}
	return Result;
	
}


void Serial_SendNumber(uint32_t Number,uint8_t Length)
{
	uint8_t i;
	Serial_SendByte('@');
	for(i=0;i<Length;i++)
	{
		Serial_SendByte(Number/Serial_Pow(10,Length-i-1)%10+'0');
	}
   Serial_SendByte('\r');
   Serial_SendByte('\n');	
}

void Serial_SendData(uint32_t Dis, uint32_t Flag, uint8_t D_Len, uint8_t F_Len)
{
	uint8_t i;
	Serial_SendByte('@');
	for (i = 0; i < D_Len; i++)
	{
		Serial_SendByte(Dis / Serial_Pow(10, D_Len - i - 1) % 10 + '0');
	}
	for (i = 0; i < F_Len; i++)
	{
		Serial_SendByte(Flag / Serial_Pow(10, F_Len - i - 1) % 10 + '0');
	}
   Serial_SendByte('\r');
   Serial_SendByte('\n');
}

int fputc(int ch,FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

void Serial_Printf(char *format,...)
{
	char String[100];
	va_list arg;              //参数列表变量
	va_start (arg,format);
	vsprintf(String,format,arg);
	va_end(arg);              //释放参数表
	Serial_SendString(String);	
	
}


uint8_t Serial_GetRxFlag(void)
{
	if(Serial_RxFlag==1)
	{
		Serial_RxFlag=0;
		return 1;
	}
	return 0;
}

uint32_t transit(char*arr)
{
	int i=0,a=0;
	for(i=0;i<strlen(arr);i++)
	{
		a+=(arr[i]-'0')*Serial_Pow(10,strlen(arr)-1-i);
	}
	return a;
}

void USART1_IRQHandler(void)
{
	static uint8_t RxState=0;
	static uint8_t pRxPacket=0;
	
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE)==SET)
	{
		uint8_t RxData=USART_ReceiveData(USART1); 
		
		if(RxState==0)
		{
			if(RxData=='@')
			{
				RxState=1;
				pRxPacket=0;
			}
		}
		else
			if(RxState==1)
			{
				if(RxData=='\r')
				{
					RxState=2;
			  }
				else
				{
				Serial_RxPacket[pRxPacket]=RxData;
				pRxPacket++;
				}
			}
		else
			if(RxState==2)
			{
				if(RxData=='\n')
				{
					RxState=0;
					Serial_RxPacket[pRxPacket]='\0';
					Serial_RxFlag=1;
					

				}
			}
	
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
		
	}
	
}
	
	
