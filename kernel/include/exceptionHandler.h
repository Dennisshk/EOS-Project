#ifndef EOS_PROJECT_EXCEPTIONHANDLER_H
#define EOS_PROJECT_EXCEPTIONHANDLER_H

#include <stdint.h>

void handle_exception_IRQ_same_el_with_SP_ELx();
void uart_irq_config(void);

#endif //EOS_PROJECT_EXCEPTIONHANDLER_H
