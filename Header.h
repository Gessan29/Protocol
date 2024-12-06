#ifndef HEADER_H
#define	HEADER_H

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
#define APPLY_VOLTAGE_RL1 0 // команда подать лог. 1 или 0 на RL1 для замыкания цепи питания 12В
#define TEST_VOLTAGE_4_POINT 1 // команда проверка напр. в 4 контрольных точках +6 -6 +5 +3.3В
#define ANALYSIS_VOLTAGE_CORRENT 2 // команда измерение напр. и тока питания
#define APPLY_VOLTAGE_RL2 3 // Команда лог. 1 или 0 на RL2 для замыкания R1 и R22
#define TEST_VOLTAGE_11_POINT 4 // команда проверки напр. в 12 контр. точках
#define TEST_CORRENT_LASER 5 // Команда измерения формы тока лазерного диода 
#define TEST_VOLTAGE_PELTIE 6 // Команда измерения напряжения элемента Пельтье  
#define APPLY_VOLTAGE_5_RL 7 // команда подать лог. 0 или 1 для РАЗМЫКАНИЯ RL3-RL7
#define MASSAGE_RS232 8 // команда отправки заготовленного пакета по RS232
#define MASSAGE_NMEA 9 // команда отправки заготовленных пакетов NMEA на GPS через RS232 раз в сек

#define CRC_INIT 0xffff // для подсчета контрольной суммы CRC

enum parser_result {
    PARSER_OK,
    PARSER_ERROR,
    PARSER_DONE,
};

struct for_receiving {
    uint8_t data_size_l;
    uint8_t data_size_h;
    uint8_t cmd;
    uint8_t error;
    uint32_t value[4];
    uint8_t crc_l;
    uint8_t crc_h;
};

struct for_transfer
{
    uint8_t* buf;
    size_t buf_size;
    uint8_t cmd;
    uint8_t status;
    uint32_t value;
};

struct value_range {
    uint32_t min;
    uint32_t max;
};

 static const struct value_range VALUE_RANGES[] = {
   [APPLY_VOLTAGE_RL1] = {.min = 0, .max = 1},
   [TEST_VOLTAGE_4_POINT] = {.min = 0, .max = 3},
   [ANALYSIS_VOLTAGE_CORRENT] = {.min = 0, .max = 1},
   [APPLY_VOLTAGE_RL2] = {.min = 0, .max = 1},
   [TEST_VOLTAGE_11_POINT] = {.min = 0, .max = 12},
   [TEST_CORRENT_LASER] = {1},
   [TEST_VOLTAGE_PELTIE] = {1},
   [APPLY_VOLTAGE_5_RL] = {.min = 0, .max = 1},
   [MASSAGE_RS232] = {1},
   [MASSAGE_NMEA] = {1},
};

void serialize_reply(struct for_transfer* data);
void deserialize_reply(const uint8_t* buf, size_t buf_size, struct for_receiving* priem);

#endif