#! /bin/bash - 
inputssid=""

boa

#close eth port first
eth_no=`ifconfig -a | grep eth | awk '{print $1}'`
ifconfig $eth_no down

#confirm wlan plugged in
ex_8192=`ifconfig -a | grep wlan`
ex_2870=`ifconfig -a | grep ra0`
if [ "$ex_8192"x = "x" ]
then
	echo wifi rtl8192cu not detected!
else
	echo wifi rtl8192cu detected!
fi
if [ "$ex_2870"x = "x" ]
then
	echo wifi rt2870sta not detected!
else	
	echo wifi rt2870sta detected!
fi	

if ! [ "$ex_8192"x = "x" ] && ! [ "$ex_2870"x = "x" ]
then
	echo Please choose which wifi you want to use!
	echo "(TPLINK823N,1) (360Wifi2,2)"
	read wifi_choice
	if [ "$wifi_choice" = "1" ]
	then
		wlan_no=`ifconfig -a | grep wlan | awk '{print $1}'`
	elif [ "$wifi_choice" = "2" ]
	then
		wlan_no="ra0"
	fi
elif ! [ "$ex_8192"x = "x" ]
then
	wlan_no=`ifconfig -a | grep wlan | awk '{print $1}'`
elif ! [ "$ex_2870"x = "x" ]
then
	wlan_no="ra0"
else
	echo no wlan found! please check error!
	exit 1
fi

echo You chosed $wlan_no

#exit 0
#wlan_no=`ifconfig -a | grep wlan | awk '{print $1}'`
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
echo linking...
iwconfig $wlan_no essid $inputssid
echo please wait...
dhclient $wlan_no

ip=` ifconfig | grep -A 1 $wlan_no | grep inet | awk -F ':' '{print $2}' | awk '
{print $1}'`
echo "Now you can visit $ip to control smarter car!"
