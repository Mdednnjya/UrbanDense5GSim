#ifndef __URBANDENSE5GSIM_AMF_H
#define __URBANDENSE5GSIM_AMF_H

#include <omnetpp.h>
#include "../messages/NetworkMessages_m.h"

using namespace omnetpp;
using namespace urbandense5gsim;

class AMF : public cSimpleModule {
private:
    int maxRetries;
    double timeout;
    simtime_t registrationTimeout;
    cMessage* timeoutEvent;
    cModule* udmModule;
    cModule* ausfModule;
    cModule* smfModule;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage* msg) override;
    virtual void processRegistrationRequest(RegistrationRequest* msg);
    virtual void sendAuthenticationRequest(RegistrationRequest* msg);
    virtual void handleAuthenticationResponse(AuthenticationResponse* msg);
    virtual void handleTimeout(cMessage* msg);
    virtual void finish() override;
};

#endif
