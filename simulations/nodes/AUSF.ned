package urbandense5gsim.simulations.nodes;

simple AUSF {
    parameters:
        @display("i=block/crypto");
        @class(AUSF); // Ensure this matches the C++ class name
        string udmAddress = default("");
        double authenticationDelay @unit(ms) = default(5ms);
    gates:
        inout amfg;    // Gate to AMF
        inout udmg;    // Gate to UDM
}