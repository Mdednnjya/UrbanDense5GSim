#include "UDM.h"

Define_Module(UDM);

void UDM::initialize() {
    dataTimeout = par("dataTimeout");
    loadSubscriberDatabase();
}

void UDM::handleMessage(cMessage *msg) {
    if (AuthVector *request = dynamic_cast<AuthVector *>(msg)) {
        handleAuthVectorRequest(request);
    } else if (SubscriberDataRequest *request = dynamic_cast<SubscriberDataRequest *>(msg)) {
        handleSubscriberDataRequest(request);
    }
    delete msg;
}

void UDM::handleAuthVectorRequest(AuthVector *request) {
    int ueId = request->getUeId();
    AuthVector *response = generateAuthVector(ueId);
    send(response, "ausfg$o");
}

void UDM::handleSubscriberDataRequest(SubscriberDataRequest *request) {
    int ueId = request->getUeId();
    auto it = subscriberDatabase.find(ueId);

    SubscriberData *response = new SubscriberData();
    response->setUeId(ueId);

    if (it != subscriberDatabase.end()) {
        response->setImsi(it->second.imsi.c_str());
        response->setSubscriptionStatus(it->second.subscriptionActive);
        response->setQosProfile(it->second.qosProfile.c_str());
    }

    send(response, "amfg$o");
}

AuthVector* UDM::generateAuthVector(int ueId) {
    AuthVector *av = new AuthVector();
    av->setUeId(ueId);
    av->setRand("random_value");
    av->setAutn("auth_token");
    av->setXres("expected_response");
    av->setKasme("key_value");
    return av;
}

void UDM::loadSubscriberDatabase() {
    // Load sample subscriber data
    SubscriberInfo info;
    info.imsi = "123456789";
    info.subscriptionActive = true;
    info.qosProfile = "standard";
    subscriberDatabase[1] = info;
}
