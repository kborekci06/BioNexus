#ifndef APP_CONFIG_H
#define APP_CONFIG_H

// ==========================================
// BIONEXUS UWB INITIATOR OVERRIDES
// ==========================================

#define NRF52 1

// 1. Disable Nordic's bloated logger to prevent dependency hell
#define NRF_LOG_ENABLED 0
#define NRF_LOG_BACKEND_UART_ENABLED 0

// 2. Enable standard UART and its dependencies for printf
#define UART_ENABLED 1
#define UART0_ENABLED 1
#define APP_UART_ENABLED 1
#define RETARGET_ENABLED 1
#define APP_FIFO_ENABLED 1

// 3. Enable SPI for UWB Radio Communication
#define SPI_ENABLED 1
#define SPI1_ENABLED 1
#define SPI2_ENABLED 1

// 4. Enable GPIOTE for the UWB Radio Interrupt (IRQ) pin
#define GPIOTE_ENABLED 1
#define NRFX_GPIOTE_ENABLED 1

// 5. Enable Clock driver (required by the Decawave platform port)
#define NRF_CLOCK_ENABLED 1
#define CLOCK_ENABLED 1

// ==========================================
// BIONEXUS DWM1001-DEV HARDWARE PINS
// ==========================================
#define SPI_SCK_PIN     16
#define SPI_MOSI_PIN    20
#define SPI_MISO_PIN    18
#define SPI_CS_PIN      17
#define DW1000_RST      24
#define DW1000_IRQ      19

// ==========================================
// SPI DRIVER CONFIGURATION
// ==========================================
#define SPI_ENABLED 1
#define SPI1_ENABLED 1
#define SPI1_USE_EASY_DMA 0
#define SPIM1_ENABLED 1
#define SPI_DEFAULT_CONFIG_IRQ_PRIORITY 7
#define SPIM1_IRQ_PRIORITY 7

#endif // APP_CONFIG_H