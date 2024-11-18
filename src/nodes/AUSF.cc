#include "AUSF.h"

Define_Module(AUSF);

void AUSF::initialize() {
    maxAuthRetries = par("maxAuthRetries");
    authTimeout = par("authTimeout");
    authenticationTimeout = authTimeout;

    // Get module references
    udmModule = getModuleByPath(par("udmAddress"));
    amfModule = getModuleByPath(par("amfAddress"));

    if (!udmModule || !amfModule) {
        EV_ERROR << "Required modules not found!" << omnetpp::endl;
    }
}

void AUSF::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        // Handle timeouts
        int ueId = msg->getKind();
        cleanupAuthVector(ueId);
        delete msg;
    } else {
        if (AuthenticationRequest *request = dynamic_cast<AuthenticationRequest *>(msg)) {
            handleAuthenticationRequest(request);
        } else if (AuthVector *response = dynamic_cast<AuthVector *>(msg)) {
            processUDMResponse(response);
        }
        delete msg;
    }
}

void AUSF::handleAuthenticationRequest(AuthenticationRequest *request) {
    int ueId = request->getUeId();

    // Request authentication vectors from UDM
    AuthVector *authReq = new AuthVector();
    authReq->setUeId(ueId);
    send(authReq, "udmg$o");

    // Cache the pending authentication
    authVectorCache[ueId] = nullptr;

    // Set timeout
    cMessage *timeoutMsg = new cMessage("authTimeout");
    timeoutMsg->setKind(ueId);
    scheduleAt(simTime() + authenticationTimeout, timeoutMsg);
}

void AUSF::processUDMResponse(AuthVector *response) {
    int ueId = response->getUeId();

    if (authVectorCache.find(ueId) != authVectorCache.end()) {
        // Verify authentication vector
        bool authSuccess = true; // In real implementation, verify XRES
        sendAuthResponseToAMF(ueId, authSuccess);
        cleanupAuthVector(ueId);
    }
}

void AUSF::sendAuthResponseToAMF(int ueId, bool success) {
    AuthenticationResponse *response = new AuthenticationResponse();
    response->setUeId(ueId);
    response->setAuthenticated(success);
    send(response, "amfg$o");
}

void AUSF::cleanupAuthVector(int ueId) {
    auto it = authVectorCache.find(ueId);
    if (it != authVectorCache.end()) {
        delete it->second;
        authVectorCache.erase(it);
    }
}
