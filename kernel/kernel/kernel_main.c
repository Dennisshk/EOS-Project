#include "../include/kernel_main.h"

uint64_t kernel_main() {
    volatile int a = 5;
    volatile int b = 7;
    volatile int c = a + b;
    return 0;
}