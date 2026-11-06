#include "../include/kernel_main.h"

#define UART_DATA_Register 0x3F201000
#define UART_FLAG_Register 0x3F201018
#define UART_INT_BAUT_RATE 0x3F201024
#define UART_FRAC_BAUT_RATE 0x3F201028
#define UART_PARITAET_LENGTH_STOPBITS 0x3F20102c
#define UART_CONTROL_REGISTER 0x3F201030

#define READ_DR() (*(volatile uint32_t *) UART_DATA_Register)
#define READ_FR() (*(volatile uint32_t *) UART_FLAG_Register)

#define WRITE_DR(val) ((*(volatile uint32_t *)UART_DATA_Register) = (val))
#define WRITE_IBRB(val) ((*(volatile uint32_t *)UART_INT_BAUT_RATE) = (val))
#define WRITE_FBRD(val) ((*(volatile uint32_t *)UART_FRAC_BAUT_RATE) = (val))
#define WRITE_LCR(val) ((*(volatile uint32_t *)UART_PARITAET_LENGTH_STOPBITS) = (val))
#define WRITE_CR(val) (*(volatile uint32_t *)UART_CONTROL_REGISTER = (val))

void uart_char(char c) {
    // Puffer frei?
    while (READ_FR() & (1 << 5)) {}
    // (1 << 5) erzeugt Binärzahl mit 1 an fünfter Stelle, & ist bitwise -> Wenn ein Bit 1, dann kommt true heraus

    WRITE_DR(c);
}

void uart_string(const char *str) {
    while (*str != '\0') {
        uart_char(*str);
        str++;
    }
}

void uart_config(void){
    // UART deaktivieren
    WRITE_CR(0x0);

    // Baudrate
    uint32_t uartclk = 48000000;
    uint32_t ibrb = uartclk/(16*115200);
    WRITE_IBRB(ibrb);
    WRITE_FBRD(((uartclk % (16 * 115200)) * 64 + (16 * 115200) / 2) / (16 * 115200));

    // 8 Bits, kein Paritätsbit, 1 Stopbit
    WRITE_LCR(0x70);  //01110000 = 0x70

    // UART aktivieren:
    WRITE_CR(0x301);
}

uint64_t kernel_main() {
    uart_config();
    uart_string("Backpapier");

    volatile int a = 5;
    volatile int b = 7;
    volatile int c = a - b;
    return 0;
}
