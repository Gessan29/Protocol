// Протокол общения компа с платой стенда и платой газоанализатора, CRC - проверка целостности
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//#include <string>
#include <stdint.h>

#define MAX_DATA_SIZE 16 
#define SYNC_BYTE 0xAA 
#define TIMEOUT_RX 500 // время выполнения команды???
#define DATA_SIZE_OFFSET 3 //???
// Команды
#define CMD_GET 0
#define CMD_SET 1

//коды ошибок
#define STATUS_OK 0
#define STATUS_EXEC_ERROR 1 // Ошибка выполнения команды
#define STATUS_INVALID_CMD 2 // Несуществующая команда
#define STATUS_TIMED_OUT 3 // Превышено время выполнения команды
#define STATUS_INVALID_SIZE 4 // Ошибка размера данных команды

//Тестовые команды для отладки протокола
#define VOLTAGE_SUPPLY 0 // напряжение питания
#define CURRENT_SUPPLY 1 // ток потребления

#define CRC_INIT 0xffff // для подсчета контрольной суммы CRC

struct protocol_parser {
    enum {
        STATE_SYNC,
        STATE_SIZE_L,
        STATE_SIZE_H,
        STATE_CMD,
        STATE_DATA,
        STATE_CRC_L,
        STATE_CRC_H,
    } state;

    uint8_t buffer[MAX_DATA_SIZE];
    uint16_t buffer_length;// кол-во байт в буфере
    uint16_t data_size;// полезные данные 
    uint8_t cmd;
    uint16_t crc;
};

enum parser_result {
    PARSER_OK,
    PARSER_ERROR,
    PARSER_DONE,
};

struct for_receiving{
    uint8_t data_size_l;
    uint8_t data_size_h;
    uint8_t cmd;
    uint8_t error;
    uint32_t value;
    uint8_t crc_l;
    uint8_t crc_h;
};

struct for_transfer
{
    uint8_t buf[11];
    uint8_t cmd;
    uint8_t status;
    uint32_t value;
};

struct value_range {
    uint32_t min;
    uint32_t max;
};

static const struct value_range VALUE_RANGES[] = {
    [VOLTAGE_SUPPLY] = {.min = 0, .max = 12}, // V
    [CURRENT_SUPPLY] = {.min = 0, .max = 200} //mA
};

