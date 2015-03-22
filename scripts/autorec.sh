#!/bin/bash


ip route get 8.8.8.8 | awk 'NR==1 {print $NF}' | grep 10.137
if [[ $? == 0 ]];
then
	pid=$(pidof vpnc)
	if test -z "${pid}"
	then
	    sudo vpnc wireless
	else
	    sudo kill -9 ${pid}
	    sudo vpnc wireless
	fi
	/home/digital/scripts/ipTweet.py
fi
