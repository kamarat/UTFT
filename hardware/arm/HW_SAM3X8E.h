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
    REG_PIOC_OWER = 0x25E00000; // PC29, PC27, PC26, PC22, PC21 enable
    REG_PIOC_OWDR = 0xDA1FFFFF; // others disable
    //REG_PIOC_OER = 0x00400000;
    REG_PIOC_ODSR = ((uint32_t)(VL & 0x11) << 22) | ((uint32_t)(VL & 0x02) << 20) | ((uint32_t)(VL & 0x04) << 27) | 
                    ((uint32_t)(VL & 0x40) << 18) | ((uint32_t)(VL & 0x80) << 16);
    
    REG_PIOD_OWER = 0x00000080; // PD7 enable
    REG_PIOD_OWDR = 0xFFFFFF7F; // others disable
    //REG_PIOD_OER = 0x00000080;
    REG_PIOD_ODSR = (uint32_t)(VL & 0x08) << 4;
    
    REG_PIOB_OWER = 0x08000000; // PB27 enable
    REG_PIOB_OWDR = 0xF7FFFFFF; // others disable
    //REG_PIOB_OER = 0x08000000;
    REG_PIOB_ODSR = (uint32_t)(VL & 0x20) << 22;
    
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
      REG_PIOC_OWER = 0x25E00000; // PC29, PC27, PC26, PC22, PC21 enable
      REG_PIOC_OWDR = 0xDA1FFFFF; // others disable
      //REG_PIOC_OER = 0x00400000;
      REG_PIOC_ODSR = ((int)(ch & 0x11) << 22) | ((int)(ch & 0x02) << 20) | ((int)(ch & 0x04) << 27) | 
                      ((int)(ch & 0x40) << 18) | ((int)(ch & 0x80) << 16);
      
      REG_PIOD_OWER = 0x00000080; // PD7 enable
      REG_PIOD_OWDR = 0xFFFFFF7F; // others disable
      //REG_PIOD_OER = 0x00000080;
      REG_PIOD_ODSR = (uint32_t)(ch & 0x08) << 4;
      
      REG_PIOB_OWER = 0x08000000; // PB27 enable
      REG_PIOB_OWDR = 0xF7FFFFFF; // others disable
      //REG_PIOB_OER = 0x08000000;
      REG_PIOB_ODSR = (uint32_t)(ch & 0x20) << 22;
      
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
