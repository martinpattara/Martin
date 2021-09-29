cleanup () {

ip netns del mpls_vm1
ip netns del mpls_vm2
ovs-vsctl del-port  br_mpls1 udp_port1
ovs-vsctl del-port  br_mpls2 udp_port2
ovs-vsctl del-br br_mpls1
ovs-vsctl del-br br_mpls2
ip link del br1_port

}

ingress_port=101
egress_port=102
bareudp_ingress_port=201
bareudp_egress_port=202


mpls_encap_rules () {
#ovs-ofctl -O OpenFlow13 add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=encap(mpls),set_field:13->mpls_label,encap(ethernet),push_mpls:0x8847,set_field:15->mpls_label,output:$egress_port"
#ovs-ofctl -O OpenFlow13 add-flow br_mpls1 "in_port=$egress_port actions=encap(mpls),output:$ingress_port"
#ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "in_port=$ingress_port actions=encap(mpls),output:$egress_port"
#ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "in_port=$egress_port actions=encap(mpls),output:$ingress_port"
#ovs-ofctl -O OpenFlow13 add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=encap(mpls),set_field:13->mpls_label,encap(mpls),set_field:14->mpls_label,encap(ethernet),push_mpls:0x8847,set_field:15->mpls_label,output:$egress_port"
#ovs-ofctl -O OpenFlow13 add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=encap(mpls(ether_type=0x8847)),set_field:13->mpls_label,encap(ethernet),push_mpls:0x8847,set_field:15->mpls_label,output:$egress_port"
#ovs-ofctl -O OpenFlow13 add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=encap(nsh(md_type=1)),output:$egress_port"
ovs-ofctl -O OpenFlow13 add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=encap(mpls(ether_type=0x8847)),encap(ethernet),output:$egress_port"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847 actions=decap(),decap(packet_type(ns=0,type=0),goto_table:1"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "in_port=$egress_port,dl_type=0x0800 actions=goto_table:1"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "table=1,in_port=$egress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=output:$ingress_port"


}

nsh_encap_rules() {
ovs-ofctl -O OpenFlow13 add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=encap(nsh(md_type=1)),set_field:0x1234->nsh_spi,set_field:0x11223344->nsh_c1,encap(ethernet),output:$egress_port"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "in_port=$egress_port,dl_type=0x894f actions=decap(),decap(),goto_table:1"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "in_port=$egress_port,dl_type=0x0800 actions=goto_table:1"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "table=1,in_port=$egress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=output:$ingress_port"

}



non_mpls_rules () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port actions=output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port actions=output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port actions=output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port actions=output:$ingress_port"
}

mpls_rules () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:12->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.4 actions=push_mpls:0x8847,set_field:13->mpls_label,push_mpls:0x8847,set_field:12->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.5 actions=push_mpls:0x8847,set_field:15->mpls_label,push_mpls:0x8847,set_field:14->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,push_mpls:0x8847,set_field:12->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls1 "table=1,dl_type=0x8847,mpls_label=11 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions=push_mpls:0x8847,set_field:11->mpls_label,push_mpls:0x8847,set_field:12->mpls_label,output:$egress_port"
#ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x8847,pop_mpls:0x0800,output:$ingress_port"
#ovs-ofctl add-flow br_mpls2 "table=1,dl_type=0x8847,mpls_label=11 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "table=1,dl_type=0x8847,mpls_label=19 actions=goto_table:2"
}

mpls_rules_one_label_with_push () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:12->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions= push_mpls:0x8847,set_field:13->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x0800,output:$ingress_port"
}
mpls_rules_one_label_bareudp () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:12->mpls_label,output:$bareudp_egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$bareudp_egress_port,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions= push_mpls:0x8847,set_field:13->mpls_label,output:$bareudp_egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$bareudp_egress_port,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x0800,output:$ingress_port"
}

