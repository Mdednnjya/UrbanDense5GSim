cplusplus {{
#include <omnetpp.h>
}}

namespace urbandense5gsim;

//
// Base class for all network messages
//
message NetworkMessage {
    int ueId;
}

//
// Registration and Authentication Messages
//
message RegistrationRequest extends NetworkMessage {
    string imsi;
}

message AuthenticationRequest extends NetworkMessage {
    string authData;
}

message AuthenticationResponse extends NetworkMessage {
    bool authenticated;
}

//
// Subscriber Data Messages
//
message SubscriberDataRequest extends NetworkMessage {
}

message SessionRequest extends NetworkMessage {
    string sessionType;
    string qosProfile;  
}

message AuthVector extends NetworkMessage {
    string rand;
    string autn;
    string xres;
    string kasme;
}

message SubscriberData extends NetworkMessage {
    string imsi;
    bool subscriptionStatus;
    string accessRestrictions;
    string qosProfile;
}

message SessionManagementMsg extends NetworkMessage {
    string sessionType;
    string qosParameters;
    bool emergency;
}

message AUSFMessage extends NetworkMessage {
    string authData;
}

message UDMMessage extends NetworkMessage {
    string subscriberData;
}
