#ifndef SMF_H
#define SMF_H

#include <omnetpp.h>

using namespace omnetpp;

class SMF : public cSimpleModule {
  private:
    std::string upfAddress;
    double sessionSetupDelay;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

  public:
    SMF();
    virtual ~SMF();

    void handleSessionRequest(cMessage *msg);
};

#endif // SMF_H
