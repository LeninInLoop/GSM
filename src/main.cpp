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
    if (gsmModule.verifyConnection()) {
        Serial.println("GSM Connection Established");
    } else {
        Serial.println("GSM Connection Failed");
    }

    // Test GSM registration details
    GsmRegistrationInfo gsmRegistrationInfo = gsmModule.fetchRegistrationDetails();
    Serial.println("Unsolicited notification enabled: " + String(gsmRegistrationInfo.unsolicitedNotificationEnabled));
    Serial.println("Registration state: " + String(gsmRegistrationInfo.registrationState));

    // Test signal strength
    int signalStrength = gsmModule.getSignalStrength();
    Serial.println("Signal strength: " + String(signalStrength));

    // Test SMS sending
    const char* phoneNumber = "+12132432435";
    const char* message = "Hello, this is a test SMS message.";
    if (gsmModule.sendSms(phoneNumber, message)) {
        Serial.println("SMS sent successfully");
    } else {
        Serial.println("Failed to send SMS");
    }
}

void loop() {
    // Main loop code goes here
}