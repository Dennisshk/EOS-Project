#include "exceptionHandler.h"
#include "uart_driver.h"

// Daten senden/empfangen
#define UART_DATA_Register 0x3F201000
#define READ_DR() (*(volatile uint32_t *) UART_DATA_Register)
#define WRITE_DR(val) ((*(volatile uint32_t *)UART_DATA_Register) = (val))

#define UART_FLAG_Register 0x3F201018
#define READ_FR() (*(volatile uint32_t *) UART_FLAG_Register)


// IRQs bestimmen / gelesen markieren
#define IRQ_BASIC_PENDING 0x3F00B200
#define READ_IRQ_BASIC_PENDING() (*(volatile uint32_t *) IRQ_BASIC_PENDING)

#define MIS 0x3F201040
#define READ_MIS() (*(volatile uint32_t *) MIS)

#define ICR 0x3F201044
#define WRITE_ICR(val) ((*(volatile uint32_t *)ICR) = (val))


// Konfiguration IRQs empfangen Und Puffer Größe
#define IMSC 0x3F201038
#define WRITE_IMSC(val) ((*(volatile uint32_t *)IMSC) = (val))
#define IFLS 0x3F201034
#define WRITE_IFLS(val) ((*(volatile uint32_t *)IFLS) = (val))



void handle_uart_interrupt(){
    while (!(READ_FR() & (1u << 4))){
        char input = (char)READ_DR();

        uart_char(input);
        //uart_string(input);
    }
}





void handle_exception_IRQ_same_el_with_SP_ELx(){
    uart_string("handle");
    if (READ_IRQ_BASIC_PENDING() & (1u << 19)) { //Uart Interrupt
        uint32_t interruptTypes = READ_MIS();
        if (interruptTypes & (1u << 4)) {// Receive Interrupt
            handle_uart_interrupt();
            WRITE_ICR(1u << 4);
        }

        if (interruptTypes & (1u << 6)) {// Receive Timeout Interrupt
            handle_uart_interrupt();
            WRITE_ICR(1u << 6);
        }
    }
}






void uart_irq_config(void){
    // In UART selbst Receive und Timeout Interrupts freigeben
    WRITE_IMSC((1u << 4) | (1u << 6));
    WRITE_IFLS(0b000 << 3); // Bit 3-5 entscheidet: b000 = Receive FIFO becomes 1/8 full
}
