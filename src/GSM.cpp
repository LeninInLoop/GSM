#include "GSM.h"
#include "GsmSms.h"

Gsm::Gsm(int rxPin, int txPin, int baudRate)
        : rxPin(rxPin),
          txPin(txPin),
          baudRate(baudRate),
          serialModule(rxPin, txPin, baudRate) {}

bool Gsm::verifyConnection() {
    // Check if the GSM module is ready & connected
    String response = serialModule.executeCommand("AT");
    return response.indexOf("OK") != -1;
}

GsmRegistrationInfo Gsm::fetchRegistrationDetails() {
    GsmRegistrationInfo registrationInfo{};
    String response = serialModule.executeCommand("AT+CGREG?");

    registrationInfo.unsolicitedNotificationEnabled = response.substring(
            0, response.indexOf(',')
            ).toInt();

    registrationInfo.registrationState = response.substring(
            response.indexOf(',') + 1
            ).toInt();

    return registrationInfo;
}

int Gsm::getSignalStrength() {
    String response = serialModule.executeCommand("AT+CSQ");

    int signalStrength = response.substring(
            response.indexOf("+CSQ:") + 5,
            response.indexOf(",")
            ).toInt();

    return signalStrength;
}

bool Gsm::setUnsolicitedNotification(int mode) {
    char command[20];
    sprintf(command, "AT+CGREG=%d", mode);
    String response = serialModule.executeCommand(command);
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

bool Gsm::isSIMReady() {
    String response = serialModule.executeCommand("AT+CPIN?");
    return (response.indexOf("+CPIN: READY") != -1);
}

String Gsm::getSIMStatus() {
    String response = serialModule.executeCommand("AT+CPIN?");
    if (response.indexOf("+CPIN: READY") != -1)
        return "Ready";
    else if (response.indexOf("+CPIN: SIM PIN") != -1)
        return "SIM PIN";
    if (response.indexOf("+CPIN: SIM PUK") != -1)
        return "SIM PUK";
    return "NOT INSERTED";
}

ProviderInfo Gsm::getProviderInfo() {
    ProviderInfo info;
    String response = serialModule.executeCommand("AT+COPS?");

    int commaCount = 0;
    bool containsOperatorName = false;
    for (char c: response) {
        if (c == ',')
            commaCount++;
        else if (c == '\"')
            containsOperatorName = true;
    }

    info.selectionMode = response.substring(
            response.indexOf(":"),
            response.indexOf(",")
            ).toInt();

    info.operatorFormat = response.substring(
            response.indexOf(","),
            response.indexOf(",") + 1
            ).toInt();

    if (commaCount == 2) {
        info.radioAccessTechnology = response.substring(
                response.indexOf(":"),
                response.indexOf("OK") - 4
                ).toInt();
    }

    if (containsOperatorName) {
        info.operatorName = response.substring(
                response.indexOf("\"") + 1,
                response.lastIndexOf("\""));
    }

    return info;
}

bool Gsm::sendSms(const char *phoneNumber, const char *message) {
    return GsmSms::sendSms(serialModule, phoneNumber, message);
}