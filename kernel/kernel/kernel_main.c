#include "../include/kernel_main.h"

#define UART_DATA_Register 0x3F20100
#define UART_FLAG_Register 0x3F20118
#define UART_INT_BAUT_RATE 0x3F20124
#define UART_FRAC_BAUT_RATE 0x3F20128
#define UART_PARITAET_LENGTH_STOPBITS 0x3F2012c

#define READ_DR() (*(volatile uint32_t *) UART_DATA_Register)
#define READ_FR() (*(volatile uint32_t *) UART_FLAG_Register)

#define WRITE_DR(val) ((*(volatile uint32_t *)UART_DATA_Register) = (val))
#define WRITE_FR(val) ((*(volatile uint32_t *)UART_FLAG_Register) = (val))
#define WRITE_IBRB(val) ((*(volatile uint32_t *)UART_INT_BAUT_RATE) = (val))
#define WRITE_FBRD(val) ((*(volatile uint32_t *)UART_FRAC_BAUT_RATE) = (val))
#define WRITE_LCR(val) ((*(volatile uint32_t *)UART_PARITAET_LENGTH_STOPBITS) = (val))

uint64_t kernel_main() {
    WRITE_FBRD(115200);
    WRITE_IBRB(115200);
    WRITE_LCR(1100000);

    /**
        Bit 6:5
        11 = 8 Bits
        10 = 7 Bits
        01 = 6 Bits
        00 = 5 Bits
        Bit 4	1 = FIFOs aktiviert, 0 = FIFOs deaktiviert
        Bit 3	1 = 2 Stoppbits, 0 = 1 Stoppbit
        Bit 2	1 = Gerade Parität, 0 = Ungerade Parität
        Bit 1	1 = Parität aktiv, 0 = Parität inaktiv
     */

    volatile int a = 5;
    volatile int b = 7;
    volatile int c = a - b;
    return 0;
}