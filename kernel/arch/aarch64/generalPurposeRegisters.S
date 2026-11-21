.global IRQ_same_el_with_SP_ELx
.extern exception_handler_IRQ_same_el_with_SP_ELx

.macro push reg1 reg2
    // Allgemeinregister sind 8 Byte groß, Stack muss immer 16 Byte Ausrichtung haben
    sub sp, sp, #16
    // stp = zwei Register gleichzeitig auf [sp] schieben, [sp] = Die Adresse, die in sp gespeichert ist
    stp \reg1, \reg2, [sp]
.endm

.macro pop reg1 reg2
    ldp \reg1, \reg2, [sp]
    add sp, sp, #16
.endm

.macro push_all
    push x0, x1
    push x2, x3
    push x4, x5
    push x6, x7
    push x8, x9
    push x10, x11
    push x12, x13
    push x14, x15
    push x16, x17
    push x18, x19
    push x20, x21
    push x22, x23
    push x24, x25
    push x26, x27
    sub sp,sp, #16
    str x28, [sp]
.endm

.macro pop_all
    ldr x28, [sp]
    add sp, sp, #16
    pop x26, x27
    pop x24, x25
    pop x22, x23
    pop x20, x21
    pop x18, x19
    pop x16, x17
    pop x14, x15
    pop x12, x13
    pop x10, x11
    pop x8, x9
    pop x6, x7
    pop x4, x5
    pop x2, x3
    pop x0, x1
.endm

IRQ_same_el_with_SP_ELx:
    push_all
    bl exception_handler_IRQ_same_el_with_SP_ELx
    pop_all
    // Hier wird weitergemacht: Als Gelesen markieren, zurückspringen!!! (davor war b)


