#define _CRT_SECURE_NO_WARNINGS
#include "func.h"

#include <stdint.h>
#include <string.h>

void func_5(uint32_t* buf)
{
	for (uint32_t i = 0; i < 10; i++)
	{
		buf[i] = i + i;
    }
    
}
