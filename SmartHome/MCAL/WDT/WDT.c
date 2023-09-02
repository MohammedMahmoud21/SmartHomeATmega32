#include "WDT_interface.h"


void WDT_SetTime(TimeOut_type time)
{
	u8 wdt_val = 0x08; //enable wde.
	wdt_val |= time;
	WDTCR |= (1 << WDTOE) | (1 << WDE);
	WDTCR = wdt_val;
}
void WDT_Stop(void)
{
	WDTCR = (1 << WDTOE) | (1 << WDE);
	WDTCR =0;
}