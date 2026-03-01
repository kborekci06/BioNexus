#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include "nrf_delay.h"
#include "boards.h"
#include "app_uart.h"
#include "app_error.h"

#define UART_TX_BUF_SIZE 256
#define UART_RX_BUF_SIZE 256

// =================================================================
// CUSTOM BIONEXUS ERROR HANDLERS
// (Bypasses the massive Nordic logging dependency chain)
// =================================================================
void app_error_fault_handler(uint32_t id, uint32_t pc, uint32_t info) {
    printf("\r\n[CRITICAL FAULT] ID: %d, PC: %d\r\n", (int)id, (int)pc);
    while(1) {
        bsp_board_led_invert(0); 
        nrf_delay_ms(100); // Fast blink to indicate crash
    }
}

void app_error_handler_bare(uint32_t error_code) {
    printf("\r\n[BARE ERROR] Code: 0x%04X\r\n", (unsigned int)error_code);
    while(1) {
        bsp_board_led_invert(0);
        nrf_delay_ms(100); // Fast blink to indicate crash
    }
}

// UART Event Handler
void uart_error_handle(app_uart_evt_t * p_event) {
    if (p_event->evt_type == APP_UART_COMMUNICATION_ERROR) {
        APP_ERROR_HANDLER(p_event->data.error_communication);
    } else if (p_event->evt_type == APP_UART_FIFO_ERROR) {
        APP_ERROR_HANDLER(p_event->data.error_code);
    }
}

int main(void)
{
    uint32_t err_code;

    // 1. Configure the UART parameters
    const app_uart_comm_params_t comm_params = {
          RX_PIN_NUMBER,
          TX_PIN_NUMBER,
          RTS_PIN_NUMBER,
          CTS_PIN_NUMBER,
          APP_UART_FLOW_CONTROL_DISABLED,
          false,
          UART_BAUDRATE_BAUDRATE_Baud115200
    };

    // 2. Initialize the UART module
    APP_UART_FIFO_INIT(&comm_params,
                       UART_RX_BUF_SIZE,
                       UART_TX_BUF_SIZE,
                       uart_error_handle,
                       APP_IRQ_PRIORITY_LOWEST,
                       err_code);
    APP_ERROR_CHECK(err_code);

    // 3. Initialize LEDs
    bsp_board_leds_init();

    // 4. Print the startup message!
    printf("\r\n--- BioNexus System Online (Board 2) ---\r\n");

    int counter = 0;

    while (true)
    {
        bsp_board_led_invert(0); // Toggle Blue LED
        printf("Heartbeat tick: %d\r\n", counter);
        counter++;
        nrf_delay_ms(1000);
    }
}