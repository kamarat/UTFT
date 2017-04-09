void UTFT::_hw_special_init()
{
}

void UTFT::LCD_Writ_Bus(char VL)
{   
		PORTH &= ~0x78;
		PORTH |= ((VL & 0x03)<<5)+((VL & 0xC0)>>3);
                PORTG &= ~0x20;
		PORTG |= (VL & 0x10)<<1;
		PORTE &= ~0x38;
		PORTE |=((VL & 0x20)>>2)+ ((VL& 0x0C)<<2);
                pulse_low(P_WR, B_WR);
}

void UTFT::_set_direction_registers(byte mode)
{
	for(int p=2;p<10;p++)  {   pinMode(p,OUTPUT);  } 
       pinMode(A0, OUTPUT);  digitalWrite(A0, 1); // подать на вывод RD дисплея, лог.1    
}

void UTFT::_fast_fill_16(int ch, int cl, long pix)
{
}

void UTFT::_fast_fill_8(int ch, long pix)
{
	long blocks;
		PORTH &= ~0x78;
		PORTH |= ((ch & 0x03)<<5)+((ch & 0xC0)>>3);
                PORTG &= ~0x20;
		PORTG |= (ch & 0x10)<<1;
		PORTE &= ~0x38;
		PORTE |=((ch & 0x20)>>2)+ ((ch & 0x0C)<<2);
                pulse_low(P_WR, B_WR);

	blocks = pix/16;
	for (int i=0; i<blocks; i++)
	{

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
	if ((pix % 16) != 0)
		for (int i=0; i<(pix % 16)+1; i++)
		{
			pulse_low(P_WR, B_WR);pulse_low(P_WR, B_WR);
		}
}
