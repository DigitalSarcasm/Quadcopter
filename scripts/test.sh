#test=$( ip route get 8.8.8.8 | awk 'NR==1 {print $NF}' | grep 10. )
#echo $test
#systemctl status netctl-auto@wlan0.service | grep FAILURE
#sudo ping -c 1 google.com | grep byte
#sudo ping -c 1 google.com | grep "1 received"

#ip route get 8.8.8.8 | awk 'NR==1 {print $NF}' | grep 10.137
pid=$(pidof vpnc)
if test -z "$pid"
then
	echo "yes"
else
	echo "no"
fi

#sudo vpnc wireless
