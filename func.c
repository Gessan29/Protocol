#define _CRT_SECURE_NO_WARNINGS
#include "func.h"
#include <stdint.h>
#include <string.h>

void func_0(uint8_t* buf, uint8_t* status)
{
	*status = STATUS_OK;
}

void func_1(uint8_t* buf, uint8_t* status)
{
	uint16_t voltage = 330;
	buf[0] = (uint8_t)(voltage & 0xFF);
	buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
	*status = STATUS_OK;
}

void func_2(uint8_t* buf, uint8_t* status)
{
	uint16_t voltage = 500;
	buf[0] = (uint8_t)(voltage & 0xFF);
	buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
	*status = STATUS_OK;
}

void func_3(uint8_t* buf, uint8_t* status)
{
	*status = STATUS_OK;
}

void func_4(uint8_t* buf, uint8_t* status)
{
	uint16_t voltage = 330;
	buf[0] = (uint8_t)(voltage & 0xFF);
	buf[1] = (uint8_t)(voltage >> 8 & 0xFF);
	*status = STATUS_OK;
}

void func_5(uint8_t* buf, uint8_t* status)
{
	uint16_t voltage = 0;
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
	uint16_t voltage = 0;
	for (int i = 0; i < 20; i += 2)
	{
		buf[i] = (uint8_t)(voltage & 0xFF);
		buf[i + 1] = (uint8_t)(voltage >> 8 & 0xFF);
		voltage += 5;
	}
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
	*status = STATUS_OK;
}