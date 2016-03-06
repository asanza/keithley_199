#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/keithley_199.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/keithley_199.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/drivers/eeprom.c src/drivers/tmp275.c src/drivers/dispkyb.c src/drivers/usb_uart.c src/drivers/adc.c src/drivers/adcctrl.c src/eefs/crc32.c src/eefs/eefs.c src/FreeRTOS/portable/MemMang/heap_4.c src/FreeRTOS/portable/MPLAB/PIC32MX/port.c src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.S src/FreeRTOS/timers.c src/FreeRTOS/tasks.c src/FreeRTOS/list.c src/FreeRTOS/event_groups.c src/FreeRTOS/croutine.c src/FreeRTOS/queue.c src/hal/fuses.c src/hal/exceptions.c src/hal/isrWrappers.S src/hal/hal_adc.c src/hal/hal_uart.c src/hal/hal_i2c.c src/hal/hal_spi.c src/hal/hal_timer.c src/hal/hal_io.c src/hal/hal_sys.c src/scpi-parser/libscpi/src/lexer.c src/scpi-parser/libscpi/src/error.c src/scpi-parser/libscpi/src/fifo.c src/scpi-parser/libscpi/src/ieee488.c src/scpi-parser/libscpi/src/minimal.c src/scpi-parser/libscpi/src/parser.c src/scpi-parser/libscpi/src/units.c src/scpi-parser/libscpi/src/utils.c src/sys/src/system.c src/sys/src/settings.c src/tasks/task_calibration.c src/tasks/task_multimeter.c src/tasks/main.c src/tasks/tskmgr.c src/tasks/task_scpi.c src/utils/fcvt-1.1/fcvt.c src/utils/src/diag.c src/utils/src/fitlinear.c src/utils/src/disfmt.c src/utils/src/util_ringbuff.c src/utils/src/strutils.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/drivers/eeprom.o ${OBJECTDIR}/src/drivers/tmp275.o ${OBJECTDIR}/src/drivers/dispkyb.o ${OBJECTDIR}/src/drivers/usb_uart.o ${OBJECTDIR}/src/drivers/adc.o ${OBJECTDIR}/src/drivers/adcctrl.o ${OBJECTDIR}/src/eefs/crc32.o ${OBJECTDIR}/src/eefs/eefs.o ${OBJECTDIR}/src/FreeRTOS/portable/MemMang/heap_4.o ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port.o ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o ${OBJECTDIR}/src/FreeRTOS/timers.o ${OBJECTDIR}/src/FreeRTOS/tasks.o ${OBJECTDIR}/src/FreeRTOS/list.o ${OBJECTDIR}/src/FreeRTOS/event_groups.o ${OBJECTDIR}/src/FreeRTOS/croutine.o ${OBJECTDIR}/src/FreeRTOS/queue.o ${OBJECTDIR}/src/hal/fuses.o ${OBJECTDIR}/src/hal/exceptions.o ${OBJECTDIR}/src/hal/isrWrappers.o ${OBJECTDIR}/src/hal/hal_adc.o ${OBJECTDIR}/src/hal/hal_uart.o ${OBJECTDIR}/src/hal/hal_i2c.o ${OBJECTDIR}/src/hal/hal_spi.o ${OBJECTDIR}/src/hal/hal_timer.o ${OBJECTDIR}/src/hal/hal_io.o ${OBJECTDIR}/src/hal/hal_sys.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/lexer.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/error.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/fifo.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/ieee488.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/minimal.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/parser.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/units.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/utils.o ${OBJECTDIR}/src/sys/src/system.o ${OBJECTDIR}/src/sys/src/settings.o ${OBJECTDIR}/src/tasks/task_calibration.o ${OBJECTDIR}/src/tasks/task_multimeter.o ${OBJECTDIR}/src/tasks/main.o ${OBJECTDIR}/src/tasks/tskmgr.o ${OBJECTDIR}/src/tasks/task_scpi.o ${OBJECTDIR}/src/utils/fcvt-1.1/fcvt.o ${OBJECTDIR}/src/utils/src/diag.o ${OBJECTDIR}/src/utils/src/fitlinear.o ${OBJECTDIR}/src/utils/src/disfmt.o ${OBJECTDIR}/src/utils/src/util_ringbuff.o ${OBJECTDIR}/src/utils/src/strutils.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/drivers/eeprom.o.d ${OBJECTDIR}/src/drivers/tmp275.o.d ${OBJECTDIR}/src/drivers/dispkyb.o.d ${OBJECTDIR}/src/drivers/usb_uart.o.d ${OBJECTDIR}/src/drivers/adc.o.d ${OBJECTDIR}/src/drivers/adcctrl.o.d ${OBJECTDIR}/src/eefs/crc32.o.d ${OBJECTDIR}/src/eefs/eefs.o.d ${OBJECTDIR}/src/FreeRTOS/portable/MemMang/heap_4.o.d ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port.o.d ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o.d ${OBJECTDIR}/src/FreeRTOS/timers.o.d ${OBJECTDIR}/src/FreeRTOS/tasks.o.d ${OBJECTDIR}/src/FreeRTOS/list.o.d ${OBJECTDIR}/src/FreeRTOS/event_groups.o.d ${OBJECTDIR}/src/FreeRTOS/croutine.o.d ${OBJECTDIR}/src/FreeRTOS/queue.o.d ${OBJECTDIR}/src/hal/fuses.o.d ${OBJECTDIR}/src/hal/exceptions.o.d ${OBJECTDIR}/src/hal/isrWrappers.o.d ${OBJECTDIR}/src/hal/hal_adc.o.d ${OBJECTDIR}/src/hal/hal_uart.o.d ${OBJECTDIR}/src/hal/hal_i2c.o.d ${OBJECTDIR}/src/hal/hal_spi.o.d ${OBJECTDIR}/src/hal/hal_timer.o.d ${OBJECTDIR}/src/hal/hal_io.o.d ${OBJECTDIR}/src/hal/hal_sys.o.d ${OBJECTDIR}/src/scpi-parser/libscpi/src/lexer.o.d ${OBJECTDIR}/src/scpi-parser/libscpi/src/error.o.d ${OBJECTDIR}/src/scpi-parser/libscpi/src/fifo.o.d ${OBJECTDIR}/src/scpi-parser/libscpi/src/ieee488.o.d ${OBJECTDIR}/src/scpi-parser/libscpi/src/minimal.o.d ${OBJECTDIR}/src/scpi-parser/libscpi/src/parser.o.d ${OBJECTDIR}/src/scpi-parser/libscpi/src/units.o.d ${OBJECTDIR}/src/scpi-parser/libscpi/src/utils.o.d ${OBJECTDIR}/src/sys/src/system.o.d ${OBJECTDIR}/src/sys/src/settings.o.d ${OBJECTDIR}/src/tasks/task_calibration.o.d ${OBJECTDIR}/src/tasks/task_multimeter.o.d ${OBJECTDIR}/src/tasks/main.o.d ${OBJECTDIR}/src/tasks/tskmgr.o.d ${OBJECTDIR}/src/tasks/task_scpi.o.d ${OBJECTDIR}/src/utils/fcvt-1.1/fcvt.o.d ${OBJECTDIR}/src/utils/src/diag.o.d ${OBJECTDIR}/src/utils/src/fitlinear.o.d ${OBJECTDIR}/src/utils/src/disfmt.o.d ${OBJECTDIR}/src/utils/src/util_ringbuff.o.d ${OBJECTDIR}/src/utils/src/strutils.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/drivers/eeprom.o ${OBJECTDIR}/src/drivers/tmp275.o ${OBJECTDIR}/src/drivers/dispkyb.o ${OBJECTDIR}/src/drivers/usb_uart.o ${OBJECTDIR}/src/drivers/adc.o ${OBJECTDIR}/src/drivers/adcctrl.o ${OBJECTDIR}/src/eefs/crc32.o ${OBJECTDIR}/src/eefs/eefs.o ${OBJECTDIR}/src/FreeRTOS/portable/MemMang/heap_4.o ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port.o ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o ${OBJECTDIR}/src/FreeRTOS/timers.o ${OBJECTDIR}/src/FreeRTOS/tasks.o ${OBJECTDIR}/src/FreeRTOS/list.o ${OBJECTDIR}/src/FreeRTOS/event_groups.o ${OBJECTDIR}/src/FreeRTOS/croutine.o ${OBJECTDIR}/src/FreeRTOS/queue.o ${OBJECTDIR}/src/hal/fuses.o ${OBJECTDIR}/src/hal/exceptions.o ${OBJECTDIR}/src/hal/isrWrappers.o ${OBJECTDIR}/src/hal/hal_adc.o ${OBJECTDIR}/src/hal/hal_uart.o ${OBJECTDIR}/src/hal/hal_i2c.o ${OBJECTDIR}/src/hal/hal_spi.o ${OBJECTDIR}/src/hal/hal_timer.o ${OBJECTDIR}/src/hal/hal_io.o ${OBJECTDIR}/src/hal/hal_sys.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/lexer.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/error.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/fifo.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/ieee488.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/minimal.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/parser.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/units.o ${OBJECTDIR}/src/scpi-parser/libscpi/src/utils.o ${OBJECTDIR}/src/sys/src/system.o ${OBJECTDIR}/src/sys/src/settings.o ${OBJECTDIR}/src/tasks/task_calibration.o ${OBJECTDIR}/src/tasks/task_multimeter.o ${OBJECTDIR}/src/tasks/main.o ${OBJECTDIR}/src/tasks/tskmgr.o ${OBJECTDIR}/src/tasks/task_scpi.o ${OBJECTDIR}/src/utils/fcvt-1.1/fcvt.o ${OBJECTDIR}/src/utils/src/diag.o ${OBJECTDIR}/src/utils/src/fitlinear.o ${OBJECTDIR}/src/utils/src/disfmt.o ${OBJECTDIR}/src/utils/src/util_ringbuff.o ${OBJECTDIR}/src/utils/src/strutils.o

