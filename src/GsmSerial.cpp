//
// Created by Adib on 5/19/2024.
//

#include <SoftwareSerial.h>
#include <Arduino.h>
#include "GsmSerial.h"

GsmSerial::GsmSerial(const int rxPin, const int txPin, const int baudRate)
        : rxPin(rxPin),
          txPin(txPin),
          baudRate(baudRate),
          GSMSerialModule(rxPin, txPin) {
    GSMSerialModule.begin(baudRate);
}

String GsmSerial::readReceivedData() {
    String receivedData = "";
    delay(1000); // Delay to ensure data is ready to be read

    while (GSMSerialModule.available() > 0) {
        char receivedCharacter = (char)GSMSerialModule.read();
        receivedData += receivedCharacter;
    }

    return receivedData;
}

String GsmSerial::executeCommand(const char* commandToSend) {
    GSMSerialModule.println(commandToSend); // Send the command to the GSMModule
    return readReceivedData();
}