#ifndef AMF_H
#define AMF_H

#include <omnetpp.h>

using namespace omnetpp;

class AMF : public cSimpleModule {
  private:
    std::string udmAddress;
    std::string ausfAddress;
    std::string smfAddress;
    int maxUeSupported;
    simtime_t processingDelay;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

  public:
    AMF();
    virtual ~AMF();
};

#endif // AMF_H