# Source Files
SOURCEFILES=src/drivers/eeprom.c src/drivers/tmp275.c src/drivers/dispkyb.c src/drivers/usb_uart.c src/drivers/adc.c src/drivers/adcctrl.c src/eefs/crc32.c src/eefs/eefs.c src/FreeRTOS/portable/MemMang/heap_4.c src/FreeRTOS/portable/MPLAB/PIC32MX/port.c src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.S src/FreeRTOS/timers.c src/FreeRTOS/tasks.c src/FreeRTOS/list.c src/FreeRTOS/event_groups.c src/FreeRTOS/croutine.c src/FreeRTOS/queue.c src/hal/fuses.c src/hal/exceptions.c src/hal/isrWrappers.S src/hal/hal_adc.c src/hal/hal_uart.c src/hal/hal_i2c.c src/hal/hal_spi.c src/hal/hal_timer.c src/hal/hal_io.c src/hal/hal_sys.c src/scpi-parser/libscpi/src/lexer.c src/scpi-parser/libscpi/src/error.c src/scpi-parser/libscpi/src/fifo.c src/scpi-parser/libscpi/src/ieee488.c src/scpi-parser/libscpi/src/minimal.c src/scpi-parser/libscpi/src/parser.c src/scpi-parser/libscpi/src/units.c src/scpi-parser/libscpi/src/utils.c src/sys/src/system.c src/sys/src/settings.c src/tasks/task_calibration.c src/tasks/task_multimeter.c src/tasks/main.c src/tasks/tskmgr.c src/tasks/task_scpi.c src/utils/fcvt-1.1/fcvt.c src/utils/src/diag.c src/utils/src/fitlinear.c src/utils/src/disfmt.c src/utils/src/util_ringbuff.c src/utils/src/strutils.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/keithley_199.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX350F256L
MP_LINKER_FILE_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o: src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o.ok ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o.d" "${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o.d"  -o ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.S    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
	
${OBJECTDIR}/src/hal/isrWrappers.o: src/hal/isrWrappers.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/isrWrappers.o.d 
	@${RM} ${OBJECTDIR}/src/hal/isrWrappers.o 
	@${RM} ${OBJECTDIR}/src/hal/isrWrappers.o.ok ${OBJECTDIR}/src/hal/isrWrappers.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/isrWrappers.o.d" "${OBJECTDIR}/src/hal/isrWrappers.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/src/hal/isrWrappers.o.d"  -o ${OBJECTDIR}/src/hal/isrWrappers.o src/hal/isrWrappers.S    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/src/hal/isrWrappers.o.asm.d",--defsym=__ICD2RAM=1,--defsym=__MPLAB_DEBUG=1,--gdwarf-2,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1
	
else
${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o: src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o.ok ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o.d" "${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o.d"  -o ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.S    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port_asm.o.asm.d",--gdwarf-2
	
${OBJECTDIR}/src/hal/isrWrappers.o: src/hal/isrWrappers.S  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/isrWrappers.o.d 
	@${RM} ${OBJECTDIR}/src/hal/isrWrappers.o 
	@${RM} ${OBJECTDIR}/src/hal/isrWrappers.o.ok ${OBJECTDIR}/src/hal/isrWrappers.o.err 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/isrWrappers.o.d" "${OBJECTDIR}/src/hal/isrWrappers.o.asm.d" -t $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC} $(MP_EXTRA_AS_PRE)  -c -mprocessor=$(MP_PROCESSOR_OPTION) -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/src/hal/isrWrappers.o.d"  -o ${OBJECTDIR}/src/hal/isrWrappers.o src/hal/isrWrappers.S    -Wa,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_AS_POST),-MD="${OBJECTDIR}/src/hal/isrWrappers.o.asm.d",--gdwarf-2
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/drivers/eeprom.o: src/drivers/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drivers/eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/drivers/eeprom.o.d" -o ${OBJECTDIR}/src/drivers/eeprom.o src/drivers/eeprom.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/drivers/tmp275.o: src/drivers/tmp275.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/tmp275.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/tmp275.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drivers/tmp275.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/drivers/tmp275.o.d" -o ${OBJECTDIR}/src/drivers/tmp275.o src/drivers/tmp275.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/drivers/dispkyb.o: src/drivers/dispkyb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/dispkyb.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/dispkyb.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drivers/dispkyb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/drivers/dispkyb.o.d" -o ${OBJECTDIR}/src/drivers/dispkyb.o src/drivers/dispkyb.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/drivers/usb_uart.o: src/drivers/usb_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/usb_uart.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/usb_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drivers/usb_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/drivers/usb_uart.o.d" -o ${OBJECTDIR}/src/drivers/usb_uart.o src/drivers/usb_uart.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/drivers/adc.o: src/drivers/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/adc.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/adc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drivers/adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/drivers/adc.o.d" -o ${OBJECTDIR}/src/drivers/adc.o src/drivers/adc.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/drivers/adcctrl.o: src/drivers/adcctrl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/adcctrl.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/adcctrl.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drivers/adcctrl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/drivers/adcctrl.o.d" -o ${OBJECTDIR}/src/drivers/adcctrl.o src/drivers/adcctrl.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/eefs/crc32.o: src/eefs/crc32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/eefs" 
	@${RM} ${OBJECTDIR}/src/eefs/crc32.o.d 
	@${RM} ${OBJECTDIR}/src/eefs/crc32.o 
	@${FIXDEPS} "${OBJECTDIR}/src/eefs/crc32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/eefs/crc32.o.d" -o ${OBJECTDIR}/src/eefs/crc32.o src/eefs/crc32.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/eefs/eefs.o: src/eefs/eefs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/eefs" 
	@${RM} ${OBJECTDIR}/src/eefs/eefs.o.d 
	@${RM} ${OBJECTDIR}/src/eefs/eefs.o 
	@${FIXDEPS} "${OBJECTDIR}/src/eefs/eefs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/eefs/eefs.o.d" -o ${OBJECTDIR}/src/eefs/eefs.o src/eefs/eefs.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/FreeRTOS/portable/MemMang/heap_4.o: src/FreeRTOS/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS/portable/MemMang" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/MemMang/heap_4.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/MemMang/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/portable/MemMang/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/FreeRTOS/portable/MemMang/heap_4.o.d" -o ${OBJECTDIR}/src/FreeRTOS/portable/MemMang/heap_4.o src/FreeRTOS/portable/MemMang/heap_4.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port.o: src/FreeRTOS/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port.o.d" -o ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port.o src/FreeRTOS/portable/MPLAB/PIC32MX/port.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/FreeRTOS/timers.o: src/FreeRTOS/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/timers.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/FreeRTOS/timers.o.d" -o ${OBJECTDIR}/src/FreeRTOS/timers.o src/FreeRTOS/timers.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/FreeRTOS/tasks.o: src/FreeRTOS/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/tasks.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/tasks.o.d" -o ${OBJECTDIR}/src/FreeRTOS/tasks.o src/FreeRTOS/tasks.c     
	
${OBJECTDIR}/src/FreeRTOS/list.o: src/FreeRTOS/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/list.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/list.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/FreeRTOS/list.o.d" -o ${OBJECTDIR}/src/FreeRTOS/list.o src/FreeRTOS/list.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/FreeRTOS/event_groups.o: src/FreeRTOS/event_groups.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/event_groups.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/event_groups.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/event_groups.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/FreeRTOS/event_groups.o.d" -o ${OBJECTDIR}/src/FreeRTOS/event_groups.o src/FreeRTOS/event_groups.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/FreeRTOS/croutine.o: src/FreeRTOS/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/croutine.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/FreeRTOS/croutine.o.d" -o ${OBJECTDIR}/src/FreeRTOS/croutine.o src/FreeRTOS/croutine.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/FreeRTOS/queue.o: src/FreeRTOS/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/queue.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/FreeRTOS/queue.o.d" -o ${OBJECTDIR}/src/FreeRTOS/queue.o src/FreeRTOS/queue.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/fuses.o: src/hal/fuses.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/fuses.o.d 
	@${RM} ${OBJECTDIR}/src/hal/fuses.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/fuses.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/fuses.o.d" -o ${OBJECTDIR}/src/hal/fuses.o src/hal/fuses.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/exceptions.o: src/hal/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/exceptions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/exceptions.o.d" -o ${OBJECTDIR}/src/hal/exceptions.o src/hal/exceptions.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/hal_adc.o: src/hal/hal_adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/hal_adc.o.d 
	@${RM} ${OBJECTDIR}/src/hal/hal_adc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/hal_adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/hal_adc.o.d" -o ${OBJECTDIR}/src/hal/hal_adc.o src/hal/hal_adc.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/hal_uart.o: src/hal/hal_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/hal_uart.o.d 
	@${RM} ${OBJECTDIR}/src/hal/hal_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/hal_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/hal_uart.o.d" -o ${OBJECTDIR}/src/hal/hal_uart.o src/hal/hal_uart.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/hal_i2c.o: src/hal/hal_i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/hal_i2c.o.d 
	@${RM} ${OBJECTDIR}/src/hal/hal_i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/hal_i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/hal_i2c.o.d" -o ${OBJECTDIR}/src/hal/hal_i2c.o src/hal/hal_i2c.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/hal_spi.o: src/hal/hal_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/hal_spi.o.d 
	@${RM} ${OBJECTDIR}/src/hal/hal_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/hal_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/hal_spi.o.d" -o ${OBJECTDIR}/src/hal/hal_spi.o src/hal/hal_spi.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/hal_timer.o: src/hal/hal_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/src/hal/hal_timer.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/hal_timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/hal_timer.o.d" -o ${OBJECTDIR}/src/hal/hal_timer.o src/hal/hal_timer.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/hal_io.o: src/hal/hal_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/hal_io.o.d 
	@${RM} ${OBJECTDIR}/src/hal/hal_io.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/hal_io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/hal_io.o.d" -o ${OBJECTDIR}/src/hal/hal_io.o src/hal/hal_io.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/hal_sys.o: src/hal/hal_sys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/hal_sys.o.d 
	@${RM} ${OBJECTDIR}/src/hal/hal_sys.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/hal_sys.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/hal_sys.o.d" -o ${OBJECTDIR}/src/hal/hal_sys.o src/hal/hal_sys.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/lexer.o: src/scpi-parser/libscpi/src/lexer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/lexer.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/lexer.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/lexer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/lexer.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/lexer.o src/scpi-parser/libscpi/src/lexer.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/error.o: src/scpi-parser/libscpi/src/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/error.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/error.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/error.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/error.o src/scpi-parser/libscpi/src/error.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/fifo.o: src/scpi-parser/libscpi/src/fifo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/fifo.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/fifo.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/fifo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/fifo.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/fifo.o src/scpi-parser/libscpi/src/fifo.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/ieee488.o: src/scpi-parser/libscpi/src/ieee488.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/ieee488.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/ieee488.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/ieee488.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/ieee488.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/ieee488.o src/scpi-parser/libscpi/src/ieee488.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/minimal.o: src/scpi-parser/libscpi/src/minimal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/minimal.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/minimal.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/minimal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/minimal.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/minimal.o src/scpi-parser/libscpi/src/minimal.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/parser.o: src/scpi-parser/libscpi/src/parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/parser.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/parser.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/parser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/parser.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/parser.o src/scpi-parser/libscpi/src/parser.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/units.o: src/scpi-parser/libscpi/src/units.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/units.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/units.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/units.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/units.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/units.o src/scpi-parser/libscpi/src/units.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/utils.o: src/scpi-parser/libscpi/src/utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/utils.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/utils.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/utils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/utils.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/utils.o src/scpi-parser/libscpi/src/utils.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/sys/src/system.o: src/sys/src/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/sys/src" 
	@${RM} ${OBJECTDIR}/src/sys/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/sys/src/system.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/src/system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/sys/src/system.o.d" -o ${OBJECTDIR}/src/sys/src/system.o src/sys/src/system.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/sys/src/settings.o: src/sys/src/settings.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/sys/src" 
	@${RM} ${OBJECTDIR}/src/sys/src/settings.o.d 
	@${RM} ${OBJECTDIR}/src/sys/src/settings.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/src/settings.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/sys/src/settings.o.d" -o ${OBJECTDIR}/src/sys/src/settings.o src/sys/src/settings.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/tasks/task_calibration.o: src/tasks/task_calibration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/tasks" 
	@${RM} ${OBJECTDIR}/src/tasks/task_calibration.o.d 
	@${RM} ${OBJECTDIR}/src/tasks/task_calibration.o 
	@${FIXDEPS} "${OBJECTDIR}/src/tasks/task_calibration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/tasks/task_calibration.o.d" -o ${OBJECTDIR}/src/tasks/task_calibration.o src/tasks/task_calibration.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/tasks/task_multimeter.o: src/tasks/task_multimeter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/tasks" 
	@${RM} ${OBJECTDIR}/src/tasks/task_multimeter.o.d 
	@${RM} ${OBJECTDIR}/src/tasks/task_multimeter.o 
	@${FIXDEPS} "${OBJECTDIR}/src/tasks/task_multimeter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/tasks/task_multimeter.o.d" -o ${OBJECTDIR}/src/tasks/task_multimeter.o src/tasks/task_multimeter.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/tasks/main.o: src/tasks/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/tasks" 
	@${RM} ${OBJECTDIR}/src/tasks/main.o.d 
	@${RM} ${OBJECTDIR}/src/tasks/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/tasks/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/tasks/main.o.d" -o ${OBJECTDIR}/src/tasks/main.o src/tasks/main.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/tasks/tskmgr.o: src/tasks/tskmgr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/tasks" 
	@${RM} ${OBJECTDIR}/src/tasks/tskmgr.o.d 
	@${RM} ${OBJECTDIR}/src/tasks/tskmgr.o 
	@${FIXDEPS} "${OBJECTDIR}/src/tasks/tskmgr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/tasks/tskmgr.o.d" -o ${OBJECTDIR}/src/tasks/tskmgr.o src/tasks/tskmgr.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/tasks/task_scpi.o: src/tasks/task_scpi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/tasks" 
	@${RM} ${OBJECTDIR}/src/tasks/task_scpi.o.d 
	@${RM} ${OBJECTDIR}/src/tasks/task_scpi.o 
	@${FIXDEPS} "${OBJECTDIR}/src/tasks/task_scpi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/tasks/task_scpi.o.d" -o ${OBJECTDIR}/src/tasks/task_scpi.o src/tasks/task_scpi.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/utils/fcvt-1.1/fcvt.o: src/utils/fcvt-1.1/fcvt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/utils/fcvt-1.1" 
	@${RM} ${OBJECTDIR}/src/utils/fcvt-1.1/fcvt.o.d 
	@${RM} ${OBJECTDIR}/src/utils/fcvt-1.1/fcvt.o 
	@${FIXDEPS} "${OBJECTDIR}/src/utils/fcvt-1.1/fcvt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/utils/fcvt-1.1/fcvt.o.d" -o ${OBJECTDIR}/src/utils/fcvt-1.1/fcvt.o src/utils/fcvt-1.1/fcvt.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/utils/src/diag.o: src/utils/src/diag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/utils/src" 
	@${RM} ${OBJECTDIR}/src/utils/src/diag.o.d 
	@${RM} ${OBJECTDIR}/src/utils/src/diag.o 
	@${FIXDEPS} "${OBJECTDIR}/src/utils/src/diag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/utils/src/diag.o.d" -o ${OBJECTDIR}/src/utils/src/diag.o src/utils/src/diag.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/utils/src/fitlinear.o: src/utils/src/fitlinear.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/utils/src" 
	@${RM} ${OBJECTDIR}/src/utils/src/fitlinear.o.d 
	@${RM} ${OBJECTDIR}/src/utils/src/fitlinear.o 
	@${FIXDEPS} "${OBJECTDIR}/src/utils/src/fitlinear.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/utils/src/fitlinear.o.d" -o ${OBJECTDIR}/src/utils/src/fitlinear.o src/utils/src/fitlinear.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/utils/src/disfmt.o: src/utils/src/disfmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/utils/src" 
	@${RM} ${OBJECTDIR}/src/utils/src/disfmt.o.d 
	@${RM} ${OBJECTDIR}/src/utils/src/disfmt.o 
	@${FIXDEPS} "${OBJECTDIR}/src/utils/src/disfmt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/utils/src/disfmt.o.d" -o ${OBJECTDIR}/src/utils/src/disfmt.o src/utils/src/disfmt.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/utils/src/util_ringbuff.o: src/utils/src/util_ringbuff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/utils/src" 
	@${RM} ${OBJECTDIR}/src/utils/src/util_ringbuff.o.d 
	@${RM} ${OBJECTDIR}/src/utils/src/util_ringbuff.o 
	@${FIXDEPS} "${OBJECTDIR}/src/utils/src/util_ringbuff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/utils/src/util_ringbuff.o.d" -o ${OBJECTDIR}/src/utils/src/util_ringbuff.o src/utils/src/util_ringbuff.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/utils/src/strutils.o: src/utils/src/strutils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/utils/src" 
	@${RM} ${OBJECTDIR}/src/utils/src/strutils.o.d 
	@${RM} ${OBJECTDIR}/src/utils/src/strutils.o 
	@${FIXDEPS} "${OBJECTDIR}/src/utils/src/strutils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1 -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/utils/src/strutils.o.d" -o ${OBJECTDIR}/src/utils/src/strutils.o src/utils/src/strutils.c      -Wno-packed-bitfield-compat -fno-short-double 
	
else
${OBJECTDIR}/src/drivers/eeprom.o: src/drivers/eeprom.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/eeprom.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/eeprom.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drivers/eeprom.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/drivers/eeprom.o.d" -o ${OBJECTDIR}/src/drivers/eeprom.o src/drivers/eeprom.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/drivers/tmp275.o: src/drivers/tmp275.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/tmp275.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/tmp275.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drivers/tmp275.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/drivers/tmp275.o.d" -o ${OBJECTDIR}/src/drivers/tmp275.o src/drivers/tmp275.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/drivers/dispkyb.o: src/drivers/dispkyb.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/dispkyb.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/dispkyb.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drivers/dispkyb.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/drivers/dispkyb.o.d" -o ${OBJECTDIR}/src/drivers/dispkyb.o src/drivers/dispkyb.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/drivers/usb_uart.o: src/drivers/usb_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/usb_uart.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/usb_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drivers/usb_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/drivers/usb_uart.o.d" -o ${OBJECTDIR}/src/drivers/usb_uart.o src/drivers/usb_uart.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/drivers/adc.o: src/drivers/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/adc.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/adc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drivers/adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/drivers/adc.o.d" -o ${OBJECTDIR}/src/drivers/adc.o src/drivers/adc.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/drivers/adcctrl.o: src/drivers/adcctrl.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/adcctrl.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/adcctrl.o 
	@${FIXDEPS} "${OBJECTDIR}/src/drivers/adcctrl.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/drivers/adcctrl.o.d" -o ${OBJECTDIR}/src/drivers/adcctrl.o src/drivers/adcctrl.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/eefs/crc32.o: src/eefs/crc32.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/eefs" 
	@${RM} ${OBJECTDIR}/src/eefs/crc32.o.d 
	@${RM} ${OBJECTDIR}/src/eefs/crc32.o 
	@${FIXDEPS} "${OBJECTDIR}/src/eefs/crc32.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/eefs/crc32.o.d" -o ${OBJECTDIR}/src/eefs/crc32.o src/eefs/crc32.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/eefs/eefs.o: src/eefs/eefs.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/eefs" 
	@${RM} ${OBJECTDIR}/src/eefs/eefs.o.d 
	@${RM} ${OBJECTDIR}/src/eefs/eefs.o 
	@${FIXDEPS} "${OBJECTDIR}/src/eefs/eefs.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/eefs/eefs.o.d" -o ${OBJECTDIR}/src/eefs/eefs.o src/eefs/eefs.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/FreeRTOS/portable/MemMang/heap_4.o: src/FreeRTOS/portable/MemMang/heap_4.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS/portable/MemMang" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/MemMang/heap_4.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/MemMang/heap_4.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/portable/MemMang/heap_4.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/FreeRTOS/portable/MemMang/heap_4.o.d" -o ${OBJECTDIR}/src/FreeRTOS/portable/MemMang/heap_4.o src/FreeRTOS/portable/MemMang/heap_4.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port.o: src/FreeRTOS/portable/MPLAB/PIC32MX/port.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port.o.d" -o ${OBJECTDIR}/src/FreeRTOS/portable/MPLAB/PIC32MX/port.o src/FreeRTOS/portable/MPLAB/PIC32MX/port.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/FreeRTOS/timers.o: src/FreeRTOS/timers.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/timers.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/timers.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/timers.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/FreeRTOS/timers.o.d" -o ${OBJECTDIR}/src/FreeRTOS/timers.o src/FreeRTOS/timers.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/FreeRTOS/tasks.o: src/FreeRTOS/tasks.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/tasks.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/tasks.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/tasks.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -MMD -MF "${OBJECTDIR}/src/FreeRTOS/tasks.o.d" -o ${OBJECTDIR}/src/FreeRTOS/tasks.o src/FreeRTOS/tasks.c     
	
${OBJECTDIR}/src/FreeRTOS/list.o: src/FreeRTOS/list.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/list.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/list.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/list.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/FreeRTOS/list.o.d" -o ${OBJECTDIR}/src/FreeRTOS/list.o src/FreeRTOS/list.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/FreeRTOS/event_groups.o: src/FreeRTOS/event_groups.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/event_groups.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/event_groups.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/event_groups.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/FreeRTOS/event_groups.o.d" -o ${OBJECTDIR}/src/FreeRTOS/event_groups.o src/FreeRTOS/event_groups.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/FreeRTOS/croutine.o: src/FreeRTOS/croutine.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/croutine.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/croutine.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/croutine.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/FreeRTOS/croutine.o.d" -o ${OBJECTDIR}/src/FreeRTOS/croutine.o src/FreeRTOS/croutine.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/FreeRTOS/queue.o: src/FreeRTOS/queue.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/FreeRTOS" 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/queue.o.d 
	@${RM} ${OBJECTDIR}/src/FreeRTOS/queue.o 
	@${FIXDEPS} "${OBJECTDIR}/src/FreeRTOS/queue.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/FreeRTOS/queue.o.d" -o ${OBJECTDIR}/src/FreeRTOS/queue.o src/FreeRTOS/queue.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/fuses.o: src/hal/fuses.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/fuses.o.d 
	@${RM} ${OBJECTDIR}/src/hal/fuses.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/fuses.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/fuses.o.d" -o ${OBJECTDIR}/src/hal/fuses.o src/hal/fuses.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/exceptions.o: src/hal/exceptions.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/exceptions.o.d 
	@${RM} ${OBJECTDIR}/src/hal/exceptions.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/exceptions.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/exceptions.o.d" -o ${OBJECTDIR}/src/hal/exceptions.o src/hal/exceptions.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/hal_adc.o: src/hal/hal_adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/hal_adc.o.d 
	@${RM} ${OBJECTDIR}/src/hal/hal_adc.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/hal_adc.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/hal_adc.o.d" -o ${OBJECTDIR}/src/hal/hal_adc.o src/hal/hal_adc.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/hal_uart.o: src/hal/hal_uart.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/hal_uart.o.d 
	@${RM} ${OBJECTDIR}/src/hal/hal_uart.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/hal_uart.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/hal_uart.o.d" -o ${OBJECTDIR}/src/hal/hal_uart.o src/hal/hal_uart.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/hal_i2c.o: src/hal/hal_i2c.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/hal_i2c.o.d 
	@${RM} ${OBJECTDIR}/src/hal/hal_i2c.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/hal_i2c.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/hal_i2c.o.d" -o ${OBJECTDIR}/src/hal/hal_i2c.o src/hal/hal_i2c.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/hal_spi.o: src/hal/hal_spi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/hal_spi.o.d 
	@${RM} ${OBJECTDIR}/src/hal/hal_spi.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/hal_spi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/hal_spi.o.d" -o ${OBJECTDIR}/src/hal/hal_spi.o src/hal/hal_spi.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/hal_timer.o: src/hal/hal_timer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/hal_timer.o.d 
	@${RM} ${OBJECTDIR}/src/hal/hal_timer.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/hal_timer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/hal_timer.o.d" -o ${OBJECTDIR}/src/hal/hal_timer.o src/hal/hal_timer.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/hal_io.o: src/hal/hal_io.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/hal_io.o.d 
	@${RM} ${OBJECTDIR}/src/hal/hal_io.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/hal_io.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/hal_io.o.d" -o ${OBJECTDIR}/src/hal/hal_io.o src/hal/hal_io.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/hal/hal_sys.o: src/hal/hal_sys.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/hal" 
	@${RM} ${OBJECTDIR}/src/hal/hal_sys.o.d 
	@${RM} ${OBJECTDIR}/src/hal/hal_sys.o 
	@${FIXDEPS} "${OBJECTDIR}/src/hal/hal_sys.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/hal/hal_sys.o.d" -o ${OBJECTDIR}/src/hal/hal_sys.o src/hal/hal_sys.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/lexer.o: src/scpi-parser/libscpi/src/lexer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/lexer.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/lexer.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/lexer.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/lexer.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/lexer.o src/scpi-parser/libscpi/src/lexer.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/error.o: src/scpi-parser/libscpi/src/error.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/error.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/error.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/error.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/error.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/error.o src/scpi-parser/libscpi/src/error.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/fifo.o: src/scpi-parser/libscpi/src/fifo.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/fifo.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/fifo.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/fifo.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/fifo.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/fifo.o src/scpi-parser/libscpi/src/fifo.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/ieee488.o: src/scpi-parser/libscpi/src/ieee488.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/ieee488.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/ieee488.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/ieee488.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/ieee488.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/ieee488.o src/scpi-parser/libscpi/src/ieee488.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/minimal.o: src/scpi-parser/libscpi/src/minimal.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/minimal.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/minimal.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/minimal.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/minimal.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/minimal.o src/scpi-parser/libscpi/src/minimal.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/parser.o: src/scpi-parser/libscpi/src/parser.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/parser.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/parser.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/parser.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/parser.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/parser.o src/scpi-parser/libscpi/src/parser.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/units.o: src/scpi-parser/libscpi/src/units.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/units.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/units.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/units.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/units.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/units.o src/scpi-parser/libscpi/src/units.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/scpi-parser/libscpi/src/utils.o: src/scpi-parser/libscpi/src/utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/scpi-parser/libscpi/src" 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/utils.o.d 
	@${RM} ${OBJECTDIR}/src/scpi-parser/libscpi/src/utils.o 
	@${FIXDEPS} "${OBJECTDIR}/src/scpi-parser/libscpi/src/utils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/scpi-parser/libscpi/src/utils.o.d" -o ${OBJECTDIR}/src/scpi-parser/libscpi/src/utils.o src/scpi-parser/libscpi/src/utils.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/sys/src/system.o: src/sys/src/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/sys/src" 
	@${RM} ${OBJECTDIR}/src/sys/src/system.o.d 
	@${RM} ${OBJECTDIR}/src/sys/src/system.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/src/system.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/sys/src/system.o.d" -o ${OBJECTDIR}/src/sys/src/system.o src/sys/src/system.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/sys/src/settings.o: src/sys/src/settings.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/sys/src" 
	@${RM} ${OBJECTDIR}/src/sys/src/settings.o.d 
	@${RM} ${OBJECTDIR}/src/sys/src/settings.o 
	@${FIXDEPS} "${OBJECTDIR}/src/sys/src/settings.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/sys/src/settings.o.d" -o ${OBJECTDIR}/src/sys/src/settings.o src/sys/src/settings.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/tasks/task_calibration.o: src/tasks/task_calibration.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/tasks" 
	@${RM} ${OBJECTDIR}/src/tasks/task_calibration.o.d 
	@${RM} ${OBJECTDIR}/src/tasks/task_calibration.o 
	@${FIXDEPS} "${OBJECTDIR}/src/tasks/task_calibration.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/tasks/task_calibration.o.d" -o ${OBJECTDIR}/src/tasks/task_calibration.o src/tasks/task_calibration.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/tasks/task_multimeter.o: src/tasks/task_multimeter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/tasks" 
	@${RM} ${OBJECTDIR}/src/tasks/task_multimeter.o.d 
	@${RM} ${OBJECTDIR}/src/tasks/task_multimeter.o 
	@${FIXDEPS} "${OBJECTDIR}/src/tasks/task_multimeter.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/tasks/task_multimeter.o.d" -o ${OBJECTDIR}/src/tasks/task_multimeter.o src/tasks/task_multimeter.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/tasks/main.o: src/tasks/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/tasks" 
	@${RM} ${OBJECTDIR}/src/tasks/main.o.d 
	@${RM} ${OBJECTDIR}/src/tasks/main.o 
	@${FIXDEPS} "${OBJECTDIR}/src/tasks/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/tasks/main.o.d" -o ${OBJECTDIR}/src/tasks/main.o src/tasks/main.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/tasks/tskmgr.o: src/tasks/tskmgr.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/tasks" 
	@${RM} ${OBJECTDIR}/src/tasks/tskmgr.o.d 
	@${RM} ${OBJECTDIR}/src/tasks/tskmgr.o 
	@${FIXDEPS} "${OBJECTDIR}/src/tasks/tskmgr.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/tasks/tskmgr.o.d" -o ${OBJECTDIR}/src/tasks/tskmgr.o src/tasks/tskmgr.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/tasks/task_scpi.o: src/tasks/task_scpi.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/tasks" 
	@${RM} ${OBJECTDIR}/src/tasks/task_scpi.o.d 
	@${RM} ${OBJECTDIR}/src/tasks/task_scpi.o 
	@${FIXDEPS} "${OBJECTDIR}/src/tasks/task_scpi.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/tasks/task_scpi.o.d" -o ${OBJECTDIR}/src/tasks/task_scpi.o src/tasks/task_scpi.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/utils/fcvt-1.1/fcvt.o: src/utils/fcvt-1.1/fcvt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/utils/fcvt-1.1" 
	@${RM} ${OBJECTDIR}/src/utils/fcvt-1.1/fcvt.o.d 
	@${RM} ${OBJECTDIR}/src/utils/fcvt-1.1/fcvt.o 
	@${FIXDEPS} "${OBJECTDIR}/src/utils/fcvt-1.1/fcvt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/utils/fcvt-1.1/fcvt.o.d" -o ${OBJECTDIR}/src/utils/fcvt-1.1/fcvt.o src/utils/fcvt-1.1/fcvt.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/utils/src/diag.o: src/utils/src/diag.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/utils/src" 
	@${RM} ${OBJECTDIR}/src/utils/src/diag.o.d 
	@${RM} ${OBJECTDIR}/src/utils/src/diag.o 
	@${FIXDEPS} "${OBJECTDIR}/src/utils/src/diag.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/utils/src/diag.o.d" -o ${OBJECTDIR}/src/utils/src/diag.o src/utils/src/diag.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/utils/src/fitlinear.o: src/utils/src/fitlinear.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/utils/src" 
	@${RM} ${OBJECTDIR}/src/utils/src/fitlinear.o.d 
	@${RM} ${OBJECTDIR}/src/utils/src/fitlinear.o 
	@${FIXDEPS} "${OBJECTDIR}/src/utils/src/fitlinear.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/utils/src/fitlinear.o.d" -o ${OBJECTDIR}/src/utils/src/fitlinear.o src/utils/src/fitlinear.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/utils/src/disfmt.o: src/utils/src/disfmt.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/utils/src" 
	@${RM} ${OBJECTDIR}/src/utils/src/disfmt.o.d 
	@${RM} ${OBJECTDIR}/src/utils/src/disfmt.o 
	@${FIXDEPS} "${OBJECTDIR}/src/utils/src/disfmt.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/utils/src/disfmt.o.d" -o ${OBJECTDIR}/src/utils/src/disfmt.o src/utils/src/disfmt.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/utils/src/util_ringbuff.o: src/utils/src/util_ringbuff.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/utils/src" 
	@${RM} ${OBJECTDIR}/src/utils/src/util_ringbuff.o.d 
	@${RM} ${OBJECTDIR}/src/utils/src/util_ringbuff.o 
	@${FIXDEPS} "${OBJECTDIR}/src/utils/src/util_ringbuff.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/utils/src/util_ringbuff.o.d" -o ${OBJECTDIR}/src/utils/src/util_ringbuff.o src/utils/src/util_ringbuff.c      -Wno-packed-bitfield-compat -fno-short-double 
	
${OBJECTDIR}/src/utils/src/strutils.o: src/utils/src/strutils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/utils/src" 
	@${RM} ${OBJECTDIR}/src/utils/src/strutils.o.d 
	@${RM} ${OBJECTDIR}/src/utils/src/strutils.o 
	@${FIXDEPS} "${OBJECTDIR}/src/utils/src/strutils.o.d" $(SILENT) -rsi ${MP_CC_DIR}../  -c ${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -mips16 -DNDEBUG -DREPOVERSION=\\'"$(GIT_VERSION)\'\" -DREPOBRANCH=\\'"$(GIT_BRANCH)\'\" -I"src/hal" -I"src/FreeRTOS/include" -I"src/FreeRTOS/portable/MPLAB/PIC32MX" -I"src/sys/include" -I"src/eefs" -I"src/libscpi/inc" -I"src/dmm" -I"src/utils/include" -I"src/drivers" -I"src/scpi-parser/libscpi/inc" -Wall -MMD -MF "${OBJECTDIR}/src/utils/src/strutils.o.d" -o ${OBJECTDIR}/src/utils/src/strutils.o src/utils/src/strutils.c      -Wno-packed-bitfield-compat -fno-short-double 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/keithley_199.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mdebugger -D__MPLAB_DEBUGGER_PK3=1 -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -o dist/${CND_CONF}/${IMAGE_TYPE}/keithley_199.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}              -mreserve=boot@0x1FC02000:0x1FC02FEF -mreserve=boot@0x1FC02000:0x1FC0275F  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,--defsym=_min_heap_size=2000,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/keithley_199.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION) -mips16 -o dist/${CND_CONF}/${IMAGE_TYPE}/keithley_199.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}            -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=_min_heap_size=2000,--gc-sections,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map"
	${MP_CC_DIR}/xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/keithley_199.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
