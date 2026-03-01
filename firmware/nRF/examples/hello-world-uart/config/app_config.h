#ifndef APP_CONFIG_H
#define APP_CONFIG_H

// ==========================================
// BIONEXUS CUSTOM OVERRIDES
// ==========================================

// Explicitly disable Nordic's internal logger so it doesn't steal the UART port
#define NRF_LOG_ENABLED 0
#define NRF_LOG_BACKEND_UART_ENABLED 0

// Enable standard UART and its dependencies for printf
#define UART_ENABLED 1
#define UART0_ENABLED 1
#define APP_UART_ENABLED 1
#define RETARGET_ENABLED 1
#define APP_FIFO_ENABLED 1

#endif // APP_CONFIG_H