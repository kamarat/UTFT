// *** Hardwarespecific functions ***
#include "UTFT.h"

void UTFT::_hw_special_init()
{
  // Set the TFT_RD pin permanently HIGH as it is not supported by UTFT
  pinMode(A0, OUTPUT);
  digitalWrite(A0, 1); // подать на вывод RD дисплея, лог.1
}

void UTFT::LCD_Writ_Bus(char VL)
{
  #ifdef OPEN_SMART_ILI9327
    /* Pins LCD - DUE
     * D0 -  8 (PC22)
     * D1 -  9 (PC21)
     * D2 - 10 (PC29)
     * D3 - 11 (PD7)
     * D4 -  4 (PC26)
     * D5 - 13 (PB27)
     * D6 -  6 (PC24)
     * D7 -  7 (PC23)
     */
    /*REG_PIOB_OWER = 0x08000000; // PB27 enable
    REG_PIOB_OWDR = 0xF7FFFFFF; // others disable
    REG_PIOB_ODSR = (VL & 0x20) << 22;
    REG_PIOC_OWER = 0x25E00000; // PC29, PC27, PC26, PC22, PC21 enable
    REG_PIOC_OWDR = 0xDA1FFFFF;
    REG_PIOC_ODSR |= ((VL & 0x11) << 22) | ((VL & 0x02) << 20) | ((VL & 0x04) << 27) | ((VL & 0x40) << 18) | ((VL & 0x80) << 16);
    REG_PIOD_OWER = 0x00000080; // PD7 enable
    REG_PIOD_OWDR = 0xFFFFFF7F;
    REG_PIOD_ODSR = (VL & 0x08) << 4;*/
    digitalWrite(8, VL & 0x01);
    digitalWrite(9, VL & 0x02);
    digitalWrite(10, VL & 0x04);
    digitalWrite(11, VL & 0x08);
    digitalWrite(4, VL & 0x10);
    digitalWrite(13, VL & 0x20);
    digitalWrite(6, VL & 0x40);
    digitalWrite(7, VL & 0x80);
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
}

void UTFT::_fast_fill_16(int ch, int cl, long pix)
{
}

void UTFT::_fast_fill_8(int ch, long pix)
{
	long blocks;
    #ifdef OPEN_SMART_ILI9327
      /*REG_PIOB_OWER = 0x08000000; // PB27 enable
      REG_PIOB_OWDR = 0xF7FFFFFF; // others disable
      REG_PIOB_ODSR = (ch & 0x20) << 22;
      REG_PIOC_OWER = 0x25E00000; // PC29, PC27, PC26, PC22, PC21 enable
      REG_PIOC_OWDR = 0xDA1FFFFF;
      REG_PIOC_ODSR |= ((ch & 0x11) << 22) | ((ch & 0x02) << 20) | ((ch & 0x04) << 27) | ((ch & 0x40) << 18) | ((ch & 0x80) << 16);
      REG_PIOD_OWER = 0x00000080; // PD7 enable
      REG_PIOD_OWDR = 0xFFFFFF7F;
      REG_PIOD_ODSR = (ch & 0x08) << 4;
      pulse_low(P_WR, B_WR);*/
      digitalWrite(8, ch & 0x01);
      digitalWrite(9, ch & 0x02);
      digitalWrite(10, ch & 0x04);
      digitalWrite(11, ch & 0x08);
      digitalWrite(4, ch & 0x10);
      digitalWrite(13, ch & 0x20);
      digitalWrite(6, ch & 0x40);
      digitalWrite(7, ch & 0x80);
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
