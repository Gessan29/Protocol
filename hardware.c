#define _CRT_SECURE_NO_WARNINGS
#include "hardware.h"
#include <stdint.h>
#include <string.h>
uint16_t voltage;

void func_0(uint8_t* buf, uint8_t* status)
{
	*status = STATUS_OK;
}

void func_1(uint8_t* buf, uint8_t* status)
{
	switch (buf[0])
	{
	case 1:
		voltage = 600;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;
	
	case 2:
		voltage = 330;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;
	
	case 3:
		voltage = 500;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;
	
	case 4:
		voltage = 600;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;
	default:
		*status = STATUS_INVALID_CMD;
		break;
	}
}

void func_2(uint8_t* buf, uint8_t* status)
{
	switch (buf[0])
	{
	case 0: // voltage
		voltage = 1200;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;

	case 1: // current
		voltage = 500;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;
	default:
		*status = STATUS_INVALID_CMD;
		break;
	}
}

void func_3(uint8_t* buf, uint8_t* status)
{
	*status = STATUS_OK;
}

void func_4(uint8_t* buf, uint8_t* status)
{
	switch (buf[0])
	{
	case 0:
		voltage = 120;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;
	case 1:
		voltage = 180;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;

	case 2:
		voltage = 250;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;

	case 3:
		voltage = 550;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;

	case 4:
		voltage = 450;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;
	case 5:
		voltage = 550;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;

	case 6:
		voltage = 550;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;

	case 7:
		voltage = 180;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;

	case 8:
		voltage = 250;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;
	case 9:
		voltage = 500;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;

	case 10:
		voltage = 2048;
		buf[0] = (uint8_t)(voltage & 0xFF);
		buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
		*status = STATUS_OK;
		break;
	default:
		*status = STATUS_INVALID_CMD;
		break;
	}
}

void func_5(uint8_t* buf, uint8_t* status)
{
	voltage = 0;
	for (int i = 0; i < 200; i += 2)
	{
		buf[i] = (uint8_t)(voltage & 0xFF);
		buf[i + 1] = (uint8_t)(voltage >> 8 & 0xFF);
		voltage += 10;
    }
	*status = STATUS_OK;
    
}

void func_6(uint8_t* buf, uint8_t* status)
{
	voltage = 550;
	buf[0] = (uint8_t)(voltage & 0xFF);
	buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
	buf[2] = 0;
	buf[3] = 0;
	*status = STATUS_OK;
}

void func_7(uint8_t* buf, uint8_t* status)
{
	*status = STATUS_OK;
}

void func_8(uint8_t* buf, uint8_t* status)
{
	*status = STATUS_OK;
}

void func_9(uint8_t* buf, uint8_t* status)
{
	buf[1] = 0; //12:35:0...
	buf[2] = 5;
	buf[3] = 3;
	buf[4] = 2;
	buf[5] = 1;
	buf[6] = 0;
	buf[7] = 0;
	*status = STATUS_OK;
}