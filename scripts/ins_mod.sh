#! /bin/sh -
export PATH=$PATH:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin
if [ "`lsmod | grep mt7601`x" = "x" ]
then
	insmod /etc/Wireless/RT2870STA/mt7601Usta.ko
	if [ "`lsmod | grep mt7601`x" = "x" ]
	then
		echo "360 Wifi init failed!"
	else
		echo "360 Wifi init Successful!"
	fi
else
	echo "You 360wifi already inserted!"
	exit 1
fi

insmod /root/package_c/optical.ko
insmod /root/package_c/pwmdriver.ko
insmod /root/package_c/ultrasonic.ko

val=`cat /proc/devices | grep optical | awk '{print $1}'`
if [ "`lsmod | grep optical`x" = "x" ]
then
	echo "optical init failed!"
else
	echo "Optical init Successful!"
	mknod /dev/opt_mod c $val 0
fi

val=`cat /proc/devices | grep pwm | awk '{print $1}'`
if [ "`lsmod | grep pwmdriver`x" = "x" ]
then
	echo "pwm init failed!"
else
	echo "Pwm init Successful!"
	mknod /dev/pwm_mod c $val 0
fi
val=`cat /proc/devices | grep ultrasonic | awk '{print $1}'`
if [ "`lsmod | grep pwmdriver`x" = "x" ]
then
	echo "ultrasonic init failed!"
else
	echo "Ultrasonic init Successful!"
	mknod /dev/ult_mod c $val 0
fi

echo insmod finished!