mpls_encap_rules_bareudp () {
ovs-ofctl -O OpenFlow13 add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=encap(mpls(ether_type=0x8847)),set_field:13->mpls_label,encap(ethernet),output:$bareudp_egress_port"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "in_port=$bareudp_egress_port,dl_type=0x8847 actions=decap(),decap(packet_type(ns=0,type=0)),goto_table:1"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "in_port=$bareudp_egress_port,dl_type=0x0800 actions=goto_table:1"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "table=1,in_port=$bareudp_egress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=output:$ingress_port"
}
mpls_encap_rules_bareudp_l3 () {
ovs-ofctl -O OpenFlow13 add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=encap(mpls(ether_type=0x8847)),set_field:13->mpls_label,output:$bareudp_egress_port"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "in_port=$bareudp_egress_port,dl_type=0x8847 actions=decap(),decap(packet_type(ns=0,type=0)),goto_table:1"
#ovs-ofctl -O OpenFlow14 add-flow br_mpls2 "in_port=$bareudp_egress_port,dl_type=0x8847 actions=output:$ingress_port"
#ovs-ofctl  -O Openflow14 add-flow br_mpls2 "packet_type=(1,0x8847) actions=decap(packet_type(ns=0,type=0)),output:$ingress_port"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "in_port=$bareudp_egress_port,dl_type=0x0800 actions=goto_table:1"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "table=1,in_port=$bareudp_egress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=output:$ingress_port"
}

mpls_encap_rules_bareudp_l3_vpn () {
ovs-ofctl -O OpenFlow13 add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:13->mpls_label,decap()output:$bareudp_egress_port"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "in_port=$bareudp_egress_port,dl_type=0x8847 actions=pop_mpls:0x0800,goto_table:1"
#ovs-ofctl -O OpenFlow14 add-flow br_mpls2 "in_port=$bareudp_egress_port,dl_type=0x8847 actions=output:$ingress_port"
#ovs-ofctl  -O Openflow14 add-flow br_mpls2 "packet_type=(1,0x8847) actions=decap(packet_type(ns=0,type=0)),output:$ingress_port"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "in_port=$bareudp_egress_port,dl_type=0x0800 actions=goto_table:1"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "table=1,in_port=$bareudp_egress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=output:$ingress_port"
}
mpls_encap_rules_bareudp_l3_vpn_test () {
ovs-ofctl -O OpenFlow13 add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:13->mpls_label,output:$bareudp_egress_port"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "in_port=$bareudp_egress_port,dl_type=0x8847 actions=pop_mpls:0x0800,goto_table:1"
#ovs-ofctl -O OpenFlow14 add-flow br_mpls2 "in_port=$bareudp_egress_port,dl_type=0x8847 actions=output:$ingress_port"
#ovs-ofctl  -O Openflow14 add-flow br_mpls2 "packet_type=(1,0x8847) actions=decap(packet_type(ns=0,type=0)),output:$ingress_port"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "in_port=$bareudp_egress_port,dl_type=0x0800 actions=goto_table:1"
ovs-ofctl -O OpenFlow13 add-flow br_mpls2 "table=1,in_port=$bareudp_egress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=output:$ingress_port"
}




