#include "GSM.h"
#include "GsmSms.h"

Gsm::Gsm(int rxPin, int txPin, int baudRate)
        : rxPin(rxPin),
          txPin(txPin),
          baudRate(baudRate),
          gsmSerialModule(rxPin, txPin, baudRate) {}

bool Gsm::verifyConnection() {
    // Check if the GSM module is ready
    String response = gsmSerialModule.executeCommand("AT");
    return response.indexOf("OK") != -1;
}

GsmRegistrationInfo Gsm::fetchRegistrationDetails() {
    GsmRegistrationInfo registrationInfo{};
    String response = gsmSerialModule.executeCommand("AT+CGREG?");
    registrationInfo.unsolicitedNotificationEnabled = response.substring(0, response.indexOf(',')).toInt();
    registrationInfo.registrationState = response.substring(response.indexOf(',') + 1).toInt();
    return registrationInfo;
}

int Gsm::getSignalStrength() {
    String response = gsmSerialModule.executeCommand("AT+CSQ");
    int signalStrength = response.substring(response.indexOf("+CSQ:") + 5, response.indexOf(",")).toInt();
    return signalStrength;
}

bool Gsm::setUnsolicitedNotification(int mode) {
    char command[20];
    sprintf(command, "AT+CGREG=%d", mode);
    String response = gsmSerialModule.executeCommand(command);
    return response.indexOf("OK") != -1;
}

int Gsm::getRxPin() const {
    return rxPin;
}

int Gsm::getTxPin() const {
    return txPin;
}

int Gsm::getBaudRate() const {
    return baudRate;
}

bool Gsm::sendSms(const char *phoneNumber, const char *message) {
    return GsmSms::sendSms(gsmSerialModule, phoneNumber, message);
}