//
// Created by adib on 5/26/24.
//

#ifndef GSMCALL_H
#define GSMCALL_H
#include <GsmSerial.h>


class GsmCall {
public:
    /**
     * Calls a number using the provided GsmSerial instance.
     * @param gsmModule the GsmSerial instance to use for communication.
     * @param phoneNumber the phone number to call.
     * @return true if the Call was sent successfully, false otherwise.
     */
    static bool call(GsmSerial& gsmModule, const char* phoneNumber);

private:

    /**
     * Builds the command to Call.
     * @param phoneNumber the phone number to Call.
     * @return the command string.
     */
    static const char* buildCallCommand(const char* phoneNumber);
};



#endif //GSMCALL_H