mpls_rules_one_label_bareudp_none () {
ovs-ofctl  -O OpenFlow13 add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:12->mpls_label,decap(),output:$bareudp_egress_port"
ovs-ofctl  -O OpenFlow13 add-flow br_mpls1 "in_port=$bareudp_egress_port,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x0800,encap(ethernet),output:$ingress_port"
ovs-ofctl  -O OpenFlow13 add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions=push_mpls:0x8847,set_field:13->mpls_label,decap(),output:$bareudp_egress_port"
ovs-ofctl  -O OpenFlow13 add-flow br_mpls2 "in_port=$bareudp_egress_port,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x0800,output:$ingress_port"
#ovs-ofctl  -O Openflow14 add-flow br_mpls2 "packet_type=(1,0x8847) actions=encap(ethernet),output:$ingress_port"
}
mpls_rules_one_label_bareudp_none_ip () {
ovs-ofctl  -O OpenFlow13 add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=decap(),output:$bareudp_egress_port"
ovs-ofctl  -O OpenFlow13 add-flow br_mpls1 "in_port=$bareudp_egress_port,dl_type=0x0800 actions=push_mpls:0x8847,set_field:12->mpls_label,output:$ingress_port"
ovs-ofctl  -O OpenFlow13 add-flow br_mpls2 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.3 actions=push_mpls:0x8847,set_field:13->mpls_label,decap(),output:$bareudp_egress_port"
ovs-ofctl  -O OpenFlow13 add-flow br_mpls2 "in_port=$bareudp_egress_port,dl_type=0x0800,actions=push_mpls:0x8847,set_field:13->mpls_label,output:$ingress_port"
#ovs-ofctl  -O Openflow14 add-flow br_mpls2 "packet_type=(1,0x8847) actions=encap(ethernet),output:$ingress_port"
}



mpls_rules_one_label_bareudp_none_decap () {
ovs-ofctl  -O OpenFlow13 add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:12->mpls_label,decap(),output:$bareudp_egress_port"
ovs-ofctl  -O OpenFlow13 add-flow br_mpls1 "in_port=$bareudp_egress_port,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x0800,encap(ethernet),output:$ingress_port"
ovs-ofctl  -O OpenFlow13 add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions=push_mpls:0x8847,set_field:13->mpls_label,decap(),output:$bareudp_egress_port"
ovs-ofctl  -O OpenFlow13 add-flow br_mpls2 "dl_type=0x8847,mpls_label=12 actions=decap(),goto_table:1"
ovs-ofctl  -O Openflow14 add-flow br_mpls2 "table=1,packet_type=(1,0x8847) actions=pop_mpls:0x0800,output:$ingress_port"
}





mpls_rules_one_label () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:12->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions= push_mpls:0x8847,set_field:13->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x0800,output:$ingress_port"
}

mpls_rules_one_label_push_pop () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:12->mpls_label,pop_mpls:0x0800,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions= push_mpls:0x8847,set_field:13->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x0800,output:$ingress_port"
}


mpls_rules_one_label_set () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:12->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=13 actions=set_field:20->mpls_label,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions= push_mpls:0x8847,set_field:13->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=12 actions=set_field:0x6->mpls_label,output:$ingress_port"
}

mpls_rules_one_label_push () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:12->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=13 actions=set_field:20->mpls_label,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions= push_mpls:0x8847,set_field:13->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=12 actions=push_mpls:0x8847,set_field:13->mpls_label,output:$ingress_port"
}




mpls_rules_two_label () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:12->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=15 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls1 "table=1,dl_type=0x8847,mpls_label=14 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions=push_mpls:0x8847,set_field:14->mpls_label,push_mpls:0x8847,set_field:15->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls2 "table=1,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x0800,output:$ingress_port"
}

mpls_rules_two_label_withjump () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:12->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=15 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls1 "table=1,dl_type=0x8847,mpls_label=14 actions=pop_mpls:0x0800,goto_table:2"
ovs-ofctl add-flow br_mpls1 "table=2,dl_type=0x0800,nw_dst=1.1.1.3 actions=output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions=push_mpls:0x8847,set_field:14->mpls_label,push_mpls:0x8847,set_field:15->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls2 "table=1,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x0800,output:$ingress_port"
}


mpls_rules_three_label () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:12->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,push_mpls:0x8847,set_field:14->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=17 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls1 "table=1,dl_type=0x8847,mpls_label=16 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls1 "table=2,dl_type=0x8847,mpls_label=15 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions= push_mpls:0x8847,set_field:15->mpls_label,push_mpls:0x8847,set_field:16->mpls_label,push_mpls:0x8847,set_field:17->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=14 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls2 "table=1,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls2 "table=2,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x0800,output:$ingress_port"
}

