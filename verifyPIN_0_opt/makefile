NAME            = app
# Add initialize.o and code.o to the list of objects to compile
OBJECTS         = main.o initialize.o code.o oracle.o countermeasure.o

MSPGCC_PFX      = msp430-elf

# Add your include directories to CFLAGS
INC_DIR         = -I../share -Iinclude
CFLAGS          = $(INC_DIR) -Os -D PFX_MSP430_ELF -Wall -g -mcpu=msp430 -mhwmult=none -ffunction-sections -fdata-sections

# Toolchain executables
CC              = ${MSPGCC_PFX}-gcc
OBJCOPY         = ${MSPGCC_PFX}-objcopy
OBJDUMP         = ${MSPGCC_PFX}-objdump
OBJSIZE         = ${MSPGCC_PFX}-size

.PHONY: all FORCE clean

#all should be the first target. it's built when make is run without args
all: ${NAME}.elf ${NAME}.a43 ${NAME}.ver ${NAME}.lst ${NAME}.size

# Project dependencies
main.o: main.c
initialize.o: initialize.c
code.o: code.c
oracle.o: oracle.c
countermeasure.o: countermeasure.c

# If copydata.c is still part of your project, uncomment the next line
mylib/copydata.o: mylib/copydata.c

#additional rules for files
${NAME}.elf: ${OBJECTS}
	${CC} ${CFLAGS} -T ../shared/linker.ld -fno-use-linker-plugin -Wl,--gc-sections -o $@ ${OBJECTS}

${NAME}.ver: ${NAME}.elf
	${OBJCOPY} -O verilog $^ $@

${NAME}.a43: ${NAME}.elf
	${OBJCOPY} -O ihex $^ $@

${NAME}.lst: ${NAME}.elf
	${OBJDUMP} -dSt $^ >$@

${NAME}.size: ${NAME}.elf
	${OBJSIZE} $^ >$@

clean:
	rm -f ${NAME} ${NAME}.a43 ${NAME}.ver ${NAME}.lst ${NAME}.elf ${NAME}.size *.o *~

