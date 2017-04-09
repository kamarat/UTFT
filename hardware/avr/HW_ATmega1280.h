#include "UTFT.h"

void UTFT::_hw_special_init()
{
}

void UTFT::LCD_Writ_Bus(char VL)
{
  #ifdef OPEN_SMART_ILI9327
    /* Pins LCD - MEGA
     * D0 -  8 (PH5)
     * D1 -  9 (PH6)
     * D2 - 10 (PB4)
     * D3 - 11 (PB5)
     * D4 -  4 (PG5)
     * D5 - 13 (PB7)
     * D6 -  6 (PH3)
     * D7 -  7 (PH4)
     */
     PORTB &= 0x4F;
     PORTB |= (VL & 0x2C) << 2;
     PORTG &= 0xDF;
     PORTG |= (VL & 0x10) << 1;
     PORTH &= 0x87;
     PORTH |= ((VL & 0x03) << 5 ) | ((VL & 0xC0) >> 3);
     pulse_low(P_WR, B_WR);
  #else
    PORTH &= ~0x78;
    PORTH |= ((VL & 0x03)<<5)+((VL & 0xC0)>>3);
    PORTG &= ~0x20;
    PORTG |= (VL & 0x10)<<1;
    PORTE &= ~0x38;
    PORTE |=((VL & 0x20)>>2)+ ((VL& 0x0C)<<2);
    pulse_low(P_WR, B_WR);
  #endif  // #ifdef OPEN_SMART_ILI9327
}

void UTFT::_set_direction_registers(byte mode)
{
	/*for(int p=2;p<10;p++) {
    pinMode(p,OUTPUT);
  } */
  pinMode(4,OUTPUT);
  for(int p=6;p<12;p++) {
    pinMode(p,OUTPUT);
  }
  pinMode(13,OUTPUT);
  
  // Set the TFT_RD pin permanently HIGH as it is not supported by UTFT
  pinMode(A0, OUTPUT);
  digitalWrite(A0, 1); // подать на вывод RD дисплея, лог.1    
}

void UTFT::_fast_fill_16(int ch, int cl, long pix)
{
}

void UTFT::_fast_fill_8(int ch, long pix)
{
	long blocks;
    #ifdef OPEN_SMART_ILI9327
      PORTB &= 0x4F;
      PORTB |= (ch & 0x2C) << 2;
      PORTG &= 0xDF;
      PORTG |= (ch & 0x10) << 1;
      PORTH &= 0x87;
      PORTH |= ((ch & 0x03) << 5 ) | ((ch & 0xC0) >> 3);
      pulse_low(P_WR, B_WR);
    #else
      PORTH &= ~0x78;
      PORTH |= ((ch & 0x03)<<5)+((ch & 0xC0)>>3);
      PORTG &= ~0x20;
      PORTG |= (ch & 0x10)<<1;
      PORTE &= ~0x38;
      PORTE |=((ch & 0x20)>>2)+ ((ch & 0x0C)<<2);
      pulse_low(P_WR, B_WR);
    #endif

	blocks = pix/16;
	for (int i=0; i<blocks; i++) {
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
	}
	
  if ((pix % 16) != 0) {
		for (int i=0; i<(pix % 16)+1; i++) {
			pulse_low(P_WR, B_WR);
      pulse_low(P_WR, B_WR);
		}
  }
}
