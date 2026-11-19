.section .text.vectors
.global _interruptStart
.extern endlos


_interruptStart:
    // Lädt Adresse des vektors (label später definiert), speichert sie in vbar_el2 -> msr für spezielles system register, ldr für allgemeines register
    ldr x0,=vectors
    msr vbar_el2,x0
    msr daif,xzr
    ret



// Makro = Code der später injiziert werden kann, Name vector, Param label => Springt zur Adresse label nach Verschieben
.macro vector label
.p2align 7
b \label
.endm



// vector table must be 2048-byte aligned
.p2align 11
vectors:
    // EL2 SP0 stack
    vector endlos //Syn
    vector endlos //IRQ
    vector endlos //FIQ
    vector endlos //SError

    // EL2 own stack (kernel mode)
    vector endlos
    vector endlos
    vector endlos
    vector endlos

    // 64-bit EL0-1->EL2 (user mode)
    vector endlos
    vector endlos
    vector endlos
    vector endlos

    // 32-bit EL0-1->EL2 (user mode)
    vector endlos
    vector endlos
    vector endlos
    vector endlos