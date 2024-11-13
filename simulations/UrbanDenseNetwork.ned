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
import urbandense5gsim.simulations.nodes.AMF; 
import urbandense5gsim.simulations.nodes.AUSF; 
import urbandense5gsim.simulations.nodes.UDM; 
import urbandense5gsim.simulations.nodes.SMF; 
import urbandense5gsim.simulations.nodes.CustomGNodeB;



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

    // 5G Core Network Components
    amf: AMF {
        @display("p=587.20245,150;is=l");
        udmAddress = "udm";
        ausfAddress = "ausf";
        smfAddress = "smf";
    }
    ausf: AUSF {
        @display("p=455.7,89.9;is=l");
        udmAddress = "udm";
    }
    udm: UDM {
        @display("p=714.55005,89.9;is=l");
    }
    smf: SMF {
        @display("p=585.9,282.1;is=l");
        upfAddress = "upf";
    }
    upf: Upf {
        @display("p=587.20245,400");
    }

	// New Radio Network	
    gnb1: CustomGNodeB {
        @display("p=325.5475,267.74;is=vl");
    }
    gnb2: CustomGNodeB {
        @display("p=847.33624,267.74;is=vl");
    }
    ueSource: NRUe {
        @display("p=348.36624,491.36374");
    }
    ueDestination: NRUe {
        @display("p=789.52875,491.36374");
    }

connections allowunconnected:
    // Core Network Connections
    amf.ausfg <--> Eth10G <--> ausf.amfg;
    amf.udmg <--> Eth10G <--> udm.amfg;
    amf.smfg <--> Eth10G <--> smf.amfg;
    smf.upfg <--> Eth10G <--> upf.pppg++;

    // RAN Connections
    gnb1.ppp <--> Eth10G <--> upf.pppg++;
    gnb2.ppp <--> Eth10G <--> upf.pppg++;

    // AMF to gNodeB connections
    amf.gnbgg++ <--> Eth10G <--> gnb1.amfg;
    amf.gnbgg++ <--> Eth10G <--> gnb2.amfg;
}
