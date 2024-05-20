//
// Created by Adib on 5/19/2024.
//

#ifndef GSM_SERIAL_H
#define GSM_SERIAL_H

#include <SoftwareSerial.h>

/**
 * The GsmSerial class provides a wrapper around the SoftwareSerial library to communicate with a GSM module.
 * It handles the low-level serial communication and provides methods to execute commands and read responses.
 */
class GsmSerial {
public:
    /**
     * Constructs a GsmSerial object with the specified RX pin, TX pin, and baud rate.
     * @param rxPin the RX pin connected to the GSM module.
     * @param txPin the TX pin connected to the GSM module.
     * @param baudRate the baud rate for the serial communication.
     */
    GsmSerial(int rxPin, int txPin, int baudRate);

    /**
     * Executes a command on the GSM module and returns the response.
     * @param commandToSend the command to be executed.
     * @return the response from the GSM module.
     */
    String executeCommand(const char* commandToSend);

    /**
     * Reads the response from the GSM module.
     * @return the response from the GSM module.
     */
    String readReceivedData();

    /**
     * The SoftwareSerial object used for communication with the GSM module.
     */
    SoftwareSerial GSMSerialModule;

private:
    /**
     * The RX pin connected to the GSM module.
     */
    const int rxPin;

    /**
     * The TX pin connected to the GSM module.
     */
    const int txPin;

    /**
     * The baud rate for the serial communication with the GSM module.
     */
    const int baudRate;

};

#endif //GSM_SERIAL_H