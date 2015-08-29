/*
 * task_scpi.c
 *
 * Copyright (c) 2015, Diego F. Asanza. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
 *
 * Created on August 29, 2015, 7:20 PM
 */

#include <scpi/scpi.h>

#include "usb_uart.h"

#define SCPI_INPUT_BUFFER_LENGTH 256
static char scpi_input_buffer[SCPI_INPUT_BUFFER_LENGTH];

static scpi_reg_val_t scpi_regs[SCPI_REG_COUNT];

size_t SCPI_Write(scpi_t * context, const char * data, size_t len) {
    printf("%s", data);
    /*if (context->user_context != NULL) {
        int fd = *(int *)(context->user_context);
        return write(fd, data, len);
    }*/
    return 0;
}

static scpi_result_t DMM_MeasureVoltageDcQ(scpi_t * context) {
    scpi_number_t param1, param2;
    char bf[15];
    printf("meas:volt:dc\r\n"); // debug command name   

    // read first parameter if present
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
        // do something, if parameter not present
    }

    // read second paraeter if present
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param2, FALSE)) {
        // do something, if parameter not present
    }

    
    SCPI_NumberToStr(context, scpi_special_numbers_def, &param1, bf, 15);
    printf( "\tP1=%s\r\n", bf);

    
    SCPI_NumberToStr(context, scpi_special_numbers_def, &param2, bf, 15);
    printf( "\tP2=%s\r\n", bf);

    SCPI_ResultDouble(context, 0);
    
    return SCPI_RES_OK;
}


static scpi_result_t DMM_MeasureVoltageAcQ(scpi_t * context) {
    scpi_number_t param1, param2;
    char bf[15];
    printf("meas:volt:ac\r\n"); // debug command name   

    // read first parameter if present
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param1, FALSE)) {
        // do something, if parameter not present
    }

    // read second paraeter if present
    if (!SCPI_ParamNumber(context, scpi_special_numbers_def, &param2, FALSE)) {
        // do something, if parameter not present
    }

    
    SCPI_NumberToStr(context, scpi_special_numbers_def, &param1, bf, 15);
    printf( "\tP1=%s\r\n", bf);

    
    SCPI_NumberToStr(context, scpi_special_numbers_def, &param2, bf, 15);
    printf( "\tP2=%s\r\n", bf);

    SCPI_ResultDouble(context, 0);
    
    return SCPI_RES_OK;
}

static scpi_result_t DMM_ConfigureVoltageDc(scpi_t * context) {
    double param1, param2;
    printf( "conf:volt:dc\r\n"); // debug command name   

    // read first parameter if present
    if (!SCPI_ParamDouble(context, &param1, TRUE)) {
        return SCPI_RES_ERR;
    }

    // read second paraeter if present
    if (!SCPI_ParamDouble(context, &param2, FALSE)) {
        // do something, if parameter not present
    }

    printf( "\tP1=%lf\r\n", param1);
    printf( "\tP2=%lf\r\n", param2);

    return SCPI_RES_OK;
}

static scpi_result_t TEST_Bool(scpi_t * context) {
    scpi_bool_t param1;
    printf( "TEST:BOOL\r\n"); // debug command name   

    // read first parameter if present
    if (!SCPI_ParamBool(context, &param1, TRUE)) {
        return SCPI_RES_ERR;
    }

    printf( "\tP1=%d\r\n", param1);

    return SCPI_RES_OK;
}

scpi_choice_def_t trigger_source[] = {
    {"BUS", 5},
    {"IMMediate", 6},
    {"EXTernal", 7},
    SCPI_CHOICE_LIST_END /* termination of option list */
};


static scpi_result_t TEST_ChoiceQ(scpi_t * context) {

    int32_t param;
    const char * name;
    
    if (!SCPI_ParamChoice(context, trigger_source, &param, TRUE)) {
        return SCPI_RES_ERR;
    }
    
    SCPI_ChoiceToName(trigger_source, param, &name);
    printf( "\tP1=%s (%ld)\r\n", name, (long int)param);
    
    SCPI_ResultInt(context, param);

    return SCPI_RES_OK;
}

static scpi_result_t TEST_Numbers(scpi_t * context) {
    int32_t numbers[2];

    SCPI_CommandNumbers(context, numbers, 2);

    printf( "TEST numbers %d %d\r\n", numbers[0], numbers[1]);

    return SCPI_RES_OK;
}

static scpi_result_t TEST_Text(scpi_t * context) {
    char buffer[100];
    size_t copy_len;

    SCPI_ParamCopyText(context, buffer, sizeof(buffer), &copy_len, FALSE);
    buffer[copy_len] = '\0';

    printf( "TEXT: ***%s***\r\n", buffer);

    return SCPI_RES_OK;
}

static scpi_result_t TEST_ArbQ(scpi_t * context) {
    const char * data;
    size_t len;

    SCPI_ParamArbitraryBlock(context, &data, &len, FALSE);

    SCPI_ResultArbitraryBlock(context, data, len);

    return SCPI_RES_OK;
}

/**
 * Reimplement IEEE488.2 *TST?
 *
 * Result should be 0 if everything is ok
 * Result should be 1 if something goes wrong
 *
 * Return SCPI_RES_OK
 */
