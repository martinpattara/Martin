clean () {
ovs-vsctl del-br br-dummy
}
clean1() {
ovs-vsctl del-br br-dummy1
ovs-vsctl del-br br-dummy2
}






encap_test() {
ovs-vsctl add-br br-dummy -- \
   set bridge br-dummy other-config:hwaddr=aa:66:aa:66:00:00 -- \
   set bridge br-dummy datapath-type=dummy other-config:datapath-id=1234 \
                  fail-mode=secure -- \
   add-port br-dummy p1 -- set Interface p1 type=dummy ofport_request=1	-- \
   add-port br-dummy p2 -- set Interface p2 type=dummy ofport_request=2  



ovs-ofctl -O OpenFlow13 add-flow br-dummy "in_port=p1,actions=encap(mpls(ether_type=0x8847)),encap(ethernet),set_field:00:00:00:00:00:02->dl_dst,set_field:00:00:00:00:00:01->dl_src,output:p2"

ovs-appctl ofproto/trace ovs-dummy 'in_port(1),eth(src=f8:bc:12:44:34:b6,dst=f8:bc:12:46:58:e0),eth_type(0x0800),ipv4(src=10.1.1.22,dst=10.0.0.3,proto=6,tos=0,ttl=64,frag=no),tcp(src=53295,dst=8080)'
}

decap_test () {
ovs-vsctl add-br br-dummy1 -- \
   set bridge br-dummy1 other-config:hwaddr=aa:66:aa:66:00:00 -- \
   set bridge br-dummy1 datapath-type=dummy other-config:datapath-id=1234 \
                  fail-mode=secure -- \
   add-port br-dummy1 p1 -- set Interface p1 type=dummy ofport_request=1 -- \
   add-port br-dummy1 p2 -- set Interface p2 type=patch \
                                       options:peer=p3

ovs-vsctl add-br br-dummy2 -- \
   set bridge br-dummy2 other-config:hwaddr=aa:66:aa:66:00:00 -- \
   set bridge br-dummy2 datapath-type=dummy other-config:datapath-id=1234 \
                  fail-mode=secure -- \
   add-port br-dummy2 p3 -- set Interface p3 type=patch \
                                       options:peer=p2 -- \
   add-port br-dummy2 p4 -- set Interface p4 type=dummy ofport_request=4 

ovs-appctl dpif/show

ovs-ofctl -O OpenFlow13 add-flow br-dummy1 "in_port=p1,actions=encap(mpls(ether_type=0x8847)),encap(ethernet),set_field:00:00:00:00:00:02->dl_dst,set_field:00:00:00:00:00:01->dl_src,output:p2"

ovs-ofctl -O OpenFlow13 add-flow br-dummy2 "in_port=p3,dl_type=0x8847 actions=decap(),decap(packet_type(ns=0,type=0)),output:p4"

ovs-appctl ofproto/trace ovs-dummy 'in_port(1),eth(src=f8:bc:12:44:34:b6,dst=f8:bc:12:46:58:e0),eth_type(0x0800),ipv4(src=10.1.1.22,dst=10.0.0.3,proto=6,tos=0,ttl=64,frag=no),tcp(src=53295,dst=8080)'

ovs-appctl netdev-dummy/receive p1 1e2ce92a669e3a6dd2099cab0800450000548a53400040011addc0a80a0ac0a80a1e08006f200a4d0001fc509a58000000002715020000000000101112131415161718191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f3031323334353637

ovs-appctl dpctl/dump-flows dummy@ovs-dummy | grep -v ipv6 | sort
}

push_decap_test () {
ovs-vsctl add-br br-dummy1 -- \
   set bridge br-dummy1 other-config:hwaddr=aa:66:aa:66:00:00 -- \
   set bridge br-dummy1 datapath-type=dummy other-config:datapath-id=1234 \
                  fail-mode=secure -- \
   add-port br-dummy1 p1 -- set Interface p1 type=dummy ofport_request=1 -- \
   add-port br-dummy1 p2 -- set Interface p2 type=patch \
                                       options:peer=p3

ovs-vsctl add-br br-dummy2 -- \
   set bridge br-dummy2 other-config:hwaddr=aa:66:aa:66:00:00 -- \
   set bridge br-dummy2 datapath-type=dummy other-config:datapath-id=1234 \
                  fail-mode=secure -- \
   add-port br-dummy2 p3 -- set Interface p3 type=patch \
                                       options:peer=p2 -- \
   add-port br-dummy2 p4 -- set Interface p4 type=dummy ofport_request=4

ovs-appctl dpif/show

ovs-ofctl -O OpenFlow13 add-flow br-dummy1 "in_port=p1,actions=push_mpls:0x8847,set_field:13->mpls_label,output:p2"

#ovs-ofctl -O OpenFlow13 add-flow br-dummy2 "in_port=p3,dl_type=0x8847 actions=decap(),decap(packet_type(ns=1,type=0x0800)),output:p4"
ovs-ofctl -O OpenFlow13 add-flow br-dummy2 "in_port=p3,dl_type=0x8847 actions=decap(),pop_mpls:0x0800,output:p4"

ovs-appctl ofproto/trace ovs-dummy 'in_port(1),eth(src=f8:bc:12:44:34:b6,dst=f8:bc:12:46:58:e0),eth_type(0x0800),ipv4(src=10.1.1.22,dst=10.0.0.3,proto=6,tos=0,ttl=64,frag=no),tcp(src=53295,dst=8080)'

ovs-appctl netdev-dummy/receive p1 1e2ce92a669e3a6dd2099cab0800450000548a53400040011addc0a80a0ac0a80a1e08006f200a4d0001fc509a58000000002715020000000000101112131415161718191a1b1c1d1e1f202122232425262728292a2b2c2d2e2f3031323334353637

ovs-appctl dpctl/dump-flows dummy@ovs-dummy
}

clean
clean1
decap_test
#clean1
#push_decap_test

