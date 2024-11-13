#ifndef UDM_H
#define UDM_H

#include <omnetpp.h>

using namespace omnetpp;

class UDM : public cSimpleModule {
  private:
    double dataRetrievalDelay;
    std::string databaseFile;

  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;

  public:
    UDM();
    virtual ~UDM();

    void handleDataRequest(cMessage *msg);
};

#endif // UDM_H