static scpi_result_t My_CoreTstQ(scpi_t * context) {

    SCPI_ResultInt(context, 0);

    return SCPI_RES_OK;
}

static const scpi_command_t scpi_commands[] = {
    /* IEEE Mandated Commands (SCPI std V1999.0 4.1.1) */
    { .pattern = "*CLS", .callback = SCPI_CoreCls,},
    { .pattern = "*ESE", .callback = SCPI_CoreEse,},
    { .pattern = "*ESE?", .callback = SCPI_CoreEseQ,},
    { .pattern = "*ESR?", .callback = SCPI_CoreEsrQ,},
    { .pattern = "*IDN?", .callback = SCPI_CoreIdnQ,},
    { .pattern = "*OPC", .callback = SCPI_CoreOpc,},
    { .pattern = "*OPC?", .callback = SCPI_CoreOpcQ,},
    { .pattern = "*RST", .callback = SCPI_CoreRst,},
    { .pattern = "*SRE", .callback = SCPI_CoreSre,},
    { .pattern = "*SRE?", .callback = SCPI_CoreSreQ,},
    { .pattern = "*STB?", .callback = SCPI_CoreStbQ,},
    { .pattern = "*TST?", .callback = My_CoreTstQ,},
    { .pattern = "*WAI", .callback = SCPI_CoreWai,},

    /* Required SCPI commands (SCPI std V1999.0 4.2.1) */
    {.pattern = "SYSTem:ERRor[:NEXT]?", .callback = SCPI_SystemErrorNextQ,},
    {.pattern = "SYSTem:ERRor:COUNt?", .callback = SCPI_SystemErrorCountQ,},
    {.pattern = "SYSTem:VERSion?", .callback = SCPI_SystemVersionQ,},

    //{.pattern = "STATus:OPERation?", .callback = scpi_stub_callback,},
    //{.pattern = "STATus:OPERation:EVENt?", .callback = scpi_stub_callback,},
    //{.pattern = "STATus:OPERation:CONDition?", .callback = scpi_stub_callback,},
    //{.pattern = "STATus:OPERation:ENABle", .callback = scpi_stub_callback,},
    //{.pattern = "STATus:OPERation:ENABle?", .callback = scpi_stub_callback,},

    {.pattern = "STATus:QUEStionable[:EVENt]?", .callback = SCPI_StatusQuestionableEventQ,},
    //{.pattern = "STATus:QUEStionable:CONDition?", .callback = scpi_stub_callback,},
    {.pattern = "STATus:QUEStionable:ENABle", .callback = SCPI_StatusQuestionableEnable,},
    {.pattern = "STATus:QUEStionable:ENABle?", .callback = SCPI_StatusQuestionableEnableQ,},

    {.pattern = "STATus:PRESet", .callback = SCPI_StatusPreset,},

    /* DMM */
    {.pattern = "MEASure:VOLTage:DC?", .callback = DMM_MeasureVoltageDcQ,},
    {.pattern = "CONFigure:VOLTage:DC", .callback = DMM_ConfigureVoltageDc,},
    {.pattern = "MEASure:VOLTage:DC:RATio?", .callback = SCPI_StubQ,},
    {.pattern = "MEASure:VOLTage:AC?", .callback = DMM_MeasureVoltageAcQ,},
    {.pattern = "MEASure:CURRent:DC?", .callback = SCPI_StubQ,},
    {.pattern = "MEASure:CURRent:AC?", .callback = SCPI_StubQ,},
    {.pattern = "MEASure:RESistance?", .callback = SCPI_StubQ,},
    {.pattern = "MEASure:FRESistance?", .callback = SCPI_StubQ,},
    {.pattern = "MEASure:TEMPerature?", .callback = SCPI_StubQ,},
    {.pattern = "MEASure:PERiod?", .callback = SCPI_StubQ,},

    //{.pattern = "SYSTem:COMMunication:TCPIP:CONTROL?", .callback = SCPI_SystemCommTcpipControlQ,},

    {.pattern = "TEST:BOOL", .callback = TEST_Bool,},
    {.pattern = "TEST:CHOice?", .callback = TEST_ChoiceQ,},
    {.pattern = "TEST#:NUMbers#", .callback = TEST_Numbers,},
    {.pattern = "TEST:TEXT", .callback = TEST_Text,},
    {.pattern = "TEST:ARBitrary?", .callback = TEST_ArbQ,},

    SCPI_CMD_LIST_END
};

static scpi_interface_t scpi_interface = {
    .error = NULL,//SCPI_Error,
    .write = SCPI_Write,
    .control = NULL,//SCPI_Control,
    .flush = NULL,//SCPI_Flush,
    .reset = NULL,//SCPI_Reset,
};

scpi_t scpi_context = {
    .cmdlist = scpi_commands,
    .buffer = {
        .length = SCPI_INPUT_BUFFER_LENGTH,
        .data = scpi_input_buffer,
    },
    .interface = &scpi_interface,
    .registers = scpi_regs,
    .units = scpi_units_def,
    .idn = {"Advaced Microsystems Inc", "Keithley 199", NULL, REPOVERSION},
};

char buff[50];
void scpi_task(void* param){
    SCPI_Init(&scpi_context);
    while(1){
        int rec = usb_uart_readline(buff, 50);
        SCPI_Input(&scpi_context, buff, rec);
    }
}