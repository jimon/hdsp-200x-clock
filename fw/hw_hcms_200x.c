#include "hw_hcms_200x.h"
#include <avr/io.h>
#include <stdbool.h>
#include <avr/interrupt.h>
//#include "hw_hcms_200x_font.h"

// loosely based on https://github.com/wespo/HDSP2000Shield

void hcms_200x_start()
{
	// enable output
	DDR_COL |= 1 << PORT_COL1;
	DDR_COL |= 1 << PORT_COL2;
	DDR_COL |= 1 << PORT_COL3;
	DDR_COL |= 1 << PORT_COL4;
	DDR_COL |= 1 << PORT_COL5;
	DDR_CTRL |= 1 << PORT_CTRL_VB;
	DDR_CTRL |= 1 << PORT_CTRL_CLK;
	DDR_CTRL |= 1 << PORT_CTRL_DIN;

	//TCCR0B |= (1 << CS12) | (1 << CS10); // 1/1024
	//TCCR0B |= _BV(CS11) | _BV(CS10); // 1/64
	TCCR0B |= _BV(CS11); // 1/8
	//TCCR0B |= _BV(CS10); // 1/1
	TIMSK |= 1 << TOIE0;
	sei();
}

void hcms_200x_stop()
{
	TIMSK &= ~(1 << TOIE0);
}

#define CLK_DELAY \
{ \
	__asm__ __volatile__ ("nop"); \
	__asm__ __volatile__ ("nop"); \
}

#define VB_DELAY \
{ \
	volatile uint8_t i = 0; \
	for(i = 0; i < 100; ++i) \
		__asm__ __volatile__ ("nop"); \
}

//const char text[4] = "HEY!";

#define    _____  0x00
#define    ____x  0x01
#define    ___x_  0x02
#define    ___xx  0x03
#define    __x__  0x04
#define    __x_x  0x05
#define    __xx_  0x06
#define    __xxx  0x07
#define    _x___  0x08
#define    _x__x  0x09
#define    _x_x_  0x0A
#define    _x_xx  0x0B
#define    _xx__  0x0C
#define    _xx_x  0x0D
#define    _xxx_  0x0E
#define    _xxxx  0x0F
#define    x____  0x10
#define    x___x  0x11
#define    x__x_  0x12
#define    x__xx  0x13
#define    x_x__  0x14
#define    x_x_x  0x15
#define    x_xx_  0x16
#define    x_xxx  0x17
#define    xx___  0x18
#define    xx__x  0x19
#define    xx_x_  0x1A
#define    xx_xx  0x1B
#define    xxx__  0x1C
#define    xxx_x  0x1D
#define    xxxx_  0x1E
#define    xxxxx  0x1F

const uint8_t letter_F[] =
{
	xxxxx,
	x____,
	x____,
	xxx__,
	x____,
	x____,
	x____
}; // F


#define xxxxxxx 0b1111111
#define x__x___ 0b1001000
#define x______ 0b1000000

const uint8_t letter_F2[] =
{
	xxxxxxx,
	x__x___,
	x__x___,
	x______,
	x______,
}; // F


//__attribute__((optimize("unroll-loops")))

#define DATA1_CLK \
{ \
	PORT_CTRL |= (1 << PORT_CTRL_DIN) | (1 << PORT_CTRL_CLK); \
	PORT_CTRL &= ~((1 << PORT_CTRL_DIN) | (1 << PORT_CTRL_CLK)); \
}
#define DATA0_CLK \
{ \
	PORT_CTRL |= (1 << PORT_CTRL_CLK); \
	PORT_CTRL &= ~(1 << PORT_CTRL_CLK); \
}

static void _push_rows(uint8_t col)
{
	uint8_t chr = 0;
	int8_t row = 0;
	for(chr = 0; chr < DISPLAYS_COUNT * CHARACTERS_COUNT; ++chr)
	{
		for(row = 0; row < 7; ++row)
		{
			if((letter_F2[col] >> row) & 1)
			{
				DATA1_CLK;
			}
			else
			{
				DATA0_CLK;
			}
		}
	}
}

volatile uint8_t _col = 0;
const uint8_t _col_port[5] = {PORT_COL1, PORT_COL2, PORT_COL3, PORT_COL4, PORT_COL5};

static void hcms_200x_display()
{
	PORT_CTRL &= ~(1 << PORT_CTRL_VB);

	PORT_COL &= ~(1 << _col_port[_col]);
	_col = (_col + 1) % 5;
	PORT_COL |= 1 << _col_port[_col];

	_push_rows(_col);

	PORT_CTRL |= 1 << PORT_CTRL_VB;
}

ISR(TIMER0_OVF_vect)
{
	hcms_200x_display();
}
