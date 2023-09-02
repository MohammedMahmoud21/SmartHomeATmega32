#ifndef MEMMAP_H_
#define MEMMAP_H_
#include "StdTypes.h"

typedef volatile unsigned char*const CPvu8;
/************************************************************************/
/*\ DIO Registers.														*/
/*\CPvu8 -> volatile unsigned char*const.                               */
/************************************************************************/
#define PINA	(*((CPvu8)0x39))
#define DDRA	(*((CPvu8)0x3A))
#define PORTA	(*((CPvu8)0x3B))
#define PINB	(*((CPvu8)0x36))
#define DDRB	(*((CPvu8)0x37))
#define PORTB	(*((CPvu8)0x38))
#define PINC	(*((CPvu8)0x33))
#define DDRC	(*((CPvu8)0x34))
#define PORTC	(*((CPvu8)0x35))
#define PIND	(*((CPvu8)0x30))
#define DDRD	(*((CPvu8)0x31))
#define PORTD	(*((CPvu8)0x32))
/************************************************************************/
/*\ ADC Registers.														*/
/*\CPvu8 -> volatile unsigned char*const.                               */
/************************************************************************/
//ADC Lower byte register
#define ADCL	(*((CPvu8)(0x24)))
//ADC Higher byte register
#define ADCH	(*((CPvu8)(0x25)))
//ADC Control and Status Register
#define ADCSRA	(*((CPvu8)(0x26)))
//Set to 1 to enable ADC.
#define ADEN	7
//set to 1 to start conversion.
#define ADSC	6
//set 1 to enble auto trigger conversion.
#define ADATE	5
//This bit is set when an ADC conversion completes and the Data Registers are updated.
#define ADIF	4
//set to one and the I-bit in SREG is set, the ADC Conversion Completed Interrupt is activated.
#define ADIE	3
//These bits determine the division factor between the XTAL frequency.
#define ADPS2	2
#define ADPS1	1
#define ADPS0	0

//ADC Multiplexer Selection Register
#define ADMUX	(*((CPvu8)(0x27)))
//These two bits for setting reference voltage.
/* s1 s0
*  0 0 AREF, Internal Vref turned off
*  0 1 AVCC with external capacitor at AREF pin
*  1 0 Reserved
*  1 1 Internal 2.56V Voltage Reference with external capacitor at AREF pin
*/
#define REFS1	7
#define REFS0	6
//Write one to ADLAR to left adjust the result.
#define ADLAR	5
//Input Channel and Gain Selections
#define MUX4	4
#define MUX3	3
#define MUX2	2
#define MUX1	1
#define MUX0	0

/************************************************************************/
/*\ Interrupt macros.														*/
/*\CPvu8 -> volatile unsigned char*const.                               */
/************************************************************************/
#define RESET_VECT				__vector_0
#define INT0_VECT				__vector_1
#define INT1_VECT				__vector_2
#define INT2_VECT				__vector_3
#define TIMER2_COMP_VECT		__vector_4
#define TIMER2_OVF_VECT			__vector_5
#define TIMER1_CAPT_VECT		__vector_6
#define TIMER1_COMPA_VECT		__vector_7
#define TIMER1_COMPB_VECT		__vector_8
#define TIMER1_OVF_VECT			__vector_9
#define TIMER0_COMP_VECT		__vector_10
#define TIMER0_OVF_VECT			__vector_11
#define SPI_STC_VECT			__vector_12
#define USART_RXC_VECT			__vector_13
#define USART_UDRE_VECT			__vector_14
#define USART_TXC_VECT			__vector_15
#define ADC_VECT				__vector_16
#define EE_RDY_VECT				__vector_17
#define ANA_COMP_VECT			__vector_18
#define TWI_VECT				__vector_19
#define SPM_RDY_VECT			__vector_20

//macro to unmasking global interrupt before save context
#define ISR_NOBLOCK		__attribute__ ((interrupt))
//macro to tell compile don't add any extra assembly codes (don't add context).
#define ISR_NAKED		__attribute__ ((naked))

