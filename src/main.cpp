#include <Arduino.h>
#include "GSM.h"

void initializeSerialDebug() {
    Serial.begin(9600);
}

Gsm gsmModule(10, 5, 9600);

void setup() {
    initializeSerialDebug();
    delay(5000); // Wait for the GSM module to initialize

    // Test GSM module connection
    if (gsmModule.verifySerialConnection()) {
        Serial.println("GSM Connection Established");
    } else {
        Serial.println("GSM Connection Failed");
    }

    // Test GSM registration details
    auto gsmRegistrationInfo = gsmModule.fetchRegistrationDetails();
    Serial.println("Unsolicited notification enabled: " + String(gsmRegistrationInfo.unsolicitedNotificationEnabled));
    Serial.println("Registration state: " + String(gsmRegistrationInfo.registrationState));

    // Test signal strength
    int signalStrength = gsmModule.getSignalStrength();
    Serial.println("Signal strength: " + String(signalStrength));

    // // Test SMS sending
    // const char* phoneNumber = "+98";
    // const char* message = "Hello, this is a test SMS message.";
    // if (gsmModule.sendSms(phoneNumber, message)) {
    //     Serial.println("SMS sent successfully");
    // } else {
    //     Serial.println("Failed to send SMS");
    // }

    auto AvailableBaudRates = gsmModule.getSIMStatus();
    Serial.println(AvailableBaudRates);

    auto isSIMReady = gsmModule.isSIMReady();
    Serial.println(isSIMReady);

    auto providerInfo = gsmModule.getProviderInfo();
    Serial.println(providerInfo.operatorName);
    Serial.println(providerInfo.selectionMode);
    Serial.println(providerInfo.operatorFormat);
    Serial.println(providerInfo.radioAccessTechnology);
}

void loop() {
    // Main loop code goes here
}