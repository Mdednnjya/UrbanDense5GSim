// 
//                  Simu5G
//
// Authors: Giovanni Nardini, Giovanni Stea, Antonio Virdis (University of Pisa)
// 
// This file is part of a software released under the license included in file
// "license.pdf". Please read LICENSE and README files before using it.
// The above files and the present reference are part of the software itself, 
// and cannot be removed from it.
// 
package urbandense5gsim.simulations;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.networklayer.ipv4.RoutingTableRecorder;
import inet.node.ethernet.Eth10G;
import inet.node.inet.Router;
import inet.node.inet.StandardHost;
import simu5g.common.binder.Binder;
import simu5g.common.carrierAggregation.CarrierAggregation;
import simu5g.nodes.Upf;
import simu5g.nodes.NR.gNodeB;
import simu5g.nodes.NR.NRUe;
import simu5g.nodes.backgroundCell.BackgroundCell;
import simu5g.world.radio.LteChannelControl;



network UrbanDenseNetwork
{
    parameters:
        double radius @unit(m) = default(1000m);
        @display("bgi=background/budapest;bgb=1090.7362,771.27374");

    submodules:
        channelControl: LteChannelControl {
            @display("p=50,25;is=s");
            @class(LteChannelControl);
        }
        configurator: Ipv4NetworkConfigurator {
            @display("p=50,75");
            config = xmldoc("demo.xml");
        }
        binder: Binder {
            @display("p=50,125;is=s");
        }
        carrierAggregation: CarrierAggregation {
            @display("p=50,175;is=s");
        }
        upf: Upf {
            @display("p=587.20245,222.1025");
        }

        gnb1: gNodeB {
            @display("p=325.5475,267.74;is=vl");
        }
        ueSource: NRUe {
            @display("p=348.36624,491.36374");
        }

        gnb2: gNodeB {
            @display("p=847.33624,267.74;is=vl");
        }
        ueDestination: NRUe {
            @display("p=789.52875,491.36374");
        }

    connections allowunconnected:
        upf.pppg++ <--> Eth10G <--> gnb1.ppp;
        upf.pppg++ <--> Eth10G <--> gnb2.ppp;
}
