#! /bin/sh -

insmod pwmdriver.ko
val=`cat /proc/devices | grep pwm | awk '{print $1}'`
mknod /dev/pwm_mod c $val 0
if ! [ `ls /dev | grep pwm_mod` == `echo` ]
then
	echo insmod. pwm. successful
fi
