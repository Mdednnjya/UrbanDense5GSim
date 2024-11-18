package urbandense5gsim.nodes;


simple SMF {
    parameters:
        @display("i=block/network2");
        double sessionTimeout = default(1);
        string upfAddress = default("^.upf");
    gates:
        inout amfg;
        inout upfg;
}
