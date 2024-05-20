#include "GsmSms.h"
#include "GsmSerial.h"
#include "Arduino.h"

bool GsmSms::sendSms(GsmSerial& gsmModule, const char* phoneNumber, const char* message) {
    // Set the SMS mode to text mode
    if (!setTextMode(gsmModule)) {
        return false;
    }

    // Prepare the command to send the SMS
    const char* command = buildSendSmsCommand(phoneNumber);

    // Send the command to initiate the SMS sending
    if (!initiateSMSSend(gsmModule, command)) {
        return false;
    }

    // Send the message
    sendSmsMessage(gsmModule, message);

    // Send the end-of-text character (Ctrl+Z)
    sendEndOfText(gsmModule);

    // Wait for the response and check for success
    return checkSMSSendResponse(gsmModule);
}

bool GsmSms::setTextMode(GsmSerial& gsmModule) {
    String response = gsmModule.executeCommand("AT+CMGF=1");
    return response.indexOf("OK") != -1;
}

const char* GsmSms::buildSendSmsCommand(const char* phoneNumber) {
    static char command[100];
    sprintf(command, "AT+CMGS=\"%s\"", phoneNumber);
    return command;
}

bool GsmSms::initiateSMSSend(GsmSerial& gsmModule, const char* command) {
    String response = gsmModule.executeCommand(command);
    return response.indexOf(">") != -1;
}

void GsmSms::sendSmsMessage(GsmSerial& gsmModule, const char* message) {
    gsmModule.executeCommand(message);
}

void GsmSms::sendEndOfText(GsmSerial& gsmModule) {
    gsmModule.serialModule.write(0x1A);
}

bool GsmSms::checkSMSSendResponse(GsmSerial& gsmModule) {
    unsigned long startTime = millis();
    const unsigned long timeout = 10000; // 10 seconds timeout

    while (millis() - startTime < timeout) {
        String response = gsmModule.readReceivedData();
        if (response.indexOf("+CMGS:") != -1) {
            // The +CMGS: response indicates the SMS has been sent successfully
            return true;
        }
        if (response.indexOf("ERROR") != -1) {
            // The ERROR response indicates a failure in sending the SMS
            return false;
        }
        delay(100); // Wait for a short time before checking the response again
    }

    // Timeout reached without receiving a valid response
    return false;
}