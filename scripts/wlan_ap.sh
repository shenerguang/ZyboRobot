#! /bin/bash - 
boa

#close eth port first
eth_no=`ifconfig -a | grep eth | awk '{print $1}'`
ifconfig $eth_no down

#confirm wlan plugged in
ex_8192=`ifconfig -a | grep wlan`
ex_2870=`ifconfig -a | grep ra0`
if [ "$ex_8192"x == "x" ]
then
	echo wifi hardware not detected! please make sure you inserted it!
	echo If you have inserted it ,please replug it!
	exit 1
else
	echo wifi rtl8192cu detected!
fi

if ! [ "$ex_2870"x == "x" ]
then
	echo wifi rt2870sta detected!
fi	
#exit 0

#get wlan No.
if [ `ifconfig -a | grep wlan| wc -l` -eq 2 ]
then
	wlan_no=`ifconfig -a | grep wlan |awk 'NR==2{print $1}'`
else
	wlan_no=`ifconfig -a | grep wlan | awk '{print $1}'`
fi

#modify wlan config files
wlan1=`cat /etc/hostapd/hostapd.conf | grep wlan | awk -F '=' '{print $2}'`
sed -i "s/$wlan1/$wlan_no/g" /etc/hostapd/hostapd.conf
wlan2=`cat /etc/network/interfaces | grep wlan | awk '{print $2}'`
sed -i "s/$wlan2/$wlan_no/g" /etc/network/interfaces
wlan3=`cat /etc/udhcpd.conf | grep wlan | awk '{print $2}'`
sed -i "s/$wlan3/$wlan_no/g" /etc/udhcpd.conf

#run wlan ap and dhcp
ifconfig $wlan_no 192.168.0.1
/etc/init.d/udhcpd restart
/etc/init.d/hostapd restart

#tell user
name=`cat /etc/hostapd/hostapd.conf | grep ssid | head -n 1 | awk -F '=' '{print $2}'`

echo "Now you can connect wlan named $name"
echo "And  visit 192.168.0.1 to control smarter car!"