mpls_rules_three_label_clone () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:12->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,push_mpls:0x8847,set_field:14->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=17 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls1 "table=1,dl_type=0x8847,mpls_label=16 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls1 "table=2,dl_type=0x8847,mpls_label=15 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions= push_mpls:0x8847,set_field:15->mpls_label,push_mpls:0x8847,set_field:16->mpls_label,push_mpls:0x8847,set_field:17->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=14 actions=pop_mpls:0x8847,clone(pop_mpls:0x8847,output:$ingress_port),clone(pop_mpls:0x8847,output:$ingress_port),clone(pop_mpls:0x8847,output:$ingress_port),clone(pop_mpls:0x8847,pop_mpls:0x8847,pop_mpls:0x8847,output:$ingress_port),pop_mpls:0x8847,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "table=1,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls2 "table=2,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x0800,output:$ingress_port"
}




mpls_rules_three_label_push () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:12->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,push_mpls:0x8847,set_field:14->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=17 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls1 "table=1,dl_type=0x8847,mpls_label=16 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls1 "table=2,dl_type=0x8847,mpls_label=15 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions= push_mpls:0x8847,set_field:15->mpls_label,push_mpls:0x8847,set_field:16->mpls_label,push_mpls:0x8847,set_field:17->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=14 actions=push_mpls:0x8847,set_field:19->mpls_label, push_mpls:0x8847,set_field:20->mpls_label,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "table=1,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls2 "table=2,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x0800,output:$ingress_port"
}


mpls_rules_three_label_normal () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:12->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,push_mpls:0x8847,set_field:14->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=17 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls1 "table=1,dl_type=0x8847,mpls_label=16 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls1 "table=2,dl_type=0x8847,mpls_label=15 actions=pop_mpls:0x0800,goto_table:3"
ovs-ofctl add-flow br_mpls1 "table=3 actions=normal"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions= push_mpls:0x8847,set_field:15->mpls_label,push_mpls:0x8847,set_field:16->mpls_label,push_mpls:0x8847,set_field:17->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=14 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls2 "table=1,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls2 "table=2,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x0800,goto_table:3"
ovs-ofctl add-flow br_mpls2 "table=3 actions=normal"
}


mpls_rules_three_label_with_zero () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:0->mpls_label,push_mpls:0x8847,set_field:12->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=17 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls1 "table=1,dl_type=0x8847,mpls_label=16 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls1 "table=2,dl_type=0x8847,mpls_label=15 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions= push_mpls:0x8847,set_field:15->mpls_label,push_mpls:0x8847,set_field:16->mpls_label,push_mpls:0x8847,set_field:17->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls2 "table=1,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls2 "table=2,dl_type=0x8847,mpls_label=0 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.5 actions=push_mpls:0x8847,set_field:12->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,output:$egress_port"
}

mpls_rules_three_label_with_2_overlap () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:11->mpls_label,push_mpls:0x8847,set_field:12->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=17 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls1 "table=1,dl_type=0x8847,mpls_label=16 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls1 "table=2,dl_type=0x8847,mpls_label=15 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions= push_mpls:0x8847,set_field:15->mpls_label,push_mpls:0x8847,set_field:16->mpls_label,push_mpls:0x8847,set_field:17->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls2 "table=1,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x8847,output:$ingress_port"
#ovs-ofctl add-flow br_mpls2 "table=2,dl_type=0x8847,mpls_label=0 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.5 actions=push_mpls:0x8847,set_field:12->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,output:$egress_port"
}


