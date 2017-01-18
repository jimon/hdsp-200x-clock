#pragma once

#define DISPLAYS_COUNT 1
#define CHARACTERS_COUNT 4

#define DDR_COL   DDRB
#define PORT_COL  PORTB
#define PORT_COL1 PORTB0
#define PORT_COL2 PORTB1
#define PORT_COL3 PORTB2
#define PORT_COL4 PORTB3
#define PORT_COL5 PORTB4

#define DDR_CTRL      DDRD
#define PORT_CTRL     PORTD
#define PORT_CTRL_VB  PORTD5
#define PORT_CTRL_CLK PORTD0
#define PORT_CTRL_DIN PORTD1

void hcms_200x_start();
void hcms_200x_stop();
