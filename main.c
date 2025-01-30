#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

int main()
{
    unsigned int input_number; // переменная для передачи записи и передачи в struct for_transfer чисел
    
    
    printf("Choose set (1) or get (0) command (cmd): ");
    scanf("%u", &input_number);

    if (input_number < 0 || input_number > 1)
    {
        printf("Error, overflow!");
        return -1;
    }

    data.cmd = (uint8_t)input_number;
    
    switch (data.cmd)
    {
    case 0:
        printf("Choose code parametrs: 5,6,8  ");
        scanf("%u", &input_number);
        if (input_number == 5 || input_number == 6 || input_number == 8 )
        {
            data.status = (uint8_t)input_number;
            printf("\nYour write cmd: %u\nYour write code parametrs: %u\n", data.cmd, data.status);
            data.buf_size = 7;
            data.buf = (uint8_t*)malloc(data.buf_size * sizeof(uint8_t));
            if (data.buf == NULL)
            {
                printf("Memory allocation failed\n");
                return -1;
            }
            serialize_reply(&data);
            printf("Paket:\n");
            for (int a = 0; a < 7; a++) {
                printf("0x%02X\n", data.buf[a]);
            }
            printf("\n");
        }
        else {
            printf("Error, overflow!");
            return -1;
        }
        
        break;

    case 1:
        printf("Choose code parametrs: 0,1,2,3,4,7,9  ");
        scanf("%u", &input_number);
        if (input_number == 0 || input_number == 1 || input_number == 2 || input_number == 3 || input_number == 4 || input_number == 7 || input_number == 9 )
        {
            data.value = (uint8_t*)malloc(4 * sizeof(uint8_t));
            if (data.value == NULL)
            {
                printf("Memory allocation failed\n");
                return -1;
            }
            data.status = (uint8_t)input_number;
            switch (data.status)
            {
            case APPLY_VOLTAGE_RL1:
                printf("%d: Set low (0) or high (1) level voltage on RL1\n", data.status);
                printf("Write code command [%u-%u]: ", VALUE_RANGES[data.status].min, VALUE_RANGES[data.status].max);
                scanf("%u", &data.value[0]);
                if (data.value[0] < VALUE_RANGES[data.status].min || data.value[0] > VALUE_RANGES[data.status].max)
                {
                    printf("Error, overflow!");
                    return -1;
                }
                break;

            case TEST_VOLTAGE_4_POINT:
                printf("%d: 4 voltage check points test\n", data.status);
                printf("Choose one check point:\n1: -%d\n2: +%d.3\n3: +%d\n4: +%d\n", VALUE_RANGES[data.status].voltage_4[0], VALUE_RANGES[data.status].voltage_4[1], VALUE_RANGES[data.status].voltage_4[2], VALUE_RANGES[data.status].voltage_4[3]);
                scanf("%u", &data.value[0]);
                if (data.value[0] < VALUE_RANGES[data.status].min || data.value[0] > VALUE_RANGES[data.status].max)
                {
                    printf("Error, overflow!");
                    return -1;
                }
                break;

            case ANALYSIS_VOLTAGE_CORRENT:
                printf("%d: Analysis voltage\n", data.status);
                printf("Write code command. 0 - voltage; 1 - corrent  [%u-%u]: ", VALUE_RANGES[data.status].min, VALUE_RANGES[data.status].max);
                scanf("%u", &data.value[0]);
                if (data.value[0] < VALUE_RANGES[data.status].min || data.value[0] > VALUE_RANGES[data.status].max)
                {
                    printf("Error, overflow!");
                    return -1;
                }
                break;

            case APPLY_VOLTAGE_RL2:
                printf("%d: Set low (0) or high (1) level voltage on RL2\n", data.status);
                printf("Write code command [%u-%u]: ", VALUE_RANGES[data.status].min, VALUE_RANGES[data.status].max);
                scanf("%u", &data.value[0]);
                if (data.value[0] < VALUE_RANGES[data.status].min || data.value[0] > VALUE_RANGES[data.status].max)
                {
                    printf("Error, overflow!");
                    return -1;
                }
                break;

            case TEST_VOLTAGE_11_POINT:
                printf("%d: 11 voltage check points test\n", data.status);
                printf("Choose one check point:\n");
                for (int a = 0; a < 11; a++) {
                    printf("%d: %.3fV\n", a, (float)VALUE_RANGES[data.status].voltage_11[a] /1000);
                }
                scanf("%u", &data.value[0]);
                if (data.value[0] < VALUE_RANGES[data.status].min || data.value[0] > VALUE_RANGES[data.status].max)
                {
                    printf("Error, overflow!");
                    return -1;
                }
                break;

            case APPLY_VOLTAGE_5_RL:
                printf("%d: Set low (0) or high (1) level voltage on RL3-RL7\n", data.status);
                printf("Write code command [%u-%u]: ", VALUE_RANGES[data.status].min, VALUE_RANGES[data.status].max);
                scanf("%u", &data.value[0]);
                if (data.value[0] < VALUE_RANGES[data.status].min || data.value[0] > VALUE_RANGES[data.status].max)
                {
                    printf("Error, overflow!");
                    return -1;
                }
                break;

            case MASSAGE_NMEA:
                printf("%d: Choose which second to send (HHMMSS.SSS)\n", data.status);
                printf("Write second [%u-%u]: ", VALUE_RANGES[data.status].min, VALUE_RANGES[data.status].max);
                scanf("%u", &data.value[0]);
                if (data.value[0] < VALUE_RANGES[data.status].min || data.value[0] > VALUE_RANGES[data.status].max)
                {
                    printf("Error, overflow!");
                    return -1;
                }
                break;
            }
            printf("\nYour write cmd: %u\nYour write code parametrs: %u\nYour write command: %u\n", data.cmd, data.status, data.value[0]);
            data.buf_size = 11;
            data.buf = (uint8_t*)malloc(data.buf_size * sizeof(uint8_t));
            if (data.buf == NULL)
            {
                printf("Memory allocation failed\n");
                return -1;
            }
            serialize_reply(&data);
            free(data.value);
            printf("Paket:\n");
            for (int a = 0; a < 11; a++) {
                printf("0x%02X\n", data.buf[a]);
            }
            printf("\n");
        }
        else {
            printf("Error, overflow!");
            return -1;
        }
        break;
    }
    
    deserialize_reply(data.buf, data.buf_size, &priem);
    free(data.buf);
    if (data.buf_size == 11) {
        printf("Received data:\n0xAA\n0x%X\n0x%X\n0x%X\n0x%X\n", priem.data >> 0, priem.data >> 8, priem.cmd, priem.status);
        printf("0x%X\n0x%X\n0x%X\n0x%X\n", priem.value[0], priem.value[1], priem.value[2], priem.value[3]);
        printf("0x%X\n0x%X\n", priem.crc >> 0 & 0xff, priem.crc >> 8);
    }
    else {
        printf("Received data:\n0xAA\n0x%X\n0x%X\n0x%X\n", priem.data >> 0, priem.data >> 8, priem.cmd);
        printf("0x%X\n0x%X\n0x%X\n", priem.status, priem.crc >> 0 & 0xff, priem.crc >> 8);
    }

    choose_command(&priem.status, &priem.value, &priem.value_size);
    transmission(&data, &priem);
    serialize_reply(&data);

    printf("\nPaket:\n");
    switch (data.buf[4]) {
    case STATUS_OK:
        printf("Successfully!\n");
        break;
    case STATUS_EXEC_ERROR:
        printf("Command execution error!\n"); 
        break;
    case STATUS_INVALID_CMD:
        printf("A non-existent team\n");
        break;
    case STATUS_TIMED_OUT:
        printf("Command execution time exceeded\n");
        break;
    case STATUS_INVALID_SIZE:
        printf("Command data size error\n");
        break;
    }
    for (int a = 0; a < data.buf_size; a++) {
        printf("0x%02X\n", data.buf[a]);
    }
    printf("\n");

    free(priem.value);
    
    return 0;
}