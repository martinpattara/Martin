#!/bin/bash
# SPDX-License-Identifier: GPL-2.0

# This test is for verifying MPLS traffic over bareudp tunnel
#
# Trafic between 2 hosts are encapsulated inside an MPLS tunnel and sent over UDP.
# The PE devices encapsulate IP traffic from Host device in MPLS tunnels.
# The GW devices encapsulate MPLS traffic from PE devices in UDP tunnels.
#
#
# +-------------------+                       +-------------------+
# |                   |                       |                   |
# |    host-1 netns   |                       |    host-2 netns   |
# |                   |                       |                   |
# |  +-------------+  |                       |  +-------------+  |
# |  |   pe-h1-h   |  |                       |  |   pe-h2-h   |  |
# |  | 1.1.1.2/24  |  |                       |  | 2.1.1.2/24  |  |
# |  +-------------+  |                       |  +-------------+  |
# |        .          |                       |         .         |
# +-------------------+                       +-------------------+
#          .                                            .
#          .  IP Traffic                                . IP Traffic         .
#          .                                            .
#          .                                            .
# +-------------------------------+           +-------------------------------+
# |        .                      |           |         .                     |
# |        .        PE-1 netns    |           |         .        PE-2 netns   |
# |  +------------------+         |           |  +---------------+            |
# |  |    pe-h1-pe      |         |           |  |    pe-h2-pe   |            |
# |  |   1.1.1.1/24     |         |           |  |   2.1.1.1/24  |            |
# |  +------------------+         |           |  +---------------+            |
# |  +------------------+         |           |  +- -------------+            |
# |  |  gw-pe1-pe       |         |           |  |   gw-pe2-pe   |            |
# |  |  3.1.1.2/24      |         |           |  |   3.1.1.2/24  |            |
# |  +------------------+         |           |  +---------------+            |
# |        .                      |           |         .     .               |
# +-------------------------------+           +-------------------------------+
#          .                                            .
#          .                                            .
#          .    MPLS Traffic                            .   MPLS Traffic
#          .                                            .
# +-------------------------------+           +-------------------------------+
# |        .                      |           |         .                     |
# |        .         GW-1 netns   |           |         .       GW-2 netns    |
# |  +------------------+         |           |  +--------------+             |
# |  |  gw-pe1-pe       |                     |  |  gw-pe2-pe   |             |
# |  |  3.1.1.3/24      |         |           |  |  3.1.1.3/24  |             |
# |  +------------------+         |           |  +--------------+             |
# |  +------------------+         |           |  +---------------+            |
# |  |     gw-peer-1    |         | UDP Tunnel|  |   gw-peer-2   |            |
# |  |    9.1.1.2/24    |. . . .  |. . . . . .| .| 9.1.1.3/24    |            |
# |  +------------------+         |           |  +---------------+            |
# |                               |           |                     .         |
# +-------------------------------+           +-------------------------------+
#

set -e
num_hosts=2
num_pes=2

cleanup() {
    local i

    for ((i = 1; i <= $num_hosts; ++i)); do
        ip netns del host-$i || true
    done

    for ((i = 1; i <= $num_pes; ++i)); do
        ip netns del pe-$i || true
    done
    ip netns del gw-1 || true
    ip netns del gw-2 || true

}

# Clean start
cleanup &> /dev/null

[[ $1 == "clean" ]] && exit 0

#trap cleanup EXIT

set -e
num_hosts=2
num_pes=2


setup_pe() {
    local id=$1
    ip netns exec  pe-$id sysctl -w net.mpls.platform_labels=1000
}
setup_gw() {
    local id=$1
    ip netns exec  gw-$id sysctl -w net.mpls.platform_labels=1000
}

create_mpls_tunnel() {
    local id=$1
    local net=$2
    local label=$3
    local gw=$4
    ip -netns pe-$id route add $net encap mpls $label via inet $gw dev \
              gw-pe$id-pe
}
pe_add_label_route() {
    local id=$1
    local host=$3
    local label=$2
    ip -netns pe-$id -f mpls route add $label via inet $host dev pe-h$id-pe
}
gw_add_label_route() {
    local id=$1
    local host=$3
    local label=$2
    ip -netns gw-$id -f mpls route add $label as $label  via inet $host dev gw-pe$id-gw
}

create_veth_interfaces()
{
    local i

    for ((i = 1; i <= $num_hosts; ++i)); do
       ip link add pe-h$i-h type veth peer name  pe-h$i-pe
    done
    for ((i = 1; i <= $num_pes; ++i)); do
       ip link add gw-pe$i-pe type veth peer name   gw-pe$i-gw
    done
}

create_hosts() {
    local i

    for ((i = 1; i <= $num_hosts; ++i)); do
        ip netns add host-$i
    done
}

create_pes() {
    local i

    for ((i = 1; i <= $num_pes; ++i)); do
        ip netns add pe-$i
    done
}

