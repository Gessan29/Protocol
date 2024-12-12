// Протокол общения компа с платой стенда и платой газоанализатора, CRC - проверка целостности
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Header.h"

//void serialize_reply(struct for_transfer* data);
//void deserialize_reply(const uint8_t* buf, size_t buf_size, struct for_receiving* priem);

int main()
{

    unsigned int input_number; // переменная для передачи записи и передачи в struct for_transfer чисел
    data.buf_size = 7;
    //----------------------------------------------------------------------------------------
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
        printf("Choose code parametrs: 5,6,8,9  ");
        scanf("%u", &input_number);
        if (input_number == 5 || input_number == 6 || input_number == 8 || input_number == 9)
        {
            data.status = (uint8_t)input_number;
            printf("\nYour write cmd: %u\nYour write code parametrs: %u\n", data.cmd, data.status);
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
        printf("Choose code parametrs: 0,1,2,3,4,7  ");
        scanf("%u", &input_number);
        if (input_number == 0 || input_number == 1 || input_number == 2 || input_number == 3 || input_number == 4 || input_number == 7)
        {
            data.status = (uint8_t)input_number;
            switch (data.status)
            {
            case APPLY_VOLTAGE_RL1:
                printf("%d: Set low (0) or high (1) level voltage on RL1\n", data.status);
                printf("Write code command [%u-%u]: ", VALUE_RANGES[data.status].min, VALUE_RANGES[data.status].max);
                scanf("%u", &data.value);
                if (data.value < VALUE_RANGES[data.status].min || data.value > VALUE_RANGES[data.status].max)
                {
                    printf("Error, overflow!");
                    return -1;
                }
                break;

            case TEST_VOLTAGE_4_POINT:
                printf("%d: CURRENT_SUPPLY\n", data.status);
                printf("Write code command in the range [%u-%u]: ", VALUE_RANGES[data.status].min, VALUE_RANGES[data.status].max);
                scanf("%u", &data.value);
                if (data.value < VALUE_RANGES[data.status].min || data.value > VALUE_RANGES[data.status].max)
                {
                    printf("Error, overflow!");
                    return -1;
                }
                break;

            case ANALYSIS_VOLTAGE_CORRENT:
                printf("%d: Analysis voltage\n", data.status);
                printf("Write code command in the range [%u-%u]: ", VALUE_RANGES[data.status].min, VALUE_RANGES[data.status].max);
                scanf("%u", &data.value);
                if (data.value < VALUE_RANGES[data.status].min || data.value > VALUE_RANGES[data.status].max)
                {
                    printf("Error, overflow!");
                    return -1;
                }
                break;

            case APPLY_VOLTAGE_RL2:
                printf("%d: Set low (0) or high (1) level voltage on RL2\n", data.status);
                printf("Write code command [%u-%u]: ", VALUE_RANGES[data.status].min, VALUE_RANGES[data.status].max);
                scanf("%u", &data.value);
                if (data.value < VALUE_RANGES[data.status].min || data.value > VALUE_RANGES[data.status].max)
                {
                    printf("Error, overflow!");
                    return -1;
                }
                break;

            case TEST_VOLTAGE_11_POINT:
                printf("%d: Test voltage 11 point\n", data.status);
                printf("Write code command in the range [%u-%u]: ", VALUE_RANGES[data.status].min, VALUE_RANGES[data.status].max);
                scanf("%u", &data.value);
                if (data.value < VALUE_RANGES[data.status].min || data.value > VALUE_RANGES[data.status].max)
                {
                    printf("Error, overflow!");
                    return -1;
                }
                break;

            case APPLY_VOLTAGE_5_RL:
                printf("%d: Set low (0) or high (1) level voltage on RL3-RL7\n", data.status);
                printf("Write code command [%u-%u]: ", VALUE_RANGES[data.status].min, VALUE_RANGES[data.status].max);
                scanf("%u", &data.value);
                if (data.value < VALUE_RANGES[data.status].min || data.value > VALUE_RANGES[data.status].max)
                {
                    printf("Error, overflow!");
                    return -1;
                }
                break;
            }
            printf("\nYour write cmd: %u\nYour write code parametrs: %u\nYour write command: %u\n", data.cmd, data.status, data.value);
            data.buf_size = 11;
            serialize_reply(&data);
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
    if (data.buf_size == 11) {
        printf("Received data:\n0xAA\n0x%02X\n0x%02X\n0x%02X\n", priem.data_size_l, priem.data_size_h, priem.cmd);
        printf("0x%02X", priem.status);
        switch (priem.status) {
        case STATUS_OK:
            printf("  Successfully!\n");
            break;
        case STATUS_EXEC_ERROR:
            printf("  Successfully!\n"); //(Сommand execution error)
            break;
        case STATUS_INVALID_CMD:
            printf("  A non-existent team\n");
            break;
        case STATUS_TIMED_OUT:
            printf("  Command execution time exceeded\n");
            break;
        case STATUS_INVALID_SIZE:
            printf("  Сommand data size error\n");
            break;
        }
        printf("0x%02X\n0x%02X\n0x%02X\n0x%02X\n", priem.value[0], priem.value[1], priem.value[2], priem.value[3]);
        printf("0x%02X\n0x%02X\n", priem.crc_l, priem.crc_h);
    }
    else {
        printf("Received data:\n0xAA\n0x%02X\n0x%02X\n0x%02X\n", priem.data_size_l, priem.data_size_h, priem.cmd);
        printf("0x%02X\n0x%02X\n0x%02X\n", priem.status, priem.crc_l,priem.crc_h);
    }

    choose_command(priem.status, priem.value);
    for (uint32_t i = 0; i < 10; i++)
    {
        printf("%u\n", &priem.value[i]);
    }

    free(priem.value);
    
    return 0;
}



