#ifndef __URBANDENSE5GSIM_UDM_H
#define __URBANDENSE5GSIM_UDM_H

#include <omnetpp.h>
#include "../messages/NetworkMessages_m.h"
#include <map>
#include <string>

using namespace omnetpp;
using namespace urbandense5gsim;

class UDM : public cSimpleModule {
private:
    struct SubscriberInfo {
        std::string imsi;
        bool subscriptionActive;
        std::string qosProfile;
        AuthVector authVector;
    };

    std::map<int, SubscriberInfo> subscriberDatabase;
    double dataTimeout;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

private:
    void handleAuthVectorRequest(AuthVector *request);
    void handleSubscriberDataRequest(SubscriberDataRequest *request);
    AuthVector* generateAuthVector(int ueId);
    void loadSubscriberDatabase();
};

#endif
