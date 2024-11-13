package urbandense5gsim.simulations.nodes;

simple AMF {
    parameters:
        @display("i=block/routing");
        @class(AMF); // Corrected from ASF to AMF
        string udmAddress = default("");
        string ausfAddress = default("");
        string smfAddress = default("");
        int maxUeSupported = default(10000);
        double processingDelay @unit(ms) = default(10ms);
    gates:
        inout gnbgg[]; // Gates to gNodeB
        inout ausfg;   // Gate to AUSF
        inout udmg;    // Gate to UDM
        inout smfg;    // Gate to SMF
}