#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "boards.h"

int main(void)
{
    bsp_board_leds_init(); // This uses the definitions in dw1001_dev.h

    while (true)
    {
        for (int i = 0; i < LEDS_NUMBER; i++)
        {
            bsp_board_led_invert(i);
        }
        nrf_delay_ms(100);
    }
}