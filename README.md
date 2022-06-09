# 8051
Examples for Computer Architecture and Microcontrollers Course. All these examples are designed to be assembled/compiled using sdcc(Small Device C Compiler) toolchain.
Many examples assume a board layout similar to what comes with EdSim51DI simulator. Students are expected to analyse these examples critically, and tryout them on
simulator to get skilled in 8051 assembly and C programming

## List of examples (in increasing order of difficulty)
### Assembly Language
* asm\_add
* asm\_jmp
* asm\_compare
* asm\_call
### C Language
* c\_delay
* c\_chaser
* c\_keyboard
* c\_lcd
* c\_timer
* c\_timer\_isr
* c\_serial

## Installing the SDCC toolchain (on Ubuntu/Linux)
* sudo apt install sdcc

## Running EdSim51DI (on Ubuntu/Linux)
* Instrall jre (Java Runtime) from package manager: sudo apt install openjdk-11-jre
* Download EdSim51 from https://www.edsim51.com/8051simulator/edsim51di.zip
* Extract
* Open Terminal -> cd to extracted directory
* java -jar edsim51di.jar

## Assembly language examples
### Simulator
Assembly language files can be directly opened/copy pasted into the EdSim51DI simulator

### Hardware
When assembly is required

sdas8051 -l main.asm

this will produce a main.lst file which can be visually inspected. For hardware binaries, we need to first assemble using

sdas8051 -o main.asm

which produces main.rel object file. After this, we need to link using

sdld -i main.ihx main.rel

which produces the binary file main.ihx in intel hex format, which almost all the hardware burners accept for dumping into 8051 chip.


## C language examples
Both for hardware and simulator, we need to do compile

sdcc main.c

the above command will create many output files. The .ihx file contains the machine language information that can be dumped into a microcontroller using a flasher or can be loaded into simulators.
