#include "SPI_interface.h"

static void (*SPI_PFunc)(void)=NULL_PTR;

void SPI_Init(void)
{
	#if SPI_STATE == MASTER
	//Master
	SET_BIT(SPCR,MSTR);

	#elif SPI_STATE == SLAVE
	//Slave
	CLR_BIT(SPCR,MSTR);
	#endif
	
	#if DATA_ORDER == BIG_ENDIAN
	CLR_BIT(SPCR,DORD);
	#elif DATA_ORDER == LITEL_ENDIAN
	SET_BIT(SPCR,DORD);
	#endif
	//clock phase
	SET_BIT(SPCR,CPHA);
	//enable
	SET_BIT(SPCR,SPE);
}

u8 SPI_SendReceive_Master(u8 data)
{
	u8 received=0;
	SPDR = data;
	while(ZERO_INIT == READ_BIT(SPSR,SPIF));
	received = SPDR;
	return (received);
}
#if SPI_STATE == SLAVE
u8	SPI_ReceivePeriodic(u8 *data)
{
	u8 ret_val=0;
	
	if(1 == READ_BIT(SPSR,SPIF))
	{
		*data = SPDR;
		ret_val=1;
	}
	else
	{
		ret_val=0;
	}
	return (ret_val);	
}
u8	SPI_ReceiveNoBlock(void)
{
	return SPDR;
}
void SPI_SendNoBlock(u8 data)
{
	SPDR=data;	
}
#endif

void SPI_InterruptEnable(void)
{
	SET_BIT(SPCR,SPIE);
}

/****CallBack*****/

void SPI_SetCallBack(void (*p_func)(void))
{
	SPI_PFunc = p_func;
}
/******ISR*******/

ISR(SPI_STC_VECT)
{
	if(NULL_PTR != SPI_PFunc)
	{
		SPI_PFunc();
	}
	else
	{
		;
	}
}