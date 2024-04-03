NAME            = app
OBJECTS         = main.o initialize.o code.o oracle.o countermeasure.o

MSPGCC_PFX      = msp430-elf

INC_DIR         = -I../shared -Iinclude
# Ad flags for function and data sections
CFLAGS          = $(INC_DIR) -Os -D PFX_MSP430_ELF -Wall -g -mcpu=msp430 -mhwmult=none 

# Toolchain executables
CC              = ${MSPGCC_PFX}-gcc
OBJCOPY         = ${MSPGCC_PFX}-objcopy
OBJDUMP         = ${MSPGCC_PFX}-objdump
OBJSIZE         = ${MSPGCC_PFX}-size

.PHONY: all FORCE clean

all: ${NAME}.elf ${NAME}.a43 ${NAME}.ver ${NAME}.lst ${NAME}.size

# Project dependencies
main.o: main.c
initialize.o: initialize.c
code.o: code.c
oracle.o: oracle.c
countermeasure.o: countermeasure.c
mylib/copydata.o: mylib/copydata.c

# Additional rules for files
${NAME}.elf: ${OBJECTS}
	${CC} ${CFLAGS} -T ../shared/linker.ld -fno-use-linker-plugin -o $@ ${OBJECTS}

${NAME}.ver: ${NAME}.elf
	${OBJCOPY} -O verilog $^ $@

${NAME}.a43: ${NAME}.elf
	${OBJCOPY} -O ihex $^ $@

# Generate listing file
${NAME}.lst: ${NAME}.elf
	${OBJDUMP} -dSt $^ > $@

# Generate size summary
${NAME}.size: ${NAME}.elf
	${OBJSIZE} -A $^ > $@

clean:
	rm -f ${NAME} ${NAME}.a43 ${NAME}.ver ${NAME}.lst ${NAME}.elf ${NAME}.size *.o *~

