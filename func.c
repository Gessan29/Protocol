#define _CRT_SECURE_NO_WARNINGS
#include "func.h"

#include <stdint.h>
#include <string.h>

void func_5(uint8_t* buf, uint8_t* status)
{
	for (uint32_t i = 0; i < 10; i++)
	{
		buf[i] = i;
    }
	*status = STATUS_OK;
    
}
