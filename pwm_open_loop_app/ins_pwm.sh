#! /bin/sh -

insmod pwmdriver.ko
cat /proc/devices | grep pwm
mknod /dev/pwm_mod c 249 0
if ! [ `ls /dev | grep pwm_mod` == `echo` ]
then
	echo insmod. pwm. successful
fi
