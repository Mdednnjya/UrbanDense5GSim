#include <omnetpp.h>
#include "AMF.h"
#include "AUSF.h"
#include "UDM.h"
#include "../messages/NetworkMessages_m.h"

Define_Module(AMF);

void AMF::initialize() {
    maxRetries = par("maxRetries");
    timeout = par("timeout");
    registrationTimeout = timeout;
    timeoutEvent = new cMessage("registrationTimeout");

    // Get module references
    udmModule = getModuleByPath(par("udmAddress"));
    ausfModule = getModuleByPath(par("ausfAddress"));
    smfModule = getModuleByPath(par("smfAddress"));

    if (!udmModule || !ausfModule || !smfModule) {
        EV_ERROR << "Required modules not found!" << omnetpp::endl;
    }
}

void AMF::handleMessage(cMessage* msg) {
    if (msg->isSelfMessage()) {
        handleTimeout(msg);
    } else {
        if (msg->getArrivalGate() == gate("in")) {
            processRegistrationRequest(check_and_cast<RegistrationRequest*>(msg));
        } else if (msg->getArrivalGate() == gate("ausfg$i")) {
            handleAuthenticationResponse(check_and_cast<AuthenticationResponse*>(msg));
        }
    }
}

void AMF::processRegistrationRequest(RegistrationRequest* msg) {
    // Send authentication request to AUSF
    sendAuthenticationRequest(msg);
    // Start timeout for registration
    scheduleAt(simTime() + registrationTimeout, timeoutEvent);
}

void AMF::sendAuthenticationRequest(RegistrationRequest* msg) {
    AUSF* ausf = check_and_cast<AUSF*>(getParentModule()->getSubmodule("ausf"));
    AuthenticationRequest* authReq = new AuthenticationRequest("AuthenticationRequest");
    authReq->setUeId(msg->getUeId());
    send(authReq, "ausfOut");
}

void AMF::handleAuthenticationResponse(AuthenticationResponse* msg) {
    // Process the authentication response from AUSF
    // If authenticated, communicate with UDM for subscriber data
    UDM* udm = check_and_cast<UDM*>(getParentModule()->getSubmodule("udm"));
    SubscriberDataRequest* request = new SubscriberDataRequest("SubscriberDataRequest");
    request->setUeId(msg->getUeId());
    send(request, "udmOut");
}

void AMF::handleTimeout(cMessage* msg) {
    // Handle registration timeout
    EV << "Registration timeout occurred for UE ID: " << msg->getKind() << omnetpp::endl;
    delete msg;
}

void AMF::finish() {
    cancelAndDelete(timeoutEvent);
}
