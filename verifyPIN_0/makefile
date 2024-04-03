# makefile configuration
NAME            = app
OBJECTS         = main.o

MSPGCC_PFX      = msp430-elf

CFLAGS          = $(INC_DIR) -Os -D PFX_MSP430_ELF -Wall -g -mcpu=msp430 -mhwmult=none

# Toolchain executables
CC          = ${MSPGCC_PFX}-gcc
OBJCOPY	    = ${MSPGCC_PFX}-objcopy
OBJDUMP     = ${MSPGCC_PFX}-objdump
OBJSIZE     = ${MSPGCC_PFX}-size
INC_DIR     = -I../share -Iinclude
.PHONY: all FORCE clean

#all should be the first target. it's built when make is runwithout args
all: ${NAME}.elf ${NAME}.a43 ${NAME}.ver ${NAME}.lst ${NAME}.size

#project dependencies
main.o: countermeasure.c initialize.c oracle.c code.c main.c 
mylib/copydata.o: mylib/copydata.c

#additional rules for files
${NAME}.elf: ${OBJECTS}
	${CC} ${CFLAGS} -T ../shared/linker.ld -fno-use-linker-plugin -o $@ ${OBJECTS}

${NAME}.ver: ${NAME}.elf
	${OBJCOPY} -O verilog $^ $@

${NAME}.a43: ${NAME}.elf
	${OBJCOPY} -O ihex $^ $@

${NAME}.lst: ${NAME}.elf
	${OBJDUMP} -dSt $^ >$@

${NAME}.size: ${NAME}.elf
	${OBJSIZE}  $^ >$@

clean:
	rm -f ${NAME} ${NAME}.a43 ${NAME}.ver ${NAME}.lst ${NAME}.elf ${NAME}.size *.o *~
