/*
Architektur: AArch64
Prozessor: ARM Cortex-A75
Umgebung: Bare Metal (auf direkt auf Hardware)
*/

/* Definiert Variable _start als Beginn der Assembly Datei */
ENTRY(_assemblyStart)

/* Startpunkt, wo Linker arbeitet */
. = 0x80000;

SECTIONS{
   .text.boot : ALIGN(CONSTANT(MAXPAGESIZE)) {
   /* Übernimmt alle .text.boot-Sections aus kompilierten Dateien*/
       KEEP(*(.text.boot))
   }

   .text.vectors : ALIGN(CONSTANT(MAXPAGESIZE)) {
          KEEP(*(.text.vectors))
      }

   .text : ALIGN(CONSTANT(MAXPAGESIZE)) {
       _TEXT_START_ = .;
       /* Übernimmt alle .text-Sections aus kompilierten Dateien */
       *(.text*)
       _TEXT_END_ = .;
   }

   /*Read Only Data*/
   .rodata : ALIGN(CONSTANT(MAXPAGESIZE)) {
         _RODATA_START_ = .;
         *(.rodata*)
         _RODATA_END_ = .;
   }

   .data : ALIGN(CONSTANT(MAXPAGESIZE)) {
        _DATA_START_ = .;
        *(.data*)
        _DATA_END_ = .;
   }

   .bss : ALIGN(CONSTANT(MAXPAGESIZE)) {
   /*Damit Assembly Schleife ganze Bytes entfernt*/
        . = ALIGN(8);
        _BSS_START_ = .;
        *(.bss*)
        . = ALIGN(8);
        _BSS_END_ = .;
   }

   .stack : {
        . = ALIGN(16);
        _STACK_BOTTOM_ = .;
        . += 0x4000;
        _STACK_TOP_ = .;
   }
}

/* Angepasst aus  https://wiki.osdev.org/Linker_Scripts */