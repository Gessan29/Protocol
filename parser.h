#ifndef PARSER_H
#define	PARSER_H
#include <stdint.h>
#include "hardware.h"
#define MAX_DATA_SIZE 16 
#define SYNC_BYTE 0xAA 
#define TIMEOUT_RX 500 // ����� ���������� �������???
#define DATA_SIZE_OFFSET 3 // 2 ����� crc + ��� �������
#define SIZE_PAKET 7 // ���������� + 2 ����� �������� ������ + cmd + status + 2 CRC
// �������
#define CMD_GET 0
#define CMD_SET 1

//���� ������
#define STATUS_OK 0
#define STATUS_EXEC_ERROR 1 // ������ ���������� �������
#define STATUS_INVALID_CMD 2 // �������������� �������
#define STATUS_TIMED_OUT 3 // ��������� ����� ���������� �������
#define STATUS_INVALID_SIZE 4 // ������ ������� ������ �������

//�������� ������� ��� ������� ���������
#define APPLY_VOLTAGE_RL1 0 // ������� ������ ���. 0 ��� 1 �� RL1 ��� ��������� ���� ������� 12�
#define TEST_VOLTAGE_4_POINT 1 // ������� �������� ����. � 4 ����������� ������ +6 -6 +5 +3.3�
#define ANALYSIS_VOLTAGE_CORRENT 2 // ������� ��������� ����. � ���� �������
#define APPLY_VOLTAGE_RL2 3 // ������� ���. 0 ��� 1 �� RL2 ��� ��������� R1 � R22
#define TEST_VOLTAGE_11_POINT 4 // ������� �������� ����. � 12 �����. ������
#define TEST_CORRENT_LASER 5 // ������� ��������� ����� ���� ��������� ����� 
#define TEST_VOLTAGE_PELTIE 6 // ������� ��������� ���������� �������� �������  
#define APPLY_VOLTAGE_5_RL 7 // ������� ������ ���. 0 ��� 1 ��� ���������� RL3-RL7
#define MASSAGE_RS232 8 // ������� �������� �������������� ������ �� RS232
#define MASSAGE_NMEA 9 // ������� �������� ������������� ������� NMEA �� GPS ����� RS232

#define CRC_INIT 0xffff // ��� �������� ����������� ����� CRC

enum parser_result {
    PARSER_OK,
    PARSER_ERROR,
    PARSER_DONE,
};

struct for_receiving {
    uint16_t data;
    size_t value_size;
    uint8_t cmd;
    uint8_t status;
    uint8_t* value;
    uint16_t crc;
    
};

struct for_transfer
{
    uint8_t* buf;
    size_t buf_size;
    uint8_t cmd;
    uint8_t status;
    uint8_t* value;
};

struct value_range {
    uint32_t min;
    uint32_t max;
    uint32_t voltage_4[4];
    uint32_t voltage_11[11];
};

 static const struct value_range VALUE_RANGES[] = {
   [APPLY_VOLTAGE_RL1] = {.min = 0, .max = 1},
   [TEST_VOLTAGE_4_POINT] = {.min = 1, .max = 4, .voltage_4 = {6, 3, 5, 6}},
   [ANALYSIS_VOLTAGE_CORRENT] = {.min = 0, .max = 1},
   [APPLY_VOLTAGE_RL2] = {.min = 0, .max = 1},
   [TEST_VOLTAGE_11_POINT] = {.min = 0, .max = 10, .voltage_11 = {1200, 1800, 2500, 5500, 4500, 5500, 5500, 1800, 2500, 5000, 2048}},
   [TEST_CORRENT_LASER] = {1},
   [TEST_VOLTAGE_PELTIE] = {1},
   [APPLY_VOLTAGE_5_RL] = {.min = 0, .max = 1},
   [MASSAGE_RS232] = {1},
   [MASSAGE_NMEA] =  {.min = 0, .max = 59},
};

 struct for_transfer data;
 struct for_receiving priem;
void serialize_reply(struct for_transfer* data);
void deserialize_reply(const uint8_t* buf, size_t buf_size, struct for_receiving* priem);
void choose_command(uint8_t* status, uint8_t** value, size_t* value_size);// ������ ��� ������ �������
void transmission(struct for_transfer* data, struct for_receiving* priem); // ������� ��� ������ �� for_transfer �� for_receiving
#endif