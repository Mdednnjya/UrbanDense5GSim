package urbandense5gsim.nodes;


simple AMF {
    parameters:
        @display("i=block/circle");
        int maxRetries = default(3);
        double timeout = default(1);
        string udmAddress = default("^.udm");
        string ausfAddress = default("^.ausf");
        string smfAddress = default("^.smf");
    gates:
        input in;
        inout ausfg;
        inout udmg;
        inout smfg;
        inout gnbgg[];
}