mpls_rules_three_label_with_1_overlap () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:11->mpls_label,push_mpls:0x8847,set_field:12->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=17 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls1 "table=1,dl_type=0x8847,mpls_label=16 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls1 "table=2,dl_type=0x8847,mpls_label=15 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions= push_mpls:0x8847,set_field:15->mpls_label,push_mpls:0x8847,set_field:16->mpls_label,push_mpls:0x8847,set_field:17->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x8847,output:$ingress_port"
#ovs-ofctl add-flow br_mpls2 "table=1,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x8847,output:$ingress_port"
#ovs-ofctl add-flow br_mpls2 "table=2,dl_type=0x8847,mpls_label=0 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.5 actions=push_mpls:0x8847,set_field:13->mpls_label,output:$egress_port"
}

mpls_rules_four_label () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:11->mpls_label,push_mpls:0x8847,set_field:12->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,push_mpls:0x8847,set_field:14->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.5 actions=push_mpls:0x8847,set_field:10->mpls_label,push_mpls:0x8847,set_field:12->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,push_mpls:0x8847,set_field:14->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=17 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls1 "table=1,dl_type=0x8847,mpls_label=16 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls1 "table=2,dl_type=0x8847,mpls_label=15 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions= push_mpls:0x8847,set_field:15->mpls_label,push_mpls:0x8847,set_field:16->mpls_label,push_mpls:0x8847,set_field:17->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=14 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls2 "table=1,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls2 "table=2,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x0800,output:$ingress_port"
}



mpls_rules_eight_label () {
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.2 actions=push_mpls:0x8847,set_field:7->mpls_label,push_mpls:0x8847,set_field:8->mpls_label ,push_mpls:0x8847,set_field:9->mpls_label,push_mpls:0x8847,set_field:10->mpls_label,push_mpls:0x8847,set_field:11->mpls_label,push_mpls:0x8847,set_field:12->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,push_mpls:0x8847,set_field:14->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$ingress_port,dl_type=0x0800,nw_dst=1.1.1.5 actions=push_mpls:0x8847,set_field:10->mpls_label,push_mpls:0x8847,set_field:12->mpls_label,push_mpls:0x8847,set_field:13->mpls_label,push_mpls:0x8847,set_field:14->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls1 "in_port=$egress_port,dl_type=0x8847,mpls_label=17 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls1 "table=1,dl_type=0x8847,mpls_label=16 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls1 "table=2,dl_type=0x8847,mpls_label=15 actions=pop_mpls:0x0800,output:$ingress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$ingress_port ,dl_type=0x0800,nw_dst=1.1.1.3 actions= push_mpls:0x8847,set_field:15->mpls_label,push_mpls:0x8847,set_field:16->mpls_label,push_mpls:0x8847,set_field:17->mpls_label,output:$egress_port"
ovs-ofctl add-flow br_mpls2 "in_port=$egress_port,dl_type=0x8847,mpls_label=14 actions=pop_mpls:0x8847,goto_table:1"
ovs-ofctl add-flow br_mpls2 "table=1,dl_type=0x8847,mpls_label=13 actions=pop_mpls:0x8847,goto_table:2"
ovs-ofctl add-flow br_mpls2 "table=2,dl_type=0x8847,mpls_label=12 actions=pop_mpls:0x0800,output:$ingress_port"
}



cleanup >> /dev/null

ovs-vsctl add-br br_mpls1
echo createing mpls_port_1
ip link add Nokia-eth1 type veth peer name mpls_port_1
echo created mpls_port_1
ip netns add mpls_vm1
ip link set Nokia-eth1 netns  mpls_vm1
ip netns exec mpls_vm1 ifconfig Nokia-eth1 up
ifconfig mpls_port_1 up
ip netns exec mpls_vm1 ifconfig Nokia-eth1 1.1.1.3 up
ip netns exec  mpls_vm1 ip link set Nokia-eth1  address 36:b1:ee:7c:01:03

ip netns exec mpls_vm1 arp -s 1.1.1.2 36:b1:ee:7c:01:02
ip netns exec mpls_vm1 arp -s 1.1.1.4 36:b1:ee:7c:01:04
ip netns exec mpls_vm1 arp -s 1.1.1.5 36:b1:ee:7c:01:05
ovs-vsctl add-port br_mpls1  mpls_port_1 -- set interface mpls_port_1 ofport_request=$ingress_port



