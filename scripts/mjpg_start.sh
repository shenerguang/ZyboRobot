#! /bin/bash -
export LD_LIBRARY_PATH=/root/mjpeg_face_leaf_detection/mjpg-streamer

boa
#get ip address!
echo "what network device you choose?"
echo -e "( wlan, eth, custom )\c"
read choice
if [ $choice == "wlan" ]
then
	if [ "`ifconfig | grep wlan`x" == "x" ]
	then
		echo "wlan status off, please start wlan"
		exit 1
	fi
	ip=` ifconfig | grep -A 1 wlan | grep inet | awk -F ':' '{print $2}' | awk '{print $1}'`
	echo "$ip"x
elif [ $choice == "eth" ]
then
	if [ "`ifconfig | grep eth`x" == "xx" ]
	then
		echo "eth status off, please start ethnet port"
		exit 1
	fi
	ip=` ifconfig | grep -A 1 eth | grep inet | awk -F ':' '{print $2}' | awk '{print $1}'`
	echo "$ip"x
elif [ $choice == "custom" ]
then
	echo -e "please input an ip:\c"
	read ip
	echo "IP address you input is '$ip'x"
else
	echo "bad input"
	exit 1
fi

#modify files
ip_home=`cat /var/www/home.html | grep 8080 | awk -F ':' '{print $2}' | grep -o '[^/]*'`
sed -i "s/$ip_home/$ip/g" /var/www/home.html

ip_index=`cat /var/www/index.html | grep 8080 | awk -F ':' '{print $2}' | awk '{$a=substr($0,3,16);print $a}'`
sed -i "s/$ip_index/$ip/g" /var/www/index.html

mjpg_streamer -i "input_uvc.so -y -f 5 -r 640*480 -q 60" "output_http.so -p 8080 -w /var/www"
