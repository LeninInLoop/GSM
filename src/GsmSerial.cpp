//
// Created by Adib on 5/19/2024.
//

#include <SoftwareSerial.h>
#include <Arduino.h>
#include "GsmSerial.h"

GsmSerial::GsmSerial(const int rxPin, const int txPin, const int baudRate)
        : serialModule(rxPin, txPin),
          rxPin(rxPin),
          txPin(txPin),
          baudRate(baudRate) {
    serialModule.begin(baudRate);
}

String GsmSerial::readReceivedData() {
    String receivedData = "";
    int dataCount = 0;

    delay(1000); // Delay to ensure data is ready to be read
    while (serialModule.available() > 0) {
        char receivedCharacter = (char)serialModule.read();
        receivedData += receivedCharacter;

        if (dataCount > 50)
            break;

        dataCount++;
    }

    return receivedData;
}

String GsmSerial::executeCommand(const char* commandToSend) {
    serialModule.println(commandToSend); // Send the command to the GSMModule
    return readReceivedData();
}