ovs-vsctl add-br br_mpls2
ip link add Nokia-eth2 type veth peer name mpls_port_2
ip netns add mpls_vm2
ip link set Nokia-eth2 netns  mpls_vm2
ip netns exec mpls_vm2 ifconfig Nokia-eth2 up
ifconfig mpls_port_2 up
ip netns exec mpls_vm2 ifconfig Nokia-eth2 1.1.1.2 up
ip netns exec mpls_vm2 ifconfig lo:1 1.1.1.4 up
ip netns exec mpls_vm2 ifconfig lo:2 1.1.1.5 up
ip netns exec  mpls_vm2 ip link set Nokia-eth2  address 36:b1:ee:7c:01:02
ip netns exec mpls_vm2 arp -s 1.1.1.3 36:b1:ee:7c:01:03
ovs-vsctl add-port br_mpls2  mpls_port_2  -- set interface mpls_port_2 ofport_request=$ingress_port


ip link add br1_port type veth peer name br2_port
ifconfig br2_port up
ifconfig br1_port up
ovs-vsctl add-port br_mpls1 br1_port -- set interface br1_port ofport_request=$egress_port
ovs-vsctl add-port br_mpls2 br2_port -- set interface br2_port ofport_request=$egress_port
ifconfig lo:2 2.1.1.2 up
ifconfig lo:3 2.1.1.3 up

#ifconfig br_mpls1 2.1.1.2/24 up
#ifconfig br_mpls2 2.1.1.3/24 up

ovs-vsctl add-port  br_mpls1 udp_port1 -- set interface udp_port1 type=bareudp options:remote_ip=2.1.1.3 options:local_ip=2.1.1.2 options:payload_type=mpls options:dst_port=6635 options:packet_type="legacy_l3" ofport_request=$bareudp_egress_port
ovs-vsctl add-port  br_mpls2 udp_port2 -- set interface udp_port2 type=bareudp options:remote_ip=2.1.1.2 options:local_ip=2.1.1.3 options:payload_type=mpls  options:dst_port=6635 options:packet_type="legacy_l3" ofport_request=$bareudp_egress_port

#ovs-vsctl add-port  br_mpls1 udp_port1 -- set interface udp_port1 type=bareudp options:remote_ip=2.1.1.3 options:local_ip=2.1.1.2 options:dst_port=6635 ofport_request=$bareudp_egress_port
#ovs-vsctl add-port  br_mpls2 udp_port2 -- set interface udp_port2 type=bareudp options:remote_ip=2.1.1.2 options:local_ip=2.1.1.3 options:dst_port=6635 ofport_request=$bareudp_egress_port






ovs-ofctl del-flows br_mpls1
ovs-ofctl del-flows br_mpls2

#mpls_rules
#mpls_rules_one_label
#mpls_rules_one_label_set
#mpls_rules_one_label_push_pop
#mpls_rules_two_label
#mpls_rules_two_label_withjump
#mpls_rules_three_label
#mpls_rules_three_label_clone
#mpls_rules_three_label_normal
#mpls_rules_three_label_with_zero
#mpls_rules_three_label_with_2_overlap
#mpls_rules_three_label_with_1_overlap
#mpls_rules_four_label
#mpls_encap_rules
#nsh_encap_rules
#mpls_rules_eight_label
#mpls_rules_three_label_push
#mpls_rules_one_label_push
#mpls_rules_one_label_bareudp
#mpls_rules_one_label_bareudp_none
#mpls_rules_one_label_bareudp_none_decap
#mpls_rules_one_label_bareudp_none_ip
#mpls_encap_rules_bareudp
#mpls_encap_rules_bareudp_l3
#mpls_encap_rules_bareudp_l3_vpn
mpls_encap_rules_bareudp_l3_vpn_test

