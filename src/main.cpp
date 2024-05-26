#include <Arduino.h>
#include "GSM.h"

#define baudrate 115200

void initializeSerialDebug() {
    Serial.begin(baudrate);
}

Gsm gsmModule(11, 8, baudrate);

void setup() {
    initializeSerialDebug();
    delay(5000); // Wait for the GSM module to initialize

    const auto response_0 = gsmModule.setBaudRate(baudrate);
    Serial.println(response_0);

    const auto response_1 = gsmModule.saveCurrentConfigurations();
    Serial.println(response_1);

    // Test GSM module connection
    if (gsmModule.verifySerialConnection()) {
        Serial.println("GSM Connection Established");
    } else {
        Serial.println("GSM Connection Failed");
    }

    // Test GSM registration details
    const auto gsmRegistrationInfo = gsmModule.getRegistrationDetails();
    Serial.println("Unsolicited notification enabled: " + String(gsmRegistrationInfo.unsolicitedNotificationEnabled));
    Serial.println("Registration state: " + String(gsmRegistrationInfo.registrationState));

    // Test signal strength
    int signalStrength = gsmModule.getSignalStrength();
    Serial.println("Signal strength: " + String(signalStrength));

    // Test SMS sending
    const auto phoneNumber = "+989170137789";
    const auto message = "Hello, this is a test SMS message.";
    if (gsmModule.sendSms(phoneNumber, message)) {
        Serial.println("SMS sent successfully");
    } else {
        Serial.println("Failed to send SMS");
    }

    const auto AvailableBaudRates = gsmModule.getSIMStatus();
    Serial.println(AvailableBaudRates);

    const auto isSIMReady = gsmModule.isSIMReady();
    Serial.println(isSIMReady);

    const auto providerInfo = gsmModule.getProviderInfo();
    Serial.println(providerInfo.operatorName);
    Serial.println(providerInfo.selectionMode);
    Serial.println(providerInfo.operatorFormat);
    Serial.println(providerInfo.radioAccessTechnology);

    const auto response = gsmModule.getModelNumber();
    Serial.println(response);

    const auto response2 = gsmModule.getManufacturerName();
    Serial.println(response2);

    const auto response3 = gsmModule.getIMEI();
    Serial.println(response3);

    const auto response4 = gsmModule.getSoftwareVersion();
    Serial.println(response4);

    const auto response5 = gsmModule.getIMSI();
    Serial.println(response5);

    const auto response6 = gsmModule.getISDNNumber();
    Serial.println(response6);

    const auto response7 = gsmModule.getBatteryStatus();
    Serial.println(response7.chargeStatus);
    Serial.println(response7.chargeLevel);
    Serial.println(response7.voltage);

    const auto response8 = gsmModule.call("+989170137789");
    Serial.println(response8);
}

void loop() {
    // Main loop code goes here
}