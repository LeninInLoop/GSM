#ifndef GSM_GSM_H
#define GSM_GSM_H

#include "GsmSerial.h"

struct GsmRegistrationInfo {
    int unsolicitedNotificationEnabled = 0; // Indicates if unsolicited notifications are enabled
    int registrationState = 0; // Current registration state of the GSM module
};

struct ProviderInfo {
    int selectionMode = 0;
    int operatorFormat = 0;
    String operatorName = "";
    int radioAccessTechnology = 0;
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

    /**
     * Retrieves the model number of the connected GSM module.
     *
     * extracts the model number from the response, and returns it.
     * if the model number could not be retrieved it returns "NOT_FOUND"
     *
     * @return A string representing the model number of the GSM module, or "NOT_FOUND" if the model number could not be retrieved.
     */
    String getModelNumber();

    /**
     * Retrieves the manufacturer name of the connected GSM module.
     *
     * Extracts the manufacturer name from the response and returns it.
     * If the manufacturer name could not be retrieved, it returns "NOT_FOUND".
     *
     * @return A string representing the manufacturer name of the GSM module, or "NOT_FOUND" if the manufacturer name could not be retrieved.
     */
    String getManufacturerName();

    /**
     * Retrieves the IMEI (International Mobile Equipment Identity) of the connected GSM module.
     *
     * Extracts the IMEI from the response and returns it.
     * If the IMEI could not be retrieved, it returns "NOT_FOUND".
     *
     * @return A string representing the IMEI of the GSM module, or "NOT_FOUND" if the IMEI could not be retrieved.
     */
    String getIMEI();

    /**
     * Retrieves the software version of the connected GSM module.
     *
     * Extracts the software version from the response and returns it.
     * If the software version could not be retrieved, it returns "NOT_FOUND".
     *
     * @return A string representing the software version of the GSM module, or "NOT_FOUND" if the software version could not be retrieved.
     */
    String getSoftwareVersion();

    /**
     * Retrieves the International Mobile Subscriber Identity (IMSI) of the connected GSM module.
     *
     * Extracts the IMSI from the response of the AT command "AT+CIMI".
     * If the IMSI could not be retrieved, it returns "NOT_FOUND".
     *
     * @return A string representing the IMSI of the GSM module, or "NOT_FOUND" if the IMSI could not be retrieved.
     */
    String getIMSI();

    /**
     * Retrieves the Integrated Services Digital Network (ISDN) Number of the connected GSM module.
     *
     * Extracts the ISDN number from the response of the AT command "AT+CNUM".
     * If the ISDN number could not be retrieved, it returns "NOT_FOUND".
     *
     * @return A string representing the ISDN number of the GSM module, "NOT_FOUND" if the ISDN number could not be retrieved.
     */
    String getISDNNumber();


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