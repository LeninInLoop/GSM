#ifndef GSM_GSMSMS_H
#define GSM_GSMSMS_H

#include "GsmSerial.h"

class GsmSms {
public:
    /**
     * Sends an SMS message using the provided GsmSerial instance.
     * @param gsmModule the GsmSerial instance to use for communication.
     * @param phoneNumber the phone number to send the SMS to.
     * @param message the SMS message to be sent.
     * @return true if the SMS was sent successfully, false otherwise.
     */
    static bool sendSms(GsmSerial& gsmModule, const char* phoneNumber, const char* message);

private:
    /**
     * Sets the SMS mode to text mode.
     * @param gsmModule the GsmSerial instance to use for communication.
     * @return true if the text mode was set successfully, false otherwise.
     */
    static bool setTextMode(GsmSerial& gsmModule);

    /**
     * Builds the command to send the SMS.
     * @param phoneNumber the phone number to send the SMS to.
     * @return the command string.
     */
    static const char* buildSendSmsCommand(const char* phoneNumber);

    /**
     * Initiates the SMS sending process.
     * @param gsmModule the GsmSerial instance to use for communication.
     * @param command the command to initiate the SMS sending.
     * @return true if the SMS sending was initiated successfully, false otherwise.
     */
    static bool initiateSMSSend(GsmSerial& gsmModule, const char* command);

    /**
     * Sends the SMS message.
     * @param gsmModule the GsmSerial instance to use for communication.
     * @param message the SMS message to be sent.
     */
    static void sendSmsMessage(GsmSerial& gsmModule, const char* message);

    /**
     * Sends the end-of-text character (Ctrl+Z) to indicate the end of the SMS message.
     * @param gsmModule the GsmSerial instance to use for communication.
     */
    static void sendEndOfText(GsmSerial& gsmModule);

    /**
     * Checks the response from the GSM module for a successful SMS send.
     * @param gsmModule the GsmSerial instance to use for communication.
     * @return true if the SMS was sent successfully, false otherwise.
     */
    static bool checkSMSSendResponse(GsmSerial& gsmModule);
};

#endif //GSM_GSMSMS_H