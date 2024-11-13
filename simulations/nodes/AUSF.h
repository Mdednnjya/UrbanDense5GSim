#ifndef AUSF_H
#define AUSF_H

#include <omnetpp.h>

using namespace omnetpp;

class AUSF : public cSimpleModule {
  private:
    std::string udmAddress;
    double authenticationDelay;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

  public:
    AUSF();
    virtual ~AUSF();

    void handleAuthRequest(cMessage *msg);
};

#endif // AUSF_H
