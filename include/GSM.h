#ifndef GSM_GSM_H
#define GSM_GSM_H

#include "GsmSerial.h"

struct GsmRegistrationInfo {
    int unsolicitedNotificationEnabled; // Indicates if unsolicited notifications are enabled
    int registrationState; // Current registration state of the GSM module
};

struct ProviderInfo {
    int selectionMode;
    int operatorFormat;
    String operatorName;
    int radioAccessTechnology;
};

class Gsm {
public:
    Gsm(int rxPin, int txPin, int baudRate);

    /**
     * Checks if the GSM module is ready.
     * @return true if the GSM module is ready, false otherwise.
     */
    bool verifySerialConnection();

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
     * Checks if the SIM card inside the GSM module is ready and responsive.
     * @return true if the SIM card inside the GSM module is ready, false otherwise.
     */
    bool isSIMReady();

    /**
     * Checks the presence and status of the SIM card.
     *
     * The possible responses include:
     *      - "READY" - SIM card is present and ready for use.
     *      - "SIM PIN" - SIM card is present but requires a PIN code.
     *      - "SIM PUK" - SIM card is blocked and requires a PUK code.
     *      - "NOT INSERTED" - SIM card is not inserted.
     *
     * @return status of the card as a String.
     */
    String getSIMStatus();

    /**
     * Retrieves provider information using the provided GsmSerial instance.
     * This method queries the GSM module for details about the currently selected network provider,
     * including the selection mode, operator format, operator name, and radio access technology.
     *
     * @return A ProviderInfo structure containing the retrieved provider information.
     *         - selectionMode: The selection mode of the network operator.
     *         - operatorFormat: The format of the operator identifier.
     *         - operatorName: The name of the operator.
     *         - radioAccessTechnology: The radio access technology being used.
     */
    ProviderInfo getProviderInfo();

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
    GsmSerial serialModule;

};

#endif //GSM_GSM_H