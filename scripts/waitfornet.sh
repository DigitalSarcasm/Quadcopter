#!/bin/bash

while true
do
	sudo ping -c 1 google.com | grep "1 received"
	if [[ $? == 0 ]];
	then
		ip route get 8.8.8.8 | awk 'NR==1 {print $NF}' | grep 10.137
		if [[ $? == 0 ]];
		then
			#sudo killall vpnc
			sudo vpnc wireless
			continue
		else				
			echo "network available"
			sudo ntpdate ca.pool.ntp.org
			while true
			do
				year="$(date +"%y")"
				if [[ $year == "14" ]];
				then
					/home/digital/scripts/ipTweet.py
					break
				fi
			done
			break
		fi
	else
		systemctl status netctl-auto@wlan0.service | grep FAILURE
		if [[ $? == 0 ]];
		then
			sudo netctl start wlan0-wpa
		fi
	fi
done


# Wait for Network to be available.
#while true
#do
#	#sudo vpnc wireless
#	#sudo netctl start wlan0-edu
#	#sudo vpnc wireless
#	sudo ping -c 1 google.com
#	if [[ $? == 0 ]];
#	then
#		echo ‘Network available.’
#		sudo ntpdate ca.pool.ntp.org
#		while true
#		do
#			year="$(date +"%y")" 
#			if [[ $year == "14" ]];
#			then
#				/home/digital/ipTweet.py
#				break
#			else
#				echo 'not'
#			fi
#		done
#	break;
#	else
#	echo ‘Network is not available, waiting..’
#	sleep 5
#	fi
#done
#echo ‘If you see this message, then Network was successfully loaded.’
