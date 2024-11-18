#include "SMF.h"

Define_Module(SMF);

void SMF::initialize() {
    // Initialize parameters
    sessionTimeout = par("sessionTimeout");

    // Get reference to UPF module
    upfModule = getModuleByPath(par("upfAddress"));
    if (!upfModule) {
        EV_ERROR << "UPF module not found!" << omnetpp::endl;
    }
}

void SMF::handleMessage(cMessage *msg) {
    // Process incoming messages
    if (msg->isSelfMessage()) {
        // Handle timeout
        cleanupSession(msg->getKind());
    } else {
        // Handle session establishment request
        if (auto *request = dynamic_cast<SessionRequest *>(msg)) {
            // Now using the correct field name as defined in the message
            handleSessionRequest(request->getUeId(), request->getSessionType());
        }
    }
    delete msg;
}

void SMF::handleSessionRequest(int ueId, const std::string& qosProfile) {
    SessionInfo session;
    session.ueId = ueId;
    session.qosProfile = qosProfile;
    session.active = true;

    sessions[ueId] = session;
    configureUPF(session);
}

void SMF::configureUPF(const SessionInfo& session) {
    EV << "Configuring UPF for UE " << session.ueId << omnetpp::endl;
    // Send configuration to UPF
    // Implementation depends on your UPF interface
}

void SMF::cleanupSession(int ueId) {
    auto it = sessions.find(ueId);
    if (it != sessions.end()) {
        sessions.erase(it);
    }
}
