#ifndef __URBANDENSE5GSIM_SMF_H
#define __URBANDENSE5GSIM_SMF_H

#include <omnetpp.h>
#include "../messages/NetworkMessages_m.h"
#include <map>
#include <string>

using namespace omnetpp;
using namespace urbandense5gsim;

class SMF : public cSimpleModule {
private:
    struct SessionInfo {
        int ueId;
        std::string qosProfile;
        bool active;
    };

    cModule* upfModule;
    std::map<int, SessionInfo> sessions;
    double sessionTimeout;

protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

private:
    void handleSessionRequest(int ueId, const std::string& qosProfile);
    void configureUPF(const SessionInfo& session);
    void cleanupSession(int ueId);
};

#endif
