//
// Created by adib on 5/26/24.
//

#include "GsmCall.h"
#include <Arduino.h>

bool GsmCall::call(GsmSerial& gsmModule, const char* phoneNumber)
{
    const char* command = buildCallCommand(phoneNumber);
    const String response = gsmModule.executeCommand(command);

    return (response.indexOf("OK") != -1);
}

const char* GsmCall::buildCallCommand(const char* phoneNumber)
{
    static char command[100];
    sprintf(command,"ATD%s;", phoneNumber);
    return command;
}