connect_pe_gw() {
    local dc_id=$1
    local pe_id=$2
    local tunnel_src_ip=$3
    local tunnel_dst_ip=$4
    local pe_net=$5
    local gw_net=$6
    local pe=$7
    ip link set gw-pe$pe_id-pe netns pe-$pe_id
    ip link set gw-pe$pe_id-gw netns gw-$dc_id
    ip netns exec gw-$dc_id tc qdisc add dev bareudp0 handle ffff: ingress
    ip netns exec gw-$dc_id tc qdisc add dev gw-pe$pe_id-gw handle ffff: ingress
    ip netns exec gw-$dc_id tc filter add dev gw-pe$pe_id-gw  protocol 0x8847 \
                                 parent ffff: \
                                 flower action tunnel_key set src_ip $tunnel_src_ip \
                                 dst_ip $tunnel_dst_ip id 0 \
                                 action mirred egress redirect dev bareudp0
#    ip netns exec gw-$dc_id tc filter add dev bareudp0 protocol 0x8847 \
#                                 parent ffff: flower \
#                                 action mirred egress redirect dev gw-pe$pe_id-gw
#    ip netns exec gw-$dc_id tc filter add dev bareudp0 protocol 0x8847 parent ffff: \
#                                 flower \
#                                 action pedit ex munge eth dst set \
#                                 00:00:05:00:00:0$pe_id continue
    ip -netns pe-$pe_id link set gw-pe$pe_id-pe address 00:00:05:00:00:0$pe_id
    ip -netns pe-$pe_id addr add $pe_net dev  gw-pe$pe_id-pe
    ip -netns pe-$pe_id link set gw-pe$pe_id-pe up
    ip -netns gw-$dc_id addr add $gw_net dev gw-pe$pe_id-gw
    ip -netns gw-$dc_id link set gw-pe$pe_id-gw up
    ip netns exec pe-$pe_id sysctl -w net.mpls.conf.gw-pe$pe_id-pe.input=1
    ip netns exec gw-$dc_id sysctl -w net.mpls.conf.gw-pe$pe_id-gw.input=1
    ip netns exec gw-$dc_id sysctl -w net.mpls.conf.bareudp0.input=1
}


connect_host_pe() {
    local host_id=$1
    local pe_id=$2
    local host_net=$3
    local pe_net=$4
    local gw=$5
    ip link set pe-h$host_id-h netns host-$host_id
    ip link set pe-h$host_id-pe netns pe-$pe_id
    ip -netns host-$host_id addr add $host_net dev pe-h$host_id-h
    ip -netns host-$host_id link set pe-h$host_id-h up
    ip -netns host-$host_id route add default nexthop via $gw
    ip -netns pe-$pe_id addr add $pe_net dev  pe-h$host_id-pe
    ip -netns pe-$pe_id link set pe-h$host_id-pe up
    ip netns exec pe-$pe_id sysctl -w net.mpls.conf.pe-h$host_id-pe.input=1
}

create_gw() {
    local id=$1
    local net=$2
    ip netns add gw-$id
    ip link set gw-peer-$id netns gw-$id

    ip -netns gw-$id link add dev bareudp0 type bareudp dstport 6635 \
       ethertype 0x8847
    ip -netns gw-$id link set bareudp0 up
    ip -netns gw-$id addr add $net dev gw-peer-$id
    ip -netns gw-$id link set gw-peer-$id up
}

echo start test
modprobe mpls_router
echo 1 >> /proc/sys/net/ipv4/ip_forward
create_hosts
create_pes
ip link add gw-peer-1  type veth peer name   gw-peer-2
create_gw 1 9.1.1.2/24
create_gw 2 9.1.1.3/24
echo "dc gws created"
create_veth_interfaces
connect_pe_gw 1 1 9.1.1.2 9.1.1.3 3.1.1.2/24 3.1.1.3/24
connect_pe_gw 2 2 9.1.1.3 9.1.1.2 3.1.1.2/24 3.1.1.3/24
connect_host_pe 1 1 1.1.1.2/24 1.1.1.1/24 1.1.1.1
connect_host_pe 2 2 2.1.1.2/24 2.1.1.1/24 2.1.1.1

setup_pe 1
setup_pe 2
setup_gw 1
setup_gw 2

create_mpls_tunnel 1 2.1.1.2/32 200 3.1.1.3
pe_add_label_route 1 100 1.1.1.2
create_mpls_tunnel 2 1.1.1.2/32 100 3.1.1.3
pe_add_label_route 2 200 2.1.1.2
gw_add_label_route 1 100 3.1.1.2
gw_add_label_route 2 200 3.1.1.2

ip netns exec host-1 ping -c 1 -W 1 2.1.1.2 &> /dev/null || (echo "[FAIL]"; false)
echo "[ OK ]"