int main()
{
    static void serialize_reply(uint8_t * buf, size_t buf_size, uint8_t cmd, uint8_t status, uint32_t value);
    static void deserialize_reply(const uint8_t * buf, size_t buf_size, uint8_t data_size_l, uint8_t data_size_h, uint8_t cmd, uint8_t error_code, uint32_t value, uint8_t crc_l, uint8_t crc_h);

    struct for_transfer data;
    struct for_receiving priem;
    unsigned int input_number; // переменная для передачи записи и передачи в struct for_transfer чисел

    //----------------------------------------------------------------------------------------
    printf("Choose set (1) or get (0) command (cmd): ");
    scanf("%u", &input_number);
    if (input_number < 0 || input_number > 1)
    {
        printf("Error, overflow!");
        return -1;
    }
    data.cmd = (uint8_t)input_number;
    

    printf("Choose code parametrs from 0 to 1: ");
    scanf("%u", &input_number);
    if (input_number < 0 || input_number > 1)
    {
        printf("Error, overflow!");
        return -1;
    }
    data.status = (uint8_t)input_number;
    switch (data.status)
    {
    case VOLTAGE_SUPPLY:
        printf("%d: VOLTAGE_SUPPLY\n", data.status);
        printf("Write code command in the range [%u-%u]V: ", VALUE_RANGES[data.status].min, VALUE_RANGES[data.status].max);
        scanf("%u", &data.value);
        if (data.value < VALUE_RANGES[data.status].min || data.value > VALUE_RANGES[data.status].max)
        {
            printf("Error, overflow!");
            return -1;
        }
        break;
    case CURRENT_SUPPLY:
        printf("%d: CURRENT_SUPPLY\n", data.status);
        printf("Write code command in the range [%u-%u]mA: ", VALUE_RANGES[data.status].min, VALUE_RANGES[data.status].max);
        scanf("%u", &data.value);
        if (data.value < VALUE_RANGES[data.status].min || data.value > VALUE_RANGES[data.status].max)
        {
            printf("Error, overflow!");
            return -1;
        }
        break;
    }

    printf("Your write cmd: %u\nYour write code parametrs: %u\nYour write command: %u\n", data.cmd, data.status, data.value);

    serialize_reply(data.buf, sizeof(data.buf), data.cmd, data.status, data.value );
    printf("Paket:\n");
    for (int a = 0; a < 11; a++) {
        printf("0x%02X\n", data.buf[a]);
    }
    printf("\n");

    deserialize_reply(data.buf, sizeof(data.buf), priem.data_size_l, priem.data_size_h, priem.cmd, priem.error, priem.value, priem.crc_l, priem.crc_h);

    printf("Received data:\nUseful data (L-H):\n0x%02X\n0x%02X\nCMD:\n0x%02X\n", priem.data_size_l, priem.data_size_h, priem.cmd);
    printf("Status error:\n0x%02X", priem.error);
    switch (priem.error){ 
    case STATUS_OK:
        printf("  Successfully!");
        break;
    case STATUS_EXEC_ERROR:
        printf("  Сommand execution error\n");
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
    printf("Value:\n0x%02X\n", priem.value);
    printf("CRC (L-H):\n0x%02X\n0x%02X\n", priem.crc_l, priem.crc_h);
    
    return 0;
}



static void init_protocol(struct protocol_parser* parser) {
    parser->state = STATE_SYNC; // all other fields will be initialized during parsing
}

static const uint16_t crc16_table[256]; // defined below


static uint16_t update_crc(uint16_t crc, uint8_t byte)
{
    return crc16_table[(crc ^ byte) & 0xFF] ^ (crc >> 8);
}


static uint16_t calculate_crc(const uint8_t* array, int size) {
    uint16_t crc = CRC_INIT; // #define CRC_INIT 0xffff
    int i;
    for (i = 0; i < size; i++) {
        crc = update_crc(crc, array[i]);
    }
    return crc;
}

static void deserialize_reply(const uint8_t* buf, size_t buf_size, uint8_t data_size_l, uint8_t data_size_h, uint8_t cmd, uint8_t error_code, uint32_t value, uint8_t crc_l, uint8_t crc_h)
{
    static const uint16_t PAYLOAD_SIZE = 5;
    if (buf_size < 11) {
        //printf("Error paket\n");
        return;
    }
    data_size_l = buf[1];
    data_size_h = buf[2];
    cmd = buf[3];
    error_code = buf[4];
    value = (uint32_t)buf[8] << 24 | (uint32_t)buf[7] << 16 | (uint32_t)buf[6] << 8 | (uint32_t)buf[5] << 0;
    uint16_t crc = calculate_crc(buf + 3, PAYLOAD_SIZE + 1);
    crc_l = crc << 0;
    crc_h = crc << 8;
    printf("Size paket (Bytes): %u\n", buf_size);

}


static void serialize_reply(uint8_t* buf, size_t buf_size,
    uint8_t cmd, uint8_t status, uint32_t value) {
    if (buf_size < 11) {
        //printf("Error paket\n");
        return;
    }

    static const uint16_t PAYLOAD_SIZE = 5;
    buf[0] = SYNC_BYTE;
    buf[1] = ((PAYLOAD_SIZE + DATA_SIZE_OFFSET) >> 0) & 0xff;
    buf[2] = ((PAYLOAD_SIZE + DATA_SIZE_OFFSET) >> 8) & 0xff;
    buf[3] = cmd;
    buf[4] = status;
    buf[5] = (value >> 0) & 0xff;
    buf[6] = (value >> 8) & 0xff;
    buf[7] = (value >> 16) & 0xff;
    buf[8] = (value >> 24) & 0xff;
    uint16_t crc = calculate_crc(buf + 3, PAYLOAD_SIZE + 1);
    buf[9] = (crc >> 0) & 0xff;
    buf[10] = (crc >> 8) & 0xff;
}


static const uint16_t crc16_table[256] =
{
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040,
};

