package urbandense5gsim.simulations.nodes;

simple SMF {
    parameters:
        @display("i=block/network2");
        @class(SMF); // Ensure this matches the C++ class name
        string upfAddress = default("");
        double sessionSetupDelay @unit(ms) = default(15ms);
    gates:
        inout amfg;    // Gate to AMF
        inout upfg;    // Gate to UPF
}