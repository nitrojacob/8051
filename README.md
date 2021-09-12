# 8051
Examples for Computer Architecture and Microcontrollers Course. All these examples are designed to be assembled/compiled using sdcc(Small Device C Compiler) toolchain. Many examples assume a board layout similar to what comes with EDSim51DI simulator.

## Assembly language examples
Assembly language files can be directly opened/copy pasted into the EDSim51 simulator
When assembly is required

sdas8051 -l main.asm

this will produce a main.lst file


## C language examples
sdcc main.c

the above command will create many output files. The .ihx file contains the machine language information that can be dumped into a microcontroller using a flasher or can be loaded into simulators.
