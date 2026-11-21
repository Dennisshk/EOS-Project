#include "uart_driver.h"

#include <stdint.h>

// Daten senden/empfangen
#define UART_DATA_Register 0x3F201000
#define READ_DR() (*(volatile uint32_t *) UART_DATA_Register)
#define WRITE_DR(val) ((*(volatile uint32_t *)UART_DATA_Register) = (val))

#define UART_FLAG_Register 0x3F201018
#define READ_FR() (*(volatile uint32_t *) UART_FLAG_Register)

// Konfiguration allgemein
#define UART_INT_BAUT_RATE 0x3F201024
#define WRITE_IBRB(val) ((*(volatile uint32_t *)UART_INT_BAUT_RATE) = (val))
#define UART_FRAC_BAUT_RATE 0x3F201028
#define WRITE_FBRD(val) ((*(volatile uint32_t *)UART_FRAC_BAUT_RATE) = (val))
#define UART_PARITAET_LENGTH_STOPBITS 0x3F20102c
#define WRITE_LCR(val) ((*(volatile uint32_t *)UART_PARITAET_LENGTH_STOPBITS) = (val))
#define UART_CONTROL_REGISTER 0x3F201030
#define WRITE_CR(val) (*(volatile uint32_t *)UART_CONTROL_REGISTER = (val))

// Konfiguration IRQs empfangen Und Puffer Größe
#define IMSC 0x3F201038
#define WRITE_IMSC(val) ((*(volatile uint32_t *)IMSC) = (val))
#define IFLS 0x3F201034
#define WRITE_IFLS(val) ((*(volatile uint32_t *)IFLS) = (val))

void uart_char(char c) {
    // Puffer frei?
    while (READ_FR() & (1u << 5)) {}
    /* (1 << 5) erzeugt Binärzahl mit 1 an fünfter Stelle -> 1 ist Zahl mit 0000001, danach verschieben << 5 ergibt 50000
     * u = 1 als Unsigned Int
     * & ist bitwise -> Wenn ein Bit 1, dann kommt true heraus
    */
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
    uint32_t baudrate = 115200;
    uint32_t divisor = 16 * baudrate;

    uint32_t ibrb = uartclk/divisor;
    uint32_t fbrd = (uartclk % divisor * 64 + divisor / 2) / divisor;

    WRITE_IBRB(ibrb);
    WRITE_FBRD(fbrd);

    // 8 Bits, kein Paritätsbit, 1 Stopbit
    WRITE_LCR(0x70);  //01110000 = 0x70

    // In UART selbst Receive und Timeout Interrupts freigeben
    WRITE_IMSC((1u << 4) | (1u << 6));
    WRITE_IFLS(0b000 << 3); // Bit 3-5 entscheidet: b000 = Receive FIFO becomes 1/8 full

    // UART aktivieren:
    WRITE_CR(0x301); //001100000001 = 0x301
}
