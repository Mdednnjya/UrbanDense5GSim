#include "SMF.h"

Define_Module(SMF);

SMF::SMF() {
    // Constructor
}

SMF::~SMF() {
    // Destructor
}

void SMF::initialize() {
    upfAddress = par("upfAddress").stdstringValue();
    sessionSetupDelay = par("sessionSetupDelay");
}

void SMF::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        // Handle self messages
    } else {
        switch (msg->getKind()) {
            case SESSION_REQUEST: {
                handleSessionRequest(msg);
                break;
            }
            case SESSION_RESPONSE: {
                // Handle response from UPF
                break;
            }
            default:
                delete msg; // Clean up unknown messages
                return;
        }
    }
    delete msg; // Clean up message
}

void SMF::handleSessionRequest(cMessage *msg) {
    // Process session request
    // Simulate session setup delay
    scheduleAt(simTime() + sessionSetupDelay, msg);
    // After delay, send response back to AMF
    cMessage *sessionResponse = new cMessage(SESSION_RESPONSE);
    send(sessionResponse, amfg);
}
