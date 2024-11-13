package urbandense5gsim.simulations.nodes;

simple UDM {
    parameters:
        @display("i=block/database");
        @class(UDM); // Ensure this matches the C++ class name
        double dataRetrievalDelay @unit(ms) = default(8ms);
        string databaseFile = default("subscriber_data.json");
    gates:
        inout amfg;    // Gate to AMF
        inout ausfg;   // Gate to AUSF
}