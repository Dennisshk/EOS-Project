/*Definiert Section für Linker*/
.section .text.boot

/* Gibt externe Ressourcen */
.global _assemblyStart
.global endlos

/* Nimmt externe Ressourcen */
.extern kernel_main
.extern _interruptStart

.extern _BSS_START_
.extern _BSS_END_
.extern _STACK_TOP_






_assemblyStart:
/*Stack vorbereiten*/
    LDR x0, =_STACK_TOP_
    MOV sp, x0



/*BSS Abschnitt leeren*/
    LDR x0, =_BSS_START_
    LDR x1, =_BSS_END_
bss_loop:
    CMP x0, x1
    /* Sprung zu Label, wenn Branch/Sprung (B) erfüllt Bedingung Higher Or Same (HS) */
    B.HS bss_loop_end
    STR xzr, [x0]
    ADD X0, X0, #8
    B bss_loop



/*Interrupt Init Methode aufrufen*/
bss_loop_end:
    BL _interruptStart



/*C Einstiegspunkt starten -> BL = Sprung mit gespeichertem return */
    BL kernel_main



/* Endlosschleife falls main verlassen */
endlos:
    B endlos




/*
X0–X30 Register Namen
SP Stack Pointer Register
XZR Register mit konstantem Wert 0
*/