//macro like func to init an isr function.
#define ISR(vector,...)   void vector(void) __attribute__ ((signal)); __VA_ARGS__ \
					      void vector(void)
//macros to enable and disable global interrupt
#define sei()	__asm__ __volatile__ ("sei" ::)
#define cli()	__asm__ __volatile__ ("cli" ::)
#define reti()	__asm__ __volatile__ ("reti" ::)
#define ret()	__asm__ __volatile__ ("ret" ::)

//Extern interrupt registers.
#define MCUCR	(*((CPvu8)(0x55)))
//bits definition
//bits corresponding to sense control for int0
#define ISC00	0
#define ISC01	1
//bits corresponding to sense control for int1
#define ISC10	2
#define ISC11	3

#define MCUCSR  (*((CPvu8)(0x54)))
//bit corresponding to sense control for int2
#define  ISC2	6

#define GICR	(*((CPvu8)(0x5B)))
//bit for enable int1,2 and 0
#define INT1_ENABLE		7
#define INT0_ENABLE		6
#define INT2_ENABLE		5
#define GIFR	(*((CPvu8)0x5A))
//bits coresbonding for interrupt flags of int0,1 and 2
#define INTF1	7
#define INTF0	6
#define INTF2	5

/************************************************************************/
/*\ Timers Registers.													*/
/*\CPvu8 -> volatile unsigned char*const.                               */
/************************************************************************/


/************************************************************************************************/
/* Timer 0 */
#define TCNT0   (*(volatile unsigned char*)0x52)
#define TCCR0   (*(volatile unsigned char*)0x53)
#define TWCR    (*(volatile unsigned char*)0x56)
#define SPMCR   (*(volatile unsigned char*)0x57)
#define TIFR    (*(volatile unsigned char*)0x58)
#define TIMSK   (*(volatile unsigned char*)0x59)




#define OCR0    (*(volatile unsigned char*)0x5C)
/****************************************************************************************************/

/*TIMER 1*/


#define ICR1         (*(volatile unsigned short*)0x46)
#define ICR1L     (*(volatile unsigned char*)0x46)
#define ICR1H     (*(volatile unsigned char*)0x47)
#define OCR1B     (*(volatile unsigned short*)0x48)
#define OCR1BL    (*(volatile unsigned char*)0x48)
#define OCR1BH       (*(volatile unsigned char*)0x49)
#define OCR1A     (*(volatile unsigned short*)0x4A)
#define OCR1AL    (*(volatile unsigned char*)0x4A)
#define OCR1AH      (*(volatile unsigned char*)0x4B)
#define TCNT1       (*(volatile unsigned short*)0x4C)
#define TCNT1L    (*(volatile unsigned char*)0x4C)
#define TCNT1H    (*(volatile unsigned char*)0x4D)
#define TCCR1B       (*(volatile unsigned char*)0x4E)
#define TCCR1A        (*(volatile unsigned char*)0x4F)

#define SFIOR       (*(volatile unsigned char*)0x50)

#define OSCCAL       (*(volatile unsigned char*)0x51)
/******************************************************************************/
/* Timer 2 */

#define OCR2     (*(volatile unsigned char*)0x43)
#define TCNT2    (*(volatile unsigned char*)0x44)
#define TCCR2    (*(volatile unsigned char*)0x45)


/* TCCR0 */
#define FOC0    7
#define WGM00   6
#define COM01   5
#define COM00   4
#define WGM01   3
#define CS02    2
#define CS01    1
#define CS00    0

/* TCCR2 */
#define FOC2    7
#define WGM20   6
#define COM21   5
#define COM20   4
#define WGM21   3
#define CS22    2
#define CS21    1
#define CS20    0

/* ASSR */
/* bits 7-4 reserved */
#define AS2     3
#define TCN2UB  2
#define OCR2UB  1
#define TCR2UB  0

/* TCCR1A */
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

/* TCCR1B */
#define ICNC1   7
#define ICES1   6
/* bit 5 reserved */
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

/* WDTCR */
#define WDTCR    (*(volatile unsigned char*)0x41)
/* bits 7-5 reserved */
#define WDTOE   4
#define WDE     3
#define WDP2    2
#define WDP1    1
#define WDP0    0

