#include "../include/kernel_main.h"
#include "../include/uart_driver.h"

// Interrupt Controller der CPU
#define IRQ_ENABLE_1 0x3F00B210
#define WRITE_IRQ_ENABLE_1(val) ((*(volatile uint32_t *)IRQ_ENABLE_1) = (val))
#define IRQ_ENABLE_2 0x3F00B214
#define WRITE_IRQ_ENABLE_2(val) ((*(volatile uint32_t *)IRQ_ENABLE_2) = (val))

uint64_t kernel_main() {
    // UART IRQs freigeben
    WRITE_IRQ_ENABLE_2(1u << 25);

    uart_config();
    uart_string("Backpapier");

    volatile int a = 5;
    volatile int b = 7;
    volatile int c = a - b;
    return 0;
}
