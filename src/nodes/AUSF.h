#ifndef __URBANDENSE5GSIM_AUSF_H
#define __URBANDENSE5GSIM_AUSF_H

#include <omnetpp.h>
#include "../messages/NetworkMessages_m.h"
#include <map>
#include <string>

using namespace omnetpp;
using namespace urbandense5gsim;

class AUSF : public cSimpleModule {
private:
    cModule* udmModule;
    cModule* amfModule;
    std::map<int, AuthVector*> authVectorCache;

    // Authentication parameters
    int maxAuthRetries;
    double authTimeout;
    simtime_t authenticationTimeout;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

private:
    void handleAuthenticationRequest(AuthenticationRequest *request);
    void processUDMResponse(AuthVector *response);
    void sendAuthResponseToAMF(int ueId, bool success);
    void cleanupAuthVector(int ueId);
};

#endif