/******************************************************************************/
/* USART Baud Rate Register Low */
#define UBRRL    (*(volatile unsigned char*)0x29)

/* USART Control and Status Register B */
#define UCSRB   (*(volatile unsigned char*)0x2A)

/* USART Control and Status Register A */
#define UCSRA    (*(volatile unsigned char*)0x2B)

/* USART I/O Data Register */
#define UDR       (*(volatile unsigned char*)0x2C)

/* USART Baud Rate Register High */
#define UBRRH    (*(volatile unsigned char*)0x40)

/* USART Control and Status Register C */
#define UCSRC     (*(volatile unsigned char*)0x40)

/* USART Register C */
#define    UMSEL        6
#define    UPM1         5
#define    UPM0         4
#define    USBS         3
#define    UCSZ1        2
#define    UCSZ0        1
#define    UCPOL        0

/* USART Status Register A  */
#define    RXC          7
#define    TXC          6
#define    UDRE         5
#define    FE           4
#define    DOR          3
#define    UPE          2
#define    U2X          1
#define    MPCM         0
/* USART Control Register B  */
#define    RXCIE        7
#define    TXCIE        6
#define    UDRIE        5
#define    RXEN         4
#define    TXEN         3
#define    UCSZ         2
#define    UCSZ2        2
#define    RXB8         1
#define    TXB8         0
/******************************************************************************/
/* SPI */
/* SPI Control Register */
#define SPCR       (*(volatile unsigned char*)0x2D)
/* SPI Status Register */
#define SPSR       (*(volatile unsigned char*)0x2E)
/* SPI I/O Data Register */
#define SPDR       (*(volatile unsigned char*)0x2F)

/* SPI Status Register - SPSR */
#define    SPIF         7
#define    WCOL         6
#define    SPI2X        0

/* SPI Control Register - SPCR */
#define    SPIE         7
#define    SPE          6
#define    DORD         5
#define    MSTR         4
#define    CPOL         3
#define    CPHA         2
#define    SPR1         1
#define    SPR0         0

/******************************************************************************/
/* EEPROM Control Register */
#define EECR	(*(volatile unsigned char*)0x3C)

/* EEPROM Data Register */
#define EEDR	(*(volatile unsigned char*)0x3D)

/* EEPROM Address Register */
#define EEAR	(*(volatile unsigned short*)0x3E)
#define EEARL	(*(volatile unsigned char*)0x3E)
#define EEARH	(*(volatile unsigned char*)0x3F)

/* TWI stands for "Two Wire Interface" or "TWI Was I2C(tm)" */
#define TWBR    (*(volatile unsigned char*)0x20)
#define TWSR    (*(volatile unsigned char*)0x21)
#define TWAR    (*(volatile unsigned char*)0x22)
#define TWDR    (*(volatile unsigned char*)0x23)
/*EEPROM*/
#define EERE	0
#define EEWE	1
#define EEMWE	2
#define EERIE	3
/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0

/* TIFR */
#define OCF2    7
#define TOV2    6
#define ICF1    5
#define OCF1A   4
#define OCF1B   3
#define TOV1    2
#define OCF0    1
#define TOV0    0

/* SPMCR */
#define SPMIE   7
#define RWWSB   6
/* bit 5 reserved */
#define RWWSRE  4
#define BLBSET  3
#define PGWRT   2
#define PGERS   1
#define SPMEN   0

/* TWCR */
#define TWINT   7
#define TWEA    6
#define TWSTA   5
#define TWSTO   4
#define TWWC    3
#define TWEN    2
/* bit 1 reserved */
#define TWIE    0

/* TWAR */
#define TWA6    7
#define TWA5    6
#define TWA4    5
#define TWA3    4
#define TWA2    3
#define TWA1    2
#define TWA0    1
#define TWGCE   0

/* TWSR */
#define TWS7    7
#define TWS6    6
#define TWS5    5
#define TWS4    4
#define TWS3    3
/* bit 2 reserved */
#define TWPS1   1
#define TWPS0   0

#endif /* MEMMAP_H_ */
