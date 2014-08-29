#! /bin/sh -

insmod ultrasonic.ko
val=`cat /proc/devices | grep ultrasonic | awk '{print $1}'`
mknod /dev/ult_mod c $val 0
if ! [ `ls /dev | grep ult_mod` == `echo` ]
then
	echo insmod. pwm. successful
fi
