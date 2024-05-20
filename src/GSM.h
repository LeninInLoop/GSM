#ifndef GSM_GSM_H
#define GSM_GSM_H

#include "GsmSerial.h"

struct GsmRegistrationInfo {
    int unsolicitedNotificationEnabled; // Indicates if unsolicited notifications are enabled
    int registrationState; // Current registration state of the GSM module
};

class Gsm {
public:
    Gsm(int rxPin, int txPin, int baudRate);

    /**
     * Checks if the GSM module is ready.
     * @return true if the GSM module is ready, false otherwise.
     */
    bool verifyConnection();

    /**
     * Retrieves the GSM module registration details.
     * @return GsmRegistrationInfo struct containing the unsolicited notification status and registration state.
     */
    GsmRegistrationInfo fetchRegistrationDetails();

    /**
     * Retrieves the signal strength of the GSM module.
     * @return the signal strength as an integer value.
     */
    int getSignalStrength();

    /**
     * Sets the unsolicited notification mode for the GSM module.
     * @param mode the unsolicited notification mode (0 - disabled, 1 - enabled, 2 - enabled with additional info).
     * @return true if the operation was successful, false otherwise.
     */
    bool setUnsolicitedNotification(int mode);

    /**
     * Gets the RX pin of the GSM module.
     * @return the RX pin.
     */
    int getRxPin() const;

    /**
     * Gets the TX pin of the GSM module.
     * @return the TX pin.
     */
    int getTxPin() const;

    /**
     * Gets the baud rate of the GSM module.
     * @return the baud rate.
     */
    int getBaudRate() const;

    /**
     * Sends an SMS message using the provided GsmSerial instance.
     * @param phoneNumber the phone number to send the SMS to.
     * @param message the SMS message to be sent.
     * @return true if the SMS was sent successfully, false otherwise.
     */
    bool sendSms(const char* phoneNumber, const char* message);

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

    /**
     * The SoftwareSerial object used for communication with the GSM module.
     */
    GsmSerial gsmSerialModule;
};

#endif //GSM_GSM_H