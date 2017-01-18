#include "hw_ds3231.h"
#include "USI_TWI_Master.h"

unsigned char bcd_to_decimal(unsigned char d) {return ((d & 0x0F) + (((d & 0xF0) >> 4) * 10));}
unsigned char decimal_to_bcd(unsigned char d) {return (((d / 10) << 4) & 0xF0) | ((d % 10) & 0x0F);}

unsigned char DS3231_Read(unsigned char address)
{
	unsigned char value = 0;  
	twi_start();
	twi_write(DS3231_Write_addr);
	twi_write(address);
	twi_start();
	twi_write(DS3231_Read_addr);
	value = twi_read(0);
	twi_stop();
	return value;
}

void DS3231_Write(unsigned char address, unsigned char value)
{
	twi_start();
	twi_write(DS3231_Write_addr);
	twi_write(address);
	twi_write(value);
	twi_stop();
}


void DS3231_init() 
{
	twi_Init(100000);
	DS3231_Write(controlREG, 0x00);  
	DS3231_Write(statusREG, 0x08); 
}

void getTime(unsigned char *p3, unsigned char *p2, unsigned char *p1, unsigned char *p0, unsigned char hour_format)
{
	unsigned char tmp = 0;

	tmp = DS3231_Read(secondREG);
	*p1 = bcd_to_decimal(tmp);
	tmp = DS3231_Read(minuteREG);
	*p2 = bcd_to_decimal(tmp);

	switch(hour_format)
	{
	case 1:
		tmp = DS3231_Read(hourREG);
		tmp &= 0x20;
		*p0 = (unsigned char)(tmp >> 5);
		tmp = (0x1F & DS3231_Read(hourREG));
		*p3 = bcd_to_decimal(tmp);
	default:
		tmp = (0x3F & DS3231_Read(hourREG));
		*p3 = bcd_to_decimal(tmp);
		break;
	}
}
