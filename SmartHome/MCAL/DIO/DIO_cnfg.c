#include "DIO_cnfg.h"
#include "DIO_interface.h"
/************************************************************************/
/* Use OUTPUt,INFREE and INPULL to change status of each pin            */
/************************************************************************/
const DIO_PinStatus_type Pin_Status_Array[TOTALPINS] =
{
	OUTPUT,  /*PortA Pin0 Output*/
	OUTPUT,	 /*PortA Pin1 Output*/
	OUTPUT,	 /*PortA Pin2 Output*/
	OUTPUT,	 /*PortA Pin3 Output*/
	OUTPUT,	 /*PortA Pin4 Output*/
	OUTPUT,	 /*PortA Pin5 Output*/
	OUTPUT,	 /*PortA Pin6 Output*/
	INPULL,	 /*PortA Pin7 Output*/
	OUTPUT,	 /*PortB Pin0 Input no pull up*/
	OUTPUT,	 /*PortB Pin1 Input no pull up*/
	OUTPUT,	 /*PortB Pin2 Input no pull up*//*INT2*/
	OUTPUT,	 /*PortB Pin3 Input no pull up*//*OC0*/
	OUTPUT,	 /*PortB Pin4 Input no pull up*/
	OUTPUT,	 /*PortB Pin5 Input no pull up*//*MOSI*/
	OUTPUT,	 /*PortB Pin6 Input no pull up*//*MISO*/
	OUTPUT,	 /*PortB Pin7 Input no pull up*//*SCK*/
	OUTPUT,  /*PortC Pin0 Input with pull up*/
	OUTPUT,	 /*PortC Pin1 Input with pull up*/
	OUTPUT,	 /*PortC Pin2 Input with pull up*/
	OUTPUT,	 /*PortC Pin3 Input with pull up*/
	OUTPUT,	 /*PortC Pin4 Input with pull up*/
	OUTPUT,	 /*PortC Pin5 Input with pull up*/
	OUTPUT,	 /*PortC Pin6 Input with pull up*/
	OUTPUT,	 /*PortC Pin7 Input with pull up*/
	OUTPUT,  /*PortD Pin0 Output*/
	OUTPUT,	 /*PortD Pin1 Input*/
	OUTPUT,	 /*PortD Pin2 Input*//*INT0*/
	OUTPUT,	 /*PortD Pin3 Output*//*INT1*/
	OUTPUT,	 /*PortD Pin4 Output*//*OC1B*/
	OUTPUT,	 /*PortD Pin5 Output*//*OC1A*/
	OUTPUT,	 /*PortD Pin6 Output*//*ICP1*/
	OUTPUT	 /*PortD Pin7 Output*//*OC2*/
};
