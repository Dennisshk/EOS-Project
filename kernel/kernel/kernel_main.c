#include "../include/kernel_main.h"
#include "../include/uart_driver.h"

uint64_t kernel_main() {
    uart_config();
    uart_string("Backpapier");

    volatile int a = 5;
    volatile int b = 7;
    volatile int c = a - b;
    return 0;
}
