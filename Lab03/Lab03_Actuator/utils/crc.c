
#include "crc.h"
#include <stdio.h>

int calc_SAE_J1850(int data[],int crc_len)
{
	int idx, crc, temp, temp1, temp2, idy;
	crc = 0;
	idx = 0;
	idy = 0;
	temp = 0;
	temp1 = 0;
	temp2 = 0;
	for (idx = 0; idx < crc_len; idx++)
	{
		if (idx == 0) {
			temp1 = 0;
		}
		else {
			temp1 = data[crc_len - idx];
		}
		crc = (crc ^ temp1);
		for (idy = 8; idy > 0; idy--) {
			//Save the value before top bit is shiftout
			temp2 = crc;
			crc <<= 1;
			if (0 != (temp2 & 128)) {
				crc ^=  0x1D;
			}
		}
	}
	return crc;
}
