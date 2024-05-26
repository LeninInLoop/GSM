#include "GSM.h"

#include <GsmCall.h>

#include "GsmSms.h"

Gsm::Gsm(int const rxPin, int const txPin, long int const baudRate)
    : rxPin(rxPin),
      txPin(txPin),
      baudRate(baudRate),
      serialModule(rxPin, txPin, baudRate)
{
    setBaudRate(baudRate);
}

bool Gsm::verifySerialConnection()
{
    // Check if the GSM module is ready & connected
    const String response = serialModule.executeCommand("AT");
    return response.indexOf("OK") != -1;
}

GsmRegistration Gsm::getRegistrationDetails()
{
    GsmRegistration registrationInfo{};
    const String response = serialModule.executeCommand("AT+CGREG?");

    registrationInfo.unsolicitedNotificationEnabled = response.substring(
        0, response.indexOf(',')
    ).toInt();

    registrationInfo.registrationState = response.substring(
        response.indexOf(',') + 1
    ).toInt();

    return registrationInfo;
}

int Gsm::getSignalStrength()
{
    const String response = serialModule.executeCommand("AT+CSQ");

    int signalStrength = response.substring(
        response.indexOf("+CSQ:") + 5,
        response.indexOf(",")
    ).toInt();

    return signalStrength;
}

bool Gsm::setUnsolicitedNotification(int const mode)
{
    char command[15];
    switch (mode)
    {
    case 0:
        sprintf(command, "AT+CGREG=0");
        break;
    case 1:
        sprintf(command, "AT+CGREG=1");
        break;
    case 2:
        sprintf(command, "AT+CGREG=2");
        break;
    default:
        // Handle invalid mode
        return false;
    }
    const String response = serialModule.executeCommand(command);
    return response.indexOf("OK") != -1;
}

int Gsm::getRxPin() const
{
    return rxPin;
}

int Gsm::getTxPin() const
{
    return txPin;
}

long int Gsm::getBaudRate() const
{
    return baudRate;
}

bool Gsm::setBaudRate(long int const baudrate)
{
    char command[50];
    sprintf(command,"AT+IPR=%ld",baudrate);

    const String response = serialModule.executeCommand(command);
    return response.indexOf("OK") != -1;
}

bool Gsm::saveCurrentConfigurations()
{
    const String response = serialModule.executeCommand("AT&W");
    return response.indexOf("OK") != -1;
}

bool Gsm::isSIMReady()
{
    const String response = serialModule.executeCommand("AT+CPIN?");
    return (response.indexOf("+CPIN: READY") != -1);
}

String Gsm::getSIMStatus()
{
    const String response = serialModule.executeCommand("AT+CPIN?");
    if (response.indexOf("+CPIN: READY") != -1)
        return "Ready";
    else if (response.indexOf("+CPIN: SIM PIN") != -1)
        return "SIM PIN";
    if (response.indexOf("+CPIN: SIM PUK") != -1)
        return "SIM PUK";
    return "NOT INSERTED";
}

Provider Gsm::getProviderInfo()
{
    Provider info;
    String response = serialModule.executeCommand("AT+COPS?");

    int commaCount = 0;
    bool containsOperatorName = false;
    for (char const c : response)
    {
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

    if (commaCount == 3)
    {
        info.radioAccessTechnology = response.substring(
            response.indexOf(":"),
            response.indexOf("OK") - 4
        ).toInt();
    }

    if (containsOperatorName)
    {
        info.operatorName = response.substring(
            response.indexOf("\"") + 1,
            response.lastIndexOf("\""));
    }

    return info;
}

bool Gsm::sendSms(const char* phoneNumber, const char* message)
{
    return GsmSms::sendSms(serialModule, phoneNumber, message);
}

bool Gsm::call(const char* phoneNumber)
{
    return GsmCall::call(serialModule, phoneNumber);
}

String Gsm::getModelNumber()
{
    const String response = serialModule.executeCommand("AT+CGMM");

    if (response.indexOf("OK") == -1)
    {
        return "NOT_FOUND";
    }
    String modelNumber = response.substring(
        7,
        response.indexOf("OK"));

    modelNumber.trim();
    return modelNumber;
}

String Gsm::getManufacturerName()
{
    const String response = serialModule.executeCommand("AT+CGMI");

    if (response.indexOf("OK") == -1)
    {
        return "NOT_FOUND";
    }
    String manufactorName = response.substring(
        7,
        response.indexOf("OK"));

    manufactorName.trim();
    return manufactorName;
}

String Gsm::getIMEI()
{
    const String response = serialModule.executeCommand("AT+CGSN");

    if (response.indexOf("OK") == -1)
    {
        return "NOT_FOUND";
    }
    String IMEI = response.substring(
        7,
        response.indexOf("OK"));

    IMEI.trim();
    return IMEI;
}

String Gsm::getSoftwareVersion()
{
    const String response = serialModule.executeCommand("AT+CGMR");

    if (response.indexOf("OK") == -1)
    {
        return "NOT_FOUND";
    }

    String softwareVersion = response.substring(
        7,
        response.indexOf("OK"));

    softwareVersion.trim();
    return softwareVersion;
}

String Gsm::getIMSI()
{
    const String response = serialModule.executeCommand("AT+CIMI");

    if (response.indexOf("OK") == -1)
    {
        return "NOT_FOUND";
    }

    String IMSI = response.substring(
        7,
        response.indexOf("OK"));

    IMSI.trim();
    return IMSI;
}

String Gsm::getISDNNumber()
{
    const String response = serialModule.executeCommand("AT+CNUM");

    if (response.indexOf("OK") == -1)
    {
        return "NOT_FOUND";
    }

    if (response.indexOf("My Number") == -1)
    {
        return "NOT_FOUND";
    }

    String ISDNNumber = response.substring(
        response.lastIndexOf("+"),
        response.lastIndexOf("\""));

    return ISDNNumber;
}

Battery Gsm::getBatteryStatus()
{
    Battery batteryStatus;
    const String response = serialModule.executeCommand("AT+CBC");

    if (response.indexOf("OK") == -1)
    {
        return batteryStatus;
    }

    batteryStatus.chargeStatus = response.substring(
        response.indexOf(":") + 1,
        response.indexOf(",")
    ).toInt();

    batteryStatus.chargeLevel = response.substring(
        response.indexOf(",") + 1,
        response.lastIndexOf(",")
    ).toInt();

    batteryStatus.voltage = response.substring(
        response.lastIndexOf(",") + 1,
        response.lastIndexOf("OK")
    ).toInt();

    return batteryStatus;
}
