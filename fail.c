#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define START_CODE 0xFA
#define WRITE_CODE 0x01
#define READ_CODE 0x02

#define COMMAND_ROW 19
#define COMMAND_COL 5

// 暫存器預設值
uint8_t registers[8] = {
    0x01, // 0x00: 設備 ID
    0x00, // 0x01: 保留位
    0x32, // 0x02: 溫度
    0x50, // 0x03: 最高溫度
    0x03, // 0x04: 電池電量高位
    0xA5, // 0x05: 電池電量低位
    0x01, // 0x06: 電源輸出 Enable (此暫存器設定會影響到 0x07 暫存器)
    0x01  // 0x07: 電源輸出狀態 (此暫存器會受到 0x06 影響)
};

// 測試用例
uint8_t test_cases_incomplete[] = {
    0xFA, 0xFA, 0x01, 0x03, 0x7A, // 完整的寫入操作
    0xFA, 0xFA, 0x02, 0x02, 0x00, // 完整的讀取操作
    0xFA, 0xFA, 0x01, 0x03,       // 未完成的寫入操作
    0xFA, 0xFA, 0x02, 0x04, 0x00, // 完整的讀取操作
    0xFA, 0xFA, 0x01,             // 開始但缺少數據的寫入操作
    0xFA, 0xFA, 0x01, 0x03, 0x10, // 完整的寫入操作
    0xFA, 0xFA, 0x02,             // 開始但缺少數據的讀取操作
    0xFA, 0xFA, 0x02, 0x05, 0x00, // 完整的讀取操作 (電池電量低位)
    0xFA, 0xFA, 0x01, 0x06, 0x00, // 完整的寫入操作 (電源輸出啟動)
    0xFA, 0xFA, 0x02, 0x04, 0x00, // 完整的讀取操作
    0xFA, 0xFA,                   // 開始但缺少數據
    0xFA, 0xFA, 0x02, 0x07, 0x00, // 完整的讀取操作 (電源狀態)
    0xFA, 0xFA, 0x01, 0x03,       // 未完成的寫入操作
    0xFA, 0xFA, 0x01, 0x03, 0xFF, // 完整的寫入操作
    0xFA, 0xFA, 0x02, 0x02, 0x00, // 完整的讀取操作
    0xFA, 0xFA, 0x01, 0x06,       // 未完成的寫入操作
    0xFA, 0xFA, 0x02, 0x05, 0x00, // 完整的讀取操作
    0xFA, 0xFA, 0x01, 0x03, 0x7A, // 完整的寫入操作
    0xFA, 0xFA, 0x02, 0x04, 0x00  // 完整的讀取操作
};

extern void send_response(uint8_t *);
extern void print_registers();
extern void write_instruction(uint8_t *);
extern void turn_correct_instruction(int count, uint8_t command[][5]);

int main()
{
    int count = sizeof(test_cases_incomplete) / sizeof(test_cases_incomplete[0]);
    uint8_t command[COMMAND_ROW][COMMAND_COL] = {0};
    turn_correct_instruction(count, command);
    uint8_t response[5] = {0}; // 回應數據
    for (int i = 0; i < COMMAND_ROW; i++)
    {
        response[0] = command[i][0];
        response[1] = command[i][1];
        response[2] = command[i][2];
        response[3] = command[i][3];
        response[4] = command[i][4];
        send_response(response);
        write_instruction(response);
        send_response(response);
        print_registers();
    }
    return 0;
}

void init_command_array(int number, int i, uint8_t command[][5])
{
    command[number][0] = test_cases_incomplete[i];
    command[number][1] = test_cases_incomplete[i + 1];
    command[number][2] = 0xFF;
    command[number][3] = 0xFF;
    command[number][4] = 0xFF;
}

void turn_correct_instruction(int count, uint8_t command[][5])
{
    int number = 0;
    for (int i = 0; i < count;)
    {
        init_command_array(number, i, command);

        if (test_cases_incomplete[i + 2] == 0xFA && test_cases_incomplete[i] == 0xFA)
        {
            i += 2;
        }
        else if (test_cases_incomplete[i + 3] == 0xFA && test_cases_incomplete[i] == 0xFA)
        {
            command[number][2] = test_cases_incomplete[i + 2];
            i += 3;
        }
        else if (test_cases_incomplete[i + 4] == 0xFA && test_cases_incomplete[i + 2] == 0x01 && test_cases_incomplete[i] == 0xFA)
        {
            command[number][2] = test_cases_incomplete[i + 2];
            command[number][3] = test_cases_incomplete[i + 3];
            i += 4;
        }
        else
        {
            command[number][2] = test_cases_incomplete[i + 2];
            command[number][3] = test_cases_incomplete[i + 3];
            command[number][4] = test_cases_incomplete[i + 4];
            i += 5;
        }
        number++;
    }
}

void write_operation_handle(int reg, uint8_t instruction[])
{
    if (reg == 0x03 || reg == 0x06)
    {
        instruction[2] = 0x11;
        registers[reg] = instruction[4];
        return;
    }
    instruction[2] = 0x13;
    instruction[3] = 0x00;
    instruction[4] = 0x02;
}

void read_operation_handle(int reg, uint8_t instruction[])
{
    if (reg == 0x06 || instruction[4] != 0x00)
    {
        instruction[4] = (instruction[4] != 0x00) ? 0x05 : 0x03;
        instruction[2] = 0x13;
        instruction[3] = 0x00;
        return;
    }

    instruction[2] = 0x12;
    instruction[4] = registers[instruction[3]];
}

void operation_handle(uint8_t instruction[], int reg, int data)
{
    instruction[2] = 0x13;
    instruction[3] = 0x00;
    instruction[4] = 0x04;
    if (reg < 0x00 || reg > 0x07 || data > 0xF9 || data < 0x00)
        instruction[4] = 0x01;
}
//
void write_instruction(uint8_t instruction[])
{
    uint8_t operation = instruction[2];
    uint8_t reg = instruction[3];
    uint8_t data = instruction[4];
    if (instruction[0] == START_CODE && instruction[1] == START_CODE)
    {

        if (operation == WRITE_CODE && reg <= 0x07 && reg >= 0x00 && data <= 0xF9 && data >= 0x00)
        {
            write_operation_handle(reg, instruction);
        }
        else if (operation == READ_CODE && reg <= 0x07 && reg >= 0x00 && data <= 0xF9 && data >= 0x00)
        {
            read_operation_handle(reg, instruction);
        }
        else
        {
            operation_handle(instruction, reg, data);
        }
    }
    else
    {
        operation_handle(instruction, reg, data);
    }
}

// 模擬回傳數據的函數
void send_response(uint8_t *response)
{
    printf("Response: ");
    for (int i = 0; i < 5; i++)
    {
        printf("%02X ", response[i]);
    }
}

// 列印暫存器狀態的函數
void print_registers()
{
    printf("\n=== 暫存器狀態 ===\n");
    for (int i = 0; i < 8; i++)
    {
        printf("Register 0x%02X: 0x%02X\n", i, registers[i]);
    }
    printf("\n");
}
