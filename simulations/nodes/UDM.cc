#include "UDM.h"

Define_Module(UDM);

UDM::UDM() {
    // Constructor
}

UDM::~UDM() {
    // Destructor
}

void UDM::initialize() {
    dataRetrievalDelay = par("dataRetrievalDelay");
    databaseFile = par("databaseFile").stdstringValue();
}

void UDM::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        // Handle self messages
    } else {
        switch (msg->getKind()) {
            case DATA_REQUEST: {
                handleDataRequest(msg);
                break;
            }
            case DATA_RESPONSE: {
                // Handle response from database
                break;
            }
            default:
 delete msg; // Clean up unknown messages
                return;
        }
    }
    delete msg; // Clean up message
}

void UDM::handleDataRequest(cMessage *msg) {
    // Process data request for subscriber information
    // Simulate data retrieval delay
    scheduleAt(simTime() + dataRetrievalDelay, msg);
    // After delay, send response back to AUSF
    cMessage *dataResponse = new cMessage(DATA_RESPONSE);
    send(dataResponse, ausfg);
}
