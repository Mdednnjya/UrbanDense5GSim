package urbandense5gsim.nodes;


simple UDM {
    parameters:
        @display("i=block/database2");
        double dataTimeout = default(1);
    gates:
        inout amfg;
        inout ausfg;
}
