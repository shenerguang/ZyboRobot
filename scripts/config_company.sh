#! /bin/bash -
export PATH=$PATH:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
date --set="2014-09-2"
eth_no=`ifconfig -a | grep eth | awk '{print $1}'`
ifconfig $eth_no 0
wlan_no=`ifconfig -a | grep wlan | awk '{print $1}'`
ifconfig $wlan_no down
dhclient $eth_no
ifconfig $eth_no hw ether 00:0a:35:00:01:aa 
ifconfig $eth_no
export http_proxy=http://gateway:8080
export https_proxy=https://gateway:8080
