#! /bin/bash - 
inputssid="SOC"

boa
eth_no=`ifconfig -a | grep eth | awk '{print $1}'`
ifconfig $eth_no down
wlan_no=`ifconfig -a | grep wlan | awk '{print $1}'`
ifconfig $wlan_no up
iwlist $wlan_no scan | grep ESSID

if [ "$inputssid"x = "x" ]
then
	echo -e "please input your ssid:\c"
	read inputssid
	if [ `iwlist $wlan_no scan | grep $inputssid`x = "x" ]
	then
		echo "input error!"
		echo -e "please input your ssid:\c"
		read $inputssid
	fi
fi

iwconfig $wlan_no essid $inputssid
dhclient $wlan_no
