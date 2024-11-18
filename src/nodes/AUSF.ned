package urbandense5gsim.nodes;


simple AUSF {
    parameters:
        @display("i=block/key");
        int maxAuthRetries = default(3);
        double authTimeout = default(1);
        string udmAddress = default("^.udm");
        string amfAddress = default("^.amf");
    gates:
        inout amfg;
        inout udmg;
}
