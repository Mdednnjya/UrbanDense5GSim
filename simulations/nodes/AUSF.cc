#include "AUSF.h"

Define_Module(AUSF);

AUSF::AUSF() {
    // Constructor
}

AUSF::~AUSF() {
    // Destructor
}

void AUSF::initialize() {
    udmAddress = par("udmAddress").stdstringValue();
    authenticationDelay = par("authenticationDelay");
}

void AUSF::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        // Handle self messages
    } else {
        switch (msg->getKind()) {
            case AUTH_REQUEST: {
                handleAuthRequest(msg);
                break;
            }
            case AUTH_RESPONSE: {
                // Handle response from UDM
                break;
            }
            default:
                delete msg; // Clean up unknown messages
                return;
        }
    }
    delete msg; // Clean up message
}

void AUSF::handleAuthRequest(cMessage *msg) {
    // Process authentication request
    // Send response back to AMF
    cMessage *authResponse = new cMessage(AUTH_RESPONSE);
    send(authResponse, amfg);
}
