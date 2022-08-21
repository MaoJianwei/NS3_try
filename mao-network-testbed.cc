#include <fstream>
#include "ns3/core-module.h"
#include "ns3/network-module.h"
#include "ns3/internet-module.h"
#include "ns3/csma-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-apps-module.h"
#include "ns3/ipv6-static-routing-helper.h"

#include "ns3/ipv6-routing-table-entry.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("MaoTest");

int
main (int argc, char **argv)
{
  // bool verbose = true;

  // CommandLine cmd (__FILE__);
  // cmd.AddValue ("verbose", "turn on log components", verbose);
  // cmd.Parse (argc, argv);

  // if (verbose)
  // {
    LogComponentEnable ("MaoTest", LOG_LEVEL_INFO);

    LogComponentEnable ("Ipv6L3Protocol", LOG_LEVEL_INFO);
    LogComponentEnable ("Icmpv6L4Protocol", LOG_LEVEL_INFO);
    LogComponentEnable ("Ipv6StaticRouting", LOG_LEVEL_INFO);
    LogComponentEnable ("Ipv6Interface", LOG_LEVEL_INFO);
    LogComponentEnable ("Ping6Application", LOG_LEVEL_INFO);
  // }



  NS_LOG_INFO ("Create nodes.");
  Ptr<Node> n1 = CreateObject<Node> ();
  Ptr<Node> r1 = CreateObject<Node> ();
  Ptr<Node> r2 = CreateObject<Node> ();
  Ptr<Node> r3 = CreateObject<Node> ();
  Ptr<Node> r4 = CreateObject<Node> ();
  Ptr<Node> r5 = CreateObject<Node> ();
  Ptr<Node> r6 = CreateObject<Node> ();
  Ptr<Node> n2 = CreateObject<Node> ();

  NodeContainer allRouter;
  allRouter.Add(r1);
  allRouter.Add(r2);
  allRouter.Add(r3);
  allRouter.Add(r4);
  allRouter.Add(r5);
  allRouter.Add(r6);

  NodeContainer all;
  all.Add(allRouter);
  all.Add(n1);
  all.Add(n2);


  NS_LOG_INFO ("Create channels.");

  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", DataRateValue (5000000));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("100ms"));
  pointToPoint.SetDeviceAttribute ("Mtu", UintegerValue (1500));  // P2P Network with MTU 1500

  NetDeviceContainer net_link_n1_r1 = pointToPoint.Install (n1, r1);
  NetDeviceContainer net_link_r1_r2 = pointToPoint.Install (r1, r2);
  NetDeviceContainer net_link_r2_r3 = pointToPoint.Install (r2, r3);
  NetDeviceContainer net_link_r3_r4 = pointToPoint.Install (r3, r4);
  NetDeviceContainer net_link_r4_r5 = pointToPoint.Install (r4, r5);
  NetDeviceContainer net_link_r5_r6 = pointToPoint.Install (r5, r6);
  NetDeviceContainer net_link_r6_n2 = pointToPoint.Install (r6, n2);


  NS_LOG_INFO ("Create IPv6 Internet Stack");
  InternetStackHelper ipv6Stack;
  ipv6Stack.Install (all);


  NS_LOG_INFO ("Create networks and assign IPv6 Addresses.");
  Ipv6AddressHelper ipv6;

  NS_LOG_INFO ("--> v6Intf_n1_r1");
  ipv6.SetBase (Ipv6Address ("2001:a1:b1::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer v6Intf_n1_r1 = ipv6.Assign (net_link_n1_r1);
  // v6Intf_n1_r1.GetAddress(0, 0).Print(std::cout);
  // std::cout << std::endl;
  // v6Intf_n1_r1.GetAddress(0, 1).Print(std::cout);
  // std::cout << std::endl;
  // v6Intf_n1_r1.GetAddress(1, 0).Print(std::cout);
  // std::cout << std::endl;
  // v6Intf_n1_r1.GetAddress(1, 1).Print(std::cout);
  // std::cout << std::endl;
  v6Intf_n1_r1.SetForwarding (0, false);
  v6Intf_n1_r1.SetForwarding (1, true);
  v6Intf_n1_r1.SetDefaultRouteInAllNodes (1);

  NS_LOG_INFO ("--> v6Intf_r1_r2");
  ipv6.SetBase (Ipv6Address ("2001:b1:b2::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer v6Intf_r1_r2 = ipv6.Assign (net_link_r1_r2);
  v6Intf_r1_r2.SetForwarding (0, true);
  v6Intf_r1_r2.SetForwarding (1, true);
  // v6Intf_r1_r2.GetAddress(0, 0).Print(std::cout);
  // std::cout << std::endl;
  // v6Intf_r1_r2.GetAddress(0, 1).Print(std::cout);
  // std::cout << std::endl;
  // v6Intf_r1_r2.GetAddress(1, 0).Print(std::cout);
  // std::cout << std::endl;
  // v6Intf_r1_r2.GetAddress(1, 1).Print(std::cout);
  // std::cout << std::endl;

  NS_LOG_INFO ("--> v6Intf_r2_r3");
  ipv6.SetBase (Ipv6Address ("2001:b2:b3::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer v6Intf_r2_r3 = ipv6.Assign (net_link_r2_r3);
  v6Intf_r2_r3.SetForwarding (0, true);
  v6Intf_r2_r3.SetForwarding (1, true);

  NS_LOG_INFO ("--> v6Intf_r3_r4");
  ipv6.SetBase (Ipv6Address ("2001:b3:b4::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer v6Intf_r3_r4 = ipv6.Assign (net_link_r3_r4);
  v6Intf_r3_r4.SetForwarding (0, true);
  v6Intf_r3_r4.SetForwarding (1, true);

  NS_LOG_INFO ("--> v6Intf_r4_r5");
  ipv6.SetBase (Ipv6Address ("2001:b4:b5::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer v6Intf_r4_r5 = ipv6.Assign (net_link_r4_r5);
  v6Intf_r4_r5.SetForwarding (0, true);
  v6Intf_r4_r5.SetForwarding (1, true);

  NS_LOG_INFO ("--> v6Intf_r5_r6");
  ipv6.SetBase (Ipv6Address ("2001:b5:b6::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer v6Intf_r5_r6 = ipv6.Assign (net_link_r5_r6);
  v6Intf_r5_r6.SetForwarding (0, true);
  v6Intf_r5_r6.SetForwarding (1, true);

  NS_LOG_INFO ("--> v6Intf_r6_n2");
  ipv6.SetBase (Ipv6Address ("2001:b6:a2::"), Ipv6Prefix (64));
  Ipv6InterfaceContainer v6Intf_r6_n2 = ipv6.Assign (net_link_r6_n2);
  v6Intf_r6_n2.SetForwarding (0, true);
  v6Intf_r6_n2.SetDefaultRouteInAllNodes (0);
  v6Intf_r6_n2.SetForwarding (1, false);


  // Ipv6RoutingHelper 

  NS_LOG_INFO ("Inject IPv6 routing tables.");
  Ipv6StaticRoutingHelper routingHelper;
  Ptr<Ipv6StaticRouting> r1_static_routing = routingHelper.GetStaticRouting(r1->GetObject<Ipv6>());
  r1_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b2:b3::"), Ipv6Prefix (64), 2);
  r1_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b3:b4::"), Ipv6Prefix (64), 2);
  r1_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b4:b5::"), Ipv6Prefix (64), 2);
  r1_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b5:b6::"), Ipv6Prefix (64), 2);
  r1_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b6:a2::"), Ipv6Prefix (64), 2);

  Ptr<Ipv6StaticRouting> r2_static_routing = routingHelper.GetStaticRouting(r2->GetObject<Ipv6>());
  r2_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:a1:b1::"), Ipv6Prefix (64), 1);
  r2_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b3:b4::"), Ipv6Prefix (64), 2);
  r2_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b4:b5::"), Ipv6Prefix (64), 2);
  r2_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b5:b6::"), Ipv6Prefix (64), 2);
  r2_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b6:a2::"), Ipv6Prefix (64), 2);

  Ptr<Ipv6StaticRouting> r3_static_routing = routingHelper.GetStaticRouting(r3->GetObject<Ipv6>());
  r3_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:a1:b1::"), Ipv6Prefix (64), 1);
  r3_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b1:b2::"), Ipv6Prefix (64), 1);
  r3_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b4:b5::"), Ipv6Prefix (64), 2);
  r3_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b5:b6::"), Ipv6Prefix (64), 2);
  r3_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b6:a2::"), Ipv6Prefix (64), 2);

  Ptr<Ipv6StaticRouting> r4_static_routing = routingHelper.GetStaticRouting(r4->GetObject<Ipv6>());
  r4_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:a1:b1::"), Ipv6Prefix (64), 1);
  r4_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b1:b2::"), Ipv6Prefix (64), 1);
  r4_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b2:b3::"), Ipv6Prefix (64), 1);
  r4_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b5:b6::"), Ipv6Prefix (64), 2);
  r4_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b6:a2::"), Ipv6Prefix (64), 2);

  Ptr<Ipv6StaticRouting> r5_static_routing = routingHelper.GetStaticRouting(r5->GetObject<Ipv6>());
  r5_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:a1:b1::"), Ipv6Prefix (64), 1);
  r5_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b1:b2::"), Ipv6Prefix (64), 1);
  r5_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b2:b3::"), Ipv6Prefix (64), 1);
  r5_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b3:b4::"), Ipv6Prefix (64), 1);
  r5_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b6:a2::"), Ipv6Prefix (64), 2);

  Ptr<Ipv6StaticRouting> r6_static_routing = routingHelper.GetStaticRouting(r6->GetObject<Ipv6>());
  r6_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:a1:b1::"), Ipv6Prefix (64), 1);
  r6_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b1:b2::"), Ipv6Prefix (64), 1);
  r6_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b2:b3::"), Ipv6Prefix (64), 1);
  r6_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b3:b4::"), Ipv6Prefix (64), 1);
  r6_static_routing->AddNetworkRouteTo(Ipv6Address ("2001:b4:b5::"), Ipv6Prefix (64), 1);

  NS_LOG_INFO ("Dump IPv6 routing tables.");
  Ptr<OutputStreamWrapper> routingStream = Create<OutputStreamWrapper> (&std::cout);
  routingHelper.PrintRoutingTableAt (Seconds (0), n1, routingStream);
  routingHelper.PrintRoutingTableAt (Seconds (0), r1, routingStream);
  routingHelper.PrintRoutingTableAt (Seconds (0), r2, routingStream);
  routingHelper.PrintRoutingTableAt (Seconds (0), r3, routingStream);
  routingHelper.PrintRoutingTableAt (Seconds (0), r4, routingStream);
  routingHelper.PrintRoutingTableAt (Seconds (0), r5, routingStream);
  routingHelper.PrintRoutingTableAt (Seconds (0), r6, routingStream);
  routingHelper.PrintRoutingTableAt (Seconds (0), n2, routingStream);

  

  /* Create a Ping6 application to send ICMPv6 echo request from r to n2 */
  Ping6Helper ping6;
  ping6.SetLocal (v6Intf_n1_r1.GetAddress (0, 1));
  ping6.SetRemote (v6Intf_r6_n2.GetAddress (1, 1));
  ping6.SetAttribute ("MaxPackets", UintegerValue (3));
  ping6.SetAttribute ("Interval", TimeValue (Seconds (1.0)));
  ping6.SetAttribute ("PacketSize", UintegerValue (1300));
  ApplicationContainer apps = ping6.Install (n1);
  apps.Start (Seconds (2.0));
  apps.Stop (Seconds (10.0));


  AsciiTraceHelper ascii;
  pointToPoint.EnableAsciiAll (ascii.CreateFileStream ("mao-testbed-ascii"));
  pointToPoint.EnablePcapAll (std::string ("mao-testbed-pcap"), true);


  NS_LOG_INFO ("Run Simulation.");
  Simulator::Run ();
  Simulator::Destroy ();
  NS_LOG_INFO ("Done.");
}
