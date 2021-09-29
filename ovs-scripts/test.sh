ovs-appctl dpif/show-dp-features  br_mpls1 | grep  "MPLS Label add: Yes"
res=$(ovs-appctl dpif/show-dp-features  br_mpls1 | grep  "MPLS Label add: Yes")
echo $res
echo $res
if [ "$res" == "MPLS Label add: Yes" ]
then
	echo "march"
	res1=$(test "$res" != "MPLS Label add: Yes")
	echo $?
fi
